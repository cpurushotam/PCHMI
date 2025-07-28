/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include <QFile>
#include <QUrl>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <QFont>
#include <QGuiApplication>
#include "languageconfig.h"
#include "jsontreemodel.h"
#include "definition.h"
#include "languageitem.h"

LanguageConfig* LanguageConfig::m_pLanguageObj = nullptr;
LanguageModel* LanguageConfig::m_pLanguageModelObj = nullptr;
/**************************************************************************//**
*
* \brief  Constructor and initialize m_CurrentLanguage, m_LanguageUrl, m_LanguageFiles and m_ErrorIndicator.
*         If there is the beginning running and not any configure folder and QSetting file is detected,
*         the related folder and configure QSetting file will be generated
*         and set the English language as the default language at the beginning.
*         Initialize the language model.
*
* \param  parent : QObject*, because the LanguageConfig class is inherited from QObject.
*
* \return none
*
******************************************************************************/
LanguageConfig::LanguageConfig(QObject *parent)
    : QObject(parent)
    , m_CurrentLanguge(LanguageEnum::ENGLISH_IDX)
    , m_LanguageUrl(lanugageUrl)
	, m_LanguageFiles({"ENGLISH.csv", "FRENCH.csv", "GERMAN.csv", "SPANISH.csv", "KOREAN.csv", "SIMPLIFIEDCHINESE.csv", "ITALIAN.csv", "JAPANESE.csv", "DANISH.csv", "SLOVAKIAN.csv", "POLISH.csv"})
    , m_currentLanguageFile("ENGLISH.csv")
    , m_ErrorIndicator(LanguageConfig::NO_FILE_ERROR)
{
    QDir dir;
    m_pLanguageModelObj = new LanguageModel();
    if(dir.exists(configUrl) == false)
    {
        writeLanguageIndex(m_currentLanguageFile);
    }
}

/**************************************************************************//**
*
* \brief  To get LanguageConfig singleton object.
*         The class is designed to the singleton class so the languageConfig object can used in the everywhere
*         without any new instantiation.
*         And the languageConfig object can be get easily using the this function
*         without any external declaration before using.
*
*
* \param  none
*
* \return Existing LanguageConfig object
*
******************************************************************************/
LanguageConfig *LanguageConfig::getInstance()
{
    if(m_pLanguageObj == nullptr)
    {
        m_pLanguageObj = new LanguageConfig();
    }
    return m_pLanguageObj;
}

/**************************************************************************//**
*
* \brief  To save current language file name to the QSetting file
*
* \param  current Language file name: QString
*
* \return none
*
******************************************************************************/
void LanguageConfig::writeLanguageIndex(const QString currentLanguageFile)
{
    QSettings settings(configUrl, QSettings::IniFormat);
    settings.beginGroup("Configuration");
    settings.setValue("CurrentLanguage", currentLanguageFile);
    settings.endGroup();
}

/**************************************************************************//**
*
* \brief  To get current language file from the QSetting file
*
* \param  none
*
* \return current language file : QString
*
******************************************************************************/
QString LanguageConfig::readLanguageIndex() const
{
    QString currentLanguageFile;
    QSettings settings(configUrl, QSettings::IniFormat);
    settings.beginGroup("Configuration");
    currentLanguageFile = settings.value("CurrentLanguage").value<QString>();
    settings.endGroup();
    return currentLanguageFile;
}

/**************************************************************************//**
*
* \brief  To check and load the specific languge .csv file and use the extracted data
*         to replace the original language text strings.
*
* \param  none
*
* \return If there is any issue happened during the .csv file loading,
*         the CSC_FILE_ERROR code will be set to the m_ErrorIndicator.
*
******************************************************************************/
unsigned char LanguageConfig::loadLanguageStrings()
{
    QString strCurrentLanguageUrl = m_LanguageUrl + m_LanguageFiles.at(m_CurrentLanguge);
    if(JsonTreeModel::getInstance()->readCSVFile(strCurrentLanguageUrl) == false)
        m_ErrorIndicator |= LanguageConfig::CSV_FILE_ERROR;
    else
        m_ErrorIndicator &= ~LanguageConfig::CSV_FILE_ERROR;
    if(m_ErrorIndicator == LanguageConfig::NO_FILE_ERROR)
        JsonTreeModel::getInstance()->replaceItemData();
    return m_ErrorIndicator;
}

/**************************************************************************//**
*
* \brief  To get current language index.
*         The function is to assist the Q_PROPERTY CurrentLanguage so qml can
*         get m_CurrentLanguge directly using CurrentLanguage.
*
* \param  none
*
* \return Current Language Index : int
*
******************************************************************************/
int LanguageConfig::getCurrentLanguage() const
{
    return m_CurrentLanguge;
}


/**************************************************************************//**
*
* \rief  To set current language index.
*        The function is to assist the Q_PROPERTY CurrentLanguage so qml can set
*        m_CurrentLanguage directly using CurrentLanguage.
*
* \param  tmpIndex : int
*
* \return none
*
******************************************************************************/
void LanguageConfig::setCurrentLanguage(int tmpIndex)
{
    if(tmpIndex != m_CurrentLanguge)
    {
        m_CurrentLanguge = tmpIndex;
        if(m_CurrentLanguge > (m_LanguageFiles.size() - 1) || m_CurrentLanguge == -1)
            m_CurrentLanguge = 0;
        m_currentLanguageFile = m_LanguageFiles.at(m_CurrentLanguge);
        writeLanguageIndex(m_currentLanguageFile);
        if((loadLanguageJsonFile() & LanguageConfig::JSON_FILE_ERROR) == LanguageConfig::JSON_FILE_ERROR)
        {
            //TODO Need to push down the message to the dialog screen for the showing.
            qDebug()<<"There are some errors on the json file loading. Error Code:"<< m_ErrorIndicator;
            return;
        }
        if((loadLanguageStrings() & LanguageConfig::CSV_FILE_ERROR) == LanguageConfig::CSV_FILE_ERROR)
        {
            //TODO Need to push down the message to the dialog screen for the showing.
            qDebug()<<"There are some errors on the language file parsing. Error Code:" << m_ErrorIndicator;
            return;
        }
        emit signalCurrentLanguageChanged();
    }
}

/**************************************************************************//**
*
* \brief  To check if the existing json file and all csv language files are available.
*         If there is any missing on the default csv language files, the lost file
*         can be generated automatically.
*         To check if there is any new language CSV file adding.
*         If so, the m_LanguageFile list will be reordered from A-Z sorting.
*
* \param  none
*
* \return none
*
******************************************************************************/
void LanguageConfig::checkLanguageFiles()
{
    QDir dir(m_LanguageUrl);
    if(!dir.exists())
    {
        dir.mkdir(dir.absolutePath());
    }
    for(int i = 0; i < m_LanguageFiles.size(); i++)
    {
        QFile file(m_LanguageUrl + m_LanguageFiles.at(i));
        if(!file.exists())
        {
            if((loadLanguageJsonFile() & LanguageConfig::JSON_FILE_ERROR) == LanguageConfig::NO_FILE_ERROR)
            {
                QString languageUrl = m_LanguageUrl + m_LanguageFiles.at(i);
                JsonTreeModel::getInstance()->writeCSVFile(i, languageUrl);
            }
            else
                break;
        }
    }
    if((m_ErrorIndicator & LanguageConfig::JSON_FILE_ERROR) == LanguageConfig::JSON_FILE_ERROR)
    {
        //TODO Need to push down the message to the dialog screen for the showing.
        qDebug()<<"There are some errors on the Json file loading. Error Code:"<< m_ErrorIndicator;
        return;
    }

    if((loadLanguageCSVFiles() & LanguageConfig::CSV_FILE_ERROR) == LanguageConfig::NO_FILE_ERROR)
    {
        int currentLanguage = -1;
        currentLanguage = m_LanguageFiles.indexOf(m_currentLanguageFile);
        setCurrentLanguage(currentLanguage);
    }
    else
    {
        //TODO Need to push down the message to the dialog screen for the showing.
        qDebug()<<"There are some errors on the CSV file loading. Error Code:"<< m_ErrorIndicator;
    }
}

/**************************************************************************//**
*
* \brief  To load the Json file to the software. If there is any issue happened
*         during the Json file parsing, the bit of the relevant error code will set.
*
* \param  none
*
* \return If there is any issue found on the Json file loading,
*         the JSON_FILE_ERROR code will be set to the m_ErrorIndicator.
*
******************************************************************************/
unsigned char LanguageConfig::loadLanguageJsonFile()
{
    if(JsonTreeModel::getInstance()->loadJson(jsonLanguageUrl) == false)
        m_ErrorIndicator |= LanguageConfig::JSON_FILE_ERROR;
    else
        m_ErrorIndicator &= ~LanguageConfig::JSON_FILE_ERROR;
    return m_ErrorIndicator;
}

/**************************************************************************//**
*
* \brief  To detect how many language files in the language folder and
*         extract the specific language name from the language files to the language Model.
*         If there are any new language file added, the software will extract the new language name from the new file.
*
* \param  None.
*
* \return return the error code in case of any issue happened during the CSV file loading.
*
******************************************************************************/
unsigned char LanguageConfig::loadLanguageCSVFiles()
{
    QStringList fileFilter;
    fileFilter<<"*.csv";
    QDir dir(m_LanguageUrl);
    dir.setNameFilters(fileFilter);
    QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir.entryInfoList(fileFilter));
    int totalFiles = fileInfo->count();
    int iCount = 0;
    m_LanguageFiles.clear();
    m_ErrorIndicator |= LanguageConfig::CSV_FILE_ERROR;
    //TODO Should add some sort of file authentication to make sure a corrupt language is not uploaded. Refer to Item 6135.
    for(iCount = 0; iCount < totalFiles; iCount++)
    {
        QFile file(fileInfo->at(iCount).absoluteFilePath());
        m_LanguageFiles.append(fileInfo->at(iCount).fileName());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<< "Cannot open file for reading: "<< qPrintable(file.errorString());
            break;
        }
        QTextStream in(&file);
        in.readLine();
        QStringList secondData = in.readLine().split(";");
        m_pLanguageModelObj->addNewLanguage(LanguageItem(secondData.at(1), "Open Sans", true, false, iCount));
    }
    if((iCount == totalFiles) && (iCount != 0))
        m_ErrorIndicator &= ~LanguageConfig::CSV_FILE_ERROR;
    m_currentLanguageFile = readLanguageIndex();
    return m_ErrorIndicator;
}

/**************************************************************************//**
*
* \brief  To get the language text strings using the screen index.
*         If there is any error happened, the original sourceList will be
*         return back without any new update.
*
* \param  Screen Index: The screen index has been defined in the Screen Enum;
*         souceList: It is not empty string at the beginning,
*         it always keep all the English language text strings of the current screen.
*         So the function is still able to return the English text strings for the any screen request
*         in case of any issue happened on the languages loading.
*
* \return Return the related language text strings for the screen request.
*
******************************************************************************/
QStringList LanguageConfig::getLanguageStringList(int screenIndex, QStringList sourceList)
{
    if(m_ErrorIndicator == LanguageConfig::NO_FILE_ERROR)
        JsonTreeModel::getInstance()->getItemDatas(screenIndex, sourceList);
    return sourceList;
}

/**************************************************************************//**
*
* \brief  To get the specific screen title using the screen index.
*         If there is any error happened during the files loading, the screen title
*         will keep the original and return back the source name without any new update.
*
* \param  screenIndex : The screen index has been defined in the Screen Enum;
*         sourceName: It is not empty and use the English menu name as the default.
*                     It can avoid the empty string return back in case of there is any issue on the files loading.
*
* \return Return the related screen menu name.
*
******************************************************************************/
QString LanguageConfig::getLanguageMenuName(int screenIndex, QString sourceName)
{
    if(m_ErrorIndicator == LanguageConfig::NO_FILE_ERROR)
        JsonTreeModel::getInstance()->getItemData(screenIndex, sourceName);
    return sourceName;
}

/**************************************************************************//**
*
* \brief The language Model object is the singleton object.
*        The object will be exposed to the QML and register the object pointer in the main.cpp.
*
* \param None
*
* \return The language mode singleton object pointer.
*
******************************************************************************/
LanguageModel *LanguageConfig::getLanguageModelInstance()
{
    if(m_pLanguageModelObj == nullptr)
    {
        m_pLanguageModelObj = new LanguageModel();
    }
    return m_pLanguageModelObj;
}

