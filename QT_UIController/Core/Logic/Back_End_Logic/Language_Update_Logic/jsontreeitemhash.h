/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#ifndef JSONTREEITEMHASH_H
#define JSONTREEITEMHASH_H

#include "jsontreeitem.h"
class JsonTreeItemHash
{
public:
    static QMap<QString, JsonTreeItem*> *_hashItemIndex;
    static QHash<int, JsonTreeItem*> *_hashScreenIndex;
    static QList<int> *_stackHierarchical;
    static QMap<QString, QString> *_textIndex;
public:
    explicit JsonTreeItemHash();
    ~JsonTreeItemHash();
public:
    void insertItemObjectToItemMap(JsonTreeItem* obj);
    void insertItemObjectToScreenHash(QString screenName, JsonTreeItem* obj);
};

#endif // JSONTREEITEMHASH_H
