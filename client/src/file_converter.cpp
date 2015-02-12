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
#include <cstdlib>
#include <stdio.h>

/// C++
#include <string>
#include <iostream>

/// Magic
#include <magic.h>

/// Trokam
#include "desk_log.h"
#include "file_converter.h"

/***********************************************************************
 *
 **********************************************************************/
bool trokam::file_converter::convert_to_text(std::string input_file_name, std::string output_file_name)
{
    magic_t mg= magic_open(MAGIC_CONTINUE|MAGIC_ERROR|MAGIC_MIME);
    magic_load(mg, NULL);
    std::string type(magic_file(mg, input_file_name.c_str()));
    magic_close(mg);

    LOG(DEBUG, "file type: " << type);

    if((type == "text/html; charset=utf-8") ||
       (type == "text/html; charset=us-ascii"))
    {
        std::string command= "html2text -utf8 -style pretty -o " + output_file_name + " " + input_file_name;
        system(command.c_str());
        return true;
    }

    if(type.substr(0,9) == "text/html")
    {
        std::string command= "html2text -ascii -style pretty -o " + output_file_name + " " + input_file_name;
        system(command.c_str());
        return true;
    }

    LOG(WARNING, "file type UNKNOWN: " << type);
    LOG(WARNING, "file subtype UNKNOWN: " << type.substr(0,9));
    return false;
}

