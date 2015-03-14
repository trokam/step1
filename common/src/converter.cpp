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

/// C
#include <math.h>

/// C++
#include <sstream>
#include <iostream>
#include <iomanip>

/// Trokam
#include "converter.h"

/***********************************************************************
 *
 *
 **********************************************************************/
bool trokam::converter::string_to_bool(std::string text)
{
    std::istringstream stream(text);
    bool v= false;

    try
    {
        stream >> v;
    }
    catch(std::exception &se)
    {
        /// throw(e);
    }
    return v;
}

/***********************************************************************
 *
 *
 **********************************************************************/
int trokam::converter::string_to_int(std::string text)
{
    std::istringstream stream(text);
    int v= 0;

    try
    {
        stream >> v;
    }
    catch(std::exception &se)
    {
        /// throw(e);
    }
    return v;
}

/***********************************************************************
 *
 *
 **********************************************************************/
uint trokam::converter::string_to_uint(std::string text)
{
    std::istringstream stream(text);
    uint v= 0;

    try
    {
        stream >> v;
    }
    catch(std::exception &se)
    {
        /// throw(e);
    }
    return v;
}

/***********************************************************************
 *
 *
 **********************************************************************/
long trokam::converter::string_to_long(std::string text)
{
    std::istringstream stream(text);
    long v= 0;

    try
    {
        stream >> v;
    }
    catch(std::exception &se)
    {
        /// throw(e);
    }
    return v;
}

/***********************************************************************
 *
 *
 **********************************************************************/
float trokam::converter::string_to_float(std::string text)
{
    std::istringstream stream(text);
    float v= 0;

    try
    {
        stream >> v;
    }
    catch(std::exception &se)
    {
        /// throw(e);
    }
    return v;    
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::converter::to_string(uint value)
{
    std::stringstream qStream;

    qStream << value;
    return qStream.str();
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::converter::to_string(int value)
{
    std::stringstream qStream;

    qStream << value;
    return qStream.str();
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::converter::to_string(bool value)
{
    std::string text;

    if(value)
    {
        text= "true";
    }
    else
    {
        text= "false";
    }
    return text;
}

/***********************************************************************
 *
 *
 **********************************************************************/
std::string trokam::converter::to_string(float value, int precision)
{
    std::stringstream qStream;

    qStream << std::fixed << std::setprecision(precision) << value;
    return qStream.str();
}
