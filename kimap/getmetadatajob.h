/*
    Copyright (c) 2009 Andras Mantia <amantia@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef KIMAP_GETMETADATAJOB_H
#define KIMAP_GETMETADATAJOB_H

#include "kimap_export.h"

#include "metadatajobbase.h"

namespace KIMAP {

class Session;
class Message;
class GetMetaDataJobPrivate;

class KIMAP_EXPORT GetMetaDataJob : public MetaDataJobBase
{
  Q_OBJECT
  Q_DECLARE_PRIVATE(GetMetaDataJob)

  friend class SessionPrivate;

  public:
    GetMetaDataJob( Session *session );
    virtual ~GetMetaDataJob();

    enum Depth {
      NoDepth = 0,
      OneLevel,
      AllLevels
    };

    Q_DECLARE_FLAGS(Depths, Depth)

    /**
     * Add an entry name to query, if the job is operating in Annotatemore mode, the attribute names need to be specified with
     * addAttribute.
     * @param entry the metadata entry name
     */
    void addEntry(const QByteArray &entry);

    /**
     * Add an attribute value name to query, if the job is operating in Annotatemore mode. In Metadata mode it is ignored.
     * @param attribute the metadata entry name
     */
    void addAttribute(const QByteArray &attribute);

    /**
     * Only entry values that are less than or equal in octet size to the specified @param size limit are returned. In
     * Annotatemore mode, this setting is  ignored.
     */
    void setMaxSize(qint32 size);

    /**
     * Default is NoDepth. In Annotatemore mode, this setting is  ignored.
     * @param depth
     */
    void setDepth(Depth depth);

    /**
     * Get the metadata in Metadata mode.
     * @param mailBox
     * @param entry
     * @return
     */
    QByteArray metaData(const QByteArray &mailBox, const QByteArray &entry);

    /**
     * Get the metadata in Annotatemore mode. If used in Metadata mode, @param attribute is ignored.
     * @param mailBox
     * @param entry
     * @param attribute
     * @return
     */
    QByteArray metaData(const QByteArray &mailBox, const QByteArray &entry, const QByteArray &attribute);

  protected:
    virtual void doStart();
    virtual void doHandleResponse( const Message &response );

};

}

#endif
