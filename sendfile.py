# -*- coding: utf-8 -*-
""" What is sendfile.py
This module is send 3gx to 3ds via FTP.
このモジュールはFTPで3gxを3dsに送信します。
"""

import ftplib
from ftplib import FTP

print("--------------------------")
print("Trying to Send the Plugin over FTP...")

get_ftp = FTP()

HOST_ADDRESS = "192.168.0.50"
PORT = 5000
TIME_OUT = 30.0

try:
    get_ftp.connect(HOST_ADDRESS, PORT, TIME_OUT)
except ftplib.all_errors:
    print("Failed to Connect on " + HOST_ADDRESS + " : " + str(PORT))

PATH = "luma/plugins/0004000000155400"
PLUGIN = "/Colorful-MHX3gx.3gx"

try:
    print("Successfully Logged in " + HOST_ADDRESS + "\n")
    print("Response : " + get_ftp.getwelcome())
    get_ftp.login()
    get_ftp.storbinary("STOR " + PATH + PLUGIN,
                       open(PLUGIN.replace("/", ""), "rb"))
    print("Sending Plugin to " + PATH + "\n")
except ftplib.all_errors:
    print("Login Failed!\n")
