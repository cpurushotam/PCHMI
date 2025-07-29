/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2025

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    UserIOAnalog.h file handles User IO Analog Inputs and Output functionalities related operations.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 29/1/2025 - Initial version.
***************************************************************************/
#ifndef USERIOANALOG_H
#define USERIOANALOG_H

#include <QObject>
#include "UpdateScreens.h"

class UserIOAnalog : public QObject
{
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_OBJECT

    Q_PROPERTY(QStringList analogIPoptionsModel READ analogIPoptionsModel NOTIFY analogIPoptionsModelModelChanged)
    Q_PROPERTY(QStringList analogIPoptionsModelComboboxList READ analogIPoptionsModelComboboxList NOTIFY analogIPoptionsModelModelChanged)

    Q_PROPERTY(QStringList analogIOOutputModel READ analogIOOutputModel NOTIFY digitalIOOutputModelChanged)
    Q_PROPERTY(QStringList analogIpOutputComboboxList READ analogOutputComboboxList NOTIFY digitalIOOutputModelChanged)

    Q_PROPERTY(bool IsGlobalAnalogIpSwtchEnable      READ getIsGlobalAnalogIpSwtchEnable       WRITE updateIsGlobalAnalogIpSwtchEnable         NOTIFY loadingDataChanged)
    Q_PROPERTY(bool IsGlobalAnalogOpSwtchEnable   READ getIsGlobalAnalogOpSwtchEnable         WRITE updateIsGlobalAnalogOpSwtchEnable             NOTIFY loadingDataChanged)


public:
    explicit UserIOAnalog(QObject *parent = nullptr);
    ~UserIOAnalog();

    QStringList analogIPoptionsModel() const;
    QStringList analogIPoptionsModelComboboxList() const;

    Q_INVOKABLE void setComboBoxSelection(int index, const QString &selection);  //assign the Event values from QML to cpp for input model.
    Q_INVOKABLE QString getAnalogIp(int index);                          //combobx Options visbility list
    Q_INVOKABLE QString getSelectedAnalogComboBox(int index);         //combobox Options display on displaytext
    Q_INVOKABLE int getTotalSizeofAnalogIpList();                     //Returns the count inputput model options to qml.
    /*Analog output model state and pinEnable value for digital Input model on HMI*/
    Q_INVOKABLE bool getAnalogUserIOIpPinEnable(int index);
    Q_INVOKABLE void setAnalogUserIOPinEnable(int index, bool state);  //assign the PinEnable values from QML to cpp for input model.

    Q_INVOKABLE int getCountOfAnalogIpModel();                        //Returns the count inputput model options to qml.
    Q_INVOKABLE int getCountOfAnalogOpModel();                        //Returns the count inputput model options to qml.

    //Request To ASC on Save request.
    Q_INVOKABLE void getSaveRequestForAnalogUserIO();
    //Request To ASC on ResetToDefault request.
    Q_INVOKABLE void getResetToDefRequestForAnalogUserIO();
    //Request To Cancel request.
    Q_INVOKABLE void getCancelRequestForAnalogUserIO();
    QStringList analogIOOutputModel() const;

    QStringList analogOutputComboboxList() const;
    Q_INVOKABLE QString getAnalogOP(int index);                                              //combobx Options visbility list
    Q_INVOKABLE int getTotalSizeofAnalogOPList();                                            //Returns the count inputput model options to qml.
    Q_INVOKABLE void setOutputComboBoxSelection(int index, const QString &selection);        //assign the Event values from QML to cpp for output model.
    Q_INVOKABLE bool getOutputAnalogOpUserIOPinEnable(int index);
    Q_INVOKABLE void setOutputAnalogOpUserIOPinEnable(int index, bool state);                //assign the PinEnable values from QML to cpp for output model.
    Q_INVOKABLE QString getSelectedAnalogOpComboBox(int index);                              //combobox Options display on displaytext

    bool getIsGlobalAnalogIpSwtchEnable() const;
    void updateIsGlobalAnalogIpSwtchEnable(bool newIsGlobalAnalogIpSwtchEnable);

    bool getIsGlobalAnalogOpSwtchEnable() const;
    void updateIsGlobalAnalogOpSwtchEnable(bool newIsGlobalAnalogOpSwtchEnable);

private:

    /*COntainers to store Analog Inputs combobx models*/
    QStringList m_analogIPoptionsModel;
    QStringList m_analogIPoptionsModelComboboxList;
    QVector<QString> values;

    USERIO_ANALOG m_UserIOAnalog;
    DigitalIOMgr *m_DigitalIOMgr;
    int m_ActiveWelderId = -1;

    /*Containers to store Analog Output combobx models*/
    QStringList m_analogIOOutputModel;
    QStringList m_analogIpOutputComboboxList;
    QVector<QString> m_outputvalues;

    void filterComboBoxList();                                        // Function to filter the options based on slection.
    bool checkOptionIfAvailable(QString option);                      //check if available for slection.
    //To check if the option is available for selection or not.
    bool checkOptionIfAvailableInOutputModel(QString option);
    void setOutputAnalogIOEvent(int index,const QString &selection);

    //Digital Input mapping functions.
    QString psAnalogIpEventName(ANALOG_INPUT_LINE_FUNCTION Event);
    int MappingPSAnalogInputFunc(int input);
    void readUserIOAnalogStructure();
    int MappingPSOutputFunc(int input);
    QString psOutputEventName(ANALOG_OUTPUT_LINE_FUNCTION Event);
    void setAnalogIOInputEvent(int index,const QString &selection);

    bool m_IsGlobalAnalogIpSwtchEnable;

    bool m_IsGlobalAnalogOpSwtchEnable;

signals:
    /*Signals used to notify qml screen*/
    void analogIPoptionsModelModelChanged();
    void analogIOValuesUpdated();
    void digitalIOOutputModelChanged();

    void loadingDataChanged();

private slots:
    /*Slot to be called when data update signal generated by communication thread*/
    void OnUserIOAnalogUpdated(DigitalIOMgr *DigitalIOMgr_Obj, int WelderId);
};
#endif // USERIOANALOG_H
