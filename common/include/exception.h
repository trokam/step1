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

#ifndef TROKAM_EXCEPTION_H
#define TROKAM_EXCEPTION_H

/// C++
#include <string>
#include <iostream>
#include <exception>

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class exception: public std::exception
    {
        private:
            std::string description;

        public:
            exception(std::string what_happened);
            ~exception() throw() {}
            virtual const char* what() const throw()
            {
                return description.c_str();
            }
    };
}

#endif /// TROKAM_EXCEPTION_H
