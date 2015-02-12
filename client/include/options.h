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

#ifndef TROKAM_OPTIONS_H
#define TROKAM_OPTIONS_H

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    enum severity
    {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    class options
    {
        public:
            options();
            options(int argc, const char* argv[]);
            options(int argc, char **argv);
            options(const options &opt);
            options& operator= (const options &opt);
            int          page_limit() const;
            severity     log_level() const;
            std::string  server_address() const;

        private:
            int          opt_page_limit;
            std::string  opt_server_address;            
            severity     opt_log_level;
    };
}

#endif /// TROKAM_OPTIONS_H
