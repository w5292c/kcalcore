/*
  This file is part of kdepimlibs.
  Copyright (c) 2006 Allen Winter <winter@kde.org>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#ifndef KMIME_EXPORT_H
#define KMIME_EXPORT_H

#include <kdemacros.h>

#ifndef KMIME_EXPORT
# if defined(KDEPIM_STATIC_LIBS)
   /* No export/import for static libraries */
#  define KMIME_EXPORT
# elif defined(MAKE_KMIME_LIB)
   /* We are building this library */
#  define KMIME_EXPORT KDE_EXPORT
# else
   /* We are using this library */
#  define KMIME_EXPORT KDE_IMPORT
# endif
#endif

# ifndef KMIME_EXPORT_DEPRECATED
#  define KMIME_EXPORT_DEPRECATED KDE_DEPRECATED KMIME_EXPORT
# endif

/**
  @namespace KMime

  @brief
  Contains all the KMIME library global classes, objects, and functions.
*/

#endif
