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

#ifndef TROKAM_TEXT_PROCESSOR_H
#define TROKAM_TEXT_PROCESSOR_H

/// C++
#include <string>

/// JsonCpp
#include "jsoncpp/json/json.h"

/// Trokam
#include "word_stats.h"

struct word_container
{
    std::string language;
    std::map<std::string, int> store;
};

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class text_processor
    {
        private:
            std::string content;

        public:
            text_processor(std::string file_name);
            bool word_frequency(Json::Value &page_data);
            bool word_relevance_analysis(Json::Value &page_data, trokam::word_stats &ws);
            static void clean_line(std::string &line);
    };
}

#endif /// TROKAM_TEXT_PROCESSOR_H
