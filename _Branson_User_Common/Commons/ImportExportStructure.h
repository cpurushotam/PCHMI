/**************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2023

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.


--------------------------- MODULE DESCRIPTION ----------------------------

 This file contains the USB Import Export Related implementation
 ***************************************************************************/
#ifndef USBIMPORTEXPORTSTRUCTURE_H_
#define USBIMPORTEXPORTSTRUCTURE_H_

#include "Common_Definitions.h"
#include "ProductionScreen_MB.h"

//Maximum number of reference weld signatures sent in one chunk
constexpr int MAX_NUM_OF_REFERENCE_SIGNATURES_IN_ONE_CHUNK = 3;
//Maximum number of reference weld signatures configured
constexpr int MAX_NUM_OF_REFERENCE_SIGNATURES= 3;
//Maximum number of files from storage device sent in one chunk
constexpr int MAX_NUM_OF_FILES_IN_ONE_CHUNK = 10;
//File name size in storage device
constexpr int FILE_NAME_SIZE = 50;
//Maximum number of recipes sent in one chunk
constexpr int MAX_NUM_OF_RECIPES_IN_ONE_CHUNK = 10;
//Maximum number of recipes that can be configured
constexpr int MAX_NUM_OF_RECIPES = 1000;

//Enumerations of Import Export Modules
typedef enum
{
	EXPORT_REFERENCE_GRAPH = 1,
	IMPORT_REFERENCE_GRAPH,
	READ_REFERENCE_GRAPH_NAME_FROM_SYSTEM,
	READ_REFERENCE_GRAPH_NAMES_FROM_IMPORT_EXPORT_INTERFACE,
	EXPORT_RECIPES,
	IMPORT_RECIPES,
	READ_RECIPE_NAME_FROM_SYSTEM,
	READ_RECIPE_NAMES_FROM_IMPORT_EXPORT_INTERFACE,
	EXPORT_SYSTEM_CONFIGURATION,
	IMPORT_SYSTEM_CONFIGURATION,
	READ_SYSTEM_CONFIGURATION_FILES_FROM_IMPORT_EXPORT_INTERFACE,
	EXPORT_SYSTEM_BACKUP,
	IMPORT_SYSTEM_BACKUP,
	READ_SYSTEM_BACKUP_FOLDER_FROM_IMPORT_EXPORT_INTERFACE,
	STORAGE_DEVICE_SELECTION
}IMPORT_EXPORT_SUB_ID;

//Structure holding the filenames and the selection
typedef struct StorageStruct
{
    char FileName[FILE_NAME_SIZE];
    bool Fileselection=0;

}__attribute__((packed))  StorageStruct;

typedef struct StorageStructure
{
	StorageStruct Filenames[MAX_NUM_OF_FILES_IN_ONE_CHUNK];

}__attribute__((packed))  StorageStructure;

//Structure holding the reference graph name and selection for import export
typedef struct ReferenceSignatureStruct
{
    char ReferenceGraphName[REF_GRAPH_NAME_SIZE];
    bool GraphSelection=0;

}__attribute__((packed))  ReferenceSignatureStruct;

typedef struct ReferenceSignatureStructure
{
	ReferenceSignatureStruct ReferenceGraphs[MAX_NUM_OF_REFERENCE_SIGNATURES];

}__attribute__((packed))  ReferenceSignatureStructure;

//Structure holding the recipe name and selection for import export
typedef struct RecipeStruct
{
    char RecipeName[RECIPE_NAME_SIZE];
    bool RecipeSelection=0;

}__attribute__((packed))  RecipeStruct;

typedef struct RecipeStructure
{
	RecipeStruct Recipes[MAX_NUM_OF_RECIPES_IN_ONE_CHUNK];

}__attribute__((packed))  RecipeStructure;

//Structure holding the system configuration table names
typedef struct SystemConfigurationStructure
{
    bool AlarmConfiguration;
    bool DateTimeFormat;
    bool GlobalUserSetting;
    bool NetworkConfiguration;
    bool UserPrivilege;
    bool UserProfile;
    bool SystemGeneral;
    bool UserIO;
    bool WeldSignatureConfig;
    bool FBCustomIO;
    bool DataStream;
    bool NetworkConfigurationEIP;
} __attribute__((packed))  SystemConfigurationStructure;




#endif /* USBIMPORTEXPORTSTRUCTURE_H_ */
