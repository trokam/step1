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

/// C++
#include <string>
#include <iostream>

/// Boost
#include <boost/program_options.hpp>

/// Trokam
#include "desk_log.h"
#include "options.h"

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::options::options()
{}

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::options::options(int argc, const char* argv[])
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Program Options
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help",            "Produce help message")
        ("page-limit",      boost::program_options::value<int>(),         "Number of pages to process. Default is no limit.")
        ("save-analysis",   boost::program_options::value<std::string>(), "Directory where every URL analysis is saved. Better use with --page-limit to avoid disk exhaustion. Default is no saving.")
        ("log-level",       boost::program_options::value<std::string>(), "Minimum level for logging: TRACE, DEBUG, INFO, WARNING, ERROR or FATAL")
        ("server-address",  boost::program_options::value<std::string>(), "Server address. Deafult is www.trokam.com.");
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Option 'help'
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(vm.count("help"))
    {
        std::cout << desc << std::endl;
        exit(0);
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Action for 'page-limit'
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    opt_page_limit= -1;
    if(vm.count("page-limit"))
    {
		opt_page_limit= vm["page-limit"].as<int>();
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Action for 'log level'
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    opt_log_level=trokam::INFO;
    if(vm.count("log-level"))
    {
		std::string text_log_level= vm["log-level"].as<std::string>();
        if(text_log_level == "TRACE")
        {
            opt_log_level= trokam::TRACE;
        }
        else if(text_log_level == "DEBUG")
        {
            opt_log_level= trokam::DEBUG;
        }
        else if(text_log_level == "INFO")
        {
            opt_log_level= trokam::INFO;
        }
        else if(text_log_level == "WARNING")
        {
            opt_log_level= trokam::WARNING;
        }
        else if(text_log_level == "ERROR")
        {
            opt_log_level= trokam::ERROR;
        }
        else if(text_log_level == "FATAL")
        {
            opt_log_level= trokam::FATAL;
        }
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    opt_server_address= "";
    if(vm.count("server-address"))
    {
		opt_server_address= vm["server-address"].as<std::string>();
    }

    if(opt_log_level <= trokam::DEBUG)
    {
        LOG(DEBUG, "page-limit= "      << opt_page_limit);
        LOG(DEBUG, "server-address= "  << opt_server_address);        
        LOG(DEBUG, "log-level= "       << opt_log_level);
    }
}

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::options::options(int argc, char **argv)
{}

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::options::options(const trokam::options &opt)
{
    opt_page_limit= opt.page_limit();
    opt_log_level= opt.log_level();
    opt_server_address= opt.server_address();    
}

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::options& trokam::options::operator= (const trokam::options &opt)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Avoid self-assignment
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(this == &opt)
    {
        return *this;
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Copy data
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    opt_page_limit= opt.page_limit();
    opt_log_level= opt.log_level();
    opt_server_address= opt.server_address();

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Return this object
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    return *this;
}

/***********************************************************************
 *
 *
 **********************************************************************/
int trokam::options::page_limit() const
{
    return opt_page_limit;
}

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::severity trokam::options::log_level() const
{
    return opt_log_level;
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::options::server_address() const
{
    return opt_server_address;
}
