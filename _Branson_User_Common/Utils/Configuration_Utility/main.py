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
# Main Configuration generation file.
#
# --------------------------- REVISION HISTORY ------------------------------
#  rev1: 15/09/2023 - Initial implementation.
#  rev2: 27/10/2023 - Added Support for UI
# ***************************************************************************/
# DO NOT MODIFY THIS FILE !!!
#
import json
import hashlib
import subprocess
import tempfile
import PlatformConfig
import SecureConfig
import flet as ft
from flet import icons, alignment
import datetime

# JSON configuration generation
json_config = {}

# Following function generates the encrypted JSON configuration and corresponding hash
def Generate_config():
    
    print("Generating Configuration......")
    # Temporary file for symmetric key
    tf = tempfile.NamedTemporaryFile(delete=True)
    
    # Temporary file for JSON
    JsonFile = tempfile.NamedTemporaryFile(delete=True)
    
    # Path of configuration file 
    config_A_path       = 'config_A.out'
    config_B_path       = 'config_B.out'
    
    # Create Configuration at current path.
    open(config_A_path, "w")
    open(config_B_path, "w")
    
    # Function to generate JSON file
    # with open(json_file_path, 'w') as f:
    with open(JsonFile.name, 'w') as f:
        json.dump(json_config, f)
        
    # Function to calculate SHA-512 hash
    def calculate_sha512_hash(file_path):
        sha512=hashlib.sha512()
        with open (file_path, 'rb') as file:
            while True:
                data=file.read(65536)
                if not data:
                    break
                sha512.update(data)
                return sha512.hexdigest()
    
    # Calculate the SHA-512 hash of the JSON data
    hash_value=calculate_sha512_hash(JsonFile.name)
    
    # Generate config_A.out file --> contains hash of JSON data
    with open(config_A_path, "w") as f:
        f.write(hash_value)
        
    # print(f'SHA-512 hash of JSON data :{hash_value}')   
    
    # Generate symmetric key
    subprocess.run(["openssl", "aes-256-cbc", "-pbkdf2", "-iter", "10000", "-d", "-pass", "pass:BransonTopSecret@1234#", "-in", SecureConfig.key_path, "-out", tf.name])
    
    # Generate encryoted config_B.out file --> Encrypted JSON file 
    subprocess.run(["openssl", "aes-256-cbc", "-pbkdf2", "-iter", "10000", "-e", "-k", tf.read(), "-in", JsonFile.name, "-out",  config_B_path])
    
    tf.close()
    JsonFile.close(); 

# Main Function
def main(page: ft.Page):
    page.title = "ACE Configuration (not for production use)"
    page.window_width = 500
    page.window_height = 700
    page.update()

    
    # Pop-Up element to alert status of configuration generation
    def PopUp(mytext):
        dlg = ft.AlertDialog(
            title=ft.Text(mytext), on_dismiss=lambda e: print(mytext)
        )
        return dlg
    
     # Dropdown element used to select required configuration
    def dropdown(title, listOfElements):
        return ft.Row(
            [
                ft.Text(value=title,text_align=ft.TextAlign.RIGHT, width=100, size=15),
                ft.Dropdown(
                width=150,
                options=listOfElements
                )
            ],
            alignment = ft.MainAxisAlignment.CENTER
        )
        
    # function to indentify selected index from Dropdown option
    def GetSelectedIndex(elem_dropdown):
        index = 0
        selected_index = 0
        for option in elem_dropdown.options:
            index = index + 1
            if(option.key == elem_dropdown.value):
                selected_index = index
                break
        return selected_index
    
    # Handles event after pressing "Generate" Button    
    def OnClick(e):
        json_config["Machine_Serial_Number"] = "XYZ12345678"
        json_config["Date_Time"] = datetime.datetime.now().strftime("%I:%M%p on %B %d, %Y")
        json_config["Version"] = PlatformConfig.RevisionNumber
        for row in cl._get_children():
            Rowtext = row._get_children()[0]
            RowDropdown = row._get_children()[1]
            index = GetSelectedIndex(RowDropdown)
            if(index > 0):
                json_config[Rowtext.value] = index
        print(json_config)
        Generate_config()
        dlg=PopUp("Configuration files generated successfully")
        page.dialog = dlg
        dlg.open = True
        page.update()
        json_config.clear()
    
    # dynamically load dropdown selection UI based on PlatformConfig values      
    cl = ft.Column(scroll=ft.ScrollMode.ALWAYS)
    for entry in PlatformConfig.plaform_config :
        dropdownOptions = []
        for option in PlatformConfig.plaform_config[entry]:
            dropdownOptions.append(ft.dropdown.Option(option))
        cl.controls.append(dropdown(entry,dropdownOptions))
    cl.expand = True
    cl.horizontal_alignment = ft.CrossAxisAlignment.CENTER
    cl.alignment = ft.MainAxisAlignment.CENTER
    cl.spacing = 30
    
    # "Generate" Button element
    def GenerateButton():
        cl2 = ft.Column()
        cl2.controls.append(ft.Text(size=30))
        cl2.controls.append(ft.ElevatedButton(text="Generate",width=250, height=70,on_click=OnClick))
        return cl2
    
    # Add elements to primary page   
    page.add(
        ft.AppBar(title=ft.Text("ACE Configuration Utility"), bgcolor=ft.colors.BLUE_200),
        cl,
        GenerateButton()
    )
    page.vertical_alignment = ft.MainAxisAlignment.CENTER
    page.horizontal_alignment = ft.CrossAxisAlignment.CENTER
    page.update()

ft.app(target=main)
# use following code to run from Web Browser instead of ft.app(target=main)
#ft.app(target=main, view=ft.AppView.WEB_BROWSER)