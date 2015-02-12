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

#ifndef TROKAM_WORD_STATS_H
#define TROKAM_WORD_STATS_H

/// C++
#include <string>
#include <map>

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class word_stats
    {
        public:
            word_stats();
            float get_frequency_of_word(const std::string &word,
                                        const std::string &lang);
            
        private:
            void load_word_cfg(const std::string &lang,
                               std::map<std::string, float> &word_map);

            float get_value(const std::string &word,
                            std::map<std::string, float> &word_map);
                               
            std::map<std::string, float> word_en;
            std::map<std::string, float> word_pt;
            std::map<std::string, float> word_ar;
            std::map<std::string, float> word_de;
            std::map<std::string, float> word_ru;
            std::map<std::string, float> word_ja;
            std::map<std::string, float> word_es;
    };
}

#endif /// TROKAM_WORD_STATS_H
