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

#ifndef TROKAM_FILE_MANAGEMENT_H
#define TROKAM_FILE_MANAGEMENT_H

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class file_management
    {
        public:
            static std::string get_file_contents(std::string filename);
            static void get_file_contents(const std::string &file_name, std::string &content);
            static bool is_empty(std::string filename);
            static std::string get_first_line(std::string file_name);
            static void save_file(const std::string &file_name, const std::string &content);
    };
}

#endif  /// TROKAM_FILE_MANAGEMENT_H
