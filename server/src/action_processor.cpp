/***********************************************************************
 *                            T R O K A M
 *                 Free and Open Source Search Engine
 *
 * Service        http://trokam.com
 * Development    http://dev.trokam.com
 * Repository     https://github.com/trokam
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

/// C++
#include <iostream>
#include <exception>

/// JsonCpp
#include "jsoncpp/json/json.h"

/// Trokam
#include "action_processor.h"
#include "common.h"
#include "file_management.h"
#include "server_log.h"

/***********************************************************************
 * 
 **********************************************************************/
trokam::action_processor::action_processor(trokam::options &opt)
{}

/***********************************************************************
 * 
 **********************************************************************/
trokam::action_processor::~action_processor()
{}

/***********************************************************************
 * 
 **********************************************************************/
void trokam::action_processor::process(trokam::db_handler &db,
                                       const Json::Value &incoming,
                                             Json::Value &outgoing)
{
    std::string cruncher_id= incoming[CRUNCHER_ID].asString();
    std::string instance= incoming[INSTANCE].asString();

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Is this a registered cruncher?
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(db.verify_user(cruncher_id))
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// The user could try different actions
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        std::string action= incoming[ACTION].asString();
        std::cerr << "action: " << action << std::endl;
        
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// A client request a task to be assigned.
        /// The task could be one of two kind:
        ///
        /// 1) Analyze a web page.
        ///    An URL and a task-id are send to the client.
        ///
        /// 2) Verify an analysis done by somebody else.
        ///    The analysis, an URL and a task-id are send
        ///    to the client.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if(action == GET_TASK)
        {
            LOG(TRACE, "getting task ...");

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// It verifies if this user is registered.
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            std::string cruncher_index= db.get_cruncher_index(cruncher_id);
            if(cruncher_index != EMPTY)
            {
                trokam::task user_task;
                db.get_task(cruncher_index, user_task);

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                /// All these fields are of string type
                ///
                /// outgoing[TASK_ID]:   A random number generated in the
                ///                      server that identifies uniquely the
                ///                      assigned task.
                /// outgoing[TASK_TYPE]: The type of assignement. It could
                ///                      be the word analysis of a page,
                ///                      full analysis of a page, etc.
                /// outgoing[URL]:       The URL to be analysed.
                /// outgoing[DATA]:      Empty.
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                outgoing[STATUS]= OK;
                outgoing[TASK_ID]= user_task.task_id;
                outgoing[TASK_TYPE]= user_task.task_type;
                outgoing[URL]= user_task.url;
            }
            else
            {
                outgoing[STATUS]= FAILURE;
                outgoing[FAIL_TYPE]= "the cruncher id is not registered at trokam server";
            }
        }
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// A client sends a full report of a web page.
        /// IMPROVEMENT: The cruncher-id verification is different 
        ///              from the GET_TASK case
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if(action == FULL_PAGE_REPORT)
        {
            LOG(TRACE, "Processing full page report ...");

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// Save full page report.
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            db.save_full_page_report(incoming, outgoing);
        }
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// If it is not some one of the previous alternatives
        /// is an error.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else
        {
            std::cerr << "inside: " << __PRETTY_FUNCTION__ << SPACE
                      << "request '" << action << "' unknown." << std::endl;
            outgoing[REPLY]= "error in server";
        }
    }
}
