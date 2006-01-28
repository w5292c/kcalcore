/*
 * This file is part of libsyndication
 *
 * Copyright (C) 2006 Frank Osterfeld <frank.osterfeld@kdemail.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef LIBSYNDICATION_TOOLS_H
#define LIBSYNDICATION_TOOLS_H

#include <ctime>

class QByteArray;
class QString;

namespace LibSyndication {

unsigned int calcHash(const QString& str);

unsigned int calcHash(const QByteArray& array);

QString calcMD5Sum(const QString& str);

/**
 * parses a date string in ISO 8601 extendend format.
 * (date: "2003-12-13",datetime: "2003-12-13T18:30:02.25", 
 * datetime with timezone: "2003-12-13T18:30:02.25+01:00")
 * 
 * @param str a string in ISO 8601 format
 * @return parsed date in seconds since epoch, 0 if no date could
 * be parsed from the string.
 */
time_t parseISODate(const QString& str);

/**
 * parses a date string as defined in RFC 822.
 * (Sat, 07 Sep 2002 00:00:01 GMT)
 * 
 * @param str a string in RFC 822 format
 * @return parsed date in seconds since epoch,  0 if no date could
 * be parsed from the string.
 */
time_t parseRFCDate(const QString& str);

} // namespace LibSyndication

#endif // LIBSYNDICATION_TOOLS_H
