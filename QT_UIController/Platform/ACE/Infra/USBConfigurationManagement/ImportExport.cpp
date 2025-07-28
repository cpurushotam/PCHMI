/**********************************************************************************************************
 
      Copyright (c) Branson Ultrasonics Corporation, 1996-2022
 
     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.
 
---------------------------- MODULE DESCRIPTION ----------------------------
 
It contains Import Export Class Implementation
Use this class to Import Export the tables between Database and the  Storage Device
 
**********************************************************************************************************/
#include "ImportExport.h"
#include "DataLogger.h"

namespace fs = std::filesystem;
size_t ImportExport::static_log_id=0;
/**************************************************************************//**
*
* \brief   - Constructor
*
* \param   - None.
*
* \return  - none
*
******************************************************************************/
ImportExport::ImportExport()
{
	//enroll to use logger functionality
	static_log_id = Logger::enroll(this);
	m_InitiateExportRequestForReferenceGraph = false;
	m_InitiateImportRequestForReferenceGraph = false;
	m_InitiateExportRequestForRecipes = false;
	m_InitiateImportRequestForRecipes = false;
	m_InitiateExportRequestForSystemConfiguration = false;
	m_InitiateImportRequestForSystemConfiguration = false;
	m_InitiateExportRequestForSystemBackup = false;
	m_InitiateImportRequestForSystemBackup = false;
	m_StorageDeviceSelection = USB;
	m_StorageSelection = false;
}

/******************************************************************************
* \brief - Destructor
*
* \param - none
*
* \return - none
*
******************************************************************************/
ImportExport::~ImportExport()
{
  
}

/**************************************************************************//**
*
* \brief   - Process the data coming from the ASC
*			 
* \param   - Address of source MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ImportExport::SetData(const MEMORY_BLOCK *const source)
{
	int retVal = -1;
	if((source != nullptr) && (source->id == MB_ID_IMPORT_EXPORT_DATA) )
	{
		// perform operation based on sub id
		if( (source->config & VALID_BIT) == (VALID_BIT) )
		{
			switch(source->sub_id)
			{
 
				case READ_REFERENCE_GRAPH_NAME_FROM_SYSTEM:
				{
					retVal = 0;
					processReferenceGraphNamesfromASC(source);
					break;
				}
 
				case READ_REFERENCE_GRAPH_NAMES_FROM_IMPORT_EXPORT_INTERFACE:
				{
					retVal = 0;
					processReferenceGraphfilesfromASC(source);
					break;
				}
				
				case READ_RECIPE_NAME_FROM_SYSTEM:
				{
					retVal = 0;
					processRecipeNamesfromASC (source);
					break;
				}
				
				case READ_RECIPE_NAMES_FROM_IMPORT_EXPORT_INTERFACE:
				{
					retVal = 0;
					processRecipeFileNamesFromASC(source);
					break;
				}
				
				case READ_SYSTEM_CONFIGURATION_FILES_FROM_IMPORT_EXPORT_INTERFACE:
				{
					retVal = 0;
					processSystemConfigfilesfromASC(source);
					break;
				}

				default:
				{
					char  msg[buff_size_config] = {0};
					snprintf(msg,buff_size_config,"Import Export SetData default case\n");
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
					break;
				}
			}
 
		}
		else
		{
			retVal = 0;
		}
	}
	else
	{
		char  msg[buff_size_config];
		snprintf(msg,buff_size_config,"Import Export SetData invalid request\n");
		Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
	}
	return (retVal);
}

/**************************************************************************//**
*
* \brief   - send the Import/Export request to ASC.
*
* \param   - Address of source MB.
*
* \return  - If success returns 0, else returns -1 (failure)
*
******************************************************************************/
int ImportExport:: GetData(MEMORY_BLOCK * const destination)
{
	int retVal = -1;
		// check parameter
		if((destination != nullptr) && (destination->id == MB_ID_IMPORT_EXPORT_DATA))
		{
			// perform operation based on sub id
			switch(destination->sub_id)
			{
 
				case EXPORT_REFERENCE_GRAPH:
				{
					retVal = 0;
					destination->config = VALID_BIT;
					sendExportReferenceGraphRequestToASC(destination);
					break;
				}
				case IMPORT_REFERENCE_GRAPH:
				{
					retVal = 0;
					destination->config = VALID_BIT;
					sendImportReferenceGraphRequestToASC(destination);
					break;
				}
				
				case EXPORT_RECIPES:
				{
					retVal = 0;
					destination->config = VALID_BIT;
					sendExportRecipesRequesttoASC(destination);
					break;
				}
				
				case IMPORT_RECIPES:
				{
					retVal = 0;
					destination->config = VALID_BIT;
					sendImportRecipesRequesttoASC(destination);
					break;
				}
				
				case EXPORT_SYSTEM_CONFIGURATION:
				{
					retVal = 0;
					destination->config = VALID_BIT;
					sendExportSystemConfigRequestToASC(destination);
					break;
				}
				
				case IMPORT_SYSTEM_CONFIGURATION:
				{
					retVal = 0;
					destination->config = VALID_BIT;
					sendImportSystemConfigRequesttoASC(destination);
					break;
				}
				
				case EXPORT_SYSTEM_BACKUP:
				{
					retVal = 0;
					destination->config = VALID_BIT;
					sendExportSystemBackupRequestToASC(destination);
					break;
				}
				
				case IMPORT_SYSTEM_BACKUP:
				{
					retVal = 0;
					destination->config = VALID_BIT;
					sendImportSystemBackupRequesttoASC(destination);
					break;
				}
				
				case STORAGE_DEVICE_SELECTION:
				{
					retVal = 0;
					destination->config = VALID_BIT;
					sendStorageDeviceSelectionToASC(destination);
					break;
				}
						
				
				default:
				{
					// Error ! default retVal (failure) will be returned
					// clear valid bit, reset size
					destination->size = 0;
					// clear valid bit
					destination->config = 0;
					char  msg[buff_size_config] = {0};
					snprintf(msg,buff_size_config,"Import Export GetData default case");
					Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
					break;
				}
			}
		}
		else
		{
			// error! invalid memory block id, default retVal (failure) will be returned
			// clear valid bit, reset size
			destination->size = 0;
			// clear valid bit
			destination->config = 0;
			char  msg[buff_size_config] = {0};
			snprintf(msg,buff_size_config,"Import Export GetData invalid case");
			Logger::add_entry(E_SEVERITY::E_LOG_ALARM, msg);
		}
 
		return (retVal);
}

/**************************************************************************//**
*
* \brief   - process the reference signature graph coming from ASC
*
* \param   - source - memory block holding the stream data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void ImportExport::processReferenceGraphNamesfromASC(const MEMORY_BLOCK *const source)
{
	int referenceSignatureCount = *reinterpret_cast<const int*>(source->data);
	ReferenceSignatureStruct* referenceSignatureResponse = 
			reinterpret_cast<ReferenceSignatureStruct*>(source->data + sizeof(int));
	m_ReferenceGraphs.clear();
	for (int iterator = 0; iterator < referenceSignatureCount; ++iterator)
	{
		//Store the graph names in a vector
		m_ReferenceGraphs.push_back(referenceSignatureResponse[iterator]);
	}
}

/**************************************************************************//**
*
* \brief   - process the refernce graph names and their selection
*
* \param   - source - memory block holding the stream data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void ImportExport::processReferenceGraphfilesfromASC(const MEMORY_BLOCK *const source)
{
	int fileCount = *reinterpret_cast<const int*>(source->data);
	StorageStruct* FilesArray = reinterpret_cast<StorageStruct*>(source->data + sizeof(int));
	m_GraphFiles.clear();
	for (int iterator = 0; iterator < fileCount; ++iterator)
	{
		//Store the filenames in a vector
		m_GraphFiles.push_back(FilesArray[iterator]);
	}
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_IMPORT_EXPORT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void ImportExport::sendExportReferenceGraphRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >=sizeof(ReferenceSignatureStructure))
	{
		if(m_InitiateExportRequestForReferenceGraph == true)
		{
			// update size in destination
			destination->size = sizeof(ReferenceSignatureStructure);
			// set valid bit
			destination->config = VALID_BIT;
			ReferenceSignatureStructure *m_exportData = 
					reinterpret_cast<ReferenceSignatureStructure *>(destination->data);
			*m_exportData = m_ExportGraph;
			//Make the export request flag false after the completion of export
			m_InitiateExportRequestForReferenceGraph = false;
 
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	} 
}
 
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click export button.
*
* \param   - Structure variable for export
*
* \return  - None
*
******************************************************************************/
void ImportExport::InitiateReferenceWeldSignatureExportRequest(ReferenceSignatureStructure Export)
{
	m_ExportGraph = Export;
	m_InitiateExportRequestForReferenceGraph = true;
}
 
/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_IMPORT_EXPORT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void ImportExport::sendImportReferenceGraphRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >=sizeof(StorageStructure))
	{
		if(m_InitiateImportRequestForReferenceGraph == true)
		{
			// update size in destination
			destination->size = sizeof(StorageStructure);
			// set valid bit
			destination->config = VALID_BIT;
			StorageStructure *m_importData = reinterpret_cast<StorageStructure *>(destination->data);
			*m_importData = m_ImportGraphFile;
			//Make the import request flag false after the completion of import
			m_InitiateImportRequestForReferenceGraph = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
}
 
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click import button.
*
* \param   - Structure variable for Import
*
* \return  - None
*
******************************************************************************/
void ImportExport::InitiateReferenceWeldSignatureImportRequest(StorageStructure Import)
{
	m_ImportGraphFile = Import;
	m_InitiateImportRequestForReferenceGraph = true;
}

/**************************************************************************//**
*
* \brief   - process the Recipes coming from ASC
*
* \param   - source - memory block holding the stream data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void ImportExport::processRecipeNamesfromASC (const MEMORY_BLOCK *const source)
{
	int recipeCount = *reinterpret_cast<const int*>(source->data);
	RecipeStruct* recipeResponse = reinterpret_cast<RecipeStruct*>(source->data + sizeof(int));
	m_Recipes.clear();
	for (int iterator = 0; iterator < recipeCount; ++iterator)
	{
	    m_Recipes.push_back(recipeResponse[iterator]);
	}
 
}
 
/**************************************************************************//**
*
* \brief   - process the Recipe files coming from USB
*
* \param   - source - memory block holding the recipe filenames
*
* \return  - none
*
******************************************************************************/
void ImportExport::processRecipeFileNamesFromASC(const MEMORY_BLOCK *const source)
{
    int fileCount = *reinterpret_cast<const int*>(source->data);
    StorageStruct* filesArray = reinterpret_cast<StorageStruct*>(source->data + sizeof(int));
    m_RecipeFileNames.clear();
    for (int iterator = 0; iterator < fileCount; ++iterator)
    {
        m_RecipeFileNames.push_back(filesArray[iterator]);
    }
}
 
/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_IMPORT_EXPORT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void ImportExport::sendExportRecipesRequesttoASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(RecipeStructure))
	{
		if(m_InitiateExportRequestForRecipes == true)
		{
			// update size in destination
			destination->size = sizeof(RecipeStructure);
			// set valid bit
			destination->config = VALID_BIT;
 
			RecipeStructure *m_exportRecipeData = reinterpret_cast<RecipeStructure *>(destination->data);
			*m_exportRecipeData = m_ExportRecipe;
			//Make the export request flag false after the completion of export
			m_InitiateExportRequestForRecipes = false;
 
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
 
}

/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_IMPORT_EXPORT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void ImportExport::sendImportRecipesRequesttoASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >=sizeof(StorageStructure))
	{
		if(m_InitiateImportRequestForRecipes == true)
		{
			// update size in destination
			destination->size = sizeof(StorageStructure);
			// set valid bit
			destination->config = VALID_BIT;
			StorageStructure *m_importRecipeData = reinterpret_cast<StorageStructure *>(destination->data);
			*m_importRecipeData = m_ImportRecipeFile;
			//Make the import request flag false after the completion of import
			m_InitiateImportRequestForRecipes = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click export button for Recipes.
*
* \param   - Structure variable for export
*
* \return  - None
*
******************************************************************************/
void ImportExport::InitiateExportRequestForRecipes(RecipeStructure Export)
{
	m_ExportRecipe = Export;
	m_InitiateExportRequestForRecipes = true;
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click import button for Recipes.
*
* \param   - Structure variable for Import
*
* \return  - None
*
******************************************************************************/
void ImportExport::InitiateImportRequestForRecipes(StorageStructure Import)
{
	m_ImportRecipeFile = Import;
	m_InitiateImportRequestForRecipes = true;
}

/**************************************************************************//**
*
* \brief   - process the System Configuration files coming from ASC
*
* \param   - source - memory block holding the stream data received
* 			 from ASC
*
* \return  - none
*
******************************************************************************/
void ImportExport::processSystemConfigfilesfromASC(const MEMORY_BLOCK *const source)
{
    int fileCount = *reinterpret_cast<const int*>(source->data);
    StorageStruct* filesArray = reinterpret_cast<StorageStruct*>(source->data + sizeof(int));
    m_SystemConfigFiles.clear();
    for (int iterator = 0; iterator < fileCount; ++iterator)
    {
        m_SystemConfigFiles.push_back(filesArray[iterator]);
    }
}
/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_IMPORT_EXPORT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void ImportExport ::sendExportSystemConfigRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(SystemConfigurationStructure))
	{
		if(m_InitiateExportRequestForSystemConfiguration == true)
		{
			// update size in destination
			destination->size = sizeof(SystemConfigurationStructure);
			// set valid bit
			destination->config = VALID_BIT;
			
			SystemConfigurationStructure *SystemConfigurationData = reinterpret_cast<SystemConfigurationStructure *>(destination->data);
			SystemConfigurationData->AlarmConfiguration = m_SysConfigData.AlarmConfiguration;
			SystemConfigurationData->DateTimeFormat = m_SysConfigData.DateTimeFormat;
			SystemConfigurationData->GlobalUserSetting = m_SysConfigData.GlobalUserSetting;
			SystemConfigurationData->NetworkConfiguration = m_SysConfigData.NetworkConfiguration;
			SystemConfigurationData->UserPrivilege = m_SysConfigData.UserPrivilege;
			SystemConfigurationData->UserProfile = m_SysConfigData.UserProfile;
			SystemConfigurationData->SystemGeneral = m_SysConfigData.SystemGeneral;
			SystemConfigurationData->UserIO = m_SysConfigData.UserIO;
			SystemConfigurationData->WeldSignatureConfig = m_SysConfigData.WeldSignatureConfig;
			SystemConfigurationData->FBCustomIO = m_SysConfigData.FBCustomIO;
			SystemConfigurationData->NetworkConfigurationEIP= m_SysConfigData.NetworkConfigurationEIP;
			//Make the export request flag false after the completion of export
			m_InitiateExportRequestForSystemConfiguration = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
}
/**************************************************************************//**
*
* \brief   - send the requests to ASC for memory block ID MB_ID_IMPORT_EXPORT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void ImportExport::sendImportSystemConfigRequesttoASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(StorageStructure))
	{
		if(m_InitiateImportRequestForSystemConfiguration == true)
		{
			// update size in destination
			destination->size = sizeof(StorageStructure);
			// set valid bit
			destination->config = VALID_BIT;
			StorageStructure *m_ImportSysConfigData = reinterpret_cast<StorageStructure *>(destination->data);
			*m_ImportSysConfigData = m_ImportSysConfig;
			//Make the import request flag false after the completion of import
			m_InitiateImportRequestForSystemConfiguration = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}

}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click export button for SystemConfiguration.
*
* \param   - Structure variable for export
*
* \return  - None
*
******************************************************************************/
void ImportExport::InitiateExportRequestForSystemConfiguration(SystemConfigurationStructure Export)
{
	m_SysConfigData = Export;
	m_InitiateExportRequestForSystemConfiguration = true;
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click import button for System Configuration.
*
* \param   - Structure variable for Import
*
* \return  - None
*
******************************************************************************/
void ImportExport::InitiateImportRequestForSystemConfiguration(StorageStructure Import)
{
	m_ImportSysConfig = Import;
	m_InitiateImportRequestForSystemConfiguration = true;
}

/**************************************************************************//**
*
* \brief   - send the export system backup request to ASC for memory block ID MB_ID_IMPORT_EXPORT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void ImportExport :: sendExportSystemBackupRequestToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >=sizeof(int))
	{
		if(m_InitiateExportRequestForSystemBackup == true)
		{
			// update size in destination
			destination->size = sizeof(int);
			// set valid bit
			destination->config = VALID_BIT;
			m_InitiateExportRequestForSystemBackup = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
}
/**************************************************************************//**
*
* \brief   - send the import system backup requests to ASC for memory block ID MB_ID_IMPORT_EXPORT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void ImportExport::sendImportSystemBackupRequesttoASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >=sizeof(int))
	{
		if(m_InitiateImportRequestForSystemBackup == true)
		{
			// update size in destination
			destination->size = sizeof(int);
			// set valid bit
			destination->config = VALID_BIT;
			m_InitiateImportRequestForSystemBackup = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
 
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click export button for SystemBackup.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ImportExport::InitiateExportRequestForSystemBackup()
{
	m_InitiateExportRequestForSystemBackup = true;
}

/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click import button for System SystemBackup.
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ImportExport::InitiateImportRequestForSystemBackup()
{
	m_InitiateImportRequestForSystemBackup = true;
}
/**************************************************************************//**
*
* \brief   - send the storage selection to ASC for memory block ID MB_ID_IMPORT_EXPORT_DATA.
*
* \param   - destination - Memory block containing data to be sent to ASC
*
* \return  - on success return 1 else -1.
*
******************************************************************************/
void ImportExport ::sendStorageDeviceSelectionToASC(MEMORY_BLOCK * const destination)
{
	if(destination->size >= sizeof(STORAGE_OPTIONS))
	{
		if(m_StorageSelection == true)
		{
			// update size in destination
			destination->size = sizeof(STORAGE_OPTIONS);
			// set valid bit
			destination->config = VALID_BIT;
 
			STORAGE_OPTIONS *StorageDevice = reinterpret_cast<STORAGE_OPTIONS *>(destination->data);
			*StorageDevice = m_StorageDeviceSelection;

			//Make the Storage Selection flag false
			m_StorageSelection = false;
		}
		else
		{
			destination->size = 0;
			destination->config = VALID_BIT;
		}
	}
	else
	{
		destination->size = 0;
		destination->config = 0;
	}
}
 
/**************************************************************************//**
*
* \brief   - call this method on HMI side when you click Storage selection .
*
* \param   - None
*
* \return  - None
*
******************************************************************************/
void ImportExport::SelectStorageDevice(STORAGE_OPTIONS Device)
{	
	m_StorageDeviceSelection = Device;
	m_StorageSelection = true;	
}

