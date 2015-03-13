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

#ifndef TROKAM_LOG_H
#define TROKAM_LOG_H

/// C++
#include <string>
#include <sstream>
#include <ostream>

/// Trokam
#include "options.h"

#define HERE   __PRETTY_FUNCTION__
#define SEPARATOR "  "

/***********************************************************************
 *
 *
 **********************************************************************/


#define LOG(X,Y)  {                                                    \
                      trokam::log::location << __PRETTY_FUNCTION__;    \
                      trokam::log::report   << Y;                      \
                      trokam::log::msg(trokam::X);                     \
                  }


#define START    {                                                                     \
                     trokam::log::report   << __PRETTY_FUNCTION__ << "  " << "START";  \
                     trokam::log::msg(trokam::TRACE);                                  \
                 }


#define END     {                                                    \
                    trokam::log::report   << __PRETTY_FUNCTION__     \
                                          << "  "                    \
                                          << "END";                  \
                    trokam::log::msg(trokam::TRACE);                 \
                }

#define RETURN(Z) {                                                  \
                    trokam::log::report   << __PRETTY_FUNCTION__     \
                                          << "  "                    \
                                          << "END";                  \
                    trokam::log::msg(trokam::TRACE);                 \
                    return(Z);                                       \
                  }

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    enum format
    {
        SIMPLE,
        FULL
    };

    class log
    {
        public:
            static std::stringstream location;
            static std::stringstream report;
            static void setup(trokam::options &opt);
            static void msg(trokam::severity level);
            static void quiet(bool value);

        private:
            static bool silence;
            static FILE *log_file;
            static severity display_min;
            static format display_format;
    };
}

#endif /// TROKAM_LOG_H
