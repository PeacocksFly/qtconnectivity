/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2014 Denis Shienkov <denis.shienkov@gmail.com>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWINLOWENERGYBLUETOOTH_P_H
#define QWINLOWENERGYBLUETOOTH_P_H

#include <QtCore/qstringlist.h>
#include <QtCore/qvector.h>

#include <QtBluetooth/qbluetoothaddress.h>

#include <qt_windows.h>
#include <setupapi.h>

QT_BEGIN_NAMESPACE

namespace WinLowEnergyBluetooth {

#define BLUETOOTH_GATT_FLAG_NONE                        0x00000000
#define BLUETOOTH_GATT_FLAG_CONNECTION_ENCRYPTED        0x00000001
#define BLUETOOTH_GATT_FLAG_CONNECTION_AUTHENTICATED    0x00000002
#define BLUETOOTH_GATT_FLAG_FORCE_READ_FROM_DEVICE      0x00000004
#define BLUETOOTH_GATT_FLAG_FORCE_READ_FROM_CACHE       0x00000008
#define BLUETOOTH_GATT_FLAG_SIGNED_WRITE                0x00000010
#define BLUETOOTH_GATT_FLAG_WRITE_WITHOUT_RESPONSE      0x00000020
#define BLUETOOTH_GATT_FLAG_RETURN_ALL                  0x00000040

typedef enum _BTH_LE_GATT_DESCRIPTOR_TYPE {
    CharacteristicExtendedProperties,
    CharacteristicUserDescription,
    ClientCharacteristicConfiguration,
    ServerCharacteristicConfiguration,
    CharacteristicFormat,
    CharacteristicAggregateFormat,
    CustomDescriptor
} BTH_LE_GATT_DESCRIPTOR_TYPE, *PBTH_LE_GATT_DESCRIPTOR_TYPE;

typedef enum _BTH_LE_GATT_EVENT_TYPE {
    CharacteristicValueChangedEvent
} BTH_LE_GATT_EVENT_TYPE;

typedef struct _BTH_LE_UUID {
    BOOLEAN IsShortUuid;
    union {
        USHORT ShortUuid;
        GUID LongUuid;
    } Value;
} BTH_LE_UUID, *PBTH_LE_UUID;

typedef struct _BTH_LE_GATT_SERVICE {
    BTH_LE_UUID ServiceUuid;
    USHORT AttributeHandle;
} BTH_LE_GATT_SERVICE, *PBTH_LE_GATT_SERVICE;

typedef struct _BTH_LE_GATT_CHARACTERISTIC {
    USHORT ServiceHandle;
    BTH_LE_UUID CharacteristicUuid;
    USHORT AttributeHandle;
    USHORT CharacteristicValueHandle;
    BOOLEAN IsBroadcastable;
    BOOLEAN IsReadable;
    BOOLEAN IsWritable;
    BOOLEAN IsWritableWithoutResponse;
    BOOLEAN IsSignedWritable;
    BOOLEAN IsNotifiable;
    BOOLEAN IsIndicatable;
    BOOLEAN HasExtendedProperties;
} BTH_LE_GATT_CHARACTERISTIC, *PBTH_LE_GATT_CHARACTERISTIC;

typedef struct _BTH_LE_GATT_CHARACTERISTIC_VALUE {
    ULONG DataSize;
    UCHAR Data[1];
} BTH_LE_GATT_CHARACTERISTIC_VALUE, *PBTH_LE_GATT_CHARACTERISTIC_VALUE;

typedef struct _BTH_LE_GATT_DESCRIPTOR {
    USHORT ServiceHandle;
    USHORT CharacteristicHandle;
    BTH_LE_GATT_DESCRIPTOR_TYPE DescriptorType;
    BTH_LE_UUID DescriptorUuid;
    USHORT AttributeHandle;
} BTH_LE_GATT_DESCRIPTOR, *PBTH_LE_GATT_DESCRIPTOR;

typedef struct _BTH_LE_GATT_DESCRIPTOR_VALUE {
    BTH_LE_GATT_DESCRIPTOR_TYPE DescriptorType;
    BTH_LE_UUID DescriptorUuid;
    union {
        struct {
            BOOLEAN IsReliableWriteEnabled;
            BOOLEAN IsAuxiliariesWritable;
        } CharacteristicExtendedProperties;
        struct {
            BOOLEAN IsSubscribeToNotification;
            BOOLEAN IsSubscribeToIndication;
        } ClientCharacteristicConfiguration;
        struct {
            BOOLEAN IsBroadcast;
        } ServerCharacteristicConfiguration;
        struct {
            UCHAR Format;
            UCHAR Exponent;
            BTH_LE_UUID Unit;
            UCHAR NameSpace;
            BTH_LE_UUID Description;
        } CharacteristicFormat;
    };
    ULONG DataSize;
    UCHAR Data[1];
} BTH_LE_GATT_DESCRIPTOR_VALUE, *PBTH_LE_GATT_DESCRIPTOR_VALUE;

typedef struct _BLUETOOTH_GATT_VALUE_CHANGED_EVENT {
    USHORT ChangedAttributeHandle;
    size_t CharacteristicValueDataSize;
    PBTH_LE_GATT_CHARACTERISTIC_VALUE CharacteristicValue;
} BLUETOOTH_GATT_VALUE_CHANGED_EVENT, *PBLUETOOTH_GATT_VALUE_CHANGED_EVENT;

typedef struct _BLUETOOTH_GATT_VALUE_CHANGED_EVENT_REGISTRATION {
    USHORT NumCharacteristics;
    BTH_LE_GATT_CHARACTERISTIC Characteristics[1];
} BLUETOOTH_GATT_VALUE_CHANGED_EVENT_REGISTRATION, *PBLUETOOTH_GATT_VALUE_CHANGED_EVENT_REGISTRATION;

typedef VOID (CALLBACK *PFNBLUETOOTH_GATT_EVENT_CALLBACK)(
        BTH_LE_GATT_EVENT_TYPE EventType,
        PVOID EventOutParameter,
        PVOID Context
        );

typedef ULONG64 BTH_LE_GATT_RELIABLE_WRITE_CONTEXT, *PBTH_LE_GATT_RELIABLE_WRITE_CONTEXT;

struct ServicesDiscoveryResult
{
    ServicesDiscoveryResult();
    QVector<BTH_LE_GATT_SERVICE> services;
    DWORD error;
};

bool isSupported();

ServicesDiscoveryResult startDiscoveryOfPrimaryServices(HANDLE hDevice);

} // namespace WinLowEnergyBluetooth

QT_END_NAMESPACE

#endif // QWINLOWENERGYBLUETOOTH_P_H