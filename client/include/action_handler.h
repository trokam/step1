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

#ifndef TROKAM_ACTION_HANDLER_H
#define TROKAM_ACTION_HANDLER_H

/// C++
#include <string>

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class action_handler
    {
        public:
            action_handler(trokam::options &opt);

            void perform_on_server(const std::string &request,
                                         std::string &answer);

            void perform_on_server(const std::string &request,
                                   const Json::Value &data,
                                         std::string &answer);

            void perform_on_server(const Json::Value &bundle,
                                         Json::Value &answer);
        private:
            std::string server_address;
    };
}

#endif /// TROKAM_ACTION_HANDLER_H
