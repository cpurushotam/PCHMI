/**************************************************************************

         Copyright (c) Branson Ultrasonics Corporation, 1996-2023

         This program is the property of Branson Ultrasonics Corporation
         Copying of this software is expressly forbidden, without the prior
         written consent of Branson Ultrasonics Corporation.

--------------------------- MODULE DESCRIPTION ----------------------------

 Declares SystemGeneral class which is responsible to do interaction between frontend and backend .

--------------------------- REVISION HISTORY ------------------------------
 rev1: 15-09-2023

***************************************************************************/
#include "SystemGeneral.h"
#include <QDebug>
#include <cstring>
/**************************************************************************//**
*
* \brief  - SystemGeneral Constructor
*
* \param  - None.
*
* \return - None.
*
******************************************************************************/
SystemGeneral::SystemGeneral(QObject *parent) : QObject(parent)
{
    connect(UpdateScreen::getInstance(), &UpdateScreen::SysConfgGenScreenUpdated, this, &SystemGeneral::OnSysConfgGenScreenUpdated);
}

/**************************************************************************//**
*
* \brief - Below function returns the Active Welder Name.
*
* \param - None.
*
* \return - m_WelderName
******************************************************************************/
QString SystemGeneral::getWelderName() const
{
    return m_WelderName;
}

/**************************************************************************//**
*
* \brief - Below function updates the Active Welder Name.
*
* \param - Welder Name
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateWelderName(const QString &WelderName)
{
    if (m_WelderName != WelderName)
    {
         m_WelderName = WelderName;
    }
}

/**************************************************************************//**
*
* \brief - Below function returns the Memory Full Action value.
*
* \param - None.
*
* \return - m_MemoryfullAction
******************************************************************************/
int SystemGeneral::getMemoryfullAction() const
{
    return m_MemoryfullAction;
}

/**************************************************************************//**
*
* \brief - Below function updates the Memory full Action value.
*
* \param - MemoryfullAction
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateMemoryfullAction(int MemoryfullAction)
{
    if (m_MemoryfullAction != MemoryfullAction)
    {
         m_MemoryfullAction = MemoryfullAction;
    }
}

/**************************************************************************//**
*
* \brief - Below function returns the Authority Check value.
*
* \param - None.
*
* \return - m_AuthorityChk
******************************************************************************/
int SystemGeneral::getAuthorityChk() const
{
    return m_AuthorityChk;
}

/**************************************************************************//**
*
* \brief - Below function updates the Authority Check value.
*
* \param - AuthorityChk
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateAuthorityChk(int AuthorityChk)
{
    if (m_AuthorityChk != AuthorityChk)
    {
        m_AuthorityChk = AuthorityChk;
    }
}

/**************************************************************************//**
*
* \brief - Below function returns the Key.
*
* \param - None.
*
* \return - m_Key
******************************************************************************/
QString SystemGeneral::getKey() const
{
    return m_Key;
}

/**************************************************************************//**
*
* \brief - Below function updates the Key.
*
* \param - Key
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateKey(const QString &Key)
{
    if (m_Key != Key)
    {
        m_Key = Key;
    }
}

/**************************************************************************//**
*
* \brief - Below function returns the Barcode Recall Recipe Prefix.
*
* \param - None.
*
* \return - m_BarcodeRecallRecipePrefix
******************************************************************************/
QString SystemGeneral::getBarcodeRecallRecipePrefix() const
{
    return m_BarcodeRecallRecipePrefix;
}

/**************************************************************************//**
*
* \brief - Below function updates the BarcodeRecallRecipePrefix.
*
* \param - BarcodeRecallRecipePrefix
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateBarcodeRecallRecipePrefix(const QString &BarcodeRecallRecipePrefix)
{
    if (m_BarcodeRecallRecipePrefix != BarcodeRecallRecipePrefix)
    {
        m_BarcodeRecallRecipePrefix = BarcodeRecallRecipePrefix;
    }
}

/**************************************************************************//**
*
* \brief - Below function returns the Unit value.
*
* \param - None.
*
* \return - Unit
******************************************************************************/
int SystemGeneral::getUnit() const
{
    return m_Unit;
}

/**************************************************************************//**
*
* \brief - Below function updates the Unit.
*
* \param - Unit
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateUnit(const int &Unit)
{
    if (m_Unit != Unit)
    {
        m_Unit = Unit;
    }
}
/**************************************************************************//**
*
* \brief - Below function returns the powerupOption.
*
* \param - Unit
*
* \return - m_PowerUpOption.
******************************************************************************/
int SystemGeneral::getPowerupOption() const
{
    return m_PowerUpOption;
}
/**************************************************************************//**
*
* \brief - Below function updates the powerUpOption.
*
* \param - newPowerupOption
*
* \return - None.
******************************************************************************/
void SystemGeneral::updatePowerupOption(int newPowerupOption)
{
    if (m_PowerUpOption != newPowerupOption)
    {
        m_PowerUpOption = newPowerupOption;
    }
}
/**************************************************************************//**
*
* \brief - Below function updates the Structure with the data on the HMI.
*
* \param - None
*
* \return - None.
******************************************************************************/
void SystemGeneral::dataUpdateRequestToDB()
{
    m_SystemConfigGeneralStruct.currUnit = static_cast< UNIT>(m_Unit);//m_Unit;
    m_SystemConfigGeneralStruct.AuthorityCheck= static_cast< AUTHORITYCHECK>(m_AuthorityChk);//m_AuthorityChk;
    m_SystemConfigGeneralStruct.memoryFullAction=static_cast< MEMORYFULLACTION>(m_MemoryfullAction);// m_MemoryfullAction;
    strcpy( m_SystemConfigGeneralStruct.BarcodeRecipePrefix, m_BarcodeRecallRecipePrefix.toStdString().c_str());
    strcpy(m_SystemConfigGeneralStruct.key, m_Key.toStdString().c_str());
    strncpy(m_SystemConfigGeneralStruct.welderName, m_WelderName.toStdString().c_str(), MAX_WELDER_NAME_LENGTH);
    m_SystemConfigGeneralStruct.powerupoption = static_cast<POWERUPOPTION>(m_PowerUpOption);
    m_SystemConfigGeneralStruct.PartID =m_PartID;
    m_SystemConfigGeneralStruct.ClearMemoryAtPowerup = m_MemeoryClearAtPowerup;
    m_SystemConfigGeneralStruct.ClearMemoryWithReset = m_MemoryClearReset;
    m_SystemConfigGeneralStruct.ParallelWeldResultStorageStatus = m_ParallelWeldResultStorageStatus;
    m_SystemConfigGeneralStruct.ClampOnAlarm = m_Clampon;
    m_SystemConfigGeneralStruct.WeldRecipeUniqueSerialNumGenStatus = m_UniqueWeldRecipeStatus;
    m_SystemConfigGeneralStruct.ASCIPAddress = m_ASC_IP_ADDRESS_FOR_HMI;

    if (m_SysConfgGen!=nullptr && VerifySysConfgGeneralParameter(m_SystemConfigGeneralStruct))
    {
        m_SysConfgGen->setSystemDetailsFromHMI(m_SystemConfigGeneralStruct);
    }
}

/**************************************************************************//**
*
* \brief - Below function updates SystemGeneral class about data updated on HMI
*
* \param - dataChanged
*
* \return - None.
******************************************************************************/
void SystemGeneral::changeRequestFromHMI()
{
    dataUpdateRequestToDB();
}

/**************************************************************************//**
*
* \brief - Below function updates Unit with the value selected on HMI.
*
* \param - dataChanged
*
* \return - None.
******************************************************************************/
void SystemGeneral::getHMIUnit(int a)
{
    m_Unit=a;
}

/**************************************************************************//**
*
* \brief - Role of the slot OnSysConfgGenScreenUpdated to update the System_Configuration_General Tab data.
*
* \param - SysConfgGenData_Obj : Object pointer of type SystemConfigurationGeneral_MB.
*
* \return - None.
******************************************************************************/

void SystemGeneral::OnSysConfgGenScreenUpdated(SystemConfigurationGeneral_MB *SysConfgGenData_Obj, int WelderId)
{
    m_SysConfgGen = SysConfgGenData_Obj;

    if(m_SysConfgGen->getIsDataAvailableFlag() || (m_SysConfgGen->IsDataUpdated() || m_SysConfgGen->GetKeyVerifyDataReadStatus() || m_ActiveWelderId != WelderId))
    {
        SystemConfigGeneralStruct m_WeldModeLabData;

        /*To check key verify status */
        if(m_SysConfgGen->GetKeyVerifyDataReadStatus() == true)
        {
            m_IsKeyVerified = m_SysConfgGen->IsBransonServiceUserLoggedIn();
            emit keyVerifiedDataChanged();
            m_SysConfgGen->ResetKeyVerifyDataReadStatus();
        }

        else
        {
            /* Assign updated from ASC to local variables. */
            m_Unit = m_SysConfgGen->GetSystemDetailsFromASC().currUnit;
            m_MemoryfullAction = m_SysConfgGen->GetSystemDetailsFromASC().memoryFullAction;
            m_AuthorityChk = m_SysConfgGen->GetSystemDetailsFromASC().AuthorityCheck;
            m_Key = m_SysConfgGen->GetSystemDetailsFromASC().key;
            m_BarcodeRecallRecipePrefix = m_SysConfgGen->GetSystemDetailsFromASC().BarcodeRecipePrefix;
            m_PowerUpOption = static_cast<int>(m_SysConfgGen->GetSystemDetailsFromASC().powerupoption);
            m_WelderName = QString::fromUtf8(m_SysConfgGen->GetSystemDetailsFromASC().welderName);
            m_MemoryClearReset = m_SysConfgGen->GetSystemDetailsFromASC().ClearMemoryWithReset;
            m_PartID = m_SysConfgGen->GetSystemDetailsFromASC().PartID;
            m_MemeoryClearAtPowerup = m_SysConfgGen->GetSystemDetailsFromASC().ClearMemoryAtPowerup;
            m_ParallelWeldResultStorageStatus = m_SysConfgGen->GetSystemDetailsFromASC().ParallelWeldResultStorageStatus;
            m_Clampon = m_SysConfgGen->GetSystemDetailsFromASC().ClampOnAlarm;
            m_UniqueWeldRecipeStatus = m_SysConfgGen->GetSystemDetailsFromASC().WeldRecipeUniqueSerialNumGenStatus;
            m_ipAddress = QString::fromStdString (ASCIPAddressTypeNameForHMI.at(m_SysConfgGen->GetSystemDetailsFromASC().ASCIPAddress));

            emit sysConfigDataChanged();             /* Notify Screen to update data */
            m_SysConfgGen->setIsDataAvailableFlag();
            m_SysConfgGen->SetIsDataUpdated(false);  /* Set m_IsDataUpdated flag to false after updating the data to HMI. */
            m_ActiveWelderId = WelderId;
        }
    }
}

/**************************************************************************//**
*
* \brief   - This function verifies the data against min and max values
*
* \param   - systemConfigGeneralStruct
* \return  - bErrorOccured - boolean value
*
******************************************************************************/
bool SystemGeneral::VerifySysConfgGeneralParameter(SystemConfigGeneralStruct systemConfigGeneralStruct)
{
    bool bErrorOccured = true;
    if(systemConfigGeneralStruct.currUnit < METRIC || systemConfigGeneralStruct.currUnit > IMPERIAL ){
        bErrorOccured =false;
    }
    if(systemConfigGeneralStruct.AuthorityCheck < OFF || systemConfigGeneralStruct.AuthorityCheck > BASIC ){
        bErrorOccured =false;
    }
    if(systemConfigGeneralStruct.memoryFullAction < CONTINUE || systemConfigGeneralStruct.memoryFullAction > STOP ){
        bErrorOccured =false;
    }
    return bErrorOccured;
}




/**************************************************************************//**
*
* \brief - Below function returns PartID to HMI.
*
* \param - none
*
* \return - bool - m_PartID .
******************************************************************************/

bool SystemGeneral::getPartID() const
{
    return m_PartID;
}

/**************************************************************************//**
*
* \brief - Below function updates the PartID.
*
* \param - newPartID
*
* \return - None.
******************************************************************************/
void SystemGeneral::updatePartID(const bool &newPartID)
{
    if (m_PartID != newPartID)
    {
        m_PartID = newPartID;
    }
}
/**************************************************************************//**
*
* \brief - Below function returns Memeory Clear At Powerup to HMI.
*
* \param - none
*
* \return - bool - m_MemeoryClearAtPowerup .
******************************************************************************/
bool SystemGeneral::getMemeoryClearAtPowerup() const
{
    return m_MemeoryClearAtPowerup;
}

/**************************************************************************//**
*
* \brief - Below function updates the MemeoryClearAtPowerup.
*
* \param - newMemeoryClearAtPowerup
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateMemeoryClearAtPowerup(const bool &newMemeoryClearAtPowerup)
{
    if (m_MemeoryClearAtPowerup != newMemeoryClearAtPowerup)
    {
        m_MemeoryClearAtPowerup = newMemeoryClearAtPowerup;
    }
}

/**************************************************************************//**
*
* \brief - Below function returns Memory Clear Reset to HMI.
*
* \param - none
*
* \return - bool - m_MemoryClearReset .
******************************************************************************/
bool SystemGeneral::getMemoryClearReset() const
{
    return m_MemoryClearReset;
}

/**************************************************************************//**
*
* \brief - Below function updates the MemoryClearReset.
*
* \param - newMemoryClearReset
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateMemoryClearReset(const bool &newMemoryClearReset)
{
    if (m_MemoryClearReset != newMemoryClearReset)
    {
        m_MemoryClearReset = newMemoryClearReset;
    }
}

/**************************************************************************//**
*
* \brief - Below function returns key verify status to HMI.
*
* \param - none
*
* \return - bool - m_IsKeyVerified.
******************************************************************************/
bool SystemGeneral::getKeyVerifyStatus() const
{
    return m_IsKeyVerified;
}

/**************************************************************************//**
*
* \brief - Below function is used for Reset to Default request from HMI to ASC
*
* \param - None
*
* \return - None.
******************************************************************************/
void SystemGeneral::resetToDefaultRequest()
{
    m_SysConfgGen->SetSystConfigResetToDefaultRequest();
}

/**************************************************************************//**
*
* \brief - Below function is used to verify key entered by user on HMI
*
* \param - None
*
* \return - None.
******************************************************************************/
void SystemGeneral::keyVerifyRequest()
{
    /* Send key verify request to ASC */
    m_SysConfgGen->SetKeyVerifyRequest(m_Key.toStdString());
}
/**************************************************************************//**
*
* \brief - Below function is used to return the max Welder name length.
*
* \param - None
*
* \return - MAX_WELDER_NAME_LENGTH.
******************************************************************************/
int SystemGeneral::maxWelderNameLength()
{
    return MAX_WELDER_NAME_LENGTH ;
}
/**************************************************************************//**
*
* \brief - Below function is used to initiate Branson Service Person Logout.
*
* \param - None
*
* \return - none.
******************************************************************************/
void SystemGeneral::resrtBrsnSrvcKeyRequestFromHMI()
{
    m_SysConfgGen->ResetBrsnSrvcKeyVerifyStatus();
    emit keyResetNotify();
}

/**************************************************************************//**
*
* \brief - Below function is used to rewrite the data on screen. When cancel is pressed.
*
* \param - None
*
* \return - none.
******************************************************************************/
void SystemGeneral::cancelRequestFromHMI()
{
    m_MemoryfullAction=m_SysConfgGen->GetSystemDetailsFromASC().memoryFullAction;
    m_AuthorityChk=m_SysConfgGen->GetSystemDetailsFromASC().AuthorityCheck;
    m_Key=m_SysConfgGen->GetSystemDetailsFromASC().key;
    m_BarcodeRecallRecipePrefix=m_SysConfgGen->GetSystemDetailsFromASC().BarcodeRecipePrefix;
    m_PowerUpOption = static_cast<int>(m_SysConfgGen->GetSystemDetailsFromASC().powerupoption);
    m_WelderName= QString::fromUtf8(m_SysConfgGen->GetSystemDetailsFromASC().welderName);
    m_MemoryClearReset = m_SysConfgGen->GetSystemDetailsFromASC().ClearMemoryWithReset;
    m_PartID = m_SysConfgGen->GetSystemDetailsFromASC().PartID;
    m_MemeoryClearAtPowerup = m_SysConfgGen->GetSystemDetailsFromASC().ClearMemoryAtPowerup;
    m_ParallelWeldResultStorageStatus = m_SysConfgGen->GetSystemDetailsFromASC().ParallelWeldResultStorageStatus;
    m_Clampon = m_SysConfgGen->GetSystemDetailsFromASC().ClampOnAlarm;
    m_UniqueWeldRecipeStatus = m_SysConfgGen->GetSystemDetailsFromASC().WeldRecipeUniqueSerialNumGenStatus;
    m_ipAddress =QString::fromStdString ( ASCIPAddressTypeNameForHMI.at(m_SysConfgGen->GetSystemDetailsFromASC().ASCIPAddress));

    emit sysConfigDataChanged();
}

/**************************************************************************//**
*
* \brief - Below function returns Parallel Weld Result Storage Status to HMI.
*
* \param - none
*
* \return - bool - m_ParallelWeldResultStorageStatus .
******************************************************************************/
bool SystemGeneral::getParallelWeldResultStorageStatus() const
{
    return m_ParallelWeldResultStorageStatus;
}

/**************************************************************************//**
*
* \brief - Below function updates the m_ParallelWeldResultStorageStatus.
*
* \param - parallelWeldResultStorageStatus - updated status
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateParallelWeldResultStorageStatus(const bool & parallelWeldResultStorageStatus)
{
    if (m_ParallelWeldResultStorageStatus != parallelWeldResultStorageStatus)
    {
        m_ParallelWeldResultStorageStatus = parallelWeldResultStorageStatus;
    }
}

/**************************************************************************//**
*
* \brief - Below function returns Clamp on Status to HMI.
*
* \param - none
*
* \return - bool - m_Clampon .
******************************************************************************/
bool SystemGeneral::getClampon() const
{
    return m_Clampon;
}
/**************************************************************************//**
*
* \brief - Below function updates the m_Clampon.
*
* \param - newClampon - updated status
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateClampon(const bool& newClampon)
{
    if (m_Clampon != newClampon)
    {
        m_Clampon = newClampon;
    }
}

/**************************************************************************//**
*
* \brief - Below function returns UniqueWeldRecipeStatus on Status to HMI.
*
* \param - none
*
* \return - bool - m_UniqueWeldRecipeStatus .
******************************************************************************/
bool SystemGeneral::getUniqueWeldRecipeStatus() const
{
    return m_UniqueWeldRecipeStatus;
}
/**************************************************************************//**
*
* \brief - Below function updates the m_UniqueWeldRecipeStatus.
*
* \param - newUniqueWeldRecipeStatus - updated status
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateUniqueWeldRecipeStatus(bool newUniqueWeldRecipeStatus)
{
    if (m_UniqueWeldRecipeStatus != newUniqueWeldRecipeStatus)
    {
        m_UniqueWeldRecipeStatus = newUniqueWeldRecipeStatus;
    }
}
/**************************************************************************//**
*
* \brief - Below function is used to return the IPaddress string value based on it's enum value.
*
* \param - int - Index from QML to map with enum value
*
* \return - IpAddress string value.
******************************************************************************/
QString SystemGeneral::getIpAddressForComboboxModel(int i)
{
    QString ipAdddr = "";
    //To map the string values stored in ASCIPAddressTypeNameForHMI Map with it's enum value. HMI range should start with IP_ADDRESS_START_RANGE - 100.
    ASC_IP_ADDRESS_FOR_HMI IpAddressFromHMI = static_cast<ASC_IP_ADDRESS_FOR_HMI>(IP_ADDRESS_START_RANGE+i);
    ipAdddr = QString::fromStdString (ASCIPAddressTypeNameForHMI.at(IpAddressFromHMI));
    return ipAdddr;
}

/**************************************************************************//**
*
* \brief - Below function is used to return the max welder ip address user can choose.
*
* \param - None
*
* \return - MAX_WELDER_IPADDRESS.
******************************************************************************/
int SystemGeneral::maxIpAddressInMap()
{
    return MAX_WELDER_IPADDRESS ;
}
/**************************************************************************//**
*
* \brief - Below function returns ipAddress to HMI.
*
* \param - none
*
* \return - QString - m_ipAddress .
******************************************************************************/
QString SystemGeneral::getipAddress() const
{
    return m_ipAddress;
}
/**************************************************************************//**
*
* \brief - Below function updates the m_ipAddress.
*
* \param - newIpAddress - new ipAddress from HMI
*
* \return - None.
******************************************************************************/
void SystemGeneral::updateipAddress(QString newIpAddress)
{
    if (m_ipAddress != newIpAddress)
    {
        for (const auto& pair : ASCIPAddressTypeNameForHMI)
        {
            if (pair.second == newIpAddress.toStdString())
            {
                m_ASC_IP_ADDRESS_FOR_HMI =  pair.first;
                break;
            }
        }
        m_ipAddress = newIpAddress;
    }
}
