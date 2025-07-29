/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include "languageitem.h"
/**************************************************************************//**
*
* \brief Constructor and initialize as following variables...
*        1. m_ItemName;
*        2. m_FontFamily;
*        3. m_ItemVisible;
*        4. m_ItemChecked;
*        5. m_ItemIndex;
*
* \param 1. itemName: language name;
*        2. fontFamily: it defines the font family for the specific language on the screen showing.
*        3. itemVisible: it defines if the language need to display on the screen or hidden.
*        4. itemChecked: it defines if the language is the selected or not.
*        5. itemIndex: the language index.
*
* \return none
*
******************************************************************************/
LanguageItem::LanguageItem(const QString &itemName, const QString &fontFamily,
                           const bool &itemVisible, const bool &itemChecked,
                           const int &itemIndex)
    :m_ItemName(itemName)
    , m_FontFamily(fontFamily)
    , m_ItemVisible(itemVisible)
    , m_ItemChecked(itemChecked)
    , m_ItemIndex(itemIndex)
{

}

/**************************************************************************//**
*
* \brief To get the language name.
*
* \param none
*
* \return Language name.
*
******************************************************************************/
QString LanguageItem::getItemName() const
{
    return m_ItemName;
}

/**************************************************************************//**
*
* \brief To get the language font family
*
* \param none
*
* \return Font family
*
******************************************************************************/
QString LanguageItem::getFontFamily() const
{
    return m_FontFamily;
}

/**************************************************************************//**
*
* \brief To get the Visible status.
*
* \param None
*
* \return Visible status.
*
******************************************************************************/
bool LanguageItem::getItemVisible() const
{
    return m_ItemVisible;
}

/**************************************************************************//**
*
* \brief To get the check status.
*
* \param None
*
* \return Check status.
*
******************************************************************************/
bool LanguageItem::getItemChecked() const
{
    return m_ItemChecked;
}

/**************************************************************************//**
*
* \brief To get the language index
*
* \param None
*
* \return Language index
*
******************************************************************************/
int LanguageItem::getItemIndex() const
{
    return m_ItemIndex;
}
