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
#include <map>

/// Boost
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

/// JsonCpp
#include "jsoncpp/json/value.h"

/// Trokam
#include "converter.h"
#include "common.h"
#include "desk_log.h"
#include "file_management.h"
#include "language.h"
#include "sort.h"
#include "text_processor.h"
#include "token.h"

/***********************************************************************
 *
 **********************************************************************/
trokam::text_processor::text_processor(std::string file_name)
{
    content= file_management::get_file_contents(file_name);
    
}

/***********************************************************************
 *
 **********************************************************************/
bool trokam::text_processor::word_frequency(Json::Value &page_data)
{
    std::string lang;
    int count= 0;

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Language detection
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    lang= language::detect(content);
    boost::algorithm::trim_if(lang, boost::algorithm::is_any_of(" "));
    page_data[LANGUAGE]= lang;

    LOG(DEBUG, "content length=" << content.length());

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Counting word frequency
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ((lang != "SHORT") && (lang != "UNKNOWN"))
    {
        boost::tokenizer<> tok(content);
        for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end(); ++beg)
        {
            std::string token= *beg;

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// All words are converted to lower case.
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            boost::algorithm::to_lower(token);

			if (token.length() == 1)
			{
                continue;
			}

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// It skip all words with strange characters.
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            size_t loc= token.find_first_of("°¬!¡#$%&/()=?¿*+~[]{}^;:., <>©…");
			if (loc != std::string::npos)
			{
				continue;
			}

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            ///
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            if(page_data[WORDS].isMember(token))
            {
                int token_count= page_data[WORDS][token].asInt();
                page_data[WORDS][token]= token_count + 1;
            }
            else
            {
                page_data[WORDS][token]= 1;
            }
            count++;
        }
		LOG(DEBUG, "tokens: " << count);
		LOG(DEBUG, "words: " << page_data[WORDS].size());
		LOG(DEBUG, "lang: " << page_data[LANGUAGE].asString());
        return true;
    }
    else
    {
       	LOG(WARNING, "page discarded because language is: " << lang);
        return false;
	}
}

/***********************************************************************
 *
 **********************************************************************/
bool trokam::text_processor::word_relevance_analysis(Json::Value &page_data,
                                                     trokam::word_stats &ws)
{
    std::string lang;
    int count= 0;
    std::map<std::string, int> page_words_occurrences;
    std::map<std::string, float> page_words_frequencies;
    std::map<std::string, int> words_ratios;

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Language detection
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    lang= language::detect(content);
    boost::algorithm::trim_if(lang, boost::algorithm::is_any_of(" "));
    page_data[LANGUAGE]= lang;

    LOG(DEBUG, "language: " << lang);
    LOG(DEBUG, "content length: " << content.length());
    
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// 
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ((lang != "SHORT") && (lang != "UNKNOWN"))
    {
        boost::tokenizer<> tok(content);
        for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end(); ++beg)
        {
            std::string token= *beg;

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// All words are converted to lower case.
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            boost::algorithm::to_lower(token);

			if (token.length() == 1)
			{
                continue;
			}

            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            /// It skip all words with strange characters.
            /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            size_t loc= token.find_first_of("°¬!¡#$%&/()=?¿*+~[]{}^;:., <>©…");
			if (loc != std::string::npos)
			{
				continue;
			}

            if(page_words_occurrences.find(token) != page_words_occurrences.end())
            {
                page_words_occurrences[token]++;
            }
            else
            {
                page_words_occurrences[token]= 1;
            }
            count++;
        }
    }

    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Calculate the frequency of each word within in the text
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for(std::map<std::string, int>::iterator it= page_words_occurrences.begin();
        it != page_words_occurrences.end();
        ++it)
    {
        page_words_frequencies[it->first]= float(it->second)/float(count);
    }
    
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Compare the frequency of each word within in the text to the 
    /// frequency in the global statistics.
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for(std::map<std::string, float>::iterator it= page_words_frequencies.begin();
        it != page_words_frequencies.end();
        ++it)
    {
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// What if the word do not exist in the table of frequencies?
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        std::string word= it->first;
        float global_freq= ws.get_frequency_of_word(word, lang);
        float local_freq= page_words_frequencies[word];

        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// The word is relevant if is local frequency is well over the
        /// global frequency.
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        int ratio= int(local_freq/global_freq);

        if(ratio > RATIO_THRESHOLD)
        {
             page_data[RELEVANT][it->first]= ratio;
        }
    }
    
    return true;
}

/***********************************************************************
 *
 **********************************************************************/
void trokam::text_processor::clean_line(std::string &line)
{
    boost::algorithm::erase_all(line, "  ");
    boost::algorithm::erase_all(line, "'");
    boost::replace_all(line, "<", "");
    boost::replace_all(line, ">", "");
    boost::replace_all(line, "\"", "");
    boost::replace_all(line, "\n", " ");
    boost::replace_all(line, "\r", " ");
    boost::replace_all(line, "\t", " ");
    boost::replace_all(line, "\v", " ");
    boost::replace_all(line, "\f", " ");
    boost::replace_all(line, "&", "and");
}
