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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

/// Trokam
#include "db_handler.h"
#include "server_log.h"
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
{}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::options::generate(int argc, const char* argv[])
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Program Options
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help",         "Produce help message")
        ("db-host",      boost::program_options::value<std::string>(),  "Host name or IP address of database server")
        ("db-name",      boost::program_options::value<std::string>(),  "Database name")
        ("db-user",      boost::program_options::value<std::string>(),  "Database user name")
        ("log-file",     boost::program_options::value<std::string>(),  "Location of the log file")
        ("log-level",    boost::program_options::value<std::string>(),  "Minimum level for logging: TRACE, DEBUG, INFO, WARNING, ERROR or FATAL")
        ("seeds",        boost::program_options::value<std::string>(),  "File with URL seeds to initialize the database (only with 'initialize')")
        ("url",          boost::program_options::value<std::string>(),  "The URL to query for (only with 'query')");
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
    /// Option 'db-host'
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(vm.count("db-host"))
    {
		opt_db_host= vm["db-host"].as<std::string>();
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Option 'db-name'
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(vm.count("db-name"))
    {
		opt_db_name= vm["db-name"].as<std::string>();
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Option 'db-user'
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(vm.count("db-user"))
    {
		opt_db_user= vm["db-user"].as<std::string>();
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    opt_log_file= "";
    if(vm.count("log-file"))
    {
		opt_log_file= vm["log-file"].as<std::string>();
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    opt_seeds= "";
    if(vm.count("seeds"))
    {
		opt_seeds= vm["seeds"].as<std::string>();
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    opt_url= "";
    if(vm.count("url"))
    {
		opt_url= vm["url"].as<std::string>();
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Action for 'log level'
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    opt_log_level=trokam::INFO;
    if(vm.count("log-level"))
    {
		std::string level= vm["log-level"].as<std::string>();
        set_log_level(level);
    }

    if(opt_log_level <= trokam::DEBUG)
    {
        LOG(DEBUG, "db-host= "    << opt_db_host);
        LOG(DEBUG, "db-name= "    << opt_db_name);
        LOG(DEBUG, "db-user= "    << opt_db_user);
        LOG(DEBUG, "log-file= "   << opt_log_file);
        LOG(DEBUG, "seeds= "      << opt_seeds);
        LOG(DEBUG, "url= "        << opt_seeds);
        LOG(DEBUG, "log-level= "  << opt_log_level);
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
void trokam::options::read(const std::string &filename)
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(filename, pt);
    opt_db_name= pt.get<std::string>("database.name");
    opt_db_user= pt.get<std::string>("database.user");
    opt_log_file= pt.get<std::string>("log.file");
    std::string level= pt.get<std::string>("log.level");
    set_log_level(level);    
}

void trokam::options::set_log_level(const std::string &level)
{
    if(level == "TRACE")
    {
        opt_log_level= trokam::TRACE;
    }
    else if(level == "DEBUG")
    {
        opt_log_level= trokam::DEBUG;
    }
    else if(level == "INFO")
    {
        opt_log_level= trokam::INFO;
    }
    else if(level == "WARNING")
    {
        opt_log_level= trokam::WARNING;
    }
    else if(level == "ERROR")
    {
        opt_log_level= trokam::ERROR;
    }
    else if(level == "FATAL")
    {
        opt_log_level= trokam::FATAL;
    }
}

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::options::options(const trokam::options &opt)
{
    opt_db_host= opt.db_host();
    opt_db_name= opt.db_name();
    opt_db_user= opt.db_user();
    opt_log_file= opt.log_file();
    opt_seeds= opt.seeds();
    opt_url= opt.url();
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
    opt_db_host= opt.db_host();
    opt_db_name= opt.db_name();
    opt_db_user= opt.db_user();
    opt_log_file= opt.log_file();
    opt_seeds= opt.seeds();
    opt_url= opt.url();

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Return this object
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    return *this;
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::options::log_file() const
{
    return opt_log_file;
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::options::seeds() const
{
    return opt_seeds;
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::options::db_host() const
{
    return opt_db_host;
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::options::db_name() const
{
    return opt_db_name;
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::options::db_user() const
{
    return opt_db_user;
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
std::string trokam::options::db_name(const std::string &name)
{
    opt_db_name= name;
    return opt_db_name;
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::options::db_user(const std::string &user)
{
    opt_db_user= user;
    return opt_db_user;
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::options::url() const
{
    return opt_url;
}
