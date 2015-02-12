/***********************************************************************
 *                            T R O K A M
 *                 Free and Open Source Search Engine
 *
 * Service        http://trokam.com/search
 * About          http://trokam.com/pages/about
 * Development    http://dev.trokam.com/
 * Repository     https://github.com/trokam
 * News           https://twitter.com/trokam
 *
 * Copyright (C) 2015, Nicolas Slusarenko
 *                     nicolas.slusarenko@trokam.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 **********************************************************************/

/// C
#include <cstdlib>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/// C++
#include <iostream>
#include <exception>
#include <map>

/// Boost
#include <boost/bind.hpp>

/// JsonCpp
#include "jsoncpp/json/json.h"

/// Trokam
#include "common.h"
#include "converter.h"
#include "desk_log.h"
#include "file_management.h"
#include "html_handler.h"
#include "machine.h"
#include "text_processor.h"
#include "token.h"
#include "web_cruncher.h"

/***********************************************************************
 *
 *
 **********************************************************************/
bool trokam::web_cruncher::stop;

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::web_cruncher::web_cruncher(trokam::options &options,
                                   std::string user_id_cfg,
                                   std::string instance_cfg): opt(options),
                                                              cruncher_id(user_id_cfg),
                                                              instance(instance_cfg),
                                                              ah(opt)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Install a catch for CRTL+C signal in order
    /// to quit the program in a known state
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    web_cruncher::stop= false;
    signal(SIGINT, web_cruncher::ctrl_c_signal);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Creates a directory to keep the intermediate files of
    /// the processing. Using PID allows to have several instances
    /// of the same program simultaneously each one with its
    /// own set of intermediate files.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string hp= trokam::machine::hostname_pid();
    base_directory= "/tmp/trokam/cruncher_" + hp + "/";
    trokam::machine::mkdir(base_directory);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// This file keep the file just downloaded
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    original_content_file= base_directory + "original_content";
}

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::web_cruncher::~web_cruncher()
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Remove directory created to keep the temporal files
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    trokam::machine::rm_dir(base_directory);
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::web_cruncher::ctrl_c_signal(int signal)
{
    web_cruncher::stop= true;
    LOG(WARNING, "process is scheduled to stop");
}

/***********************************************************************
 * 
 *
 **********************************************************************/
void trokam::web_cruncher::full_analysis()
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Main loop for wep page fetching, analyzing and sending
    /// results to trokam server.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int page_count=0;
    
    while(((page_count<opt.page_limit()) || (opt.page_limit() ==-1))
           && !web_cruncher::stop)
    {
        LOG(INFO, "page=" << page_count);

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Counter of crunched pages.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        page_count++;

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// This client will send a json package to trokam server
        /// asking for a task assignement along with the id of
        /// this client and a reference to this instance.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        std::string url;
        Json::Value request, reply;
        request[ACTION]= GET_TASK;
        request[CRUNCHER_ID]= cruncher_id;
        request[INSTANCE]= instance;

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Request a task to the server.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        ah.perform_on_server(request, reply);
        
        if(reply[STATUS] == OK)
        {
            url= reply[URL].asString();
            
            LOG(INFO, "processing url: " << url);

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// It fetches the web page and put into a local file.
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            int download_status= web.fetch(url, original_content_file);

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// This structure will store the analysis.
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Json::Value task_results, answer;
            task_results[ACTION]=   FULL_PAGE_REPORT;
            task_results[CRUNCHER_ID]=  cruncher_id;
            task_results[INSTANCE]= instance;
            task_results[TASK_ID]=  reply[TASK_ID];

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// Different actions depending on the download_status.
            /// If download_status is 0 then it worked right, any
            /// other value means that it failed.
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            if (download_status == 0)
            {
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                /// This structure will store the analysis.
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                Json::Value page_data;
                
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                /// Extract the URLs of the content and
                /// put them into 'page_data'.
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                up.extract(original_content_file, page_data);

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                /// Extract title.
                /// Warning: this method works only on html files.
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                trokam::html_handler::extract_title(original_content_file, page_data);

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                /// Convert the content (HTML, PDF, etc) to plain text
                /// and then process the content.
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                std::string text_content_file;
                text_content_file= base_directory + "text_content";
                if(fc.convert_to_text(original_content_file, text_content_file) == true)
                {
                    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    /// Redundant copy of the content into the
                    /// string and then into the json node.
                    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    std::string body, snippet;
                    trokam::file_management::get_file_contents(text_content_file, body);
                    snippet= body.substr(0, 400);
                    trokam::text_processor::clean_line(snippet);
                    page_data[BODY]= snippet;

                    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    ///
                    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    trokam::text_processor text(text_content_file);
                    if(text.word_relevance_analysis(page_data, ws))
                    {
                        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        ///
                        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        task_results[STATUS]=   OK;
                        task_results[FULL_PAGE_REPORT]= page_data;
                        
                        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        /// IMPROVEMENT: This should be an option
                        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        // trokam::file_management::save_file("/tmp/trokam/reports/full_report.json", task_results.toStyledString());

                        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        ///
                        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        LOG(TRACE, "sending full page report ...");
                        ah.perform_on_server(task_results, answer);
                        LOG(TRACE, "reply of server: " << answer[REPLY]);
                    }
                    else
                    {
                        LOG(WARNING, "no words occurrence for url: " << url);
                    }
                }
                else
                {
                    LOG(WARNING, "failed text conversion for url: " << url);
                    task_results[STATUS]=    FAILURE;
                    task_results[FAIL_TYPE]= trokam::converter::to_string(4000);
                    LOG(TRACE, "reporting failure ...");
                    ah.perform_on_server(task_results, answer);
                    LOG(TRACE, "reply of server: " << answer[REPLY]);                    
                }
            }
            else
            {
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                /// Report failure of file fetching
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                LOG(WARNING, "failed download for url=" << url);
                
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                ///
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                task_results[STATUS]=    FAILURE;
                task_results[FAIL_TYPE]= trokam::converter::to_string(download_status);
                LOG(TRACE, "reporting failure ...");
                ah.perform_on_server(task_results, answer);
                LOG(TRACE, "reply of server: " << answer[REPLY]);
            }
        } /// reply[STATUS] != OK
        else
        {
            std::string fail_detail= reply[FAIL_TYPE].asString();
            LOG(WARNING, "failure on request for task assignement");
            LOG(WARNING, "server replied: " << fail_detail);
        }

        std::cout << "\n";
    }
    std::cout << "\n\n";
}

