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
/// Boost signals in use by Wt library is no longer being
/// maintained and is now deprecated. This avoids the warning
/// message during compilation
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef BOOST_SIGNALS_NO_DEPRECATION_WARNING
#define BOOST_SIGNALS_NO_DEPRECATION_WARNING

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// 
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef SERVER_PROCESS
#define SERVER_PROCESS

/// C++
#include "string"

/// Wt
#include <Wt/WGroupBox>

/// Trokam
#include "db_handler.h"
#include "common.h"
#include "server_log.h"
#include "options.h"
#include "page_audit.h"

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::page_audit::page_audit(const Wt::WEnvironment& env, trokam::db_handler &db_shared): WApplication(env)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Referencing the same object?
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    db= &db_shared;    
    
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Web page title
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    setTitle("Trokam Search Engine: Audit Database");                       

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Text
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
    root()->addWidget(new Wt::WText("URL"));
    
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Create a set focus on input box
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    input_text= new Wt::WLineEdit(root());
    input_text->setFocus();

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Create the button to call the method
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Wt::WPushButton *button= new Wt::WPushButton("audit", root());
    button->setMargin(5, Wt::Left);        /// add 5 pixels margin

    root()->addWidget(new Wt::WBreak());   /// insert a line break

    // greeting_ = new Wt::WText(root());     /// empty text

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Connect signals with slots
    /// Either click on the button or a return on the input box 
    /// does the same.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    button->clicked().connect(this, &page_audit::go);
    input_text->enterPressed().connect(boost::bind(&page_audit::go, this));

    data_results= NULL;
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::page_audit::go()
{
    Wt::WString url= input_text->text();

    std::string answer;
    db->get_report_of_url(url.toUTF8(), answer);

    // Wt::WGroupBox *search_results= new Wt::WGroupBox("Search results for '" + something + "'");
    
    // LOG(TRACE, "search_results: " << search_results);
    
    if(data_results != NULL)
    {
        LOG(TRACE, "deleting 'previous audit results' ... ");
        root()->removeWidget(data_results);
        delete data_results;
        data_results= NULL;
    }
    
    data_results= new Wt::WGroupBox("Data in Trokam database for URL '" + url + "'");    
    data_results->addWidget(new Wt::WText("<pre>" + answer + "</pre>"));
    
    // search_results->addStyleClass("centered-example");
    // search_results->addWidget(new Wt::WText("<p>Some contents.</p>"));
    // search_results->addWidget(new Wt::WText("<p>More contents.</p>"));
    
    /*
    for(pqxx::result::const_iterator col= answer->begin();
        col != answer->end();   
        col++)
    {
        std::string line= col[0].as(std::string());
        search_results->addWidget(new Wt::WText("<p>" + line + "</p>"));        
    }
    */
    
    root()->addWidget(data_results);
}

#endif /// SERVER_PROCESS
#endif /// BOOST_SIGNALS_NO_DEPRECATION_WARNING
