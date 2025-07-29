/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef JSONTREEMODEL_H
#define JSONTREEMODEL_H
#include <QString>
#include <QVariant>
#include <QAbstractItemModel>
#include "jsontreeitem.h"
#include "jsontreeitemhash.h"
class JsonTreeModel : public QAbstractItemModel
{
    Q_OBJECT
protected:
    explicit JsonTreeModel(QObject *parent = nullptr);
public:
    static JsonTreeModel* getInstance();
    ~JsonTreeModel();
public:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //editable
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    bool insertRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count,
                    const QModelIndex &parent = QModelIndex()) override;
public:
    bool loadJson(const QString &filepath);
    bool setData(const QString &index, const QVariant &value);
    bool writeCSVFile(int languageIndex, QString languageUrl);
    bool readCSVFile(QString languageUrl);
    void replaceItemData();
    void getItemDatas(int screenIndex, QStringList &sourceList);
    void getItemData(int screenIndex, QString &sourceName);
public:
    static JsonTreeModel* m_pJsonTreeModelObj;
private:
    JsonTreeItem *getItem(const QString &index) const;
    JsonTreeItem *getItem(const QModelIndex &index) const;
    void parseObject(const QString &key, const QJsonObject &obj, JsonTreeItem *&item);
    void parseArray(const QString &key, const QJsonArray &arr, JsonTreeItem *&item);
    void parseValue(const QString &key, const QJsonValue &val, JsonTreeItem *&item);
private:
    JsonTreeItem *theRootItem;
    JsonTreeItemHash *m_pJsonTreeItemIndexHashObj;
    const QString TargetLangIndicator = QObject::tr("Target Language");
};

#endif // JSONTREEMODEL_H
