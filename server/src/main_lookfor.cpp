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

/// C++
#include <iostream>
#include <string>

/// Boost
#include <boost/algorithm/string.hpp>

/// FastCGI
#include <fcgi_stdio.h>

/// Trokam
#include "common.h"
#include "db_handler.h"
#include "lookfor.h"
#include "server_log.h"
#include "options.h"

/***********************************************************************
 *
 **********************************************************************/
std::string get_post_request()
{
    std::string request_type= getenv("REQUEST_METHOD");
    std::string request_length= getenv("CONTENT_LENGTH");

    int len= atoi(request_length.c_str());
    std::string request_post;

    for(int i= 0; i < len; i++)
    {
        int ch= FCGI_getchar();
        request_post+= ch;
    }
    return request_post;
}

/***********************************************************************
 *
 **********************************************************************/
void split_line(const std::string &line,
                      std::string &first,
                      std::string &second)
{
    std::size_t sep_loc= line.find("=");
    if(sep_loc == std::string::npos)
    {
        return;
    }
    else
    {
        first= line.substr(0, sep_loc);
        second= line.substr(sep_loc+1);
    }
}

/***********************************************************************
 *
 **********************************************************************/
int main(int argc, char **argv)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Process command options.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    trokam::options opt;
    opt.read(SERVER_CONFIG_FILE);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// No logging at all.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    trokam::log::quiet(true);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Only one reusable instance of database for all requests.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    trokam::db_handler db(opt);

    while(FCGI_Accept() >= 0)
    {
        std::string request= get_post_request();
        
        std::string request_type, request_arg;
        split_line(request, request_type, request_arg);
        boost::replace_all(request_arg, "+", " "); 

        if(request_type == "search")
        {
            std::string search_results;
            trokam::lookfor::search(db, request_arg, search_results);

            FCGI_fprintf(stdout,"Content-type: text/html\r\n\r\n");
            FCGI_fprintf(stdout, "%s", search_results.c_str());
        }
        
        if(request_type == "audit")
        {
            std::string audit_results;
            db.get_report_of_url(request_arg, audit_results);

            FCGI_fprintf(stdout,"Content-type: text/html\r\n\r\n");
            FCGI_fprintf(stdout, "%s", audit_results.c_str());
        }
    }
    return 0;
}
