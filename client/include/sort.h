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

#ifndef TROKAM_SORT_H
#define TROKAM_SORT_H

/// C++
#include <map>
#include <string>
#include <vector>

namespace trokam
{
    struct word_value
    {
        std::string word;
        int value;
    };
    
    class sort
    {
        public:
            static void sort_map_by_value(std::map<std::string, int> data,
                                          std::vector<trokam::word_value> &sorted);
    };
}

#endif /// TROKAM_SORT_H
