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

#ifndef TROKAM_COMMON_H
#define TROKAM_COMMON_H

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Server address
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SERVER            "http://www.trokam.com/action"

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Configuration files
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SERVER_CONFIG_FILE  "/usr/local/etc/trokam/server.cfg"

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Numerical constants
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define RATIO_THRESHOLD   300
#define FAIL              0
#define SUCCESS           1

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// String constants
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define ACTION            "action"
#define ANALYSE_PAGE      "analyse_page"
#define ANALYSIS_RESULT   "analysis_result"
#define BODY              "body"
#define CONTENT_TYPE      "Content-type: text/html\r\n\r\n"
#define CRUNCHER_ID       "cruncher_id"
#define DATA              "data"
#define EMPTY             ""
#define FAILURE           "failure"
#define FAIL_TYPE         "fail_type"
#define FULL_PAGE_REPORT  "full_page_report"
#define FULL_REPORT       "full_report"
#define GET_TASK          "get_task"
#define INSTANCE          "instance"
#define LANGUAGE          "language"
#define NOT_VALID         "not_valid"
#define NO_VALID_USER     "no_valid_user"  
#define NO_TASK_ASSIGNED  "no_task_assigned"
#define OK                "ok"
#define PERFORM           "perform"
#define RELEVANT          "relevant"
#define REPLY             "reply"
#define SPACE             " "
#define STATUS            "status"
#define TASK_ID           "task_id"
#define TASK_TYPE         "task_type"
#define TITLE             "title"
#define URL               "url"
#define URLS              "urls"
#define VEREDICT          "veredict"
#define VERIFY_RESULT     "verification_result"
#define WORDS             "words"

#endif /// TROKAM_COMMON_H
