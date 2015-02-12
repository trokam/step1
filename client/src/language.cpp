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

/// C++
#include <iostream>

/// Boost
#include <boost/algorithm/string.hpp>

/// Trokam
#include "desk_log.h"
#include "language.h"

/***********************************************************************
 *
 **********************************************************************/
std::string trokam::language::detect(std::string &text)
{
    void *h;

    h= textcat_Init("/usr/share/libexttextcat/fpdb.conf" );
    if(!h)
    {
        LOG(FATAL, "unable to init libexttextcat");
        exit(1);
    }

    std::string lang(textcat_Classify(h, text.c_str(), text.length()));
    textcat_Done(h);
    
    boost::replace_all(lang, "--utf8]", " ");
    boost::replace_all(lang, "[", " ");    

    return lang;
}
