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

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Boost signals in use by Wt library is no longer being
/// maintained and is now deprecated. This avoids the warning
/// message during compilation
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef BOOST_SIGNALS_NO_DEPRECATION_WARNING
#define BOOST_SIGNALS_NO_DEPRECATION_WARNING

/// Wt
#include <Wt/WApplication>

/// Trokam
#include "page_search.h"
#include "shared_search.h"

/***********************************************************************
 *
 *
 **********************************************************************/
trokam::shared_search::shared_search(trokam::options &opt): db_shared(new trokam::db_handler(opt))
{}

/***********************************************************************
 *
 *
 **********************************************************************/
Wt::WApplication* trokam::shared_search::create_application(const Wt::WEnvironment& env)
{
    return new page_search(env, db_shared);
}

#endif /// BOOST_SIGNALS_NO_DEPRECATION_WARNING
