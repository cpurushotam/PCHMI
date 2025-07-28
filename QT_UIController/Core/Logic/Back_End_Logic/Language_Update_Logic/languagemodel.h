/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H
#include <QAbstractListModel>
#include <QObject>
#include "languageitem.h"
class LanguageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LanguageRoles {
        IndexRole = Qt::UserRole + 1,
        NameRole,
        FontFamilyRole,
        VisibleRole,
        CheckedRole
    };
public:
    explicit LanguageModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addNewLanguage(const LanguageItem &languageItem);
    Q_INVOKABLE QString getLanguageName(int currentLanguageIndex);
    void clearLanguages();
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<LanguageItem> m_languageList;
signals:

};

#endif // LANGUAGEMODEL_H
