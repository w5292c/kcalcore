/*
  Copyright (c) 2006 - 2007 Volker Krause <vkrause@kde.org>

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

#ifndef MAILTRANSPORT_TRANSPORTCOMBOBOX_H
#define MAILTRANSPORT_TRANSPORTCOMBOBOX_H

#include <mailtransport/mailtransport_export.h>
#include <mailtransport/transportbase.h>

#include <KDE/KComboBox>

class TransportComboBoxPrivate;

namespace MailTransport {

/**
  A combo-box for selecting a mail transport.
  It is updated automatically when transports are added, changed, or removed.
*/
class MAILTRANSPORT_EXPORT TransportComboBox : public KComboBox
{
  Q_OBJECT

  public:
    /**
      Creates a new mail transport selection combo box.
      @param parent The paren widget.
    */
    TransportComboBox( QWidget *parent = 0 );

    ~TransportComboBox();

    /**
      Returns identifier of the currently selected mail transport.
    */
    int currentTransportId() const;

    /**
      Selects the given transport.
      @param transportId The transport identifier.
    */
    void setCurrentTransport( int transportId );

    /**
      Returns the type of the selected transport.
    */
    TransportBase::EnumType::type transportType() const;

  private Q_SLOTS:
    void fillComboBox();

  private:
    TransportComboBoxPrivate *const d;
};

} // namespace MailTransport

#endif // MAILTRANSPORT_TRANSPORTCOMBOBOX_H
