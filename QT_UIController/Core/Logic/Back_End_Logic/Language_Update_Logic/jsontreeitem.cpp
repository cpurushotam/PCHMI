/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include "jsontreeitem.h"
/**************************************************************************//**
*
* \brief  Constructor, to create a node under the parent what is provided as the parameter.
*         Meanwhile, the member variables need to be initialized as following...
*         1. theParentItem = parent;
*         2. theItemType = JsonTreeItem::None;
*         3. theItemDatas.insert(0, "[Key]");
*         4. theItemDatas.insert(1, "[Value]");
*
* \param  parent node object pointer against the creating node : JsonTreeItem*
*
* \return none
*
******************************************************************************/
JsonTreeItem::JsonTreeItem(JsonTreeItem *parent)
    :theParentItem(parent)
    ,theItemType(JsonTreeItem::None)
    ,theItemDatas({{0, "[Key]"}, {1, "[Value]"}})
{

}

/**************************************************************************//**
*
* \brief  Override Constructor
*
* \param  1. data will be assigned to theItemDatas that owned by the new created node;
*         2. type will be assigned to theItemType that indicates the type of the new created node;
*         3. parent node against the current new created node
*
* \return none
*
******************************************************************************/
JsonTreeItem::JsonTreeItem(const QHash<int, QVariant> &datas, JsonTreeItem::JsonItemType type, JsonTreeItem *parent)
    :theParentItem(parent)
    ,theItemType(type)
    ,theItemDatas(datas)
{

}

/**************************************************************************//**
*
* \brief  Destructor, need to delete all the children nodes under the current node before the destructing.
*
* \param  none
*
* \return none
*
******************************************************************************/
JsonTreeItem::~JsonTreeItem()
{
    deleteAllChild();
}

/**************************************************************************//**
*
* \brief  Primitive operation to add the child node to the current node
*
* \param  row : int; child : JsonTreeItem*
*
* \return result : bool
*
******************************************************************************/
bool JsonTreeItem::insertChild(int row, JsonTreeItem *child)
{
    if(row < 0 || row > theChildItems.count())
        return false;
    theChildItems.insert(row, child);
    child->setParentItem(this);
    return true;
}

/**************************************************************************//**
*
* \brief  Primitive operation to remove the specific child node under the current node.
*
* \param  row : int
*
* \return result : bool
*
******************************************************************************/
bool JsonTreeItem::removeChild(int row)
{
    if(row < 0 || row + 1 > theChildItems.count())
        return false;
    delete theChildItems.takeAt(row);
    return true;
}

/**************************************************************************//**
*
* \brief  Primitive operation to add the children nodes under the current node.
*
* \param  row : int; count : int
*
* \return result : bool
*
******************************************************************************/
bool JsonTreeItem::insertChildren(int row, int count)
{
    if(row < 0 || row > theChildItems.count())
        return false;
    for(int i = 0; i < count; i++)
    {
        JsonTreeItem *item = new JsonTreeItem(this);
        //there is not any operation for the delegate, so new item is defined as Json Value in the initialization.
        item->setType(JsonTreeItem::Value);
        theChildItems.insert(row, item);
    }
    return true;
}

/**************************************************************************//**
*
* \brief  Primitive operation to remove the specific children nodes under the current node.
*
* \param  row : int; count : int
*
* \return result : bool
*
******************************************************************************/
bool JsonTreeItem::removeChildren(int row, int count)
{
    if(row < 0 || (row + count) > theChildItems.count())
        return false;
    for(int i = 0; i < count; i++)
    {
        delete theChildItems.takeAt(row + i);
    }
    return true;
}

/**************************************************************************//**
*
* \brief  Primitive operation to append the child node under the current node.
*
* \param  row : int; count : int
*
* \return result : bool
*
******************************************************************************/
void JsonTreeItem::appendChild(JsonTreeItem *child)
{
    theChildItems.append(child);
    child->setParentItem(this);
}

/**************************************************************************//**
*
* \brief  Primitive operation to delete all the children nodes of the current node.
*
* \param  none
*
* \return none
*
******************************************************************************/
void JsonTreeItem::deleteAllChild()
{
    qDeleteAll(theChildItems);
    theChildItems.clear();
}

/**************************************************************************//**
*
* \brief  Primitive operation to get the specific child item object.
*
* \param  row : int
*
* \return child item object : JsonTreeItem*
*
******************************************************************************/
JsonTreeItem *JsonTreeItem::childItem(int row)
{
    return theChildItems.value(row);
}

/**************************************************************************//**
*
* \brief  To get parent node object of the current node.
*
* \param  none
*
* \return theParentItem : JsonTreeItem*
*
******************************************************************************/
JsonTreeItem *JsonTreeItem::parentItem()
{
    return theParentItem;
}

/**************************************************************************//**
*
* \brief  To set parent node object for the current node.
*
* \param  parent : JsonTreeItem*
*
* \return none
*
******************************************************************************/
void JsonTreeItem::setParentItem(JsonTreeItem *parent)
{
    theParentItem = parent;
}

/**************************************************************************//**
*
* \brief  To get the children count under the current Node.
*
* \param  none.
*
* \return children count : int
*
******************************************************************************/
int JsonTreeItem::childCount() const
{
    return theChildItems.count();
}

/**************************************************************************//**
*
* \brief  To get data size of the current node.
*
* \param  none
*
* \return count : int
*
******************************************************************************/
int JsonTreeItem::columnCount() const
{
    return theItemDatas.count();
}

/**************************************************************************//**
*
* \brief  To get the specific data from the current node.
*
* \param  column : int
*
* \return value : QVariant
*
******************************************************************************/
QVariant JsonTreeItem::data(int column) const
{
    return theItemDatas.value(column, QVariant());
}

/**************************************************************************//**
*
* \brief  To set the specific data of the current node.
*
* \param  val : QVariant&
*
* \return none
*
******************************************************************************/
void JsonTreeItem::setData(int column, const QVariant &val)
{
    theItemDatas.insert(column, val);
}

/**************************************************************************//**
*
* \brief  To get the position of the current node corresponding to its parent node..
*
* \param  none
*
* \return index : int
*
******************************************************************************/
int JsonTreeItem::row() const
{
    if(theParentItem)
        return theParentItem->theChildItems.indexOf(const_cast<JsonTreeItem*>(this));
    return 0;
}

/**************************************************************************//**
*
* \brief  Primitive operation to check if the data of current node can be editable.
*
* \param  column : int
*
* \return result : bool
*
******************************************************************************/
bool JsonTreeItem::editable(int column) const
{
    //In order to keep the default data structure
    //The key and value of root are not editable
    //The key of array is not editable
    //The value of array and object are not editable
    if((!theParentItem || !theParentItem->parentItem()) ||
            ((0 == column) && (theParentItem->type() == JsonTreeItem::Array)) ||
            ((1 == column) && ((type() == JsonTreeItem::Array) || (type() == JsonTreeItem::Object))))
        return false;
    return true;
}

/**************************************************************************//**
*
* \brief  To get the Key value of the first data of the current node.
*
* \param  none
*
* \return Key Value : QString
*
******************************************************************************/
QString JsonTreeItem::key() const
{
    return theItemDatas.value(0, "").toString();
}

/**************************************************************************//**
*
* \brief  To set Key value of the first data of the current node
*
* \param  key : QString&
*
* \return none
*
******************************************************************************/
void JsonTreeItem::setKey(const QString &key)
{
    theItemDatas[0] = key;
}

/**************************************************************************//**
*
* \brief  To get Value of the first data of the current node.
*
* \param  none.
*
* \return first Value of the QHash : QVariant
*
******************************************************************************/
QVariant JsonTreeItem::value() const
{
    return theItemDatas.value(1, 0);
}

/**************************************************************************//**
*
* \brief  To set Value of the first data of the current node.
*
* \param  value : QVariant&
*
* \return none
*
******************************************************************************/
void JsonTreeItem::setValue(const QVariant &value)
{
    theItemDatas[1] = value;
}

/**************************************************************************//**
*
* \brief  To get the type of the current node.
*
* \param  none
*
* \return object : JsonTreeItem
*
******************************************************************************/
JsonTreeItem::JsonItemType JsonTreeItem::type() const
{
    return theItemType;
}

/**************************************************************************//**
*
* \brief  To set the type of the current node.
*
* \param  type : JsonTreeItem::JsonItemType
*
* \return none
*
******************************************************************************/
void JsonTreeItem::setType(JsonTreeItem::JsonItemType type)
{
    theItemType = type;
}
