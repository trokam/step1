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

#ifndef TROKAM_POSTGRESQL_H
#define TROKAM_POSTGRESQL_H

/// C++
#include <string>
// #include <memory>

/// Boost
#include <boost/scoped_ptr.hpp>

/// Postgresql
#include <pqxx/pqxx>

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class postgresql
    {
        public:
            postgresql(std::string connection_parameters);
            ~postgresql();
            
            void exec_sql(const std::string &sentence);
            void exec_sql(const std::string &sentence, std::string &answer);
            void exec_sql(const std::string &sentence, boost::scoped_ptr<pqxx::result> &answer);

        private:
            pqxx::connection *db_connection;
    };
}

#endif /// TROKAM_POSTGRESQL_H
