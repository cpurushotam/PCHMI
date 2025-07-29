/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef JSONTREEITEM_H
#define JSONTREEITEM_H
#include <QList>
#include <QVariant>

// If there is any different complex structure, JsonTreeItem can be defined to a abstract basic class.
// The existing class is the simple one, but it is enough for us.
class JsonTreeItem
{
public:
    //Item type definition, None is the invalid type.
    enum JsonItemType{
        None,
        Object,
        Array,
        Value,
    };
public:
    explicit JsonTreeItem(JsonTreeItem *parent = nullptr);
    explicit JsonTreeItem(const QHash<int, QVariant> &datas, JsonTreeItem::JsonItemType type, JsonTreeItem *parent = nullptr);
    ~JsonTreeItem();

    //Add, Delete Node
    bool insertChild(int row, JsonTreeItem *child);
    bool removeChild(int row);
    bool insertChildren(int row, int count);
    bool removeChildren(int row, int count);
    void appendChild(JsonTreeItem *child);
    void deleteAllChild();

    //To be used for Model
    JsonTreeItem *childItem(int row);
    JsonTreeItem *parentItem();
    void setParentItem(JsonTreeItem *parent);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    void setData(int column, const QVariant &val);
    int row() const;
    bool editable(int column) const;

    //For Json
    QString key() const;
    void setKey(const QString &key);
    QVariant value() const;
    void setValue(const QVariant &value);
    JsonTreeItem::JsonItemType type() const;
    void setType(JsonTreeItem::JsonItemType type);

private:
    JsonTreeItem *theParentItem;        //Initialize the parent object using Constructor
    QList<JsonTreeItem*> theChildItems; //Add the chlid object using Append
    JsonItemType theItemType;
    //hash structure
    //1. key
    //2. value
    QHash<int, QVariant> theItemDatas;  //save the column(role) for qml treeview using
};

#endif // JSONTREEITEM_H
