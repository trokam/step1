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

#ifndef TROKAM_SEARCH_H
#define TROKAM_SEARCH_H

/// Wt 
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

/// Trokam
#include "db_handler.h"
 
class search: public Wt::WApplication
{
    public:
        // search(const Wt::WEnvironment& env, trokam::db_handler &db);
        search(const Wt::WEnvironment& env);

    private:
        Wt::WLineEdit *input_text;
        Wt::WText *greeting_;
        void go();
};

#endif /// TROKAM_SEARCH_H
