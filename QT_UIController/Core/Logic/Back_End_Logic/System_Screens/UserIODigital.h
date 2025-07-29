/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2024

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


---------------------------- MODULE DESCRIPTION ----------------------------

UserIODigital class - which is responsible to do interaction between frontend and backend .

***************************************************************************/
#ifndef UserIODigital_H
#define UserIODigital_H

#include <QObject>
#include <QStringList>
#include <QVector>
#include "IOManager.h"
#include "UpdateScreens.h"

class UserIODigital : public QObject
{
    Q_OBJECT
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_PROPERTY(QStringList optionsModel READ optionsModel NOTIFY optionsModelChanged)
    Q_PROPERTY(QStringList digitalIpComboboxList READ digitalIpComboboxList NOTIFY optionsModelChanged)
    Q_PROPERTY(QStringList digitalIOOutputModel READ digitalIOOutputModel NOTIFY digitalIOOutputModelChanged)
    Q_PROPERTY(QStringList digitalIpOutputComboboxList READ digitalIpOutputComboboxList NOTIFY digitalIOOutputModelChanged)
    Q_PROPERTY(bool IsLoading      READ getIsLoading     WRITE updateIsLoading     NOTIFY loadingDataChanged)

    Q_PROPERTY(bool IsGlobalDgtIpSwtchEnable      READ getIsGlobalDgtIpSwtchEnable       WRITE updateIsGlobalDgtIpSwtchEnable         NOTIFY loadingDataChanged)
    Q_PROPERTY(bool IsGlobalDgtOpSwtchEnable   READ getIsGlobalDgtOpSwtchEnable         WRITE updateIsGlobalDgtOpSwtchEnable             NOTIFY loadingDataChanged)


public:
    explicit UserIODigital(QObject *parent = nullptr);

    QStringList optionsModel() const;                         //Returns the list of input model options to qml.
    QStringList digitalIpComboboxList() const;               //Returns the list of output model options to qml.
    Q_INVOKABLE QString getComboBoxText(int index);         //Returns the specific input model option to qml based on index.
    Q_INVOKABLE int getTotalSizeofDigtialIpList();         //Returns the count inputput model options to qml.
    Q_INVOKABLE QString getDigitalIp(int index);          //combobx Options visbility list
    Q_INVOKABLE QString getSelectedComboBox(int index);  //combobox Options display on displaytext

    /*Digital output model*/
    QStringList digitalIOOutputModel() const;                        //Returns the list of input model options to qml.
    QStringList digitalIpOutputComboboxList() const;                 //Returns the list of output model options to qml.
    Q_INVOKABLE QString getDgOutPutComboBoxText(int index);          //Returns the specific input model option to qml based on index.
    Q_INVOKABLE int getTotalSizeofDigtialOPList();                   //Returns the count inputput model options to qml.
    Q_INVOKABLE QString getDigitalOP(int index);                     //combobx Options visbility list
    Q_INVOKABLE QString getSelectedOPComboBox(int index);            //combobox Options display on displaytext

    Q_INVOKABLE void setComboBoxSelection(int index, const QString &selection);  //assign the Event values from QML to cpp for input model.
    Q_INVOKABLE void setDigitalUserIOState(int index, bool state);               //assign the State values from QML to cpp for input model.
    Q_INVOKABLE void setDigitalUserIOPinEnable(int index, bool state);           //assign the PinEnable values from QML to cpp for input model.

     /*Digital output model*/
    Q_INVOKABLE void setOutputComboBoxSelection(int index, const QString &selection);      //assign the Event values from QML to cpp for output model.
    Q_INVOKABLE void setOutputDigitalUserIOState(int index, bool state);                   //assign the State values from QML to cpp for output model.
    Q_INVOKABLE void setOutputDigitalUserIOPinEnable(int index, bool state);               //assign the PinEnable values from QML to cpp for output model.

    /*Digital output model state and pinEnable value for digital Input model on HMI*/
    Q_INVOKABLE bool getDigitalUserIOState(int index);
    Q_INVOKABLE bool getDigitalUserIOPinEnable(int index);

    /*Digital output model state and pinEnable value for digital output model on HMI*/
    Q_INVOKABLE bool getOutputDigitalUserIOState(int index);
    Q_INVOKABLE bool getOutputDigitalUserIOPinEnable(int index);

    //Request To ASC on Save request.
    Q_INVOKABLE void getSaveRequestForDigitalUserIO();
    //Request To ASC on ResetToDefault request.
    Q_INVOKABLE void getResetToDefRequestForDigitalUserIO();
    //Request To on Cancel request.
    Q_INVOKABLE void getCancelRequestForDigitalUserIO();
    Q_INVOKABLE bool getIndexValue(int index);

    void filterComboBoxList();                   // Function to filter the options based on slection.
    bool checkOptionIfAvailable(QString option); //check if available for slection.

    //To check if the option is available for selection or not.
    bool checkOptionIfAvailableInOutputModel(QString option);

    Q_INVOKABLE int getCountOfIpModel();                   //Returns the count inputput model options to qml.
    Q_INVOKABLE int getCountOfOpModel();                   //Returns the count inputput model options to qml.

    //Read Structure from ASC to process the combobx listmodel.
    void readUserIOStructure();
    void setDigitalIOEvent(int index,const QString &selection);
    void setOutputDigitalIOEvent(int index,const QString &selection);

    //Digital Input mapping functions.
    QString psEventName(INPUT_LINE_FUNCTION Event);
    int MappingPSInputFunc(int input);

    //Digital Output mapping functions.
    QString psOutputEventName(OUTPUT_LINE_FUNCTION Event);
    int MappingPSOutputFunc(int input);

    bool getIsLoading() const;
    void updateIsLoading(const bool& IsLoading);

    // Signal to notify QML about updated values
    bool getIsGlobalDgtIpSwtchEnable() const;
    void updateIsGlobalDgtIpSwtchEnable(bool newIsGlobalDgtIpSwtchEnable);

    bool getIsGlobalDgtOpSwtchEnable() const;
    void updateIsGlobalDgtOpSwtchEnable(bool newIsGlobalDgtOpSwtchEnable);

signals:
    void optionsModelChanged();
    void comboBoxModelChanged();
    void valuesUpdated();
    void digitalIOOutputModelChanged();
    void loadingDataChanged();

private:

    //Containers used to store and process the digital Input values.
    QStringList m_optionsModel;
    QStringList m_digitalIpComboboxList;
    QVector<QString> values;
    QVector <bool> m_GetIndexValue;

    //Containers used to store and process the digital Ouput values.
    QStringList m_digitalIOOutputModel;
    QStringList m_digitalIpOutputComboboxList;
    QVector<QString> m_outputvalues;

    int m_ActiveWelderId = -1;
    bool m_IsLoadingFlag = false;
    bool isScreenUpdated = false;

    USERIO m_UserIO;
    DigitalIOMgr *m_DigitalIOMgr;

    bool m_IsGlobalDgtIpSwtchEnable;

    bool m_IsGlobalDgtOpSwtchEnable;

private slots:
    void OnUserIODigitalDetailsUpdated(DigitalIOMgr *DigitalIOMgrDetailsResult_Obj, int welderId);
};

#endif // UserIODigital_H


