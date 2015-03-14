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

#ifndef TROKAM_DB_HANDLER_H
#define TROKAM_DB_HANDLER_H

/// C++
#include <string>
// #include <map>
#include <vector>

/// JsonCpp
#include "jsoncpp/json/json.h"

/// Trokam
#include "options.h"
#include "postgresql.h"

/*! \brief This class is the interface with the database of web data.
 *         These methods prepare the SQL sentences, send them for
 *         execution in the database engine and return the answer.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Tables
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *   PK : Primary Key
 * 
 *   +-----------------------------------------------+
 *   | url                                           |
 *   +-----------------+-----------------------------+
 *   |     Column      |            Type             |
 *   +-----------------+-----------------------------+
 *   | index           | serial                      |
 *   | value (PK)      | character varying(1000)     |
 *   | parent          | integer                     |
 *   | level           | integer                     |
 *   | booked          | boolean                     | 
 *   | crunched        | boolean                     | 
 *   | date_insertion  | timestamp without time zone | 
 *   | date_crunched   | timestamp without time zone | 
 *   | download_status | integer                     | 
 *   +-----------------+-----------------------------+
 *
 *   +-------------------------------------+
 *   | word                                |
 *   +------------+------------------------+
 *   |  Column    |          Type          |
 *   +------------+------------------------+
 *   | index (PK) | serial                 |
 *   | value      | character varying(100) |
 *   | language   | character varying(10)  |
 *   +------------+------------------------+
 *
 *   +----------------------+
 *   | ranking              |
 *   +------------+---------+
 *   |  Column    |  Type   |
 *   +------------+---------+
 *   | url_index  | integer | 
 *   | word_index | integer | 
 *   | ratio      | integer | 
 *   | domain     | boolean | 
 *   | title      | boolean | 
 *   | path       | boolean |
 *   +------------+---------+
 *
 *   +--------------------------+
 *   | content                  |
 *   +----------------+---------+
 *   |  Column        |  Type   |
 *   +----------------+---------+
 *   | index          | serial  |
 *   | url_index (PK) | integer |
 *   | title          | text    | 
 *   | body           | text    |
 *   +----------------+---------+
 *
 *   +--------------------------------------+
 *   | cruncher                             |
 *   +-------------+------------------------+
 *   |   Column    |          Type          |
 *   +-------------+------------------------+
 *   | index       | serial                 |
 *   | id (PK)     | character varying(36)  |
 *   | name        | character varying(70)  | 
 *   | description | character varying(400) | 
 *   | link_1      | character varying(300) | 
 *   | link_2      | character varying(300) | 
 *   | since       | date                   | 
 *   | pages       | integer                |
 *   +-------------+------------------------+
 *
 *   +-----------------------------------------------+
 *   | task                                          |                                  
 *   +-----------------+-----------------------------+
 *   |      Column     |            Type             |
 *   +-----------------+-----------------------------+
 *   | index           | integer                     |
 *   | cruncher_index  | integer                     |
 *   | task_id (PK)    | character varying(10)       |
 *   | task_type       | character varying(20)       | 
 *   | url_index       | integer                     | 
 *   | completed       | boolean                     | 
 *   | date            | timestamp without time zone | 
 *   +-----------------+-----------------------------+
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Table relations
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *    +--------+                           
 *    |  url   |                           
 *    +--------+                           
 *    | index  |---+
 *    | value  |   |
 *    | parent |   |
 *    |  ...   |   |                    
 *    +--------+   |
 *                 |     +------------+
 *                 |     |  ranking   |            +----------+
 *                 |     +------------+            |  word    |
 *                 +---->| url_index  |            +----------+
 *                 |     | word_index |<-----------| index    |
 *                 |     |     ...    |            | value    |
 *                 |     +------------+            | language |
 *                 |                               +----------+   
 *                 |
 *                 |     +------------+
 *                 |     |  content   |
 *                 |     +------------+
 *                 |     | index      |
 *                 +---->| url_index  |
 *                 |     | title      |
 *                 |     | body       |           
 *                 |     +------------+          
 *                 |                             
 *                 |                             
 *                 |     +----------------+
 *                 |     |  task          |        +----------+
 *                 |     +----------------+        | cruncher |
 *                 |     | index          |        +----------+
 *                 |     | cruncher_index |<-------| index    |
 *                 +---->| url_index      |        | id       |
 *                       |      ...       |        | name     |
 *                       +----------------+        |    ...   |
 *                                                 +----------+
 *
 **********************************************************************/

namespace trokam
{
    struct task
    {
        std::string task_id;
        std::string task_type;
        std::string url;
        std::string url_index;
        std::string data;
    };

    class db_handler
    {
        public:
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// constructor and destructor
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            db_handler(trokam::options &opt);
            ~db_handler();

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// search
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            void search(const std::string &text,
                        boost::scoped_ptr<pqxx::result> &answer);

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// initialize database
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            void initialize();

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// cruncher
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            bool is_valid_user(const std::string &cruncher_id);
            bool verify_user(std::string cruncher_id);
            std::string get_cruncher_index(const std::string &cruncher_id);

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// task
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            void get_task(const std::string &cruncher_id, task &user_task);

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// report
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            void save_full_page_report(const Json::Value &incoming,
                                             Json::Value &outgoing);
            void get_report_of_url(const std::string &url_index,
                                         std::string &answer);

        private:

            trokam::options opt;
            trokam::postgresql *db;
            
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// initialize database
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            bool is_db_empty();

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// cruncher
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            bool is_right_assignement(const std::string &cruncher_id,
                                      const std::string &task_id,
                                      std::string &url_index);

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// task
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            void set_task_finished(const std::string &task_id);
            void save_task(const std::string &cruncher_id, const task &user_task);

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// ranking
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            void insert_rank(const std::string &url_index,
                             const std::string &word_index,
                             const std::string &ratio,
                                    const bool &domain,
                                    const bool &title,
                                    const bool &path);

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// url
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            std::string get_url(const std::string &index_url);
            void book_url(const std::string &url_index);
            void release_url_booking(const std::string &url_index,
                                     const std::string &download_status);
            void inject_urls(const std::string &url_index,
                             const Json::Value &report);
            std::string inject_one_url(const std::string &url,
                                       const std::string &level="0",
                                       const std::string &parent_index="-1");
            std::string get_url_task(std::string &url, std::string &url_index);
            std::string get_url_level(const std::string &url_index);
            void get_url_index(const std::string &url, 
                                     std::string &url_index);
            void get_urls(const std::string &url,
                                boost::scoped_ptr<pqxx::result> &answer);
            void fill_with_urls_in_file(std::string file_name);                                

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// word
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            void inject_words(const Json::Value &words);
            void inject_relevant_words(const std::string &url_index,
                                       const Json::Value &report);
            std::string increment_occurrence(const std::string &index,
                                             const std::string &qty);
            std::string get_word_index(const std::string &word,
                                       const std::string &lang);
            std::string insert_word(const std::string &word,
                                    const std::string &lang);
            void get_word_rank(const std::string &url,
                                     boost::scoped_ptr<pqxx::result> &answer);
                        
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// content methods
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            void inject_content(const std::string &url_index,
                                const Json::Value &report);
            void get_title(const std::string &url, 
                                 std::string &title);
            void get_body(const std::string &url, 
                                std::string &body);
    };
}

#endif /// TROKAM_DB_HANDLER_H
