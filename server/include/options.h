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

#ifndef TROKAM_OPTIONS_H
#define TROKAM_OPTIONS_H

/// C++
#include <string>

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
            
            void generate(int argc, const char* argv[]);
            void read(const std::string &filename);

            std::string  log_file() const;
            std::string  seeds() const;
            severity     log_level() const;
            std::string  db_host() const;
            std::string  db_name() const;
            std::string  db_user() const;
            std::string  url() const;
            
            std::string  db_name(const std::string &name);
            std::string  db_user(const std::string &user);

        private:
            std::string  opt_db_host;
            std::string  opt_db_name;
            std::string  opt_db_user;
            std::string  opt_log_file;
            std::string  opt_seeds;
            std::string  opt_url;
            severity     opt_log_level;
            
            void set_log_level(const std::string &level);            
    };
}

#endif /// TROKAM_OPTIONS_H
