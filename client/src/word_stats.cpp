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
#include <stdlib.h>

/// C++
#include <iostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

/// Trokam
#include "converter.h"
#include "common.h"
#include "desk_log.h"
#include "html_handler.h"
#include "text_processor.h"
#include "token.h"

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::word_stats::word_stats()
{
    LOG(TRACE, "Loading words for English ...");
    load_word_cfg("en", word_en);

    LOG(TRACE, "Loading words for Portuguese ...");    
    load_word_cfg("pt", word_pt);
    
    LOG(TRACE, "Loading words for Arabic ...");    
    load_word_cfg("ar", word_ar);
    
    LOG(TRACE, "Loading words for German ...");    
    load_word_cfg("de", word_de);
    
    LOG(TRACE, "Loading words for Russian ...");    
    load_word_cfg("ru", word_ru);
    
    LOG(TRACE, "Loading words for Japanese ...");    
    load_word_cfg("ja", word_ja);
    
    LOG(TRACE, "Loading words for Spanish ...");    
    load_word_cfg("es", word_es);
}
            
/***********************************************************************
 *
 *
 **********************************************************************/
float trokam::word_stats::get_frequency_of_word(const std::string &word,
                                                const std::string &lang)
{
    float value= 1.0;
    
    if(lang == "en")
    {
        value= get_value(word, word_en);
    }
    else if(lang == "pt")
    {
        value= get_value(word, word_pt);
    }
    else if(lang == "ar")
    {
        value= get_value(word, word_ar);
    }
    else if(lang == "de")
    {
        value= get_value(word, word_de);
    }
    else if(lang == "ru")
    {
        value= get_value(word, word_ru);
    }
    else if(lang == "ja")
    {
        value= get_value(word, word_ja);
    }
    else if(lang == "es")
    {
        value= get_value(word, word_es);
    }
    else
    {
        /// language not valid
    }
    return value;
}
            
/***********************************************************************
 *
 *
 **********************************************************************/
void trokam::word_stats::load_word_cfg(const std::string &lang,
                                       std::map<std::string, float> &word_map)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Assemble the path to locathe the directory 'config'.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string location= "/usr/local/etc/trokam/trokam_words_" + lang + ".cfg";
    std::ifstream cfg_file(location.c_str());

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Loads the contents.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string line;    
    if(cfg_file.is_open())
    {
        while(std::getline(cfg_file, line))
        {
            std::string first;
            std::string second;
            trokam::token::split_line(line, first, second);
            word_map[first]= trokam::converter::string_to_float(second);
        }
        cfg_file.close();
    }
    else
    {
        LOG(ERROR, "Unable to open file: " << location); 
    }
}

/***********************************************************************
 *
 *
 **********************************************************************/
float trokam::word_stats::get_value(const std::string &word,
                                    std::map<std::string, float> &word_map)
{
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// It looks for the word in the map <word, frequency>.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::map<std::string, float>::iterator it;
    it= word_map.find(word);

    if(it == word_map.end())
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// If the word does not exist in the statistics, it is 
        /// it is assumed a frequency equivalent to one divided
        /// by the number of words for its language, i.e. the lowest
        /// frequency.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        float word_count= word_map.size();
        return 1.0/word_count;
    }
    else
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// If the word exist in the statistics, it returns  
        /// the value of frequency.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        return it->second;
    }
}
