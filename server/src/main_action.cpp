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
#include <unistd.h>

/// C++
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

/// JsonCpp
#include "jsoncpp/json/json.h"

/// FastCGI
#include <fcgi_stdio.h>

/// Trokam
#include "action_processor.h"
#include "common.h"
#include "db_handler.h"
#include "server_log.h"
#include "options.h"

/***********************************************************************
 *
 **********************************************************************/
std::string get_post_request()
{
    std::string request_type= getenv("REQUEST_METHOD");
    std::string request_length= getenv("CONTENT_LENGTH");

    // LOG(TRACE, "request method: " << request_type << " content length: " << request_length);

    int len= atoi(request_length.c_str());
    std::string request_post;

    for(int i= 0; i < len; i++)
    {
        // int ch= getchar();
        int ch= FCGI_getchar();
        request_post+= ch;
    }
    
    return request_post;
}

/***********************************************************************
 *
 *                             MAIN
 *
 **********************************************************************/

int main(int argc, const char* argv[])
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Process command options
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /*
    trokam::options opt(argc, argv);
    opt.db_name("web_data_0002");
    opt.db_user("accmgr");
    */
    // opt.log_level(trokam::TRACE);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Process command options
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    trokam::options opt;
    opt.read(SERVER_CONFIG_FILE);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    trokam::log::setup(opt);
    LOG(TRACE, "Starting ...");    

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Only one reusable instance of database for all requests
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    trokam::db_handler db(opt);
    
	while(FCGI_Accept() >= 0)
	{    
        try
        {
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// 
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            LOG(TRACE, "inside FCGI_Accept loop ...");

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// Getting the post request
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            std::string raw_request= get_post_request();
            // LOG(TRACE, "raw_request: " << raw_request);
            
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// 
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            Json::Value incoming, outgoing;
            Json::Reader reader;
            bool parsed_success= reader.parse(raw_request, incoming, false);

            if(parsed_success == true)
            {
                // LOG(TRACE, "jason parser succeded");                

                trokam::action_processor ap(opt);
                ap.process(db, incoming, outgoing);
               
                // LOG(TRACE, "outgoing: " << outgoing.toStyledString());
                
                FCGI_fprintf(stdout, CONTENT_TYPE);
                FCGI_fprintf(stdout, outgoing.toStyledString().c_str());
            }
            else
            {
                    LOG(TRACE, "inside: " << __PRETTY_FUNCTION__ << SPACE
                                          << "parse failure");

                    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    /// This must be a JASON frame
                    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    FCGI_fprintf(stdout, CONTENT_TYPE);
                    FCGI_fprintf(stdout, "error in server");
            }
        }
        catch(std::exception& e)
        {
            LOG(TRACE, "inside: " << __PRETTY_FUNCTION__ << SPACE
                                  << "exception: " << e.what());

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// This must be a JASON frame
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            FCGI_fprintf(stdout, CONTENT_TYPE);
            FCGI_fprintf(stdout, "error in server");
        }
    }
    return 0;
}
