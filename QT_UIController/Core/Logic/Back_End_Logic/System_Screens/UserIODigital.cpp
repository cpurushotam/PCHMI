/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2024

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------
 Declares UserIODigital class which is responsible to do interaction between frontend and backend .
***************************************************************************/
#include "UserIODigital.h"
/**************************************************************************//**
*
* \brief   - Constructor to initliaze the digital input model and digital output model which is used to display the
*            comboboxes at QML.
*
* \param   -
*
* \return  - None.
******************************************************************************/
UserIODigital::UserIODigital(QObject *parent) :
    QObject(parent),
    m_digitalIpComboboxList({"Input Disable","UltraSonic disable","Cable Detect",
                            "Display Lock","Cycle Abort","Alarm Reset","Ultrasonic delay",
                            "Hold Delay","Load Recipe",
                            "Tooling input","Horn Scan","Horn Seek","Horn Test","Memory clear","Part Present input",
                            "Recipe bit 1","Recipe bit 2","Recipe bit 4","Recipe bit 8","Estop Reset", "External Amplitude Trigger 1",
                            "External Amplitude Trigger 2", "External Amplitude Trigger 3"}),

    m_digitalIpOutputComboboxList({"Output Disable","System Ready","Cycle Running",
                                   "Cycle Ok","Ultrsonic Active","Solenoid Active","Actuator Clear",
                                   "AfterBurst Delay","AfterBurst Time","Pb Release","Hold Time Active",
                                   "Actuator Home","Horn Seek","Horn Scan","Alarm General",
                                   "Alarm Custom","Alarm Reject Part","Alarm Cuttoff","Alarm Overload",
                                   "Tooling Output","Confirm Recipe"}),
    m_optionsModel({}),
    m_digitalIOOutputModel({}),
    values({}),
    m_outputvalues({})
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::DigitalUserIOUpdated, this, &UserIODigital::OnUserIODigitalDetailsUpdated);
    readUserIOStructure();
    filterComboBoxList();
}
/**************************************************************************//**
*
* \brief   -  Returns the digital input model for QML .
*
* \param   - NOne
*
* \return  - QStringList .
******************************************************************************/
QStringList UserIODigital::optionsModel() const
{
    return m_optionsModel;
}

/**************************************************************************//**
*
* \brief   - Returns the digital output model for QML
*
* \param   - None
*
* \return  - QStringList .
******************************************************************************/
QStringList UserIODigital::digitalIOOutputModel() const
{
    return m_digitalIOOutputModel;
}
/**************************************************************************//**
*
* \brief   - Retuens the Digital Input model for displaying of combobox selection values.
*
* \param   -
*
* \return  - None.
******************************************************************************/
QStringList UserIODigital::digitalIpComboboxList() const
{
    return m_digitalIpComboboxList;
}

/**************************************************************************//**
*
* \brief   - Retuens the Digital Output model for displaying of combobox selection values.
*
* \param   -
*
* \return  - None.
******************************************************************************/
QStringList UserIODigital::digitalIpOutputComboboxList() const
{
    return m_digitalIpOutputComboboxList;
}
/**************************************************************************//**
*
* \brief   - Returns the selected combobox value for input model.
*
* \param   - Index of the selected value .
*
* \return  - QString .
******************************************************************************/
QString UserIODigital::getComboBoxText(int index)
{
    if (index >= 0 && index < DIGITAL_IO_MAX_INPUTS) {
        return values[index];
    }
    return QString();
}

/**************************************************************************//**
*
* \brief   - Returns the selected combobox value for output model.
*
* \param   - Index of the selected value.
*
* \return  - QString .
******************************************************************************/
QString UserIODigital::getDgOutPutComboBoxText(int index)
{
    if (index >= 0 && index < DIGITAL_IO_MAX_OUTPUTS) {
        return m_outputvalues[index];
    }
    return QString();
}
/**************************************************************************//**
*
* \brief   - Recevies the selected combobox value and index of combobox from QML for digital input model.
*
* \param   - Index - selected combobox number . selection - selected value from combobox.
*
* \return  - None.
******************************************************************************/
void UserIODigital::setComboBoxSelection(int index, const QString &selection)
{
    values[index] = selection;
    QString textVal = "Cable Detect";
    m_GetIndexValue.clear();

    /*Update the vector with cable detect option data either available or not*/
    for(int i = 0; i < values.count(); i++)
    {
        if(values[i] == textVal)
        {
            m_GetIndexValue.append(true);
        }

        else
        {
            m_GetIndexValue.append(false);
        }
    }

    for(int i=0;i< m_optionsModel.count();i++)
    {
        if(selection == m_optionsModel[i] && selection != "Not Used")
        {
            m_optionsModel.remove(i);
            break;
        }
    }
    filterComboBoxList();
    setDigitalIOEvent(index,selection);
    emit valuesUpdated();      //Emit signal to notify QML about updated values
}

/**************************************************************************//**
*
* \brief   - Recevies the selected combobox value and index of combobox from QML for digital output model.
*
* \param   - Index - selected combobox number . selection - selected value from combobox.
*
* \return  - None.
******************************************************************************/
void UserIODigital::setOutputComboBoxSelection(int index, const QString &selection)
{
    m_outputvalues[index] = selection;

    for(int i=0;i< m_digitalIOOutputModel.count();i++)
    {
        if(selection == m_digitalIOOutputModel[i] && selection != "Not Used")
        {
            m_digitalIOOutputModel.remove(i);
            break;
        }
    }
    filterComboBoxList();
    setOutputDigitalIOEvent(index,selection);
    emit valuesUpdated();      //Emit signal to notify QML about updated values
}

/**************************************************************************//**
*
* \brief   - To set the digital input values received from QML.
*
* \param   - index - selected value index , selected - value of selected item.
*
* \return  - None.
******************************************************************************/
void UserIODigital::setDigitalIOEvent(int index ,const QString &selection)
{
    INPUT_LINE_FUNCTION selectionType = INPUT_FUNCTION_NONE ;

    for(auto it: UserInputEventName)
    {
        if(it.second == selection.toStdString())
        {
            selectionType = it.first;
            break;
        }
    }
    switch (index) {
    case 0:   m_UserIO.PS_USERIO.PsDigitalInput.J116_01.PS_EVENT =  selectionType;
              break;
    case 1:   m_UserIO.PS_USERIO.PsDigitalInput.J116_02.PS_EVENT =  selectionType;
              break;
    case 2:   m_UserIO.PS_USERIO.PsDigitalInput.J116_03.PS_EVENT =  selectionType;
              break;
    case 3:   m_UserIO.PS_USERIO.PsDigitalInput.J116_04.PS_EVENT =  selectionType;
              break;
    case 4:   m_UserIO.PS_USERIO.PsDigitalInput.J116_11.PS_EVENT =  selectionType;
              break;
    case 5:   m_UserIO.PS_USERIO.PsDigitalInput.J116_12.PS_EVENT =  selectionType;
              break;
    case 6:   m_UserIO.PS_USERIO.PsDigitalInput.J116_13.PS_EVENT =  selectionType;
              break;
    case 7:   m_UserIO.PS_USERIO.PsDigitalInput.J116_16.PS_EVENT =  selectionType;
              break;
    case 8:   m_UserIO.PS_USERIO.PsDigitalInput.J116_23.PS_EVENT =  selectionType;
              break;
    }
}


/**************************************************************************//**
*
* \brief   - To set the digital output values received from QML.
*
* \param   - index - selected value index , selected - value of selected item.
*
* \return  - None.
******************************************************************************/
void UserIODigital::setOutputDigitalIOEvent(int index ,const QString &selection)
{
    OUTPUT_LINE_FUNCTION selectionType = OUTPUT_FUNCTION_NONE ;

    for(auto it: UserOutputEventName)
    {
        if(it.second == selection.toStdString())
        {
            selectionType = it.first;
            break;
        }
    }
    switch (index) {
    case 0:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_07.PS_EVENT =  selectionType;
              break;
    case 1:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_08.PS_EVENT =  selectionType;
              break;
    case 2:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_09.PS_EVENT =  selectionType;
              break;
    case 3:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_10.PS_EVENT =  selectionType;
              break;
    case 4:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_19.PS_EVENT =  selectionType;
              break;
    case 5:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_20.PS_EVENT =  selectionType;
              break;
    case 6:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_21.PS_EVENT =  selectionType;
              break;
    case 7:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_22.PS_EVENT =  selectionType;
              break;
    }
}

/**************************************************************************//**
*
* \brief   - Returns the total number digital input options pesent in the combobox for selection
*
* \param   - none
*
* \return  - int .
******************************************************************************/

int UserIODigital::getTotalSizeofDigtialIpList()
{
    return m_optionsModel.count();
}

/**************************************************************************//**
*
* \brief   -  Returns the total number digital output options pesent in the combobox for selection
*
* \param   - None
*
* \return  - int .
******************************************************************************/

int UserIODigital::getTotalSizeofDigtialOPList()
{
    return m_digitalIOOutputModel.count();
}
/**************************************************************************//**
*
* \brief   - Returns each option of digital input model present in the combobox based on index.
*
* \param   - index of specific elemnt
*
* \return  - QString .
******************************************************************************/
QString UserIODigital::getDigitalIp(int index)
{
    return m_optionsModel[index];
}

/**************************************************************************//**
*
* \brief   - Returns each option of digital output model present in the combobox based on index.
*
* \param   - index of specific element
*
* \return  - QString .
******************************************************************************/
QString UserIODigital::getDigitalOP(int index)
{
    return m_digitalIOOutputModel[index];
}
/**************************************************************************//**
*
* \brief   - Returns the option selected on input model present in the combobox based on index.
*
* \param   - index of selected element
*
* \return  - QString .
******************************************************************************/
QString UserIODigital::getSelectedComboBox(int index)
{
    return values[index];
}
/**************************************************************************//**
*
* \brief   - Returns the option selected on output model present in the combobox based on index.
*
* \param   - index of selected element
*
* \return  - QString .
******************************************************************************/
QString UserIODigital::getSelectedOPComboBox(int index)
{
    return m_outputvalues[index];
}
/**************************************************************************//**
*
* \brief   - To validate the selected option from QML if it is present in the input combobox model or not.
*
* \param   - QString str
*
* \return  - bool .
******************************************************************************/
bool UserIODigital::checkOptionIfAvailable(QString str)
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
* \brief   - To validate the selected option from QML if it is present in the output combobox model or not.
*
* \param   - QString str
*
* \return  - bool .
******************************************************************************/
bool UserIODigital::checkOptionIfAvailableInOutputModel(QString str)
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
* \brief   - Sets the values state high/low from QML based on selection for input model.
*
* \param   - Index of the selected element , state- High/Low based on selection.
*
* \return  - None.
******************************************************************************/
void UserIODigital::setDigitalUserIOState(int index, bool state)
{
    switch (index) {

    case 0:   m_UserIO.PS_USERIO.PsDigitalInput.J116_01.Status =  state;
              break;
    case 1:   m_UserIO.PS_USERIO.PsDigitalInput.J116_02.Status =  state;
              break;
    case 2:   m_UserIO.PS_USERIO.PsDigitalInput.J116_03.Status =  state;
              break;
    case 3:   m_UserIO.PS_USERIO.PsDigitalInput.J116_04.Status =  state;
              break;
    case 4:   m_UserIO.PS_USERIO.PsDigitalInput.J116_11.Status =  state;
              break;
    case 5:   m_UserIO.PS_USERIO.PsDigitalInput.J116_12.Status =  state;
              break;
    case 6:   m_UserIO.PS_USERIO.PsDigitalInput.J116_13.Status =  state;
              break;
    case 7:   m_UserIO.PS_USERIO.PsDigitalInput.J116_16.Status =  state;
              break;
    case 8:   m_UserIO.PS_USERIO.PsDigitalInput.J116_23.Status =  state;
              break;

    }

}

/**************************************************************************//**
*
* \brief   - Sets the values state high/low from QML based on selection for output model.
*
* \param   - Index of the selected element , state- High/Low based on selection.
*
* \return  - None.
******************************************************************************/
void UserIODigital::setOutputDigitalUserIOState(int index, bool state)
{
    switch (index) {

    case 0:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_07.Status =  state;
              break;
    case 1:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_08.Status =  state;
              break;
    case 2:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_09.Status =  state;
              break;
    case 3:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_10.Status =  state;
              break;
    case 4:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_19.Status =  state;
              break;
    case 5:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_20.Status =  state;
              break;
    case 6:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_21.Status =  state;
              break;
    case 7:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_22.Status =  state;
              break;

    }
}

/**************************************************************************//**
*
* \brief   - Sets the pinEnable values from QML based on selection for input model.
*
* \param   - Index of the selected element , state- enable/disable based on selection.
*
* \return  - None.
******************************************************************************/

void UserIODigital::setDigitalUserIOPinEnable(int index, bool state)
{
    switch (index) {

    case 0:   m_UserIO.PS_USERIO.PsDigitalInput.J116_01.IsPinEnabled =  state;
              break;
    case 1:   m_UserIO.PS_USERIO.PsDigitalInput.J116_02.IsPinEnabled =  state;
              break;
    case 2:   m_UserIO.PS_USERIO.PsDigitalInput.J116_03.IsPinEnabled =  state;
              break;
    case 3:   m_UserIO.PS_USERIO.PsDigitalInput.J116_04.IsPinEnabled =  state;
              break;
    case 4:   m_UserIO.PS_USERIO.PsDigitalInput.J116_11.IsPinEnabled =  state;
              break;
    case 5:   m_UserIO.PS_USERIO.PsDigitalInput.J116_12.IsPinEnabled =  state;
              break;
    case 6:   m_UserIO.PS_USERIO.PsDigitalInput.J116_13.IsPinEnabled =  state;
              break;
    case 7:   m_UserIO.PS_USERIO.PsDigitalInput.J116_16.IsPinEnabled =  state;
              break;
    case 8:   m_UserIO.PS_USERIO.PsDigitalInput.J116_23.IsPinEnabled =  state;
              break;

    }
}


/**************************************************************************//**
*
* \brief   - Sets the pinEnable values from QML based on selection for output model.
*
* \param   - Index of the selected element , state- enable/disable based on selection.
*
* \return  - None.
******************************************************************************/

void UserIODigital::setOutputDigitalUserIOPinEnable(int index, bool state)
{
    switch (index) {

    case 0:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_07.IsPinEnabled =  state;
              break;
    case 1:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_08.IsPinEnabled =  state;
              break;
    case 2:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_09.IsPinEnabled =  state;
              break;
    case 3:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_10.IsPinEnabled =  state;
              break;
    case 4:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_19.IsPinEnabled =  state;
              break;
    case 5:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_20.IsPinEnabled =  state;
              break;
    case 6:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_21.IsPinEnabled =  state;
              break;
    case 7:   m_UserIO.PS_USERIO.PsDigitalOutput.J116_22.IsPinEnabled =  state;
              break;
    }
}
/**************************************************************************//**
*
* \brief   - returns the status values to QML input model.
*
* \param   - Index of the specific element.
*
* \return  - bool .
******************************************************************************/
bool UserIODigital::getDigitalUserIOState(int index)
{
    switch (index) {
    case 0:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_01.Status ;
             break;
    case 1:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_02.Status ;
             break;
    case 2:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_03.Status ;
             break;
    case 3:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_04.Status ;
             break;
    case 4:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_11.Status ;
             break;
    case 5:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_12.Status ;
             break;
    case 6:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_13.Status ;
             break;
    case 7:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_16.Status ;
             break;
    case 8:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_23.Status ;
             break;
    }
    return false;
}

/**************************************************************************//**
*
* \brief   - returns the status values to QML output model.
*
* \param   - Index of the specific element.
*
* \return  - bool .
******************************************************************************/
bool UserIODigital::getOutputDigitalUserIOState(int index)
{
    switch (index) {
    case 0:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_07.Status ;
             break;
    case 1:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_08.Status ;
             break;
    case 2:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_09.Status ;
             break;
    case 3:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_10.Status ;
             break;
    case 4:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_19.Status ;
             break;
    case 5:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_20.Status ;
             break;
    case 6:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_21.Status ;
             break;
    case 7:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_22.Status ;
             break;
    }
    return false;
}
/**************************************************************************//**
*
* \brief   - returns the pinEnabled values to QML input model.
*
* \param   - Index of the specific element.
*
* \return  - bool .
******************************************************************************/
bool UserIODigital::getDigitalUserIOPinEnable(int index)
{
    switch (index) {
    case 0:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_01.IsPinEnabled ;
             break;
    case 1:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_02.IsPinEnabled ;
             break;
    case 2:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_03.IsPinEnabled ;
             break;
    case 3:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_04.IsPinEnabled ;
             break;
    case 4:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_11.IsPinEnabled ;
             break;
    case 5:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_12.IsPinEnabled ;
             break;
    case 6:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_13.IsPinEnabled ;
             break;
    case 7:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_16.IsPinEnabled ;
             break;
    case 8:  return m_UserIO.PS_USERIO.PsDigitalInput.J116_23.IsPinEnabled ;
             break;
    }
    return false;
}

/**************************************************************************//**
*
* \brief   - returns the pinEnabled values to QML output model.
*
* \param   - Index of the specific element.
*
* \return  - bool .
******************************************************************************/
bool UserIODigital::getOutputDigitalUserIOPinEnable(int index)
{
    switch (index) {
    case 0:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_07.IsPinEnabled ;
             break;
    case 1:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_08.IsPinEnabled ;
             break;
    case 2:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_09.IsPinEnabled ;
             break;
    case 3:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_10.IsPinEnabled ;
             break;
    case 4:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_19.IsPinEnabled ;
             break;
    case 5:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_20.IsPinEnabled ;
             break;
    case 6:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_21.IsPinEnabled ;
             break;
    case 7:  return m_UserIO.PS_USERIO.PsDigitalOutput.J116_22.IsPinEnabled ;
             break;
    }
    return false;
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
int UserIODigital::MappingPSInputFunc(int ps_event)
{
    int function = INPUT_FUNCTION_NONE;

    switch (ps_event)
    {
    case INPUT_DISABLE:
        function = INPUT_DISABLE;
        break;
    case IN_CYCLE_ABORT:
        function = IN_CYCLE_ABORT;
        break;
    case IN_ULTRASONIC_SONIC_DISABLE:
        function = IN_ULTRASONIC_SONIC_DISABLE;
        break;
    case IN_ALARM_RESET:
        function = IN_ALARM_RESET;
        break;
    case IN_HOLD_DELAY:
        function = IN_HOLD_DELAY;
        break;
    case IN_HORN_SEEK:
        function = IN_HORN_SEEK;
        break;
    case IN_CABLE_DETECT:
        function = IN_CABLE_DETECT;
        break;
    case IN_DISPLAY_LOCK:
        function = IN_DISPLAY_LOCK;
        break;
    case IN_ULTRASONIC_DELAY:
        function = IN_ULTRASONIC_DELAY;
        break;
    case IN_HORN_TEST:
        function = IN_HORN_TEST;
        break;
    case IN_HORN_SCAN:
        function = IN_HORN_SCAN;
        break;
    case IN_MEMORY_CLEAR:
        function = IN_MEMORY_CLEAR;
        break;
    case IN_LOAD_RECIPE:
        function = IN_LOAD_RECIPE;
        break;
    case EXT_TOOLING_INPUT:
        function = EXT_TOOLING_INPUT;
        break;
    case PART_PRESENT_INPUT:
    	function = PART_PRESENT_INPUT;
    case RECIPE_1:
        function = RECIPE_1;
        break;
    case RECIPE_2:
        function = RECIPE_2;
        break;
    case RECIPE_4:
        function = RECIPE_4;
        break;
    case RECIPE_8:
        function = RECIPE_8;
        break;
    case IN_ESTOP_RESET:
        function = IN_ESTOP_RESET;
        break;
    case EXTERNAL_AMPLITUDE_TRIGGER_1:
        function = EXTERNAL_AMPLITUDE_TRIGGER_1;
        break;
    case EXTERNAL_AMPLITUDE_TRIGGER_2:
        function = EXTERNAL_AMPLITUDE_TRIGGER_2;
        break;
    case EXTERNAL_AMPLITUDE_TRIGGER_3:
        function = EXTERNAL_AMPLITUDE_TRIGGER_3;
        break;
    case INPUT_FUNCTION_MAX:
        function = INPUT_FUNCTION_MAX;
        break;
    }
    //remaining recipe bit mapping remaining
    return function;
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
int UserIODigital::MappingPSOutputFunc(int ps_event)
{
    int function = OUTPUT_FUNCTION_NONE;

    switch (ps_event)
    {
    case OUTPUT_DISABLED:
        function = OUTPUT_DISABLED;
        break;
    case SYSTEM_READY:
        function = SYSTEM_READY;
        break;
    case ULTRASONIC_ACTIVE:
        function = ULTRASONIC_ACTIVE;
        break;
    case ALARM_GENERAL:
        function = ALARM_GENERAL;
        break;
    case CYCLE_RUNNING:
        function = CYCLE_RUNNING;
        break;
    case CYCLE_OK:
        function = CYCLE_OK;
        break;
    case ALARM_CUSTOM:
        function = ALARM_CUSTOM;
        break;
    case HORN_SEEK:
        function = HORN_SEEK;
        break;
    case HOLD_TIME_ACTIVE:
        function = HOLD_TIME_ACTIVE;
        break;
    case SOLENOID_ACTIVE:
        function = SOLENOID_ACTIVE;
        break;
    case ACTUATOR_CLEAR:
        function = ACTUATOR_CLEAR;
        break;
    case AFTERBURST_DELAY:
        function = AFTERBURST_DELAY;
        break;
    case AFTERBURST_TIME:
        function = AFTERBURST_TIME;
        break;
    case PB_RELEASE:
        function = PB_RELEASE;
        break;
    case ACTUATOR_HOME:
        function = ACTUATOR_HOME;
        break;
    case HORN_SCAN:
        function = HORN_SCAN;
        break;
    case ALARM_REJECT_PART:
        function = ALARM_REJECT_PART;
        break;

    case ALARM_CUTTOFF:
        function = ALARM_CUTTOFF;
        break;
    case ALARM_OVERLOAD:
        function = ALARM_OVERLOAD;
        break;
    case EXT_TOOLING_OUTPUT:
        function = EXT_TOOLING_OUTPUT;
        break;
    case CONFIRM_RECIPE:
        function = CONFIRM_RECIPE;
        break;
    case OUTPUT_FUNCTION_MAX:
        function = OUTPUT_FUNCTION_MAX;
        break;
    }


    return function;
}
/**************************************************************************//**
*
* \brief   - To read the structure from ASC and map to it's respective values based on structure values.
*
* \param   - None
*
* \return  - None.
******************************************************************************/
void UserIODigital::readUserIOStructure()
{
    // Digital Input model for display combobox values
    values.clear();
    m_GetIndexValue.clear();

    int DigiIP1 =   MappingPSInputFunc(m_UserIO.PS_USERIO.PsDigitalInput.J116_01.PS_EVENT);
    values.append(psEventName(static_cast< INPUT_LINE_FUNCTION>(DigiIP1)));

    int DigiIP2 =   MappingPSInputFunc(m_UserIO.PS_USERIO.PsDigitalInput.J116_02.PS_EVENT);
    values.append(psEventName(static_cast< INPUT_LINE_FUNCTION>(DigiIP2)));

    int DigiIP3 =   MappingPSInputFunc(m_UserIO.PS_USERIO.PsDigitalInput.J116_03.PS_EVENT);
    values.append(psEventName(static_cast< INPUT_LINE_FUNCTION>(DigiIP3)));

    int DigiIP4 =   MappingPSInputFunc(m_UserIO.PS_USERIO.PsDigitalInput.J116_04.PS_EVENT);
    values.append(psEventName(static_cast< INPUT_LINE_FUNCTION>(DigiIP4)));

    int DigiIP5 =   MappingPSInputFunc(m_UserIO.PS_USERIO.PsDigitalInput.J116_11.PS_EVENT);
    values.append(psEventName(static_cast< INPUT_LINE_FUNCTION>(DigiIP5)));

    int DigiIP6 =   MappingPSInputFunc(m_UserIO.PS_USERIO.PsDigitalInput.J116_12.PS_EVENT);
    values.append(psEventName(static_cast< INPUT_LINE_FUNCTION>(DigiIP6)));

    int DigiIP7 =   MappingPSInputFunc(m_UserIO.PS_USERIO.PsDigitalInput.J116_13.PS_EVENT);
    values.append(psEventName(static_cast< INPUT_LINE_FUNCTION>(DigiIP7)));

    int DigiIP8 =   MappingPSInputFunc(m_UserIO.PS_USERIO.PsDigitalInput.J116_16.PS_EVENT);
    values.append(psEventName(static_cast< INPUT_LINE_FUNCTION>(DigiIP8)));

    int DigiIP9 =   MappingPSInputFunc(m_UserIO.PS_USERIO.PsDigitalInput.J116_23.PS_EVENT);
    values.append(psEventName(static_cast< INPUT_LINE_FUNCTION>(DigiIP9)));

    /*Update the vector with cable detect option data either available or not*/
    QString textVal = "Cable Detect";

    for(int i=0; i< values.count();i++)
    {
        if(values[i] == textVal)
        {
            m_GetIndexValue.append(true);
        }

        else
        {
            m_GetIndexValue.append(false);
        }
    }

    // Digital Output model for display combobox values
    m_outputvalues.clear();

    int DigiOP1 = MappingPSOutputFunc(m_UserIO.PS_USERIO.PsDigitalOutput.J116_07.PS_EVENT);
    m_outputvalues.append(psOutputEventName(static_cast< OUTPUT_LINE_FUNCTION>(DigiOP1)));

    int DigiOP2 = MappingPSOutputFunc(m_UserIO.PS_USERIO.PsDigitalOutput.J116_08.PS_EVENT);
    m_outputvalues.append(psOutputEventName(static_cast< OUTPUT_LINE_FUNCTION>(DigiOP2)));

    int DigiOP3 = MappingPSOutputFunc(m_UserIO.PS_USERIO.PsDigitalOutput.J116_09.PS_EVENT);
    m_outputvalues.append(psOutputEventName(static_cast< OUTPUT_LINE_FUNCTION>(DigiOP3)));

    int DigiOP4 = MappingPSOutputFunc(m_UserIO.PS_USERIO.PsDigitalOutput.J116_10.PS_EVENT);
    m_outputvalues.append(psOutputEventName(static_cast< OUTPUT_LINE_FUNCTION>(DigiOP4)));

    int DigiOP5 = MappingPSOutputFunc(m_UserIO.PS_USERIO.PsDigitalOutput.J116_19.PS_EVENT);
    m_outputvalues.append(psOutputEventName(static_cast< OUTPUT_LINE_FUNCTION>(DigiOP5)));

    int DigiOP6 = MappingPSOutputFunc( m_UserIO.PS_USERIO.PsDigitalOutput.J116_20.PS_EVENT);
    m_outputvalues.append(psOutputEventName(static_cast< OUTPUT_LINE_FUNCTION>(DigiOP6)));

    int DigiOP7 = MappingPSOutputFunc(m_UserIO.PS_USERIO.PsDigitalOutput.J116_21.PS_EVENT);
    m_outputvalues.append(psOutputEventName(static_cast< OUTPUT_LINE_FUNCTION>(DigiOP7)));

    int DigiOP8 = MappingPSOutputFunc(m_UserIO.PS_USERIO.PsDigitalOutput.J116_22.PS_EVENT );
    m_outputvalues.append(psOutputEventName(static_cast< OUTPUT_LINE_FUNCTION>(DigiOP8)));

    filterComboBoxList();
    emit valuesUpdated();      //Emit signal to notify QML about updated values

}
/**************************************************************************//**
*
* \brief   - Used to map with the string values of the INPUT_LINE FUNCTION.
*
* \param   - INPUT_LINE_FUNCTION - enum
*
* \return  - QString.
******************************************************************************/

QString UserIODigital::psEventName(INPUT_LINE_FUNCTION Event)
{
    QString EventType;

    for(auto it: UserInputEventName)
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
*
* \brief   - Used to map with the string values of the OUTPUT_LINE_FUNCTION.
*
* \param   - OUTPUT_LINE_FUNCTION - enum
*
* \return  - QString.
******************************************************************************/

QString UserIODigital::psOutputEventName(OUTPUT_LINE_FUNCTION Event)
{
    QString EventType;

    for(auto it: UserOutputEventName)
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
*
* \brief   - Remove the option that is selected on the combobox ,so theat it is unavailable for the other comboboxes
*            for selection.
*
* \param   - None
*
* \return  - None.
******************************************************************************/
void UserIODigital::filterComboBoxList()
{
    m_optionsModel.clear();
    m_optionsModel.append("Not Used");
    for(int i= 0;i< m_digitalIpComboboxList.count();i++)
    {
        if(!(checkOptionIfAvailable(m_digitalIpComboboxList[i])))
        {
            m_optionsModel.append(m_digitalIpComboboxList[i]);
        }
    }

    m_digitalIOOutputModel.clear();
    m_digitalIOOutputModel.append("Not Used");
    for(int i= 0;i< m_digitalIpOutputComboboxList.count();i++)
    {
        if(!(checkOptionIfAvailableInOutputModel(m_digitalIpOutputComboboxList[i])))
        {
            m_digitalIOOutputModel.append(m_digitalIpOutputComboboxList[i]);
        }
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
void UserIODigital::getSaveRequestForDigitalUserIO()
{

    m_DigitalIOMgr->saveDigitalUserIOValues(m_UserIO);
}
/**************************************************************************//**
*
* \brief   - Send Reset to Default request from HMI.
*
* \param   - NOne
*
* \return  - void.
******************************************************************************/
void UserIODigital::getResetToDefRequestForDigitalUserIO()
{
    m_DigitalIOMgr->setResetToDefaultDigiUsrIORequest(true);

    emit valuesUpdated();
}
/**************************************************************************//**
*
* \brief   - Send Cancel request from HMI.
*
* \param   - NOne
*
* \return  - None.
******************************************************************************/
void UserIODigital::getCancelRequestForDigitalUserIO()
{
    m_UserIO = m_DigitalIOMgr->GetDigitalIOStruct();
    m_IsGlobalDgtIpSwtchEnable = m_UserIO.GlobalDigitalInputSwitchState;
    m_IsGlobalDgtOpSwtchEnable = m_UserIO.GlobalDigitalOutputSwitchState;
    readUserIOStructure();
    emit valuesUpdated();      //Emit signal to notify QML about updated values
}

/**************************************************************************//**
*
* \brief   - Provide index data for mentioned index value.
*
* \param   - Index : Index of selected option.
*
* \return  - Recpective index data, whether cable detect is selected or not.
******************************************************************************/
bool UserIODigital::getIndexValue(int index)
{
    return m_GetIndexValue[index];
}
/**************************************************************************//**
*
* \brief   - Below function returns the UserIO digital loading status.
*
* \param   - None.
*
* \return  - m_IsLoadingFlag : The UserIO digital loading status.
******************************************************************************/
bool UserIODigital::getIsLoading() const
{
    return m_IsLoadingFlag;
}

/**************************************************************************//**
*
* \brief   - Below function updates the  loading status.
*
* \param   - IsLoading
*
* \return  - None.
******************************************************************************/
void UserIODigital::updateIsLoading(const bool &IsLoading)
{
    m_IsLoadingFlag = IsLoading;
    emit loadingDataChanged();
}

/**************************************************************************//**
*
* \brief   - Below function updates the  loading status.
*
* \param   - IsLoading
*
* \return  - None.
******************************************************************************/
int UserIODigital::getCountOfIpModel()
{
    return DIGITAL_IO_MAX_INPUTS;
}

/**************************************************************************//**
*
* \brief   - Below function updates the  loading status.
*
* \param   - IsLoading
*
* \return  - None.
******************************************************************************/
int UserIODigital::getCountOfOpModel()
{
    return DIGITAL_IO_MAX_OUTPUTS;
}
/**************************************************************************//**
*
* \brief   - Role of the slot OnUserIODigitalDetailsUpdated is to update values on UserIO screen.
*
* \param   - DigitalIOMgrDetailsResult_Obj : Object pointer of type DigitalIOMgr.
*
* \return  - None.
******************************************************************************/
void UserIODigital::OnUserIODigitalDetailsUpdated(DigitalIOMgr *DigitalIOMgrDetailsResult_Obj  , int WelderId)
{
    m_DigitalIOMgr =DigitalIOMgrDetailsResult_Obj;

    if(m_DigitalIOMgr->IsDigitalIOStructUpdated() || m_ActiveWelderId != WelderId )
    {
        m_UserIO = m_DigitalIOMgr->GetDigitalIOStruct();
        m_IsGlobalDgtIpSwtchEnable = m_UserIO.GlobalDigitalInputSwitchState;
        m_IsGlobalDgtOpSwtchEnable = m_UserIO.GlobalDigitalOutputSwitchState;
        readUserIOStructure();
        m_ActiveWelderId = WelderId;
        m_DigitalIOMgr->ResetIsLastDigitalIOUpdatedFlag();
        emit valuesUpdated();      //Emit signal to notify QML about updated values
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the IsGlobalDgtIpSwtchEnable status.
*
* \param   - none
*
* \return  - IsGlobalDgtIpSwtchEnable.
******************************************************************************/
bool UserIODigital::getIsGlobalDgtIpSwtchEnable() const
{
    return m_IsGlobalDgtIpSwtchEnable;
}

/**************************************************************************//**
*
* \brief   - Below function updates the  IsGlobalDgtIpSwtchEnable status.
*
* \param   - IsGlobalDgtIpSwtchEnable
*
* \return  - None.
******************************************************************************/
void UserIODigital::updateIsGlobalDgtIpSwtchEnable(bool newIsGlobalDgtIpSwtchEnable)
{
    if (m_IsGlobalDgtIpSwtchEnable != newIsGlobalDgtIpSwtchEnable)
    {
        m_IsGlobalDgtIpSwtchEnable = newIsGlobalDgtIpSwtchEnable;
        m_UserIO.GlobalDigitalInputSwitchState = m_IsGlobalDgtIpSwtchEnable;
    }
}

/**************************************************************************//**
*
* \brief   - Below function returns the  m_IsGlobalDgtOpSwtchEnable status.
*
* \param   - none
*
* \return  - m_IsGlobalDgtOpSwtchEnable.
******************************************************************************/
bool UserIODigital::getIsGlobalDgtOpSwtchEnable() const
{
    return m_IsGlobalDgtOpSwtchEnable;
}

/**************************************************************************//**
*
* \brief   - Below function updates the  IsGlobalDgtOpSwtchEnable status.
*
* \param   - IsGlobalDgtOpSwtchEnable
*
* \return  - None.
******************************************************************************/
void UserIODigital::updateIsGlobalDgtOpSwtchEnable(bool newIsGlobalDgtOpSwtchEnable)
{
    if (m_IsGlobalDgtOpSwtchEnable != newIsGlobalDgtOpSwtchEnable)
    {
        m_IsGlobalDgtOpSwtchEnable = newIsGlobalDgtOpSwtchEnable;
        m_UserIO.GlobalDigitalOutputSwitchState = m_IsGlobalDgtOpSwtchEnable;
    }
}
