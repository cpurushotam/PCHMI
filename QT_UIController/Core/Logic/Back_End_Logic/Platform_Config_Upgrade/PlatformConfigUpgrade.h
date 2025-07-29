/**************************************************************************

     Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

    Responsible for platform config upgrade

--------------------------- REVISION HISTORY ------------------------------
rev1: 23/11/2023 - Initial implementation.

***************************************************************************/
#ifndef PLATFORM_CONFIG_UPGRADE_H
#define PLATFORM_CONFIG_UPGRADE_H

#include <QThread>
#include <QQueue>

#include "BIOWrapper.h"
#include "DataLogger.h"

/* PlatformConfigUpgrade class definition */
class PlatformConfigUpgrade : public QThread
{
    Q_OBJECT

    /* Q_PROPERTY for status message to update screen */
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY updatedScreen)

    // size of TX & RX frame buffer
    static constexpr uint16_t buff_size     = 1024;
    static constexpr uint16_t SLEEP_TIME    = 500;
    static constexpr uint16_t ABORT_COMMAND = 255;

    /* Enum to define states implemented by Config upgrade thread & its transition*/
    typedef enum
    {
        CONFIG_COMM_START_REQUEST = 0,  /* State machine for connection start request */
        CONFIG_COMM_START,         	 /* State machine for starting Communication  */
        CONFIG_COMM_PROCESS,       	 /* State machine for Communication process */
    }CONFIG_THREAD_STATES;

    /* Enum declaration for index of language strings*/
    enum TextEnum
    {
        ConfigANotFoundTextIdx = 0,
        ConfigBNotFoundTextIdx,
        CommErrorTextIdx
    };

    /* Text Strings for language change support */
    QString m_ConfigANotFoundText   = "Config_A.out file not found.";
    QString m_ConfigBNotFoundText   = "Config_B.out file not found.";
    QString m_CommErrorText         = "Communication Error";

    /* list of language strings */
    QStringList m_LangList;

    static QString m_ConfigFilesPath;
    static QString m_ConfigVersion;                     /* Store config version */
    static QString m_ConfigDate;                        /* Store config date */
    QString m_StatusMessage;                            /* Store status message */

    BIOWrapper *m_ptrBIOInstance = nullptr;             /* BIO instance to access BIO wrapper class functions */
    CommConfig *m_ptrSSLConfig = nullptr;               /* Store secure socket configuration */

    uint8_t m_RxBuff [buff_size];                       /* Response buffer */
    uint8_t m_CommandBuff[buff_size];                   /* Command buffer */
    QQueue<int> m_CommandQueue;                         /* Command Queue */

    size_t m_log_id;                                    /* log identifier */
    char m_log_buffer[buff_size_config]={0};            /* log buffer */
    char m_BIOPort [5]={0};

    int StartComm();                                    /* Start secure communication */
    int Process();                                      /* Processing commands */
    int ExitComm();                                     /* Exit secure communication */

public:
    explicit PlatformConfigUpgrade(QObject *parent = nullptr);          /* Constructor declaration */

    // Command interface for the QML actions
    Q_INVOKABLE void sendCommand(int command);                          /* Send command from QML */
    Q_INVOKABLE void setConfigFilesPath(const QString configFilePath);  /* Process on configuration files */
    Q_INVOKABLE QString readConfiVersion();                             /* Read configuration version */
    Q_INVOKABLE QString readConfigDate();                               /* Read configuration Date */

    // Member functions
    void    run();                                                      /* Thread function */
    QString statusMessage();                                            /* Read configuration status message */

    // Static functions
    static QString GetConfigFilesPath();                                /* Read configuration file path from QML.*/
    static void    UpdateConfigDetails(const QString ConfigVersion, const QString ConfigDate);
                                                                        /* Update configuration version and configuration date*/

public slots:
    /* Slot on language change from HMI */
    void onSignalCurrentLanguageChanged();

signals:
    void updatedScreen();                                               /*Send signal to update configuration upgrade screen on HMI */
};

#endif // PLATFORM_CONFIG_UPGRADE_H
