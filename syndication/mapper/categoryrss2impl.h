/*
 * This file is part of the syndication library
 *
 * Copyright (C) 2006 Frank Osterfeld <osterfeld@kde.org>
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

#ifndef SYNDICATION_MAPPER_CATEGORYRSS2IMPL_H
#define SYNDICATION_MAPPER_CATEGORYRSS2IMPL_H

#include <category.h>
#include <rss2/category.h>

namespace Syndication {
    
class CategoryRSS2Impl;
typedef boost::shared_ptr<CategoryRSS2Impl> CategoryRSS2ImplPtr;

/**
 *
 * @internal
 * @author Frank Osterfeld
 */
class CategoryRSS2Impl : public Syndication::Category
{
    public:

        explicit CategoryRSS2Impl(const Syndication::RSS2::Category& category);
        
        bool isNull() const;
        
        QString term() const;
        
        QString label() const;
        
        QString scheme() const;
        
    private:
        Syndication::RSS2::Category m_category;
};
    
} // namespace Syndication

#endif // SYNDICATION_MAPPER_CATEGORYRSS2IMPL_H
