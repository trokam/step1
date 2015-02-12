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
#include <iostream>

/// Boost
#include <boost/algorithm/string.hpp>

/// JsonCpp
#include <jsoncpp/json/value.h>

/// Trokam
#include "common.h"
#include "desk_log.h"
#include "file_management.h"
#include "html_handler.h"

/***********************************************************************
 *
 **********************************************************************/
std::string trokam::html_handler::extract_title(std::string local_file_name)
{
    std::string title;
    std::string content;
    content= file_management::get_file_contents(local_file_name);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::size_t ini= content.find("<title>");
    std::size_t end= content.find("</title>");
    if((ini != std::string::npos) && (end != std::string::npos))
    {
        title= content.substr(ini+7, end-ini-7);
    }
    LOG(DEBUG, "title=" << title);
    return title;
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::html_handler::extract_title(std::string local_file_name,
                                         Json::Value &page_data)
{
    std::string title;
    std::string content;
    content= file_management::get_file_contents(local_file_name);

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ///
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::size_t ini= content.find("<title>");
    std::size_t end= content.find("</title>");
    if((ini != std::string::npos) && (end != std::string::npos))
    {
        title= content.substr(ini+7, end-ini-7);
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Character ' makes trouble on sql sentences.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    boost::algorithm::erase_all(title, "'\n\r\"");
    page_data[TITLE]= title;    
    LOG(DEBUG, "title: " << title);
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::html_handler::generate_link(const std::string &url, std::string &link)
{
    link= "<a href=\"" + url + "\">" + url + "</a>";
}

