/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares MultiwelderInterface Class - responsible for interact between frontend and backend
                                       related to multiwelder.

--------------------------- REVISION HISTORY ------------------------------
 rev1: 31/07/2023 - Initial implementation.
 rev2: 16/10/2023 - Added signal on welder selection changed from HMI
***************************************************************************/

#ifndef MULTIWELDERINTERFACE_H
#define MULTIWELDERINTERFACE_H

#include <QObject>
#include "SystemConfigurationGeneral_MB.h"

/* MultiwelderInterface Class definition */
class MultiwelderInterface : public QObject
{
    // Declaration of Q_OBJECT for signals and slots mechanism
    Q_OBJECT

    /* Q_PROPERTY for welder connected */
    Q_PROPERTY(QString m_WelderConnected READ GetWelderConnected NOTIFY welderConnectedChanged)

    Q_PROPERTY(int m_welderId READ GetWelderId NOTIFY welderConnectedChanged)

    /* Q_PROPERTY for welder disconnected */
    Q_PROPERTY(QString m_welderDisconnect READ GetwelderDisconnect NOTIFY welderDisconnectChanged)

    /* Connected welder IPAddress*/
    QString m_WelderConnected;

    /* Disconnected Welder IpAddress*/
    QString m_welderDisconnect;

    /* Connected welder Id */
    int m_welderId = -1;

    /* Selected Welder */
    static int m_ActiveWelder;

    SystemConfigurationGeneral_MB * m_SysConfgGen;           /* Pointer of SystemConfigurationGeneral_MB class */
    int m_ActiveWelderId = -1;                              /* Variable to store active Welder Id                */
    QString m_WelderName;

public:
    //Constructor
    explicit MultiwelderInterface(QObject *parent = nullptr);

    /* Return connected welder IP Address */
    QString GetWelderConnected() const;

    /* Return connected welder IP Address */
    int GetWelderId() const;

    /* Return disconnected welder IP Address */
    QString GetwelderDisconnect() const;

    /* Return Active Welder selected*/
    static int GetActiveWelder();

signals:
    /* Send signal to HMI on welder connected */
    void welderConnectedChanged();

    /* Send signal to HMI on welder disconnected */
    void welderDisconnectChanged();

    /* Send signal to HMI on welder disconnected */
    void welderIdConnectChanged();

    /* Send signal on welder selection changed from HMI */
    void selectWelderIndexChanged(int selectedWelder);

    /* Send signal on welder selection changed from HMI */
    void welderNameReceived(int welderId, QString welderName);

public slots:
    /* Implementation for reading the Active welders IpAddress connected in network. */
    void OnPeerConnected(uint16_t welderId, char *IpAddr);

    /* Implementation for reading the Disconnected welder's IpAddress connected in network. */
    void OnwelderRemoved(char *IpAddr);

    /* Set Active Welder from qml */
    void setActiveWelder(int activeWelder);

    void OnfetchNamesForWelder(SystemConfigurationGeneral_MB *SysConfgGenData_Obj, int WelderId);
};

#endif // MULTIWELDERINTERFACE_H*/
