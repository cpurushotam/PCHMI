/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef LANGUAGEDEF_H
#define LANGUAGEDEF_H
#include <QObject>
#include <QQmlEngine>

#define LANGUAGEENUM_URI_NAME "Com.Branson.LanguageEnum"
#define LANGUAGEENUM_QML_MAJOR_VERSION 1
#define LANGUAGEENUM_QML_MINOR_VERSION 0
#define LANGUAGEENUM_QML_NAME "LanguageEnum"

class LanguageEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(LANGUAGEINDEX)
public:
    enum LANGUAGEINDEX
    {
        NONE_IDX = -1,
        ENGLISH_IDX = 0,
        FRENCH_IDX,
        GERMAN_IDX,
        SPANISH_IDX,
        KOREAN_IDX,
        SIMPLIFIEDCHINESE_IDX,
        ITALIAN_IDX,
        JAPANESE_IDX,
        DANISH_IDX,
        SLOVAKIAN_IDX,
        POLISH_IDX,
        TOTAL_IDX,
    };

    static void registerQMLType()
    {
        qmlRegisterType<LanguageEnum>(LANGUAGEENUM_URI_NAME,
                                       LANGUAGEENUM_QML_MAJOR_VERSION,
                                       LANGUAGEENUM_QML_MINOR_VERSION,
                                       LANGUAGEENUM_QML_NAME);
    }
};
#endif // LANGUAGEDEF_H
