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

#ifndef TROKAM_SHARED_SEARCH_H
#define TROKAM_SHARED_SEARCH_H

/// Wt 
#include <Wt/WApplication>

/// Boost
#include <boost/shared_ptr.hpp>

/// Trokam
#include "db_handler.h"
#include "options.h"
#include "shared_search.h"

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class shared_search
    {
        public:
            shared_search(trokam::options &opt);
            Wt::WApplication* create_application(const Wt::WEnvironment& env);
        
        private:
            boost::shared_ptr<trokam::db_handler> db_shared;
    };
}

#endif /// TROKAM_SHARED_SEARCH_H
