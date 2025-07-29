/**************************************************************************

Copyright (c) Branson Ultrasonics Corporation, 1996-2025

This program is the property of Branson Ultrasonics Corporation
Copying of this software is expressly forbidden, without the prior
written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
IndustrialEthernetIO.cpp file handles Industrial Ethernet IN/OUT related operations.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 15/4/2025 - Initial version.
***************************************************************************/
#include "IndustrialEthernetIO.h"
#include "PlatformConfig.h"
#include "MultiwelderInterface.h"
#include "ActuatorInit.h"
/**************************************************************************//**
*
* \brief  - Constructor to initlaize the Control Word and Status Words combobox
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
IndustrialEthIO::IndustrialEthIO(QObject *parent) :
    QObject(parent),
    m_controlWordOptionsModel({}),
    m_statusWordoptionsModel({}),
    values({}),
    m_outputvalues({})
{
  connect(UpdateScreen::getInstance(), &UpdateScreen::IndustrialUserIOUpdated, this, &IndustrialEthIO::OnIndEthUserIOUpdated);
  readEthUserIOStructure();
  filterComboBoxList();
}

/**************************************************************************//**
*
* \brief - Destructor to clear memory allocations.
*
* \param  - None.
*
* \return  - None.
******************************************************************************/
IndustrialEthIO::~IndustrialEthIO()
{

}


/**************************************************************************//**
*
* \brief - This function handles the option list model based on the type of Actuator selector..
*
* \param  - None.
*
* \return - None.
******************************************************************************/
void IndustrialEthIO::optionSelection()
{
    if(PlatformConfig::GetConfigValue(MultiwelderInterface::GetActiveWelder(), ACTUATOR_TYPE_KEY) == ACTUATOR_ELECTRONIC )
    {
        m_controlWordOptionsModelComboboxList = {"Input Disable", "Control Word Disable", "Weld Mode", "Time Mode", "Energy Mode", "Peak Power Mode", "Ground Detect Mode", "Absolute Distance Mode", "Collapse Distance Mode", "Weld Amplitude", "Down Speed", "Trigger Force", "Weld Pressure", "Hold Time", "Hold Pressure"};
        m_statusWordOutputComboboxList = {"Output Disable", "Status Word Disable ","Weld Mode","Time Mode", "Energy Mode","Peak Power Mode", "Ground Detect Mode","Absolute Distance Mode","Collapse Distance Mode","Weld Amplitude","Down Speed","Trigger Force","Weld Pressure","Hold Time","Hold Pressure"};
    }
    else
    {
        m_controlWordOptionsModelComboboxList = {"Input Disable", "Control Word Disable", "Weld Mode", "Time Mode", "Energy Mode", "Peak Power Mode", "Ground Detect Mode",  "Weld Amplitude",  "Hold Time"};
        m_statusWordOutputComboboxList = {"Output Disable", "Status Word Disable ","Weld Mode","Time Mode", "Energy Mode","Peak Power Mode", "Ground Detect Mode", "Weld Amplitude",  "Hold Time"};
    }
}

/**************************************************************************//**
*
* \brief  - Role of the slot OnIndEthUserIOUpdated is to update values on Industrial UserIO screen.
*
*
* \param     - FieldBusIOMgr_Obj : Object pointer of type FieldBusIOMgr.
*            welderId : welder id
*
*
* \return   - none
******************************************************************************/
void IndustrialEthIO::OnIndEthUserIOUpdated(FieldBusIOMgr *FieldBusIOMgr_Obj, int WelderId)
{
  m_FieldBusIOMgr = FieldBusIOMgr_Obj;
  if(m_FieldBusIOMgr->IsFieldBusUsrIOStructUpdated() || m_ActiveWelderId != WelderId )
  {
      m_Fb_UserIO = m_FieldBusIOMgr->GetFieldBusUsrIOStruct();
      readEthUserIOStructure();
      m_ActiveWelderId = WelderId;
      m_FieldBusIOMgr->ResetFieldBusUsrIOUpdatedFlag();
      emit industrialEthIOValuesUpdated();      //Emit signal to notify QML about updated values
  }
}

/**************************************************************************//**
*
* \brief     -  Returns the control word input model for QML .
*
* \param     - None
*
* \return   - QStringList .
******************************************************************************/
QStringList IndustrialEthIO::controlWordOptionsModel() const
{
  return m_controlWordOptionsModel;
}

/**************************************************************************//**
*
* \brief     -  Returns the controlword input model for QML .
*
* \param     - NOne
*
* \return   - QStringList .
******************************************************************************/
QStringList IndustrialEthIO::controlWordOptionsModelComboboxList() const
{
  return m_controlWordOptionsModelComboboxList;
}
/**************************************************************************//**
*
* \brief     - Below function rerturns the no of controlword input present.
*
* \param     - None
*
* \return   - FB_IO_MAX_INPUTS.
******************************************************************************/
int IndustrialEthIO::getCountOfControlWrdIpModel()
{
    return FB_IO_MAX_INPUTS;
}

/**************************************************************************//**
*
* \brief     - Below function returns the no of status word output models.
*
* \param     - none
*
* \return   - FB_IO_MAX_OUTPUTS.
******************************************************************************/
int IndustrialEthIO::getCountOfStatusWrdOpModel()
{
    return FB_IO_MAX_OUTPUTS;
}
/**************************************************************************//**
*
* \brief     - Recevies the selected combobox value and index of combobox from QML for ControlWord input model.
*
* \param     - Index - selected combobox number . selection - selected value from combobox.
*
* \return   - None.
******************************************************************************/
void IndustrialEthIO::setComboBoxSelection(int index, const QString &selection)
{
    values[index] = selection;

    for(int i=0;i< m_controlWordOptionsModel.count();i++)
    {
        if(selection == m_controlWordOptionsModel[i] && selection != m_Not_Used)
        {
            m_controlWordOptionsModel.remove(i);
            break;
        }
    }
    filterComboBoxList();
    setControlWordEvent(index,selection);
    emit industrialEthIOValuesUpdated();      //Emit signal to notify QML about updated values
}

/**************************************************************************//**
*
* \brief     - Returns each option of control word input model present in the combobox based on index.
*
* \param     - index of specific elemnt
*
* \return   - QString .
******************************************************************************/
QString IndustrialEthIO::getControlWrdIp(int index)
{
    return m_controlWordOptionsModel[index];
}

/**************************************************************************//**
*
* \brief     - Returns each option of status word output model present in the combobox based on index.
*
* \param     - index of specific element
*
* \return   - QString .
******************************************************************************/
QString IndustrialEthIO::getStatusWordOP(int index)
{
    return m_statusWordoptionsModel[index];
}

/**************************************************************************//**
*
* \brief     -  Returns the total number status word output options present in the combobox for selection
*
* \param     - None
*
* \return   - int .
******************************************************************************/

int IndustrialEthIO::getTotalSizeofStatusWordOPList()
{
    return m_statusWordoptionsModel.count();
}

/**************************************************************************//**
*
* \brief     - Recevies the selected combobox value and index of combobox from QML for status word output model.
*
* \param     - Index - selected combobox number . selection - selected value from combobox.
*
* \return   - None.
******************************************************************************/
void IndustrialEthIO::setStatusWrdOutputComboBoxSelection(int index, const QString &selection)
{
    m_outputvalues[index] = selection;

    for(int i=0;i< m_statusWordoptionsModel.count();i++)
    {
        if(selection == m_statusWordoptionsModel[i] && selection != m_Not_Used)
        {
            m_statusWordoptionsModel.remove(i);
            break;
        }
    }
    filterComboBoxList();
    setStatusWordOutputComboBoxSelectionEvent(index,selection);
    emit industrialEthIOValuesUpdated();      //Emit signal to notify QML about updated values
}

/**************************************************************************//**
*
* \brief     - To set the status word output values received from QML.
*
* \param     - index - selected value index , selected - value of selected item.
*
* \return   - None.
******************************************************************************/
void IndustrialEthIO::setStatusWordOutputComboBoxSelectionEvent(int index ,const QString &selection) //setOutputAnalogIOEvent
{
    OUTPUT_FB_FUNCTION selectionType = FB_OUTPUT_FUNCTION_NONE ;

    for(auto it: UserIOFieldbusOpEventName)
    {
        if(it.second == selection.toStdString())
        {
            selectionType = it.first;
            break;
        }
    }
    switch (index)
    {
    case STATUS_WRD_1:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_01.FB_EVENT    =  selectionType;
        break;
    case STATUS_WRD_2:     m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_02.FB_EVENT  =  selectionType;
        break;
    case STATUS_WRD_3:     m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_03.FB_EVENT  =  selectionType;
        break;
    }
}


/**************************************************************************//**
*
* \brief     - returns the pinEnabled values to QML Status word output model.
*
* \param     - Index of the specific element.
*
* \return   - bool .
******************************************************************************/
bool IndustrialEthIO::getOutputStatusWrdPinEnable(int index)
{
    switch (index)
    {
    case STATUS_WRD_1:  return m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_01.IsStatusWordEnabled ;
        break;
    case STATUS_WRD_2:  return m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_02.IsStatusWordEnabled;
        break;
    case STATUS_WRD_3:  return m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_03.IsStatusWordEnabled;
        break;
    }
    return false;
}

/**************************************************************************//**
*
* \brief     - Sets the pinEnable values from QML based on selection for status word output model.
*
* \param     - Index of the selected element , state- enable/disable based on selection.
*
* \return   - None.
******************************************************************************/

void IndustrialEthIO::setOutputStatusWordPinEnable(int index, bool state)
{
    switch (index)
    {
    case STATUS_WRD_1:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_01.IsStatusWordEnabled =  state;
        break;
    case STATUS_WRD_2:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_02.IsStatusWordEnabled =  state;
        break;
    case STATUS_WRD_3:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_03.IsStatusWordEnabled =  state;
        break;
    }
}
/**************************************************************************//**
*
* \brief     - Remove the option that is selected on the combobox ,so theat it is unavailable for the other comboboxes
*            for selection.
*
* \param     - None
*
* \return   - None.
******************************************************************************/
void IndustrialEthIO::filterComboBoxList()
{
    //For Control Word - Input Model.
    m_controlWordOptionsModel.clear();
    m_controlWordOptionsModel.append(m_Not_Used);
    for(int i= 0;i< m_controlWordOptionsModelComboboxList.count();i++)
    {
        if(!(checkOptionIfAvailable(m_controlWordOptionsModelComboboxList[i])))
        {
            m_controlWordOptionsModel.append(m_controlWordOptionsModelComboboxList[i]);
        }
    }
    //For Status WOrd - Output Model.
    m_statusWordoptionsModel.clear();
    m_statusWordoptionsModel.append(m_Not_Used);
    for(int i= 0;i< m_statusWordOutputComboboxList.count();i++)
    {
        if(!(checkOptionIfAvailableInOutputModel(m_statusWordOutputComboboxList[i])))
        {
            m_statusWordoptionsModel.append(m_statusWordOutputComboboxList[i]);
        }
    }
}
/**************************************************************************//**
*
* \brief     - To validate the selected option from QML if it is present in the control word input combobox model or not.
*
* \param     - QString str
*
* \return   - bool .
******************************************************************************/
bool IndustrialEthIO::checkOptionIfAvailable(QString str)
{
    for(int i= 0;i< values.count() ;i++)
    {
        if(values[i] == str)
        {
            return true;
        }
    }
    return false;
}

/**************************************************************************//**
*
* \brief     - To validate the selected option from QML if it is present in the status word output combobox model or not.
*
* \param     - QString str
*
* \return   - bool .
******************************************************************************/
bool IndustrialEthIO::checkOptionIfAvailableInOutputModel(QString str)
{
    for(int i= 0;i< m_outputvalues.count() ;i++)
    {
        if(m_outputvalues[i] == str)
        {
            return true;
        }
    }
    return false;
}
/**************************************************************************//**
*
* \brief     - To set the control word input values received from QML.
*
* \param     - index - selected value index , selected - value of selected item.
*
* \return   - None.
******************************************************************************/
void IndustrialEthIO::setControlWordEvent(int index ,const QString &selection)
{
    INPUT_FB_FUNCTION selectionType = FB_INPUT_FUNCTION_NONE ;

    for(auto it: UserIOFieldbusIpEventName)
    {
        if(it.second == selection.toStdString())
        {
            selectionType = it.first;
            break;
        }
    }

    switch (index)
    {
    case CNTRL_WRD_1:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_01.FB_EVENT = selectionType;
              break;
    case CNTRL_WRD_2:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_02.FB_EVENT  = selectionType;
              break;
    case CNTRL_WRD_3:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_03.FB_EVENT = selectionType;
              break;
    }
}
/**************************************************************************//**
*
* \brief     - To read the structure from ASC and map to it's respective values based on structure values.
*
* \param     - None
*
* \return   - None.
******************************************************************************/
void IndustrialEthIO::readEthUserIOStructure()
{
    // Control Words Input model for display combobox values
    values.clear();

    int ControlWrd1 =   MappingControlWordInputFunc(m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_01.FB_EVENT);
    values.append(controlWordIpEventName(static_cast< INPUT_FB_FUNCTION>(ControlWrd1)));

    int ControlWrd2 =   MappingControlWordInputFunc(m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_02.FB_EVENT);
    values.append(controlWordIpEventName(static_cast< INPUT_FB_FUNCTION>(ControlWrd2)));

    int ControlWrd3 =   MappingControlWordInputFunc(m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_03.FB_EVENT);
    values.append(controlWordIpEventName(static_cast< INPUT_FB_FUNCTION>(ControlWrd3)));

    // Status Word Output model for display combobox values
    m_outputvalues.clear();

    int StatusWrd1 = MappingStatusWordFunc(m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_01.FB_EVENT );
    m_outputvalues.append(statusWrdOutputEventName(static_cast< OUTPUT_FB_FUNCTION>(StatusWrd1)));

    int StatusWrd2 = MappingStatusWordFunc(m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_02.FB_EVENT );
    m_outputvalues.append(statusWrdOutputEventName(static_cast< OUTPUT_FB_FUNCTION>(StatusWrd2)));

    int StatusWrd3 = MappingStatusWordFunc(m_Fb_UserIO.FB_CUSTOMIO.FbImplicitOutput.Status_Word_03.FB_EVENT );
    m_outputvalues.append(statusWrdOutputEventName(static_cast< OUTPUT_FB_FUNCTION>(StatusWrd3)));

    filterComboBoxList();
    emit industrialEthIOValuesUpdated();      //Emit signal to notify QML about updated values
}


/**************************************************************************//**
*
* \brief     - Used to map with the string values of the OUTPUT_FB_FUNCTION.
*
* \param     - OUTPUT_FB_FUNCTION - enum
*
* \return   - QString.
******************************************************************************/

QString IndustrialEthIO::statusWrdOutputEventName(OUTPUT_FB_FUNCTION Event)
{
    QString EventType;

    for(auto it: UserIOFieldbusOpEventName)
    {
       if(it.first == Event)
        {
            EventType = QString::fromStdString(it.second);
            break;
        }
    }
    return EventType;
}

/**************************************************************************//**
* \brief  - Correlates between UIC selected IO function and the Ethernet Io manager
* 			IO functions
*
* \param  - sw_event -	UIC IO selected event
*
* \return - function - correlated IO function
*
******************************************************************************/

int IndustrialEthIO::MappingStatusWordFunc(int sw_event)
{
    int function = FB_OUTPUT_FUNCTION_NONE;
    switch (sw_event)
    {
    case FB_OUTPUT_DISABLED:
        function = FB_OUTPUT_DISABLED;
        break;
    case OUT_WELD_MODE:
        function = OUT_WELD_MODE;
        break;
    case OUT_TIME_MODE:
        function = OUT_TIME_MODE;
        break;
    case OUT_ENERGY_MODE:
        function = OUT_ENERGY_MODE;
        break;
    case OUT_PEAK_POWER_MODE:
        function = OUT_PEAK_POWER_MODE;
        break;
    case OUT_GRD_DETECT_MODE:
        function = OUT_GRD_DETECT_MODE;
        break;
    case OUT_ABS_MODE:
        function = OUT_ABS_MODE;
        break;
    case OUT_COLLAPSE_MODE:
        function = OUT_COLLAPSE_MODE;
        break;
    case OUT_WELD_AMPLITUDE:
        function = OUT_WELD_AMPLITUDE;
        break;
    case OUT_DOWN_SPEED:
        function = OUT_DOWN_SPEED;
        break;
    case OUT_TRIGGER_FORCE:
        function = OUT_TRIGGER_FORCE;
        break;
    case OUT_WELD_PRESSURE:
        function = OUT_WELD_PRESSURE;
        break;
    case OUT_HOLD_TIME:
        function = OUT_HOLD_TIME;
        break;
    case OUT_HOLD_PRESSURE:
        function = OUT_HOLD_PRESSURE;
        break;
    case FB_OUTPUT_FUNCTION_MAX:
        function = FB_OUTPUT_FUNCTION_MAX;
        break;
    default:
        function = FB_OUTPUT_FUNCTION_NONE;
        break;
    }
    return function;
}
/**************************************************************************//**
*
* \brief     - Used to map with the string values of the INPUT_FB_FUNCTION .
*
* \param     - INPUT_FB_FUNCTION - enum
*
* \return   - QString.
******************************************************************************/

QString IndustrialEthIO::controlWordIpEventName(INPUT_FB_FUNCTION Event)
{
    QString EventType;

    for(auto it: UserIOFieldbusIpEventName)
    {
        if(it.first == Event)
        {
            EventType = QString::fromStdString(it.second);
            break;
        }
    }
    return EventType;
}
/**************************************************************************//**
* \brief  - Correlates between UIC selected IO function and the Industrial Ethernet IO manager
* 			IO functions
*
* \param  - cw_event -
*
* \return - function - correlated IO function
*
******************************************************************************/

int IndustrialEthIO::MappingControlWordInputFunc(int cw_event)
{
    int function = FB_INPUT_FUNCTION_NONE;

    switch (cw_event)
    {
    case FB_INPUT_DISABLE:
        function = FB_INPUT_DISABLE;
        break;
    case IN_WELD_MODE:
        function = IN_WELD_MODE;
        break;
    case IN_TIME_MODE:
        function = IN_TIME_MODE;
        break;
    case IN_ENERGY_MODE:
        function = IN_ENERGY_MODE;
        break;
    case IN_PEAK_POWER_MODE:
        function = IN_PEAK_POWER_MODE;
        break;
    case IN_GRD_DETECT_MODE:
        function = IN_GRD_DETECT_MODE;
           break;
    case IN_ABS_MODE:
        function = IN_ABS_MODE;
        break;
    case IN_COLLAPSE_MODE:
        function = IN_COLLAPSE_MODE;
        break;
    case IN_WELD_AMPLITUDE:
        function = IN_WELD_AMPLITUDE;
        break;
    case IN_DOWN_SPEED:
        function = IN_DOWN_SPEED;
        break;
    case IN_TRIGGER_FORCE:
        function = IN_TRIGGER_FORCE;
        break;
    case IN_WELD_PRESSURE:
        function = IN_WELD_PRESSURE;
        break;
    case IN_HOLD_TIME:
        function = IN_HOLD_TIME;
        break;
    case IN_HOLD_PRESSURE:
        function = IN_HOLD_PRESSURE;
        break;
    default:
        function = FB_INPUT_FUNCTION_NONE;
        break;
    }
    return function;
}
/**************************************************************************//**
*
* \brief     - Returns the option selected on input model present in the combobox based on index.
*
* \param     - index of selected element
*
* \return   - QString .
******************************************************************************/
QString IndustrialEthIO::getSelectedControlWrdComboBox(int index)
{
    return values[index];
}
/**************************************************************************//**
*
* \brief     - Returns the option selected on input model present in the combobox based on index.
*
* \param     - index of selected element
*
* \return   - QString .
******************************************************************************/
QString IndustrialEthIO::getSelectedStatusWrdOpComboBox(int index)
{
    return m_outputvalues[index];
}
/**************************************************************************//**
*
* \brief     - Returns the total number control word input options present in the combobox for selection
*
* \param     - none
*
* \return   - int .
******************************************************************************/

int IndustrialEthIO::getTotalSizeofControlWrdIpList()
{
    return m_controlWordOptionsModel.count();
}
/**************************************************************************//**
*
* \brief     - returns the status values to QML input model.
*
* \param     - Index of the specific element.
*
* \return   - bool .
******************************************************************************/
bool IndustrialEthIO::getControlWrdUserIOIpPinEnable(int index)
{
    switch (index)
    {
    case CNTRL_WRD_1:  return m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_01.IsControlWordEnabled;
        break;
    case CNTRL_WRD_2: return m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_02.IsControlWordEnabled ;
        break;
    case CNTRL_WRD_3: return m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_03.IsControlWordEnabled  ;
        break;
    }
    return false;
}

/**************************************************************************//**
*
* \brief     - Sets the pinEnable values from QML based on selection for controlWord input model.
*
* \param     - Index of the selected element , state- enable/disable based on selection.
*
* \return   - None.
******************************************************************************/

void IndustrialEthIO::setControlWrdIOPinEnable(int index, bool state)
{
    switch (index)
    {

    case CNTRL_WRD_1:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_01.IsControlWordEnabled = state;
              break;
    case CNTRL_WRD_2:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_02.IsControlWordEnabled  = state;
              break;
    case CNTRL_WRD_3:   m_Fb_UserIO.FB_CUSTOMIO.FbImplicitInput.Control_Word_03.IsControlWordEnabled  = state;
              break;
    }
}
/**************************************************************************//**
*
* \brief     - Send save request to ASC when user clicks Save button on HMI.
*
* \param     - None
*
* \return   - void.
******************************************************************************/
void IndustrialEthIO::getSaveRequestForIndusEthIO()
{
   m_FieldBusIOMgr->SaveIndFieldBusUserIOValues(m_Fb_UserIO);
}
/**************************************************************************//**
*
* \brief     - Send Reset to Default request from HMI.
*
* \param     - NOne
*
* \return   - void.
******************************************************************************/
void IndustrialEthIO::getResetToDefRequestForIndusEthIO()
{
    m_FieldBusIOMgr->SetResetToDefaultIndFieldBusUsrIORequest(true);
    emit industrialEthIOValuesUpdated();
}

/**************************************************************************//**
*
* \brief     -  Returns the status word op model for QML .
*
* \param     - None
*
* \return   - QStringList .
******************************************************************************/
QStringList IndustrialEthIO::statusWordoptionsModel() const
{
    return m_statusWordoptionsModel;
}
/**************************************************************************//**
*
* \brief     -  Returns the control word input model for QML .
*
* \param     - None
*
* \return   - QStringList .
******************************************************************************/
QStringList IndustrialEthIO::statusWordoptionsModelComboboxList() const
{
    return m_statusWordOutputComboboxList;
}

