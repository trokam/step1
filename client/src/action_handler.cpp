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

/// C
#include <cstdlib>

/// C++
#include <iostream>
#include <exception>

/// Curl
#include <curl/curl.h>

/// JsonCpp
#include "jsoncpp/json/json.h"

/// Trokam
#include "common.h"
#include "desk_log.h"
#include "machine.h"
#include "action_handler.h"

/***********************************************************************
 * Callback to put the fetched web page into a string
 **********************************************************************/

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


/***********************************************************************
 *
 *
 **********************************************************************/
trokam::action_handler::action_handler(trokam::options &opt)
{
    if(opt.server_address() != "")
    {
        server_address= "http://" + opt.server_address() + "/action";
    }
    else
    {
        server_address= SERVER;
    }
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::action_handler::perform_on_server(const std::string &request,
                                                     std::string &answer)
{
    START;
    
    CURL *curl;
    CURLcode res;
    std::string read_buffer;

    std::string outgoing;
    outgoing = PERFORM;
    outgoing+= "=";
    outgoing+= request;

    curl= curl_easy_init();
    if(curl)
    {
        /// Set the web page to fetch
        curl_easy_setopt(curl, CURLOPT_URL, server_address.c_str());

        /// Tell libcurl to follow redirection.
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /// Assing a callback.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /// Assign a string to fill in with data.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        /// Specifying POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, outgoing.c_str());

        /// Perform the request, res will get the return code.
        res= curl_easy_perform(curl);

        /// Check for errors.
        if(res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res);
        }

        /// Cleaning up
        curl_easy_cleanup(curl);

        /// Display results
        LOG(DEBUG, "Raw reply of server=" << read_buffer);
        
        answer= read_buffer;
    }
    END;
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::action_handler::perform_on_server(const std::string &request,
                                               const Json::Value &data,
                                                     std::string &answer)
{
    START;
    
    CURL *curl;
    CURLcode res;
    std::string read_buffer;

    std::string outgoing;
    outgoing = PERFORM;
    outgoing+= "=";
    outgoing+= request;
    outgoing+= "&";
    outgoing+= DATA;    
    outgoing+= "=";    
    outgoing+= data.toStyledString();    

    curl= curl_easy_init();
    if(curl)
    {
        /// Set the web page to fetch
        curl_easy_setopt(curl, CURLOPT_URL, server_address.c_str());

        /// Tell libcurl to follow redirection.
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /// Assing a callback.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /// Assign a string to fill in with data.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        /// Specifying POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, outgoing.c_str());

        /// Perform the request, res will get the return code.
        res= curl_easy_perform(curl);

        /// Check for errors.
        if(res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res);
        }

        /// Cleaning up
        curl_easy_cleanup(curl);

        /// Display results
        answer= read_buffer;
    }
    END;
}

/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::action_handler::perform_on_server(const Json::Value &bundle,
                                                     Json::Value &answer)
{
    CURL *curl;
    CURLcode res;
    std::string read_buffer;

    std::string outgoing= bundle.toStyledString();    

    curl= curl_easy_init();
    if(curl)
    {
        /// Set the web page to fetch
        curl_easy_setopt(curl, CURLOPT_URL, server_address.c_str());

        /// Tell libcurl to follow redirection.
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /// Assing a callback.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /// Assign a string to fill in with data.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        /// Specifying POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, outgoing.c_str());

        /// Perform the request, res will get the return code.
        res= curl_easy_perform(curl);

        /// Check for errors.
        if(res != CURLE_OK)
        {
            LOG(ERROR, "Action failed: " << curl_easy_strerror(res) << SPACE
                       "inside: " << __PRETTY_FUNCTION__);
        }

        /// Cleaning up
        curl_easy_cleanup(curl);

        /// Assemble a JSON package as the answer
        Json::Reader reader;
        reader.parse(read_buffer, answer, false);
    }
}
