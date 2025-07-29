# /**************************************************************************
#
#            Copyright (c) Branson Ultrasonics Corporation, 1996-2023
#
#            This program is the property of Branson Ultrasonics Corporation
#          Copying of this software is expressly forbidden, without the prior
#            written consent of Branson Ultrasonics Corporation.
#
# --------------------------- MODULE DESCRIPTION ----------------------------
#
# Ace Platform configuration generation utility.
# This file is used only for developement purpose, not for production !
# 
# This file contains configuration input to generate JSON configuration file.
#
# --------------------------- REVISION HISTORY ------------------------------
#  rev1: 15/09/2023 - Initial implementation.
#  rev2: 27/10/2023 - Added Support for UI.
#  rev3: 8/12/2023 - Added Support for Weld Strength Optimization.
#  rev4: 12/12/2023 - Added Support for Weld Mode and Storage Configuration.
# ***************************************************************************/

RevisionNumber = "0.1"

# This definition is used to load UI elements at runtime
# Modify this definition to add/remove configuration items on UI
plaform_config = {
    "Power_Supply_Type" : ["P2100", "P2200"],
    "Power_Level" : ["20 kHZ, 1.25kW", "20 kHZ, 2.5kW", "20 kHZ, 4.0kW", "30kHZ, 1.5kW", "40kHZ, 0.8kW"],
    "Actuator_Type" : ["Manual", "Electronic", "Electronic Plus", "No Actuator"],
    "Cylinder_Size" : ["40 mm", "50 mm", "63 mm", "80 mm"],
    "Bearing_Type" : ["Standard", "Stainless Steel"],
    "Stroke_Length" : ["100 mm"],
    "Event_Logs" : ["Not Supported", "Supported"],
    "Storage" : ["Standard", "Advanced", "Elite"],
    "Batch_Control" : ["Not Supported", "Supported"],
    "LDAP" : ["Not Supported", "Supported"],
    "User_Access_Level" : ["Standard", "Advanced"],
    "Barcode_Scanner" : ["Not Supported", "Supported"],
    "User_IO" : ["Not Supported", "Supported"],
    "Industrial_Ethernet" : ["Not Supported", "Ethernet/IP", "Profinet"],
    "PC_Utility" : ["Not Supported", "Supported"],
    # Add supported feature above this line 
    "HMI_Type" : ["Local HMI", "PC HMI", "Both"] 
    }


