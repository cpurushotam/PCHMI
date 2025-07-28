/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef LANGUAGEITEM_H
#define LANGUAGEITEM_H

#include <QString>
class LanguageItem
{

public:
    LanguageItem(const QString& itemName, const QString& fontFamily,  const bool& itemVisible, const bool& itemChecked, const int& itemIndex);

private:
    QString m_ItemName;
    QString m_FontFamily;
    bool m_ItemVisible;
    bool m_ItemChecked;
    int m_ItemIndex;
public:
    QString getItemName() const;
    QString getFontFamily() const;
    bool getItemVisible() const;
    bool getItemChecked() const;
    int getItemIndex() const;
};

#endif // LANGUAGEITEM_H
