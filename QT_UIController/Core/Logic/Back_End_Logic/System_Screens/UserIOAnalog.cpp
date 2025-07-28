/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------
    UserIOAnalog.cpp file handles Analog IP/OP related operations.
--------------------------- REVISION HISTORY ------------------------------
    rev1: 30/1/2025 - Initial version.
***************************************************************************/
#include "UserIOAnalog.h"
/**************************************************************************//**
*
* \brief  - Constructor to initlaize the Analog Input and Output combobox
*
* \param  - QObject* parent
*
* \return - None
*
******************************************************************************/
UserIOAnalog::UserIOAnalog(QObject *parent) :
    QObject(parent),
    m_analogIPoptionsModelComboboxList({"Input Disable","Input Amplitude","Frequency offset"}),
    m_analogIpOutputComboboxList({"Output Disable", "Output Power", "Output Amplitude","Output Current","Output Frequency"}),
    m_analogIPoptionsModel({}),
    m_analogIOOutputModel({}),
    values({}),
    m_outputvalues({})
{
  connect(UpdateScreen::getInstance(), &UpdateScreen::DigitalUserIOAnalogUpdated, this, &UserIOAnalog::OnUserIOAnalogUpdated);
  readUserIOAnalogStructure();
  filterComboBoxList();
}

/**************************************************************************//**
*
* \brief   - Destructor to clear memory allocations.
*
* \param   - None.
*
* \return  - None.
******************************************************************************/
UserIOAnalog::~UserIOAnalog()
{

}

/**************************************************************************//**
*
* \brief   - Role of the slot OnUserIOAnalogUpdated is to update values on UserIO Analog screen.
*
*
* \param   - DigitalIOMgr_Obj : Object pointer of type DigitalIOMgr.
*            welderId : welder id
*
*
* \return  - none
******************************************************************************/
void UserIOAnalog::OnUserIOAnalogUpdated(DigitalIOMgr *DigitalIOMgr_Obj, int WelderId)
{
  m_DigitalIOMgr = DigitalIOMgr_Obj;
  if(m_DigitalIOMgr->IsAnalogIOStructUpdated() || m_ActiveWelderId != WelderId )
  {
      m_UserIOAnalog = m_DigitalIOMgr->GetAnalogIOStruct();
      m_IsGlobalAnalogIpSwtchEnable = m_UserIOAnalog.GlobalAnalogInputSwitchState;
      m_IsGlobalAnalogOpSwtchEnable = m_UserIOAnalog.GlobalAnalogOutputSwitchState;
      readUserIOAnalogStructure();
      m_ActiveWelderId = WelderId;
      m_DigitalIOMgr->ResetIsLastAnalogIOUpdatedFlag();
      emit analogIOValuesUpdated();      //Emit signal to notify QML about updated values
  }
}

/**************************************************************************//**
*
* \brief   -  Returns the analog input model for QML .
*
* \param   - NOne
*
* \return  - QStringList .
******************************************************************************/
QStringList UserIOAnalog::analogIPoptionsModel() const
{
  return m_analogIPoptionsModel;
}

/**************************************************************************//**
*
* \brief   -  Returns the analog input model for QML .
*
* \param   - NOne
*
* \return  - QStringList .
******************************************************************************/
QStringList UserIOAnalog::analogIPoptionsModelComboboxList() const
{
  return m_analogIPoptionsModelComboboxList;
}
/**************************************************************************//**
*
* \brief   - Below function rerturns the no of Analog models present.
*
* \param   - None
*
* \return  - ANALOG_IO_MAX_INPUTS.
******************************************************************************/
int UserIOAnalog::getCountOfAnalogIpModel()
{
    return ANALOG_IO_MAX_INPUTS;
}

/**************************************************************************//**
*
* \brief   - Below function returns the no of anolog output models.
*
* \param   - none
*
* \return  - ANALOG_IO_MAX_OUTPUTS.
******************************************************************************/
int UserIOAnalog::getCountOfAnalogOpModel()
{
    return ANALOG_IO_MAX_OUTPUTS;
}
/**************************************************************************//**
*
* \brief   - Recevies the selected combobox value and index of combobox from QML for analog input model.
*
* \param   - Index - selected combobox number . selection - selected value from combobox.
*
* \return  - None.
******************************************************************************/
void UserIOAnalog::setComboBoxSelection(int index, const QString &selection)
{
    values[index] = selection;

    for(int i=0;i< m_analogIPoptionsModel.count();i++)
    {
        if(selection == m_analogIPoptionsModel[i] && selection != "Not Used")
        {
            m_analogIPoptionsModel.remove(i);
            break;
        }
    }
    filterComboBoxList();
    setAnalogIOInputEvent(index,selection);
    emit analogIOValuesUpdated();      //Emit signal to notify QML about updated values
}

/**************************************************************************//**
*
* \brief   - Returns each option of analog input model present in the combobox based on index.
*
* \param   - index of specific elemnt
*
* \return  - QString .
******************************************************************************/
QString UserIOAnalog::getAnalogIp(int index)
{
    return m_analogIPoptionsModel[index];
}

/**************************************************************************//**
*
* \brief   - Returns each option of analog output model present in the combobox based on index.
*
* \param   - index of specific element
*
* \return  - QString .
******************************************************************************/
QString UserIOAnalog::getAnalogOP(int index)
{
    return m_analogIOOutputModel[index];
}

/**************************************************************************//**
*
* \brief   -  Returns the total number analog output options pesent in the combobox for selection
*
* \param   - None
*
* \return  - int .
******************************************************************************/

int UserIOAnalog::getTotalSizeofAnalogOPList()
{
    return m_analogIOOutputModel.count();
}

/**************************************************************************//**
*
* \brief   - Recevies the selected combobox value and index of combobox from QML for analog output model.
*
* \param   - Index - selected combobox number . selection - selected value from combobox.
*
* \return  - None.
******************************************************************************/
void UserIOAnalog::setOutputComboBoxSelection(int index, const QString &selection)
{
    m_outputvalues[index] = selection;

    for(int i=0;i< m_analogIOOutputModel.count();i++)
    {
        if(selection == m_analogIOOutputModel[i] && selection != "Not Used")
        {
            m_analogIOOutputModel.remove(i);
            break;
        }
    }
    filterComboBoxList();
    setOutputAnalogIOEvent(index,selection);
    emit analogIOValuesUpdated();      //Emit signal to notify QML about updated values
}

/**************************************************************************//**
*
* \brief   - To set the analog output values received from QML.
*
* \param   - index - selected value index , selected - value of selected item.
*
* \return  - None.
******************************************************************************/
void UserIOAnalog::setOutputAnalogIOEvent(int index ,const QString &selection)
{
    ANALOG_OUTPUT_LINE_FUNCTION selectionType = AN_OUTPUT_FUNCTION_NONE ;

    for(auto it: UserIOAnalogOpEventName)
    {
        if(it.second == selection.toStdString())
        {
            selectionType = it.first;
            break;
        }
    }
    switch (index) {
    case 0:   m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogOutput.J3_24.PS_EVENT =  selectionType;
        break;
    case 1:     m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogOutput.J3_25.PS_EVENT  =  selectionType;
        break;
    }
}


/**************************************************************************//**
*
* \brief   - returns the pinEnabled values to QML analog output model.
*
* \param   - Index of the specific element.
*
* \return  - bool .
******************************************************************************/
bool UserIOAnalog::getOutputAnalogOpUserIOPinEnable(int index)
{
    switch (index)
    {
    case 0:  return m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogOutput.J3_24.IsPinEnabled ;
        break;
    case 1:  return m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogOutput.J3_25.IsPinEnabled ;
        break;
    }
    return false;
}

/**************************************************************************//**
*
* \brief   - Sets the pinEnable values from QML based on selection for analog output model.
*
* \param   - Index of the selected element , state- enable/disable based on selection.
*
* \return  - None.
******************************************************************************/

void UserIOAnalog::setOutputAnalogOpUserIOPinEnable(int index, bool state)
{
    switch (index) {

    case 0:   m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogOutput.J3_24.IsPinEnabled =  state;
        break;
    case 1:   m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogOutput.J3_25.IsPinEnabled =  state;
        break;

        }
}
/**************************************************************************//**
*
* \brief   - Remove the option that is selected on the combobox ,so theat it is unavailable for the other comboboxes
*            for selection.
*
* \param   - None
*
* \return  - None.
******************************************************************************/
void UserIOAnalog::filterComboBoxList()
{
    //For Analog Input Model.
    m_analogIPoptionsModel.clear();
    m_analogIPoptionsModel.append("Not Used");
    for(int i= 0;i< m_analogIPoptionsModelComboboxList.count();i++)
    {
        if(!(checkOptionIfAvailable(m_analogIPoptionsModelComboboxList[i])))
        {
            m_analogIPoptionsModel.append(m_analogIPoptionsModelComboboxList[i]);
        }
    }

    //For Analog Output Model.
    m_analogIOOutputModel.clear();
    m_analogIOOutputModel.append("Not Used");
    for(int i= 0;i< m_analogIpOutputComboboxList.count();i++)
    {
        if(!(checkOptionIfAvailableInOutputModel(m_analogIpOutputComboboxList[i])))
        {
            m_analogIOOutputModel.append(m_analogIpOutputComboboxList[i]);
        }
    }
}
/**************************************************************************//**
*
* \brief   - To validate the selected option from QML if it is present in the input combobox model or not.
*
* \param   - QString str
*
* \return  - bool .
******************************************************************************/
bool UserIOAnalog::checkOptionIfAvailable(QString str)
{
    for(int i= 0;i< values.count() ;i++)
    {
        if(values[i] == str){
            return true;
        }
    }
    return false;
}

/**************************************************************************//**
*
* \brief   - To validate the selected option from QML if it is present in the analog output combobox model or not.
*
* \param   - QString str
*
* \return  - bool .
******************************************************************************/
bool UserIOAnalog::checkOptionIfAvailableInOutputModel(QString str)
{
    for(int i= 0;i< m_outputvalues.count() ;i++)
    {
        if(m_outputvalues[i] == str){
            return true;
        }
    }
    return false;
}
/**************************************************************************//**
*
* \brief   - To set the analog input values received from QML.
*
* \param   - index - selected value index , selected - value of selected item.
*
* \return  - None.
******************************************************************************/
void UserIOAnalog::setAnalogIOInputEvent(int index ,const QString &selection)
{
    ANALOG_INPUT_LINE_FUNCTION selectionType = AN_INPUT_FUNCTION_NONE ;

    for(auto it: UserIOAnalogIpEventName)
    {
        if(it.second == selection.toStdString())
        {
            selectionType = it.first;
            break;
        }
    }
    switch (index) {
    case 0:   m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogInput.J3_17.PS_EVENT = selectionType;//PS_USERIO.PsDigitalInput.J116_01.PS_EVENT =  selectionType;
              break;
    case 1:   m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogInput.J3_18.PS_EVENT = selectionType;//.PsDigitalInput.J116_02.PS_EVENT =  selectionType;
              break;
    }
}
/**************************************************************************//**
*
* \brief   - To read the structure from ASC and map to it's respective values based on structure values.
*
* \param   - None
*
* \return  - None.
******************************************************************************/
void UserIOAnalog::readUserIOAnalogStructure()
{
    // Analog Input model for display combobox values
    values.clear();

    int AnalogIP1 =   MappingPSAnalogInputFunc(m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogInput.J3_17.PS_EVENT);
    values.append(psAnalogIpEventName(static_cast< ANALOG_INPUT_LINE_FUNCTION>(AnalogIP1)));

    int AnalogIP2 =   MappingPSAnalogInputFunc(m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogInput.J3_18.PS_EVENT);
    values.append(psAnalogIpEventName(static_cast< ANALOG_INPUT_LINE_FUNCTION>(AnalogIP2)));

    // Analog Output model for display combobox values
    m_outputvalues.clear();

    int AnalogOP1 = MappingPSOutputFunc(m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogOutput.J3_24.PS_EVENT);
    m_outputvalues.append(psOutputEventName(static_cast< ANALOG_OUTPUT_LINE_FUNCTION>(AnalogOP1)));

    int AnalogOP2 = MappingPSOutputFunc(m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogOutput.J3_25.PS_EVENT);
    m_outputvalues.append(psOutputEventName(static_cast< ANALOG_OUTPUT_LINE_FUNCTION>(AnalogOP2)));

    filterComboBoxList();
    emit analogIOValuesUpdated();      //Emit signal to notify QML about updated values
}


/**************************************************************************//**
*
* \brief   - Used to map with the string values of the ANALOG_OUTPUT_LINE_FUNCTION.
*
* \param   - ANALOG_OUTPUT_LINE_FUNCTION - enum
*
* \return  - QString.
******************************************************************************/

QString UserIOAnalog::psOutputEventName(ANALOG_OUTPUT_LINE_FUNCTION Event)
{
    QString EventType;

    for(auto it: UserIOAnalogOpEventName)
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
* \brief  - Correlates between UIC selected IO function and the I/O manager
* 			IO functions
*
* \param  - ps_event -	UIC IO selected event
*
* \return - function - correlated IO function
*
******************************************************************************/
int UserIOAnalog::MappingPSOutputFunc(int ps_event)
{
    int function = AN_OUTPUT_FUNCTION_NONE;

    switch (ps_event)
    {
    case AN_OUTPUT_DISABLE:
              function = AN_OUTPUT_DISABLE;
              break;
    case AN_OUTPUT_POWER:
              function = AN_OUTPUT_POWER;
              break;
    case AN_OUTPUT_AMPLITUDE:
              function = AN_OUTPUT_AMPLITUDE;
              break;
    case AN_OUTPUT_CURRENT:
              function = AN_OUTPUT_CURRENT;
              break;
    case AN_OUTPUT_FREQUENCY:
              function = AN_OUTPUT_FREQUENCY;
              break;
    case AN_OUTPUT_FUNCTION_MAX:
              function = AN_OUTPUT_FUNCTION_MAX;
              break;
    }
    return function;
}
/**************************************************************************//**
*
* \brief   - Used to map with the string values of the ANALOG_INPUT_LINE_FUNCTION .
*
* \param   - ANALOG_INPUT_LINE_FUNCTION - enum
*
* \return  - QString.
******************************************************************************/

QString UserIOAnalog::psAnalogIpEventName(ANALOG_INPUT_LINE_FUNCTION Event)
{
    QString EventType;

    for(auto it: UserIOAnalogIpEventName)
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
* \brief  - Correlates between UIC selected IO function and the I/O manager
* 			IO functions
*
* \param  - ps_event -	UIC IO selected event
*
* \return - function - correlated IO function
*
******************************************************************************/
int UserIOAnalog::MappingPSAnalogInputFunc(int ps_event)
{
    int function = AN_INPUT_FUNCTION_NONE;

    switch (ps_event)
    {
    case AN_INPUT_DISABLE:
        function = AN_INPUT_DISABLE;
        break;
    case AN_INPUT_AMPLITUDE:
        function = AN_INPUT_AMPLITUDE;
        break;
    case AN_INPUT_FREQUENCY_OFFSET:
        function = AN_INPUT_FREQUENCY_OFFSET;
        break;
    }
    return function;
}
/**************************************************************************//**
*
* \brief   - Returns the option selected on input model present in the combobox based on index.
*
* \param   - index of selected element
*
* \return  - QString .
******************************************************************************/
QString UserIOAnalog::getSelectedAnalogComboBox(int index)
{
    return values[index];
}
/**************************************************************************//**
*
* \brief   - Returns the option selected on input model present in the combobox based on index.
*
* \param   - index of selected element
*
* \return  - QString .
******************************************************************************/
QString UserIOAnalog::getSelectedAnalogOpComboBox(int index)
{
    return m_outputvalues[index];
}
/**************************************************************************//**
*
* \brief   - Returns the total number analog input options present in the combobox for selection
*
* \param   - none
*
* \return  - int .
******************************************************************************/

int UserIOAnalog::getTotalSizeofAnalogIpList()
{
    return m_analogIPoptionsModel.count();
}
/**************************************************************************//**
*
* \brief   - returns the status values to QML input model.
*
* \param   - Index of the specific element.
*
* \return  - bool .
******************************************************************************/
bool UserIOAnalog::getAnalogUserIOIpPinEnable(int index)
{
    switch (index) {
    case 0:  return m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogInput.J3_17.IsPinEnabled ;
             break;
    case 1: return m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogInput.J3_18.IsPinEnabled  ;
             break;
    }
    return false;
}

/**************************************************************************//**
*
* \brief   - Sets the pinEnable values from QML based on selection for analog input model.
*
* \param   - Index of the selected element , state- enable/disable based on selection.
*
* \return  - None.
******************************************************************************/

void UserIOAnalog::setAnalogUserIOPinEnable(int index, bool state)
{
    switch (index) {

    case 0:   m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogInput.J3_17.IsPinEnabled = state;
              break;
    case 1:    m_UserIOAnalog.PS_USERIO_ANALOG.PsAnalogInput.J3_18.IsPinEnabled = state;
              break;
    }
}
/**************************************************************************//**
*
* \brief   - Send save request to ASC when user clicks Save button on HMI.
*
* \param   - None
*
* \return  - void.
******************************************************************************/
void UserIOAnalog::getSaveRequestForAnalogUserIO()
{
    m_DigitalIOMgr->SaveAnalogUserIOValues(m_UserIOAnalog);
}
/**************************************************************************//**
*
* \brief   - Send Reset to Default request from HMI.
*
* \param   - NOne
*
* \return  - none.
******************************************************************************/
void UserIOAnalog::getResetToDefRequestForAnalogUserIO()
{

    m_DigitalIOMgr->SetResetToDefaultAnalogUsrIORequest(true);

    emit analogIOValuesUpdated();
}
/**************************************************************************//**
*
* \brief   - Send Cancel request from HMI.
*
* \param   - NOne
*
* \return  - none.
******************************************************************************/
void UserIOAnalog::getCancelRequestForAnalogUserIO()
{
    m_UserIOAnalog = m_DigitalIOMgr->GetAnalogIOStruct();
    m_IsGlobalAnalogIpSwtchEnable = m_UserIOAnalog.GlobalAnalogInputSwitchState;
    m_IsGlobalAnalogOpSwtchEnable = m_UserIOAnalog.GlobalAnalogOutputSwitchState;
    readUserIOAnalogStructure();
    emit analogIOValuesUpdated();
}
/**************************************************************************//**
*
* \brief   -  Returns the analog input model for QML .
*
* \param   - NOne
*
* \return  - QStringList .
******************************************************************************/
QStringList UserIOAnalog::analogIOOutputModel() const
{
    return m_analogIOOutputModel;
}
/**************************************************************************//**
*
* \brief   -  Returns the analog input model for QML .
*
* \param   - NOne
*
* \return  - QStringList .
******************************************************************************/
QStringList UserIOAnalog::analogOutputComboboxList() const
{
    return m_analogIpOutputComboboxList;
}

/**************************************************************************//**
*
* \brief   - Below function returns the IsGlobalAnalogIpSwtchEnable status.
*
* \param   - none
*
* \return  - m_IsGlobalAnalogIpSwtchEnable.
******************************************************************************/
bool UserIOAnalog::getIsGlobalAnalogIpSwtchEnable() const
{
    return m_IsGlobalAnalogIpSwtchEnable;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsGlobalAnalogIpSwtchEnable status.
*
* \param   - IsGlobalAnalogIpSwtchEnable
*
* \return  - none.
******************************************************************************/
void UserIOAnalog::updateIsGlobalAnalogIpSwtchEnable(bool newIsGlobalAnalogIpSwtchEnable)
{
    if (m_IsGlobalAnalogIpSwtchEnable != newIsGlobalAnalogIpSwtchEnable)
    {
            m_IsGlobalAnalogIpSwtchEnable = newIsGlobalAnalogIpSwtchEnable;
            m_UserIOAnalog.GlobalAnalogInputSwitchState = m_IsGlobalAnalogIpSwtchEnable;
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the IsGlobalAnalogOpSwtchEnable status.
*
* \param   - none
*
* \return  - IsGlobalAnalogOpSwtchEnable.
******************************************************************************/
bool UserIOAnalog::getIsGlobalAnalogOpSwtchEnable() const
{
    return m_IsGlobalAnalogOpSwtchEnable;
}

/**************************************************************************//**
*
* \brief   - Below function updates the IsGlobalAnalogOpSwtchEnable status.
*
* \param   - IsGlobalAnalogOpSwtchEnable
*
* \return  - none.
******************************************************************************/
void UserIOAnalog::updateIsGlobalAnalogOpSwtchEnable(bool newIsGlobalAnalogOpSwtchEnable)
{
    if (m_IsGlobalAnalogOpSwtchEnable != newIsGlobalAnalogOpSwtchEnable)
    {
         m_IsGlobalAnalogOpSwtchEnable = newIsGlobalAnalogOpSwtchEnable;
            m_UserIOAnalog.GlobalAnalogOutputSwitchState = m_IsGlobalAnalogOpSwtchEnable;
    }
}
