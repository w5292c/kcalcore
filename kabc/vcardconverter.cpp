/*
    This file is part of libkabc.
    Copyright (c) 2002 Tobias Koenig <tokoe@kde.org>

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

#include "vcardconverter.h"
#include "vcardtool.h"

using namespace KABC;

VCardConverter::VCardConverter()
  : d( 0 )
{
}

VCardConverter::~VCardConverter()
{
}

QByteArray VCardConverter::exportVCard( const Addressee &addr, Version version ) const
{
  Addressee::List list;
  list.append( addr );

  return exportVCards( list, version );
}

QByteArray VCardConverter::exportVCards( const Addressee::List &list, Version version ) const
{
  VCardTool tool;

  return tool.exportVCards( list, ( version == v3_0 ? VCard::v3_0 : VCard::v2_1 ) );
}

QByteArray VCardConverter::createVCard( const Addressee &addr, Version version ) const
{
  Addressee::List list;
  list.append( addr );

  return createVCards( list, version );
}

QByteArray VCardConverter::createVCards( Addressee::List list, Version version ) const
{
  VCardTool tool;

  return tool.createVCards( list, ( version == v3_0 ? VCard::v3_0 : VCard::v2_1 ) );
}

Addressee VCardConverter::parseVCard( const QByteArray &vcard ) const
{
  Addressee::List list = parseVCards( vcard );

  return list.isEmpty() ? Addressee() : list[ 0 ];
}

Addressee::List VCardConverter::parseVCards( const QByteArray &vcard ) const
{
  VCardTool tool;

  return tool.parseVCards( vcard );
}

/* Helper functions */

QString KABC::dateToVCardString( const QDateTime &dateTime )
{
  return dateTime.toString( QLatin1String( "yyyyMMddThhmmssZ" ) );
}

QString KABC::dateToVCardString( const QDate &date )
{
  return date.toString( QLatin1String( "yyyyMMdd" ) );
}

QDateTime KABC::VCardStringToDate( const QString &dateString )
{
  QDate date;
  QTime time;
  QString d( dateString );

  d = d.remove( QLatin1Char( '-' ) ).remove( QLatin1Char( ':' ) );

  if ( d.length() >= 8 ) {
    date = QDate( d.mid( 0, 4 ).toUInt(), d.mid( 4, 2 ).toUInt(), d.mid( 6, 2 ).toUInt() );
  }

  if ( d.length() > 9 && d[ 8 ].toUpper() == QLatin1Char( 'T' ) ) {
    time = QTime( d.mid( 9, 2 ).toUInt(), d.mid( 11, 2 ).toUInt(), d.mid( 13, 2 ).toUInt() );
  }

  return QDateTime( date, time );
}
