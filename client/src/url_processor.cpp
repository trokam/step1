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
#include <string>
#include <fstream>
#include <iostream>

/// Boost
#include <boost/regex.hpp>

/// JsonCpp
#include "jsoncpp/json/value.h"

/// Trokam
#include "common.h"
#include "converter.h"
#include "desk_log.h"
#include "url_processor.h"
#include "file_management.h"

boost::regex e("<\\s*A\\s+[^>]*href\\s*=\\s*\"([^\"]*)\"",
               boost::regex::normal | boost::regbase::icase);

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::url_processor::url_processor()
{}

/***********************************************************************
 *
 *
 **********************************************************************/
std::vector<std::string> trokam::url_processor::extract(std::string local_file)
{
    START;
    std::vector<std::string> url_container;
    std::string content;
    content= file_management::get_file_contents(local_file);

    boost::sregex_token_iterator i(content.begin(), content.end(), e, 1);
    boost::sregex_token_iterator j;
    while(i != j)
    {
        std::string one_url(*i);
        url_container.push_back(one_url);
        *i++;
    }
    LOG(DEBUG, "extracted=" << url_container.size());
    RETURN(url_container);
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::url_processor::extract(std::string local_file, Json::Value &page_data)
{
    START;
    std::string content;
    content= file_management::get_file_contents(local_file);

    boost::sregex_token_iterator i(content.begin(), content.end(), e, 1);
    boost::sregex_token_iterator j;

    int index= 0;
    while(i != j)
    {
        std::string one_url(*i);
        std::string key= trokam::converter::to_string(index);
        page_data[URLS][key]= one_url;

        *i++;
        index++;
    }

    /*
    int index= 0;
    while(i != j)
    {
        std::string one_url(*i);
        page_data[URLS][index]= one_url;

        *i++;
        index++;
    }
    */
    // LOG(DEBUG, "extracted= " << url_container.size());
    END;
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::url_processor::extract(std::string input_file, std::string output_file)
{
    START;
    int count= 0;

    if((input_file == "") || (output_file == ""))
    {
        LOG(FATAL, "A file name must be provided");
        exit(-1);
    }
    std::ifstream file_source(input_file.c_str());
    std::ofstream file_destination;
    file_destination.open(output_file.c_str());;

    for(std::string line; std::getline(file_source, line);)
    {
        unsigned int link= line.find("link");
        unsigned int ini= line.find("http://");
        if((ini != std::string::npos) && (link != std::string::npos))
        {
            unsigned int end= line.find("\">", ini);
            LOG(DEBUG, "found= " << line.substr(ini, end-ini));
            file_destination << line.substr(ini, end-ini) << "\n";
            count++;
        }
    }
    file_destination.close();
    LOG(DEBUG, "URL extracted=" << count);
    END;
}
