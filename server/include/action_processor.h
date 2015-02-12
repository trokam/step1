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

#ifndef TROKAM_ACTION_PROCESSOR_H
#define TROKAM_ACTION_PROCESSOR_H

/// C++
#include <string>
#include <map>
#include <vector>

/// JsonCpp
#include "jsoncpp/json/json.h"

/// Trokam
#include "db_handler.h"
#include "options.h"
#include "postgresql.h"

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class action_processor
    {
        public:
            action_processor(trokam::options &opt);
            ~action_processor();

            void process(trokam::db_handler &db,
                         const Json::Value &incoming,
                               Json::Value &outgoing);
        private:
            // trokam::db_handler db;
    };
}

#endif /// TROKAM_ACTION_PROCESSOR_H
