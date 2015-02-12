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

/// Trokam
#include "common.h"
#include "desk_log.h"
#include "file_management.h"
#include "machine.h"
#include "web_handler.h"

/***********************************************************************
 *
 *
 **********************************************************************/
int trokam::web_handler::fetch(const std::string &url,
                               const std::string &destination)
{
    LOG(DEBUG, "fetching '" << url << "' ... ");
    trokam::machine::rm_file(destination);
    std::string command= "wget -q --tries=1 --timeout=40 -O " + destination + " -k \"" + url + "\"";
    int exit_status= system(command.c_str());
    if (exit_status != 0)
    {
        LOG(WARNING, "fail during download, exit status= " << exit_status);
    }
    return exit_status;
}

/***********************************************************************
 * Callback to put the fetched web page into a string
 **********************************************************************/
/*
static size_t data_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
*/

/***********************************************************************
 * This method does not have conversion of relative URLs to
 * abosulute URLs.
 **********************************************************************/
/*
int trokam::web_handler::fetch(const std::string &url,
                               const std::string &destination)
{
    START;
    LOG(DEBUG, "fetching '" << url << "' ... ");
    
    CURL *curl;
    CURLcode res;
    std::string read_buffer;

    curl= curl_easy_init();

    if(curl)
    {
        /// Set the web page to fetch
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        /// Switch on full protocol/debug output while testing
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  
        /// Tell libcurl to follow redirection.
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /// Assing a callback.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, data_callback);

        /// Assign a string to fill in with data.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        /// Time out in seconds.
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 240);

        /// Perform the request, res will get the return code.
        res= curl_easy_perform(curl);

        /// Check for errors.
        if(res != CURLE_OK)
        {
            LOG(ERROR, "fetching web page failed: " << curl_easy_strerror(res) << SPACE
                       "inside: " << __PRETTY_FUNCTION__);

            return 1;
        }

        /// Cleaning up
        curl_easy_cleanup(curl);

        /// Save page into a file
        file_management::save_file(destination, read_buffer);
    }
    else
    {
        LOG(ERROR, "Could not initialize CURL library " << url << SPACE
                   "inside: " << __PRETTY_FUNCTION__);
        return 1;
    }
    END;

    return 0;
}
*/
