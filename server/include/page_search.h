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

#ifndef TROKAM_PAGE_SEARCH_H
#define TROKAM_PAGE_SEARCH_H

/// Boost
#include <boost/shared_ptr.hpp>

/// Wt 
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

/// Trokam
#include "db_handler.h"

/** This class generates the web page with search for words function.
 *  The connection with the rest of the sysem is the database 
 *  object and its public methods.
 */
namespace trokam
{
    class page_search: public Wt::WApplication
    {
        public:
            page_search(const Wt::WEnvironment& env,
                              boost::shared_ptr<trokam::db_handler> db_shared);

        private:
            boost::shared_ptr<trokam::db_handler> db;
            
            Wt::WLineEdit *main_input_text;
            Wt::WLineEdit *header_input_text;        
            Wt::WContainerWidget *main_container;
            Wt::WContainerWidget *header_container;
            Wt::WContainerWidget *results_container;
            Wt::WContainerWidget *audit_container;
            
            void main_search();
            void header_search();

            void clean();
            void delete_search_results();
            
            void generate_main();
            void generate_header();
            
            void audit(std::string url);
            void audit_back_to_results();
    };
}

#endif /// TROKAM_PAGE_SEARCH_H
