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

#ifndef TROKAM_CONVERTER_H
#define TROKAM_CONVERTER_H

/// C++
#include <string>

typedef unsigned int uint;

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class converter
    {
        public:
            static bool string_to_bool(std::string text);
            static int string_to_int(std::string text);
            static uint string_to_uint(std::string text);
            static long string_to_long(std::string text);
            static float string_to_float(std::string text);

            static std::string to_string(uint value);
            static std::string to_string(int value);
            static std::string to_string(bool value);
            static std::string to_string(float value, int precision= 4);
    };
}

#endif /// TROKAM_CONVERTER_H
