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

#ifndef TROKAM_WEB_CRUNCHER_H
#define TROKAM_WEB_CRUNCHER_H

/// C
#include <cstdlib>
#include <signal.h>

/// C++
#include <string>

/// Trokam
#include "file_converter.h"
#include "options.h"
#include "url_processor.h"
#include "web_handler.h"
#include "action_handler.h"
#include "word_stats.h"

/***********************************************************************
 *
 *
 **********************************************************************/
namespace trokam
{
    class web_cruncher
    {
        public:
            web_cruncher(trokam::options &options,
                         std::string cruncher_id,
                         std::string instance);
            ~web_cruncher();
            void word_stats();
            void full_analysis();

        private:

            trokam::options opt;        
            std::string cruncher_id;
            std::string instance;
            std::string base_directory;
            std::string directory_files;
            std::string original_content_file;
            std::string file_content_text;

            trokam::web_handler web;
            trokam::url_processor up;
            trokam::file_converter fc;
            trokam::action_handler ah;
            trokam::word_stats ws;

            static bool stop;
            static void ctrl_c_signal(int signal);
    };
}
#endif  /// TROKAM_WEB_CRUNCHER_H
