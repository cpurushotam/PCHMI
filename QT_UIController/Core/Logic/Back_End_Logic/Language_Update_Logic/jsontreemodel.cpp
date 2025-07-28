/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QHash>
#include "jsontreemodel.h"
#include "languagedef.h"
JsonTreeModel* JsonTreeModel::m_pJsonTreeModelObj = nullptr;
/**************************************************************************//**
*
* \brief  Constructor
*         Initialize theRootItem and m_pJsonTreeItemIndexHashObj
*
* \param  parent : QObject*, because the LanguageConfig class is inherited from QObject.
*
* \return none
*
******************************************************************************/
JsonTreeModel::JsonTreeModel(QObject *parent)
    :QAbstractItemModel(parent)
    ,theRootItem(new JsonTreeItem(nullptr))
    ,m_pJsonTreeItemIndexHashObj(new JsonTreeItemHash())
{

}

/**************************************************************************//**
*
* \brief  To get JsonTreeModel singleton object.
*         The class is designed to the singleton class so the JsonTreeModel object can used in everywhere
*         without any new instantiation.
*         And the JsonTreeModel object can be get easily using the this function
*         without any external declaration before using.
*
* \param  none
*
* \return JsonTreeModel singleton object
*
******************************************************************************/
JsonTreeModel *JsonTreeModel::getInstance()
{
    if(m_pJsonTreeModelObj == nullptr)
    {
        m_pJsonTreeModelObj = new JsonTreeModel(nullptr);
    }
    return m_pJsonTreeModelObj;
}

/**************************************************************************//**
*
* \brief  Destructor
*         1.Delete m_pJsonTreeItemIndexHashObj object pointer
*         2.Delete all the child object under the theRootItem.
*         3.Delete theRootItem object pointer.
*
* \param  none
*
* \return none
*
******************************************************************************/
JsonTreeModel::~JsonTreeModel()
{
    delete m_pJsonTreeItemIndexHashObj;
    theRootItem->deleteAllChild();
    delete theRootItem;
}

/**************************************************************************//**
*
* \brief  Qt Item module standard interface.
*         The more detailed explanation need to refer to QAbstractItemModel that we inherited from.
*         When reimplementing this function in a subclass,
*         call createIndex() to generate model indexes that other components can use to refer to items in your model.
*         Note: This function can be invoked via the meta-object system and from QML.
*
* \param  1. row is the index of the child Item under the parent,
*         2. column is the necessary parameter for the model index generating;
*         3. parent : for the parent object saving.
*
* \return index : Returns the index of the item in the model specified by the given row, column and parent index.
*
******************************************************************************/
QModelIndex JsonTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    JsonTreeItem *parentItem=getItem(parent);
    JsonTreeItem *childItem = parentItem->childItem(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

/**************************************************************************//**
*
* \brief  Qt Item module standard interface
*         The more detailed explanation need to refer to QAbstractItemModel that we inherited from.
*         A common convention used in models that expose tree data structures is that
*         only items in the first column have children.
*         For that case, when reimplementing this function in a subclass the column of the returned QModelIndex would be 0.
*         When reimplementing this function in a subclass, be careful to avoid calling QModelIndex member functions,
*         such as QModelIndex::parent(), since indexes belonging to your model will simply call your implementation,
*         leading to infinite recursion.
*         Get the upper level parent object using Model Index
*         Note: This function can be invoked via the meta-object system and from QML.
*
* \param  index : QModelIndex&
*
* \return Returns the parent of the model item with the given index. If the item has no parent,
*         an invalid QModelIndex is returned.
*
******************************************************************************/
QModelIndex JsonTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    JsonTreeItem *childItem = getItem(index);
    JsonTreeItem *parentItem = childItem->parentItem();

    if (parentItem == theRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

/**************************************************************************//**
*
* \brief  Qt Item model standard interface
*         The more detailed explanation need to refer to QAbstractItemModel that we inherited from.
*         Note: This function can be invoked via the meta-object system and from QML.
*         To get the child items number under the specific parent object.
* \param  parent : QModelIndex&
*
* \return Returns the number of rows under the given parent.
*         When the parent is valid it means that rowCount is returning the number of children of parent.
*
******************************************************************************/
int JsonTreeModel::rowCount(const QModelIndex &parent) const
{
    JsonTreeItem *parentItem = getItem(parent);
    return parentItem->childCount();
}

/**************************************************************************//**
*
* \brief  Qt Item model standard interface
*         The more detailed explanation need to refer to QAbstractItemModel that we inherited from.
*         To get the values number that attached to the current parent object.
*         Note: This function can be invoked via the meta-object system and from QML.
* \param  parent : QModelIndex&
*
* \return Returns the number of columns for the children of the given parent.
*
******************************************************************************/
int JsonTreeModel::columnCount(const QModelIndex &parent) const
{
    JsonTreeItem *parentItem = getItem(parent);
    return parentItem->columnCount();
}

/**************************************************************************//**
*
* \brief  Qt Item model standard interface
*         The more detailed explanation need to refer to QAbstractItemModel that we inherited from.
*         To locate at the specific object using the Model Index and get the data from the specific object then.
*         Note: This function can be invoked via the meta-object system and from QML.
*         Note: If you do not have a value to return, return an invalid QVariant instead of returning 0.
* \param  index : QModelIndex&; role : int
*
* \return Returns the data stored under the given role for the item referred to by the index.
*
******************************************************************************/
QVariant JsonTreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    JsonTreeItem *item = getItem(index);
    return item->data(index.column());
}

/**************************************************************************//**
*
* \brief  Qt Item model standard interface
*         The more detailed explanation need to refer to QAbstractItemModel that we inherited from.
*         To locate at the specific object using the Model Index and get the flag from the specific object then.
*         Returns Qt::ItemIsEditable if the speicifc object flag is true; otherwise returns Qt::NoItemFlags.
*         Note: This function can be invoked via the meta-object system and from QML.
*         The base class implementation returns a combination of flags that
*         enables the item (ItemIsEnabled) and allows it to be selected (ItemIsSelectable).
* \param  int : QModelIndex&
*
* \return flag enum : Qt::ItmeFlags Returns the item flags for the given index.
*
******************************************************************************/
Qt::ItemFlags JsonTreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    JsonTreeItem *item = getItem(index);
    return (item->editable(index.column()) ? Qt::ItemIsEditable : Qt::NoItemFlags)
            | QAbstractItemModel::flags(index);
}

/**************************************************************************//**
*
* \brief  Qt Item model standard interface
*         The more detailed explanation need to refer to QAbstractItemModel that we inherited from.
*         To locate at the specific data from the specific object using the Model Index and
*         to replace the specific data using the parameter value.
*         Note: This function can be invoked via the meta-object system and from QML.
*         Sets the role data for the item at index to value.
*         The dataChanged() signal should be emitted if the data was successfully set.
*
* \param  index : QModelIndex&; value : QVariant&; role : int
*
* \return result : bool Returns true if successful; otherwise returns false.
*
******************************************************************************/
bool JsonTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    JsonTreeItem *item = getItem(index);
    item->setData(index.column(), value);
    emit dataChanged(index, index, {role});
    return true;
}

/**************************************************************************//**
*
* \brief  Qt Item model standard interface
*         The more detailed explanation need to refer to QAbstractItemModel that we inherited from.
*         To create the child item object under the specific parent object.
*         Note: This function can be invoked via the meta-object system and from QML.
*
*
* \param  row :int; count : int; parent : QModelIndex&
*
* \return Returns true if the rows were successfully inserted; otherwise returns false.
*
******************************************************************************/
bool JsonTreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    JsonTreeItem *parentItem=getItem(parent);

    beginInsertRows(parent, row, row+count-1);
    const bool result=parentItem->insertChildren(row,count);
    endInsertRows();

    return result;
}

/**************************************************************************//**
*
* \brief  Qt Item model standard interface
*         On models that support this, removes count rows starting with the given row under parent parent from the model.
*         To remove the children objects under the speicifc parent object.
*         Returns true if the rows were successfully removed; otherwise returns false.
*
* \param  row is start child item index;
*         count: how many children objects need to be removed from the specific start child;
*         parent : QModelIndex&
*
* \return result : bool
*
******************************************************************************/
bool JsonTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    JsonTreeItem *parentItem=getItem(parent);

    beginRemoveRows(parent, row, row+count-1);
    const bool result=parentItem->removeChildren(row,count);
    endRemoveRows();

    return result;
}

/**************************************************************************//**
*
* \brief  The primitive operation on the Json file loading
*
* \param  Json file path : QString&
*
* \return result : bool
*
******************************************************************************/
bool JsonTreeModel::loadJson(const QString &filepath)
{
    //check if the directory is the available
    if(filepath.isEmpty())
        return false;
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    //close the file after the reading finished
    const QByteArray raw_data = file.readAll();
    file.close();

    //parse Json file
    QJsonParseError json_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(raw_data, &json_error);

    //check if the Json file is the available
    if(json_doc.isNull() || json_doc.isEmpty() || json_error.error != QJsonParseError::NoError)
        return false;

    emit beginResetModel();
    theRootItem->deleteAllChild(); //clear old items
    JsonTreeItemHash::_stackHierarchical->clear();
    JsonTreeItemHash::_hashItemIndex->clear();
    JsonTreeItemHash::_hashScreenIndex->clear();

    //check if the json is object{} or array[]
    if(json_doc.isObject())
    {
        //parse Object
        parseObject("[Root]", json_doc.object(), theRootItem);
    }
    else if(json_doc.isArray())
    {
        //parse Array
        parseArray("[Root]", json_doc.array(), theRootItem);
    }
    emit endResetModel();
    return true;
}

/**************************************************************************//**
*
* \brief  Override setData for the external C++ function can be used.
*
* \param  index : QString&; value : QVariant&
*
* \return none
*
******************************************************************************/
bool JsonTreeModel::setData(const QString &index, const QVariant &value)
{
    JsonTreeItem *item = getItem(index);
    item->setData(1, value);
    return true;
}

/**************************************************************************//**
*
* \brief  The primitive operation for the CSV file writting
*         1. Add the each language name into the CSV
*         so the system can understand what the language needs to display upon the screen.
*         2. Initialize English CSV file so the software is able to show English language at the begining.
*
* \param  languageIndex: languge enum index; languageUrl : QString
*
* \return result : bool
*
******************************************************************************/
bool JsonTreeModel::writeCSVFile(int languageIndex, QString languageUrl)
{
    QFile file(languageUrl);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        qDebug()<< "Cannot open file for writing: "<< qPrintable(file.errorString());
        return false;
    }
    QTextStream out(&file);
    //header
    out<<"Size:;"<<JsonTreeItemHash::_hashItemIndex->size()<<";\n";
    QString languageName = "";
    switch(languageIndex)
    {
    case LanguageEnum::ENGLISH_IDX:
        languageName = QObject::tr("English");
        break;
    case LanguageEnum::FRENCH_IDX:
        languageName = QObject::tr("Français");
        break;
    case LanguageEnum::GERMAN_IDX:
        languageName = QObject::tr("Deutsche");
        break;
    case LanguageEnum::SPANISH_IDX:
        languageName = QObject::tr("Español");
        break;
    case LanguageEnum::KOREAN_IDX:
        languageName = QObject::tr("한국어");
        break;
    case LanguageEnum::SIMPLIFIEDCHINESE_IDX:
        languageName = QObject::tr("中文(简化的)");
        break;
    case LanguageEnum::ITALIAN_IDX:
        languageName = QObject::tr("Italiano");
        break;
    case LanguageEnum::JAPANESE_IDX:
        languageName = QObject::tr("日本语");
        break;
    case LanguageEnum::DANISH_IDX:
        languageName = QObject::tr("dansk");
        break;
    case LanguageEnum::SLOVAKIAN_IDX:
        languageName = QObject::tr("Slovenský");
        break;
    case LanguageEnum::POLISH_IDX:
        languageName = QObject::tr("Polskie");
        break;
    default:
        languageName = QObject::tr("English");
        break;
    }

    out<<TargetLangIndicator<<":;"<<languageName<<";\n";
    out<<"Index;English(Source);"<<languageName<<"(Target)"<<"\n";
    QMap<QString, JsonTreeItem*>::const_iterator iter = JsonTreeItemHash::_hashItemIndex->constBegin();
    QString str = "";
    while(iter != JsonTreeItemHash::_hashItemIndex->constEnd())
    {
        if(languageIndex == LanguageEnum::ENGLISH_IDX)
            str = iter.key() + ";" + iter.value()->value().toString() + ";" + iter.value()->value().toString() + ";\n";
        else
            str = iter.key() + ";" + iter.value()->value().toString() + ";\n";
        out<<str;
        ++iter;
    }
    file.close();
    return true;
}

/**************************************************************************//**
*
* \brief  The primitive operation for the CSV file writting
*
* \param  languageUrl : QString
*
* \return result : bool
*
******************************************************************************/
bool JsonTreeModel::readCSVFile(QString languageUrl)
{
    QFile file(languageUrl);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<< "Cannot open file for reading: "<< qPrintable(file.errorString());
        return false;
    }

    JsonTreeItemHash::_textIndex->clear();
    QTextStream in(&file);
    // read text string size
    QStringList firstData = in.readLine().split(";");
//    int iSize = firstData.at(1).toInt();
    // Target language name reading
    in.readLine();
    // Header reading
    in.readLine();
    while(!in.atEnd())
    {
        QStringList tmpData = in.readLine().split(";");
        JsonTreeItemHash::_textIndex->insert(tmpData.at(0), tmpData.at(2));
    }

    file.close();
    return true;
}

/**************************************************************************//**
*
* \brief  The wrapper for the Item data replacement for Json model.
*         If the current language what we indicated is not any translation update
*         and still keep the blank for the translation column,
*         the index of the text string will be shown upon the screen.
*         We can easily look at what text string need to be translated in the CSV file using the shown index.
*
* \param  none
*
* \return none
*
******************************************************************************/
void JsonTreeModel::replaceItemData()
{
    QMap<QString, QString>::const_iterator iter = JsonTreeItemHash::_textIndex->constBegin();
    while(iter != JsonTreeItemHash::_textIndex->constEnd())
    {
        if(JsonTreeItemHash::_hashItemIndex->contains(iter.key()))
        {
            if(iter.value().isEmpty() != true)
            {
                setData(iter.key(), iter.value());
            }
            else
            {
                setData(iter.key(), iter.key());
            }
        }
        ++iter;
    }
}

/**************************************************************************//**
*
* \brief  The wrapper for the Item data getting for Json model.
*
* \param  screenIndex : int; sourceList : QStringList&
*
* \return none
*
******************************************************************************/
void JsonTreeModel::getItemDatas(int screenIndex, QStringList &sourceList)
{
    QStringList strList;
    strList.clear();
    if(JsonTreeItemHash::_hashScreenIndex->contains(screenIndex) == true)
    {
        JsonTreeItem* item = JsonTreeItemHash::_hashScreenIndex->value(screenIndex);
        if(item->childCount() != 0)
        {
            for(int i = 0; i< item->childCount(); i++)
            {
                JsonTreeItem* arrayItem = item->childItem(i);
                if(arrayItem->type() == JsonTreeItem::Array)
                {
                    for(int i = 0; i < arrayItem->childCount(); i++)
                    {
                        JsonTreeItem* subStringItem = arrayItem->childItem(i);
                        strList.append(subStringItem->value().toString());
                    }
                }
            }
        }
    }
    if(strList.isEmpty() != true)
    {
        sourceList.clear();
        sourceList = strList;
    }
}

/**************************************************************************//**
*
* \brief  The wrapper for the Item data getting for Json model.
*
* \param  screenIndex : int; sourceName : QString&
*
* \return none
*
******************************************************************************/
void JsonTreeModel::getItemData(int screenIndex, QString &sourceName)
{
    QString strName;
    strName.clear();
    if(JsonTreeItemHash::_hashScreenIndex->contains(screenIndex) == true)
    {
        JsonTreeItem* item = JsonTreeItemHash::_hashScreenIndex->value(screenIndex);
        if(item->childCount() != 0)
        {
            for(int i = 0; i< item->childCount(); i++)
            {
                JsonTreeItem* strItem = item->childItem(i);
                if(strItem->type() == JsonTreeItem::Value)
                {
                    strName = strItem->value().toString();
                }
            }
        }
    }
    if(strName.isEmpty() != true)
    {
        sourceName.clear();
        sourceName = strName;
    }
}

/**************************************************************************//**
*
* \brief To get the Item data object using Hash Key .
*
* \param index : QString&
*
* \return item data object : JsonTreeItem*
*
******************************************************************************/
JsonTreeItem *JsonTreeModel::getItem(const QString &index) const
{
    if(JsonTreeItemHash::_hashItemIndex->contains(index) == true)
    {
        JsonTreeItem *item = JsonTreeItemHash::_hashItemIndex->value(index);
        return item;
    }
    return theRootItem;
}

/**************************************************************************//**
*
* \brief To get the Item data object using Qt model standard parameter.
*
* \param index : QModelIndex&
*
* \return item data object : JsonTreeItem*
*
******************************************************************************/
JsonTreeItem *JsonTreeModel::getItem(const QModelIndex &index) const
{
    if(index.isValid())
    {
        JsonTreeItem *item = static_cast<JsonTreeItem*>(index.internalPointer());
        if(item)
            return item;
    }
    return theRootItem;
}

/**************************************************************************//**
*
* \brief Recursive function for the Json Object parsing
*
* \param key : QString&; obj : QJsonObject&; item : JsonTreeItem*
*
* \return none
*
******************************************************************************/
void JsonTreeModel::parseObject(const QString &key, const QJsonObject &obj, JsonTreeItem *&item)
{
    int index = 0;
    //Create Object Node
    JsonTreeItem *child = new JsonTreeItem({{0, key}, {1, "[Object]"}}, JsonTreeItem::Object, item);
    item->appendChild(child);
    m_pJsonTreeItemIndexHashObj->insertItemObjectToScreenHash(key, child);

    //Recursive Traversal for the Key of Object
    const QStringList keys = obj.keys();
    for(const QString &item_key : keys)
    {
        index++;
        JsonTreeItemHash::_stackHierarchical->push_back(index);
        parseValue(item_key, obj.value(item_key), child);
        JsonTreeItemHash::_stackHierarchical->pop_back();
    }
}

/**************************************************************************//**
*
* \brief Recursive function for the Json Array parsing
*
* \param key : QString&; arr : QJsonArray&; item : JsonTreeItem*
*
* \return none
*
******************************************************************************/
void JsonTreeModel::parseArray(const QString &key, const QJsonArray &arr, JsonTreeItem *&item)
{
    int index = 0;
    //Create Array Node
    JsonTreeItem *child = new JsonTreeItem({{0, key}, {1, "[Array]"}}, JsonTreeItem::Array, item);
    item->appendChild(child);

    //Recursive Traversal for the Array
    for(int i = 0; i < arr.count(); i++)
    {
        index++;
        JsonTreeItemHash::_stackHierarchical->push_back(index);
        parseValue("-", arr.at(i), child);
        JsonTreeItemHash::_stackHierarchical->pop_back();
    }
}

/**************************************************************************//**
*
* \brief Recursive function for the Json primitive parsing
*
* \param key : QString&; val : QJsonValue&; item : JsonTreeItem*
*
* \return none
*
******************************************************************************/
void JsonTreeModel::parseValue(const QString &key, const QJsonValue &val, JsonTreeItem *&item)
{
    QVariant the_val;
    //need to check the Value Type
    //if the type is Object or Array, it will be do recursive traversal process
    switch(val.type())
    {
    case QJsonValue::Object:
        parseObject(key, val.toObject(), item);
        return;
        break;
    case QJsonValue::Array:
        parseArray(key, val.toArray(), item);
        return;
        break;
    case QJsonValue::Bool:
        the_val = val.toBool();
        break;
    case QJsonValue::Double:
        the_val = val.toDouble();
        break;
    case QJsonValue::String:
        the_val = val.toString();
        break;
    case QJsonValue::Null: break;
    case QJsonValue::Undefined: break;
    default: break;
    }

    //Create a new node
    JsonTreeItem *child = new JsonTreeItem({{0, key}, {1, the_val}}, JsonTreeItem::Value, item);
    item->appendChild(child);
    m_pJsonTreeItemIndexHashObj->insertItemObjectToItemMap(child);
}
