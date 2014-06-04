/***************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Copyright (C) 2013 BlackBerry Limited all rights reserved
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QLOWENERGYCHARACTERISTICINFO_H
#define QLOWENERGYCHARACTERISTICINFO_H
#include <QtCore/QSharedPointer>
#include <QtCore/QObject>
#include <QtBluetooth/qbluetooth.h>
#include <QtBluetooth/QBluetoothUuid>
#include <QtBluetooth/QLowEnergyDescriptorInfo>

QT_BEGIN_NAMESPACE

class QBluetoothUuid;
class QLowEnergyCharacteristicInfoPrivate;

//TODO rename class to QLowEnergyCharacteristic
class Q_BLUETOOTH_EXPORT QLowEnergyCharacteristicInfo
{
    friend class QLowEnergyController;
    friend class QLowEnergyControllerPrivate;
public:

    enum PropertyType {
        Unknown = 0x00,
        Broadcasting = 0x01,
        Read = 0x02,
        WriteNoResponse = 0x04,
        Write = 0x08,
        Notify = 0x10,
        Indicate = 0x20,
        WriteSigned = 0x40,
        ExtendedProperty = 0x80
    };
    Q_DECLARE_FLAGS(PropertyTypes, PropertyType)

    QLowEnergyCharacteristicInfo();
    QLowEnergyCharacteristicInfo(const QBluetoothUuid &uuid);
    QLowEnergyCharacteristicInfo(const QLowEnergyCharacteristicInfo &other);
    ~QLowEnergyCharacteristicInfo();

    QLowEnergyCharacteristicInfo &operator=(const QLowEnergyCharacteristicInfo &other);

    QString name() const;

    QBluetoothUuid uuid() const;

    void setValue(const QByteArray &value);
    QByteArray value() const;

    QLowEnergyCharacteristicInfo::PropertyTypes properties() const;
    QLowEnergyHandle handle() const;

    bool isNotificationCharacteristic() const;

    QList<QLowEnergyDescriptorInfo> descriptors() const;

    bool isValid() const;

protected:
    QSharedPointer<QLowEnergyCharacteristicInfoPrivate> d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QLowEnergyCharacteristicInfo::PropertyTypes)

QT_END_NAMESPACE

#endif // QLOWENERGYCHARACTERISTICINFO_H
