/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include <QDebug>
#include "languagemodel.h"
/**************************************************************************//**
*
* \brief Constructor and initialize language list that will save all the peroperties of each language.
*
* \param QObject* parent
*
* \return None
*
******************************************************************************/
LanguageModel::LanguageModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_languageList.clear();
}

/**************************************************************************//**
*
* \brief Define which properties need to expose to QML under the Language Model.
*        Generate a link table between Model and list data.
*
* \param None
*
* \return Role QHash.
*
******************************************************************************/
QHash<int, QByteArray> LanguageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[LanguageRoles::NameRole] = "itemName";
    roles[LanguageRoles::FontFamilyRole] = "fontFamily";
    roles[LanguageRoles::IndexRole] = "itemIndex";
    return roles;
}

/**************************************************************************//**
*
* \brief Qt Item model standard interface
*        The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*        Note: This function can be invoked via the meta-object system and from QML.
*        To get the language list size number.
*
* \param It can be ignored in here.
*
* \return Return language list size.
*
******************************************************************************/
int LanguageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_languageList.count();
}

/**************************************************************************//**
*
* \brief Qt Item model standard interface
*        The more detailed explanation need to refer to QAbstractListModel that we inherited from.
*        To locate at the specific object using the Model Index and get the data from the specific object then.
*        Note: This function can be invoked via the meta-object system and from QML.
*        Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
*
* \param index.row should be in the range of the language list.
*
* \return the property data using the role index that has been defined in the RoleNames function.
*
******************************************************************************/
QVariant LanguageModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_languageList.count())
        return QVariant();
    const LanguageItem &languageObj = m_languageList[index.row()];
    switch (role)
    {
    case IndexRole:
        return languageObj.getItemIndex();
        break;
    case NameRole:
        return languageObj.getItemName();
        break;
    case FontFamilyRole:
        return languageObj.getFontFamily();
        break;
    case VisibleRole:
        return languageObj.getItemVisible();
        break;
    case CheckedRole:
        return languageObj.getItemChecked();
        break;
    }
    return QVariant();
}

/**************************************************************************//**
*
* \brief To append a new language object to the language list.
*
* \param language item object
*
* \return none
*
******************************************************************************/
void LanguageModel::addNewLanguage(const LanguageItem &languageItem)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_languageList.append(languageItem);
    endInsertRows();
}

/**************************************************************************//**
*
* \brief To get the language name from language list using the language index
*
* \param current language index.
*
* \return language name
*
******************************************************************************/
QString LanguageModel::getLanguageName(int currentLanguageIndex)
{
    QString strLanguage = "";
    if((currentLanguageIndex < m_languageList.size()) && (currentLanguageIndex != -1))
        strLanguage = m_languageList.at(currentLanguageIndex).getItemName();
    else
        strLanguage = m_languageList.at(0).getItemName();
    return strLanguage;
}

/**************************************************************************//**
*
* \brief To clear the language list
*
* \param None.
*
* \return None.
*
******************************************************************************/
void LanguageModel::clearLanguages()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_languageList.clear();
    endRemoveRows();
}


