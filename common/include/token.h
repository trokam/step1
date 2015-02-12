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

#ifndef TROKAM_TOKEN_H
#define TROKAM_TOKEN_H

/// C++
#include <string>
#include <vector>

/// Boost
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

#define RIGHT 0
#define TAB   "\t"

/** This class has static methods to process tokens in texts.
 *  
 */
namespace trokam
{
    class token
    {
        public:
            static int get_protocol(const std::string &url,
                                          std::string &protocol);
            static int split_protocol_domain_path(const std::string &url,
                                                        std::string &protocol,
                                                        std::string &domain,
                                                        std::string &path);
            static bool it_has_any_chars_of(const std::string &text,
                                            const std::string &some_chars);
            static std::string leftPadding(const std::string &text,
                                           const int &total_length,
                                           const std::string &fill= " ");
            static std::string rightPadding(const std::string &text,
                                            const int &total_length,
                                            const std::string &fill= " ");
            static void split_line(const std::string &line,
                                         std::string &first,
                                         std::string &second);
            static void separate_words(const std::string &text,
                                             std::vector<std::string> &words);
    };
}

#endif /// TROKAM_TOKEN_H
