/*
    This file is part of libkresources.

    Copyright (c) 2002 Tobias Koenig <tokoe@kde.org>
    Copyright (c) 2002 Jan-Pascal van Best <janpascal@vanbest.org>
    Copyright (c) 2003 Cornelius Schumacher <schumacher@kde.org>

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
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include <kdebug.h>
#include <klocale.h>
#include <ksimpleconfig.h>
#include <kstandarddirs.h>
#include <kstaticdeleter.h>

#include <qfile.h>

#include "resource.h"
#include "factory.h"

using namespace KRES;

QDict<Factory> *Factory::mSelves = 0;
static KStaticDeleter< QDict<Factory> > staticDeleter;

Factory *Factory::self( const QString& resourceFamily )
{
  kdDebug(5650) << "Factory::self()" << endl;

  Factory *factory = 0;
  if ( !mSelves )
    staticDeleter.setObject( mSelves, new QDict<Factory> );

  factory = mSelves->find( resourceFamily );

  if ( !factory ) {
    factory = new Factory( resourceFamily );
    mSelves->insert( resourceFamily, factory );
  } 
  return factory;
}

Factory::Factory( const QString& resourceFamily ) :
  mResourceFamily( resourceFamily )
{
  mResourceList.setAutoDelete( true );

  QStringList list = KGlobal::dirs()->findAllResources( "data", 
      "kresources/" + mResourceFamily + "/*.desktop", true, true );
  kdDebug(5650) << "Factory(): Resource list" << endl;
  for ( QStringList::iterator it = list.begin(); it != list.end(); ++it ) {
    kdDebug() << "-- " << *it << endl;

    KSimpleConfig config( *it, true );

    if ( !config.hasGroup( "Misc" ) || !config.hasGroup( "Plugin" ) )
      continue;

    ResourceInfo* info = new ResourceInfo;

    config.setGroup( "Plugin" );
    QString type = config.readEntry( "Type" );
    kdDebug(5650) << "Found plugin of type " << type << endl;
    info->library = config.readEntry( "X-KDE-Library" );
	
    config.setGroup( "Misc" );
    info->nameLabel = config.readEntry( "Name" );
    info->descriptionLabel = config.readEntry( "Comment", i18n( "No description available." ) );

    mResourceList.insert( type, info );
  }
}

Factory::~Factory()
{
  mResourceList.clear();
}

QStringList Factory::resourceTypeNames() const
{
  kdDebug(5650) << "Factory::resourceTypeNames()" << endl;
  QStringList retval;
	
  QDictIterator<ResourceInfo> it( mResourceList );
  for ( ; it.current(); ++it )
    retval << it.currentKey();

  return retval;
}

ConfigWidget *Factory::configWidget( const QString& type, QWidget *parent )
{
  ConfigWidget *widget = 0;

  if ( type.isEmpty() )
    return 0;

  QString libName = mResourceList[ type ]->library;

  KLibrary *library = openLibrary( libName );
  if ( !library )
    return 0;

  void *widget_func = library->symbol( "config_widget" );

  if ( widget_func ) {
    kdDebug(5650) << "Creating config widget for type " << type << endl;
    widget = ((ConfigWidget* (*)(QWidget *wdg))widget_func)( parent );
  } else {
    kdDebug(5650) << "'" << libName << "' is not a " + mResourceFamily + " plugin." << endl;
    return 0;
  }

  return widget;
}

ResourceInfo *Factory::info( const QString &type )
{
  if ( type.isEmpty() )
    return 0;
  else
    return mResourceList[ type ];
}

Resource *Factory::resource( const QString& type, const KConfig *config )
{
  kdDebug(5650) << "Factory::resource( " << type << ", config)" << endl;
  Resource *resource = 0;

  if ( type.isEmpty() )
    return 0;

  ResourceInfo *info = mResourceList.find( type );
  if ( !info ) {
    kdDebug(5650) << "Factory::resource(): No info for type '" << type
              << "'" << endl;
    return 0;
  }

  QString libName = info->library;

  KLibrary *library = openLibrary( libName );
  if ( !library )
    return 0;

  void *resource_func = library->symbol( "resource" );

  if ( resource_func ) {
    kdDebug(5650) << "Creating resource of type " << type << endl;
    resource = ((Resource* (*)(const KConfig *))resource_func)( config );
    resource->setType( type );
  } else {
    kdDebug(5650) << "'" << libName << "' is not a " + mResourceFamily + " plugin." << endl;
    return 0;
  }

  kdDebug(5650) << "Created resource of type " << type << endl;
  return resource;
}

KLibrary *Factory::openLibrary( const QString& libName )
{
  KLibrary *library = 0;

  QString path = KLibLoader::findLibrary( QFile::encodeName( libName ) );

  if ( path.isEmpty() ) {
    kdDebug(5650) << "No resource plugin library was found!" << endl;
    return 0;
  }

  library = KLibLoader::self()->library( QFile::encodeName( path ) );

  if ( !library ) {
    kdDebug(5650) << "Could not load library '" << libName << "'" << endl;
    return 0;
  }

  return library;
}
