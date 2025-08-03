/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef LANGUAGECONFIG_H
#define LANGUAGECONFIG_H

#include <QObject>

#include "languagedef.h"
#include "languagemodel.h"

class LanguageConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int CurrentLanguage READ getCurrentLanguage WRITE setCurrentLanguage NOTIFY signalCurrentLanguageChanged)
public:
    enum FileLoadError {
        NO_ERROR =          0x00,
        JSON_FILE_ERROR =   0x01,
        CSV_FILE_ERROR =    0x02,
    };

private:
    void writeLanguageIndex(const QString currentLanguageFile);
    QString readLanguageIndex() const;
    unsigned char loadLanguageStrings();
    unsigned char loadLanguageJsonFile();
    unsigned char loadLanguageCSVFiles();
public:
    static LanguageConfig* getInstance();

    int getCurrentLanguage() const;
    void setCurrentLanguage(int tmpIndex);

protected:
    explicit LanguageConfig(QObject *parent = nullptr);
private:
    static LanguageConfig* m_pLanguageObj;
    static LanguageModel* m_pLanguageModelObj;
    int m_CurrentLanguge;
    const QString m_LanguageUrl;
    QStringList m_LanguageFiles;
    QString m_currentLanguageFile;
	unsigned char m_ErrorIndicator;

public:
    void checkLanguageFiles();
    Q_INVOKABLE QStringList getLanguageStringList(int screenIndex, QStringList sourceList);
    Q_INVOKABLE QString getLanguageMenuName(int screenIndex, QString sourceName);
    Q_INVOKABLE LanguageModel *getLanguageModelInstance();

signals:
    void signalCurrentLanguageChanged();
};

#endif // LANGUAGECONFIG_H
