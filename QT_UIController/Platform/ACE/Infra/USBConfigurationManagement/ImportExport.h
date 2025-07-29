/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2022

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

---------------------------- MODULE DESCRIPTION ----------------------------

It contains ImportExport Class Implementation
Use this class to Import/Export tables between Database and  Mass Storage

**********************************************************************************************************/
#ifndef IMPORTEXPORT_H_
#define IMPORTEXPORT_H_
 
#include <string>
#include <stdio.h>
#include <cstdio>
#include <fstream>
#include <iostream> 
#include <cstring>
#include <filesystem>
#include <vector>
 
#include "commons.h"
#include "DataInterface.h"
#include "DataInterface.h"
#include "Common_Definitions.h"
#include "WeldSignatureStructuresAce.h"
#include "ProductionScreen_MB.h"
#include "ReportConfig.h"
#include "ImportExportStructure.h"
  
class ImportExport   : public DataInterface
{
public:
	ImportExport();
    ~ImportExport();
    
    static size_t static_log_id;
    int GetData(MEMORY_BLOCK * const destination) override;
    int SetData(const MEMORY_BLOCK *const source) override;
    void InitiateReferenceWeldSignatureExportRequest(ReferenceSignatureStructure Export);
    void InitiateReferenceWeldSignatureImportRequest(StorageStructure Import);
    void InitiateExportRequestForRecipes(RecipeStructure Export);
    void InitiateImportRequestForRecipes(StorageStructure Import);
    void InitiateExportRequestForSystemConfiguration(SystemConfigurationStructure Export);
    void InitiateImportRequestForSystemConfiguration(StorageStructure Import);
    void InitiateExportRequestForSystemBackup();
    void InitiateImportRequestForSystemBackup();
    void SelectStorageDevice(STORAGE_OPTIONS Device);
    
	void SetInterFaceID(INTERFACE_IDENTIFIER InterfaceID){m_InterfaceID = InterfaceID;};
	INTERFACE_IDENTIFIER m_InterfaceID = UNKNOWN_INTERFACE;
	
private:
	//vector holding Reference Graph Names
    std::vector<ReferenceSignatureStruct> m_ReferenceGraphs;
    //vector holding the File Names for Reference Graph
    std::vector<StorageStruct> m_GraphFiles;
    //vector holding the Recipe Names
    std::vector<RecipeStruct> m_Recipes;
    //vector holding the File Names for Recipes
    std::vector<StorageStruct> m_RecipeFileNames;
    //vector holding the File Names for System Configuration
    std::vector<StorageStruct> m_SystemConfigFiles;

    
    //Flag for setting Export Request
    bool m_InitiateExportRequestForReferenceGraph;
    //Flag for setting Import Request
    bool m_InitiateImportRequestForReferenceGraph;
    //Flag for setting Export Request for Recipes
    bool m_InitiateExportRequestForRecipes;
    //Flag for setting Import Request for Recipes
    bool m_InitiateImportRequestForRecipes;
    //Flag for setting Export Request for System Configuration
	bool m_InitiateExportRequestForSystemConfiguration;
	 //Flag for setting Import Request for System Configuration
	bool m_InitiateImportRequestForSystemConfiguration;
    //Flag for setting Export Request for System Backup
	bool m_InitiateExportRequestForSystemBackup;
	 //Flag for setting Import Request for System Backup
	bool m_InitiateImportRequestForSystemBackup;
	 //Flag for setting Storage Selection
	bool m_StorageSelection;
	
	  
	//Structure variable to hold Graph names and selection for export
	ReferenceSignatureStructure m_ExportGraph;
    //Structure variable to hold Graph files and selection for import
	 StorageStructure m_ImportGraphFile;
   //Structure variable to hold Recipe names and selection for export
	RecipeStructure m_ExportRecipe;
	//Structure variable to hold Recipe files and selection for import
	StorageStructure m_ImportRecipeFile;
	//Structure variable to hold System configuration data for export
	SystemConfigurationStructure m_SysConfigData;
	//Structure variable to hold System configuration files and selection for import
	StorageStructure m_ImportSysConfig;
	//Variable to hold the storage device selection
	STORAGE_OPTIONS m_StorageDeviceSelection;
	
    void processReferenceGraphNamesfromASC(const MEMORY_BLOCK *const source);
    void processReferenceGraphfilesfromASC(const MEMORY_BLOCK *const source);
    void sendExportReferenceGraphRequestToASC(MEMORY_BLOCK * const destination);
    void sendImportReferenceGraphRequestToASC(MEMORY_BLOCK * const destination);
    void processRecipeNamesfromASC (const MEMORY_BLOCK *const source);
    void processRecipeFileNamesFromASC(const MEMORY_BLOCK *const source);
    void sendExportRecipesRequesttoASC(MEMORY_BLOCK * const destination);
    void sendImportRecipesRequesttoASC(MEMORY_BLOCK * const destination);
    void processSystemConfigfilesfromASC(const MEMORY_BLOCK *const source);
    void sendExportSystemConfigRequestToASC(MEMORY_BLOCK * const destination);
    void sendImportSystemConfigRequesttoASC(MEMORY_BLOCK * const destination);	
    void sendExportSystemBackupRequestToASC(MEMORY_BLOCK * const destination);
	void sendImportSystemBackupRequesttoASC(MEMORY_BLOCK * const destination);
	void sendStorageDeviceSelectionToASC(MEMORY_BLOCK * const destination);
	
};

#endif /* IMPORTEXPORT_H_ */
 
 


 


 
 
 
