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
#include <cassert>
#include <iostream>

/// Trokam
#include "postgresql.h"

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#if SERVER_PROCESS
    #include "server_log.h"
#else
    #include "desk_log.h"
#endif

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::postgresql::postgresql(std::string connection_parameters)
{
    db_connection= new pqxx::connection(connection_parameters);
    LOG(DEBUG, "connected to database");
    LOG(DEBUG, "backend version: " << db_connection->server_version());
    LOG(DEBUG, "protocol version: " << db_connection->protocol_version());
}

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::postgresql::~postgresql()
{
    delete db_connection;
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::postgresql::exec_sql(const std::string &sentence)
{
    try
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Begin a transaction acting on our current connection.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        pqxx::work T(*db_connection, "execute_no_answer");

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Perform a query on the database, storing result tuples in R.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        T.exec(sentence);

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Tell the transaction that it has been successful.
        /// This is not really necessary if no modifications are made
        /// to commit.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        T.commit();
    }
    catch(const pqxx::sql_error &e)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// The sql_error exception class gives us
        /// some extra information.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LOG(ERROR, "SQL error: " << e.what());
        LOG(ERROR, "Query was: " << e.query());
    }
    catch(const std::exception &e)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// All exceptions thrown by libpqxx are
        /// derived from std::exception.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LOG(ERROR, "Exception: " << e.what());
    }
    catch(...)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// This is really unexpected.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LOG(ERROR, "Unhandled exception");
    }
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::postgresql::exec_sql(const std::string &sentence,
                                  std::string &answer)
{
    try
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Begin a transaction acting on our current connection.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        pqxx::work T(*db_connection, "execute");

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Perform a query on the database, storing result tuples in R.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        pqxx::result R(T.exec(sentence));

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Put in the string 'answer' the element of the of the first
        /// column of the first row of the results.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        pqxx::result::const_iterator c= R.begin();
        if(c != R.end())
        {
            answer= c[0].as(std::string());
        }

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Tell the transaction that it has been successful.
        /// This is not really necessary if no modifications are made
        /// to commit.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        T.commit();
    }
    catch(const pqxx::sql_error &e)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// The sql_error exception class gives us
        /// some extra information.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LOG(ERROR, "SQL error: " << e.what());
        LOG(ERROR, "Query was: " << e.query());
    }
    catch(const std::exception &e)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// All exceptions thrown by libpqxx are
        /// derived from std::exception.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LOG(ERROR, "Exception: " << e.what());
    }
    catch(...)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// This is really unexpected.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LOG(ERROR, "Unhandled exception");
    }
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::postgresql::exec_sql(const std::string &sentence,
                                  boost::scoped_ptr<pqxx::result> &answer)
{
    try
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Begin a transaction acting on our current connection.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        pqxx::work T(*db_connection, "execute");

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Perform a query on the database, storing result tuples in R.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        answer.reset(new pqxx::result(T.exec(sentence)));

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Tell the transaction that it has been successful.
        /// This is not really necessary if no modifications are made
        /// to commit.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        T.commit();
    }
    catch(const pqxx::sql_error &e)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// The sql_error exception class gives us
        /// some extra information.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LOG(ERROR, "SQL error: " << e.what());
        LOG(ERROR, "Query was: " << e.query());
    }
    catch(const std::exception &e)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// All exceptions thrown by libpqxx are
        /// derived from std::exception.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LOG(ERROR, "Exception: " << e.what());
    }
    catch(...)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// This is really unexpected.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        LOG(ERROR, "Unhandled exception");
    }
}
