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

#ifndef TROKAM_LANGUAGE_H
#define TROKAM_LANGUAGE_H

/// C++
#include <string>

/// libtextcat
#include "libexttextcat/textcat.h"

/// Trokam
#include "file_management.h"

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class language
    {
        public:
            static std::string detect(std::string &text);
    };
}

#endif /// TROKAM_LANGUAGE_H
