/**************************************************************************

          Copyright (c) Branson Ultrasonics Corporation, 1996-2023

          This program is the property of Branson Ultrasonics Corporation
          Copying of this software is expressly forbidden, without the prior
          written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
 Implements ConfigStatus class, used for interface between of QML and Backend

--------------------------- REVISION HISTORY ------------------------------
 rev1: 16/10/2023 - Initial version.
***************************************************************************/
#ifndef CONFIGSTATUS_H
#define CONFIGSTATUS_H

#include <QObject>

/* Definition of ConfigStatus class */
class ConfigStatus : public QObject
{
private:
    Q_OBJECT
    /* Q_PROPERTY for platform configuration status message for respective welder */
    Q_PROPERTY(QString StatusMsg READ getConfigWelderStatusMsg NOTIFY platformConfigStateUpdated)

    QString m_StatusMsg = "No Welder Connected";                            /* To store status message */

    /* Text Strings for language change support */
    QString m_NoConnText = "No Welder Connected";
    QString m_WelderNameText = "Welder";
    QString m_ConfigFailText = "Configuration Failed";
    QString m_ConfigWaitingText = "Waiting for configuration";

    /* list of language strings */
    QStringList m_LangList;

    /* Enum declaration for index of language strings*/
    enum TextEnum
    {
        NoConnTextIdx = 0,
        WelderNameTextIdx,
        ConfigFailTextIdx,
        ConfigWaitingTextIdx
    };
public:
    ConfigStatus();                      /* Constructor declaration */
    QString getConfigWelderStatusMsg();     /* Update welder status message on HMI*/

signals:
    void platformConfigStateUpdated(int Status);    /* Send signal to HMI to update status */
    void firmwareMismatchNotify();                  /* Send signal to HMI to update status about Firmware Mismatch*/
public slots:
    void onSelectWelderIndexChanged(int WelderId);  /* Slot on Welder index changed and config status update */
    void onFirmwareMismatchDetect(std::string ErrorMessageLog); /* Slot on Firmware mismatch change detected to update QML*/
    void onSignalCurrentLanguageChanged();          /* Slot on language change from HMI */
};

#endif // CONFIGSTATUS_H
