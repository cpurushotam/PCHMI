/**************************************************************************

Copyright (c) Branson Ultrasonics Corporation, 1996-2025

This program is the property of Branson Ultrasonics Corporation
Copying of this software is expressly forbidden, without the prior
written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
IndustrialEthIO.h file handles Industrial Ethernet User IO / Inputs and Output functionalities related operations.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 15/04/2025 - Initial version.
***************************************************************************/
#ifndef IndustrialEthIO_H
#define IndustrialEthIO_H

#include <QObject>
#include "UpdateScreens.h"

class IndustrialEthIO : public QObject
{
    /*Q_PROPERTY macro is used for declaring properties in classes that inherit QObject.
      Properties behave like class data members, but they have additional features accessible through the Meta-Object System.*/
    Q_OBJECT

    Q_PROPERTY(QStringList controlWordOptionsModel READ controlWordOptionsModel NOTIFY controlWordOptionsModelModelChanged)
    Q_PROPERTY(QStringList controlWordOptionsModelComboboxList READ controlWordOptionsModelComboboxList NOTIFY controlWordOptionsModelModelChanged)
    Q_PROPERTY(QStringList statusWordoptionsModel READ statusWordoptionsModel NOTIFY statusWordoptionsModelChanged)
    Q_PROPERTY(QStringList statusWordOutputComboboxList READ statusWordoptionsModelComboboxList NOTIFY statusWordoptionsModelChanged)

public:
    explicit IndustrialEthIO(QObject *parent = nullptr);
    ~IndustrialEthIO();

    Q_INVOKABLE void optionSelection();                 //fill model with the options based on ACTUATOR type
    QStringList controlWordOptionsModel() const;
    QStringList controlWordOptionsModelComboboxList() const;

    Q_INVOKABLE void setComboBoxSelection(int index, const QString &selection);  //assign the Event values from QML to cpp for input model.
    Q_INVOKABLE QString getControlWrdIp(int index);                          //combobx Options visbility list
    Q_INVOKABLE QString getSelectedControlWrdComboBox(int index);         //combobox Options display on displaytext
    Q_INVOKABLE int getTotalSizeofControlWrdIpList();                     //Returns the count inputput model options to qml.
    /*Analog output model state and pinEnable value for digital Input model on HMI*/
    Q_INVOKABLE bool getControlWrdUserIOIpPinEnable(int index);
    Q_INVOKABLE void setControlWrdIOPinEnable(int index, bool state);  //assign the PinEnable values from QML to cpp for input model.

    Q_INVOKABLE int getCountOfControlWrdIpModel();                        //Returns the count inputput model options to qml.
    Q_INVOKABLE int getCountOfStatusWrdOpModel();                        //Returns the count inputput model options to qml.

    //Request To ASC on Save request.
    Q_INVOKABLE void getSaveRequestForIndusEthIO();
    //Request To ASC on ResetToDefault request.
    Q_INVOKABLE void getResetToDefRequestForIndusEthIO();
    QStringList statusWordoptionsModel() const;

    QStringList statusWordoptionsModelComboboxList() const;
    Q_INVOKABLE QString getStatusWordOP(int index);                                              //combobx Options visbility list
    Q_INVOKABLE int getTotalSizeofStatusWordOPList();                                            //Returns the count inputput model options to qml.
    Q_INVOKABLE void setStatusWrdOutputComboBoxSelection(int index, const QString &selection);        //assign the Event values from QML to cpp for output model.
    Q_INVOKABLE bool getOutputStatusWrdPinEnable(int index);
    Q_INVOKABLE void setOutputStatusWordPinEnable(int index, bool state);                //assign the PinEnable values from QML to cpp for output model.
    Q_INVOKABLE QString getSelectedStatusWrdOpComboBox(int index);                              //combobox Options display on displaytext

private:

    /*COntainers to store Control word Inputs combobx models*/
    QStringList m_controlWordOptionsModel;
    QStringList m_controlWordOptionsModelComboboxList;
    QVector<QString> values;

    FB_USERIO m_Fb_UserIO;
    FieldBusIOMgr *m_FieldBusIOMgr;
    int m_ActiveWelderId = -1;

    /*Containers to store Status word output combobx models*/
    QStringList m_statusWordoptionsModel;
    QStringList m_statusWordOutputComboboxList;
    QVector<QString> m_outputvalues;

    void filterComboBoxList();                                        // Function to filter the options based on slection.
    bool checkOptionIfAvailable(QString option);                      //check if available for slection.
    //To check if the option is available for selection or not.
    bool checkOptionIfAvailableInOutputModel(QString option);
    void setStatusWordOutputComboBoxSelectionEvent(int index,const QString &selection);

    //Control Word Input mapping functions.
    QString controlWordIpEventName(INPUT_FB_FUNCTION Event);
    int MappingControlWordInputFunc(int input);
    void readEthUserIOStructure();

    //Status Word output mapping functions.
    int MappingStatusWordFunc(int input);
    QString statusWrdOutputEventName(OUTPUT_FB_FUNCTION Event);
    void setControlWordEvent(int index,const QString &selection);

    QString m_Not_Used = "Not Used";

    //Control Word enum
    typedef	enum
    {
        CNTRL_WRD_1 = 0,
        CNTRL_WRD_2,
        CNTRL_WRD_3
    }CONTROLWORD;
   //Status word enum
    typedef	enum{
        STATUS_WRD_1 = 0,
        STATUS_WRD_2,
        STATUS_WRD_3
    }STATUSWORD;

signals:
    /*Signals used to notify qml screen*/
    void controlWordOptionsModelModelChanged();
    void industrialEthIOValuesUpdated();
    void statusWordoptionsModelChanged();

private slots:
    /*Slot to be called when data update signal generated by communication thread*/
    void OnIndEthUserIOUpdated(FieldBusIOMgr *FieldBusIOMgr_Obj, int WelderId);
};
#endif // INDUSTRAILETHIO
