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
#include <stdio.h>
#include <time.h>

/// C++
#include <iostream>
#include <sstream>

/// FastCGI
#include <fcgi_stdio.h>

/// Trokam
#include "converter.h"
#include "machine.h"
#include "server_log.h"
#include "token.h"

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::severity trokam::log::display_min;
trokam::format trokam::log::display_format;
std::stringstream trokam::log::location;
std::stringstream trokam::log::report;
FILE* trokam::log::log_file;

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::log::setup(trokam::options &opt)
{
    display_min= opt.log_level();
    display_format= trokam::SIMPLE;

    std::string filename= opt.log_file();
    if(filename != "")
    {
        log_file= FCGI_fopen(filename.c_str(), "a+");
    }
    else
    {
        trokam::machine::mkdir("/tmp/trokam/server/");
        log_file= FCGI_fopen("/tmp/trokam/server/server.log", "a+");
    }
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::log::msg(trokam::severity level)
{
    if(level < display_min)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Clean the streams and return
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        location.str("");
        report.str("");
        return;
    }

    std::string tag;
    switch(level)
    {
        case TRACE:
        {
            tag= "TRACE";
        } break;

        case DEBUG:
        {
            tag= "DEBUG";
        } break;

        case INFO:
        {
            tag= "INFO";
        } break;

        case WARNING:
        {
            tag= "WARNING";
        } break;

        case ERROR:
        {
            tag= "ERROR";
        } break;

        case FATAL:
        {
            tag= "FATAL";
        } break;
    }

    time_t rawtime;
    time(&rawtime);

    struct tm *timeinfo;
    timeinfo= localtime(&rawtime);
    int year= timeinfo->tm_year + 1900;
    int month= timeinfo->tm_mon + 1;

    std::stringstream msg;

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Put the text line in the output
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    msg << tag << "\t"
        << year << "-"
        << trokam::token::leftPadding(converter::to_string(month), 2, "0") << "-"
        << timeinfo->tm_mday << " "
        << timeinfo->tm_hour << ":"
        << trokam::token::leftPadding(converter::to_string(timeinfo->tm_min), 2, "0") << ":"
        << trokam::token::leftPadding(converter::to_string(timeinfo->tm_sec), 2, "0");

    if(display_format == trokam::SIMPLE)
    {
        msg << SEPARATOR << report.str() << "\n";
    }

    if(display_format == trokam::FULL)
    {
        msg << SEPARATOR << location.str() << SEPARATOR << report.str() << "\n";
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    FCGI_fprintf(log_file, msg.str().c_str());
    FCGI_fflush(log_file);    

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Clean the stream
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    location.str("");
    report.str("");
}
