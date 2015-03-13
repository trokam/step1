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

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
///
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef SERVER_PROCESS
#define SERVER_PROCESS

/// C++
#include "string"

/// Boost
#include <boost/algorithm/string.hpp>

/// Trokam
#include "db_handler.h"
#include "common.h"
#include "converter.h"
#include "server_log.h"
#include "options.h"
#include "lookfor.h"
#include "render.h"
#include "token.h"

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::lookfor::search(trokam::db_handler &db,
                             const std::string &searched_word,
                                   std::string &search_results)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    boost::scoped_ptr<pqxx::result> answer;
    db.search(searched_word, answer);

    for(int field=0; field<4; field++)
    {
        for(pqxx::result::const_iterator col= answer->begin();
            col != answer->end();
            col++)
        {
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            ///
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            std::string combined= col[0].as(std::string());
                    int in_domain= col[1].as(int());
                    int in_title= col[2].as(int());
                    int in_path= col[3].as(int());

            if(((field == 0) && (in_domain > 0)) ||
               ((field == 1) && (in_title > 0)) ||
               ((field == 2) && (in_path > 0)) ||
               (field == 3))
            {
                std::string url_index= col[4].as(std::string());
                std::string url= col[5].as(std::string());
                std::string title= col[6].as(std::string());
                std::string body= col[7].as(std::string());
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                ///
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                LOG(TRACE, "index: " << url_index <<
                           " comb: " << combined <<
                           " dom: " << in_domain <<
                           " tit: " << in_title <<
                           " path: " << in_path);

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                ///
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                if(title == "")
                {
                    title= "(no title)";
                }
                else
                {
                    boost::replace_all(title, " & ", " and ");
                }

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                ///
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                if(body == "")
                {
                    body= "(empty body)";
                }
                else
                {
                    boost::replace_all(body, "|", " ");
                    boost::replace_all(body, "_", " ");
                    boost::replace_all(body, "  ", " ");
                    boost::replace_all(body, "--", "");
                }

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                ///
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                std::string url_modif= url;
                std::vector<std::string> words;
                trokam::token::separate_words(searched_word, words);
                trokam::render::mark_bold(words, url_modif);
                trokam::render::mark_bold(words, body);

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                ///
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                search_results+= "<a href=\"" + url + "\" target=\"_blank\"><h3>" + title + "</h3></a>";
                search_results+= "<p>" + body + "</p>";
                search_results+= "<a href=\"" + url + "\" target=\"_blank\">" + url_modif + "</a> ";
                search_results+= "<button class=\"audit\" name=\"" + url_index + "\">audit</button>";
            }
        }
    }
}

#endif /// SERVER_PROCESS
