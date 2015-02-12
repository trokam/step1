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
#include <stdio.h>

/// C++
#include <iostream>

/// Trokam
#include "common.h"
#include "desk_log.h"
#include "sort.h"

/***********************************************************************
 * 'data' must be passed by value (i.e. a copy) because this algorithm
 * modified 'data'.
 **********************************************************************/
void trokam::sort::sort_map_by_value(std::map<std::string, int> data,
                                     std::vector<trokam::word_value> &sorted)
{
    int highest= RATIO_THRESHOLD;
    
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    /// Looking for the highest value
    ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    while((data.size() > 2) && (highest >= RATIO_THRESHOLD))
    {
        std::map<std::string, int>::iterator it, top;
        top= data.begin();
        for(it= data.begin(); it != data.end(); it++)
        {
            if(it->second > top->second)
            {
                top= it;

                ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                /// Push the value into the vector
                ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                word_value wv;
                wv.word= it->first;
                wv.value= it->second;
                sorted.push_back(wv);
            }
        }

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// 
        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        highest= top->second;

        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /// Remove the pair just used
        ///~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        data.erase(top);
    }
}
