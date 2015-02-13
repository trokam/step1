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

/// Boost
#include <boost/algorithm/string.hpp>

/// Wt
#include <Wt/WGroupBox>
#include <Wt/WCssStyleSheet>
#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WLength>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WText>
#include <Wt/WVBoxLayout>

/// Trokam
#include "db_handler.h"
#include "common.h"
#include "server_log.h"
#include "options.h"
#include "page_search.h"
#include "render.h"
#include "token.h"

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::page_search::page_search(const Wt::WEnvironment& env,
                                       boost::shared_ptr<trokam::db_handler> db_shared): WApplication(env)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Both, 'db' and 'db_share' share the pointer
    /// to the web data database.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    db= db_shared;

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Web page title
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    setTitle("Trokam Search Engine");

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// External CCS
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Wt::WApplication::instance()->useStyleSheet("http://trial.trokam.com/pages/trokam_pages_x.ccs");
    Wt::WApplication::instance()->useStyleSheet("http://trokam.com/pages/trokam_pages.ccs");

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Wt::WTable *top_links = new Wt::WTable();
    top_links->setHeaderCount(1);
    top_links->elementAt(0, 0)->addWidget(new Wt::WText("<a href=\"http://trokam.com/pages/search\">Search</a>"));
    top_links->elementAt(0, 1)->addWidget(new Wt::WText("<a href=\"http://trokam.com/pages/developers\">Developers</a>"));
    top_links->elementAt(0, 2)->addWidget(new Wt::WText("<a href=\"http://trokam.com/pages/donate\">Donate</a>"));
    top_links->elementAt(0, 3)->addWidget(new Wt::WText("<a href=\"http://trokam.com/pages/acknowledgements\">Acknowledgements</a>"));
    top_links->elementAt(0, 4)->addWidget(new Wt::WText("<a href=\"http://trokam.com/pages/about\">About</a>"));
    root()->addWidget(top_links);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    generate_main();
    generate_header();

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    main_container->setHidden(false);
    header_container->setHidden(true);

    results_container= NULL;
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::page_search::main_search()
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Wt::WString search_for= main_input_text->text();
    header_input_text->setText(search_for);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    header_search();
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::page_search::header_search()
{
    START;

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    main_container->setHidden(true);
    header_container->setHidden(false);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Wt::WString search_for= header_input_text->text();
    LOG(TRACE, "searching for: " << search_for);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    boost::scoped_ptr<pqxx::result> answer;
    db->search(search_for.toUTF8(), answer);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    delete_search_results();

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    LOG(TRACE, "ready to display results");
    results_container= new Wt::WContainerWidget();

    for(int field=0; field<4; field++)
    {
        for(pqxx::result::const_iterator col= answer->begin();
            col != answer->end();
            col++)
        {
            LOG(TRACE, "displaying ... ");

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
                }

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                ///
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                std::string url_modif= url;
                std::vector<std::string> words;
                trokam::token::separate_words(search_for.toUTF8(), words);
                trokam::render::mark_bold(words, url_modif);
                trokam::render::mark_bold(words, body);

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                ///
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                results_container->addWidget(new Wt::WText("<a href=\"" + url + "\" target=\"_blank\"><h3 class=\"title_result\">" + title + "</h3></a>"));
                results_container->addWidget(new Wt::WText("<p class=\"body_result\">" + body + "</p>"));
                results_container->addWidget(new Wt::WText("<a href=\"" + url + "\" target=\"_blank\">" + url_modif + "</a>"));

                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                ///
                /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                Wt::WPushButton *audit_button= new Wt::WPushButton("audit", results_container);
                audit_button->clicked().connect(boost::bind(&page_search::audit, this, url_index));
                results_container->addWidget(audit_button);
            }
        }
    }
    LOG(TRACE, "finish displaying results");

    root()->addWidget(results_container);
    results_container->setHidden(false);
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::page_search::clean()
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    main_input_text->setText("");

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    delete_search_results();

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    main_container->setHidden(false);
    header_container->setHidden(true);
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::page_search::generate_main()
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    main_container = new Wt::WContainerWidget();
    main_container->setStyleClass("main");

    Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout();
    main_container->setLayout(vbox);

    Wt::WText *topheader= new Wt::WText("<h1>Trokam</h1>");
    topheader->setStyleClass("topheader");
    vbox->addWidget(topheader, 1);

    Wt::WText *tagline= new Wt::WText("<h2>Ads-Free and Open Source Search Engine</h2>");
    tagline->setStyleClass("tagline");
    vbox->addWidget(tagline);

    Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
    vbox->addLayout(hbox);

    main_input_text= new Wt::WLineEdit(main_container);
    main_input_text->setFocus();
    hbox->addWidget(main_input_text);

    Wt::WPushButton *main_button= new Wt::WPushButton("search", root());
    main_button->setMargin(5, Wt::Left);
    hbox->addWidget(main_button);

    root()->addWidget(main_container);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Connect methods to the buttons.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    main_button->clicked().connect(this, &page_search::main_search);
    main_input_text->enterPressed().connect(boost::bind(&page_search::main_search, this));
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::page_search::generate_header()
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    header_container = new Wt::WContainerWidget();
    header_container->setStyleClass("smallheader");

    Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
    header_container->setLayout(hbox);

    Wt::WText *smallheader= new Wt::WText("<span style=\"font-weight: bold; font-size: 200%; font-family: Ubuntu, Sans-serif;\">Trokam</span>");
    hbox->addWidget(smallheader);

    header_input_text= new Wt::WLineEdit(main_container);
    header_input_text->setFocus();
    hbox->addWidget(header_input_text);

    Wt::WPushButton *header_button_search= new Wt::WPushButton("search", root());
    header_button_search->setMargin(Wt::Left);
    hbox->addWidget(header_button_search);

    Wt::WPushButton *header_button_clean= new Wt::WPushButton("clean", root());
    header_button_clean->setMargin(Wt::Left);
    hbox->addWidget(header_button_clean);

    root()->addWidget(header_container);

    header_container->setHidden(true);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Connect methods to the buttons.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    header_button_clean->clicked().connect(this, &page_search::clean);
    header_button_search->clicked().connect(this, &page_search::header_search);
    header_input_text->enterPressed().connect(boost::bind(&page_search::header_search, this));
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::page_search::audit(std::string url)
{
    results_container->setHidden(true);
    header_container->setHidden(true);
    
    audit_container = new Wt::WContainerWidget();
        
    Wt::WPushButton *audit_button_back= new Wt::WPushButton("back", audit_container);
    audit_container->addWidget(audit_button_back);
    
    std::string answer;
    db->get_report_of_url(url, answer);
    audit_container->addWidget(new Wt::WText("<pre>" + answer + "</pre>"));
    
    root()->addWidget(audit_container);
    
    audit_button_back->clicked().connect(this, &page_search::audit_back_to_results);
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::page_search::audit_back_to_results()
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(audit_container != NULL)
    {
        LOG(TRACE, "deleting 'audit_container' ... ");
        root()->removeWidget(audit_container);
        delete audit_container;
        audit_container= NULL;
    }
    results_container->setHidden(false);
    header_container->setHidden(false);    
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::page_search::delete_search_results()
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(results_container != NULL)
    {
        LOG(TRACE, "deleting 'search_results' ... ");
        root()->removeWidget(results_container);
        delete results_container;
        results_container= NULL;
    }
}

#endif /// SERVER_PROCESS
#endif /// BOOST_SIGNALS_NO_DEPRECATION_WARNING
