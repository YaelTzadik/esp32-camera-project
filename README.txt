To create the database, follow the instruction bellow:
1) Create a folder containing passport Images in JPEG format. make sure the names has no space.
2) Open "Project_Interface/create_database_for_sd.py" and change 'image_directory' path to your folder (line 84)
3) Run python script.
4) Open "database.csv" and copy it's content into a txt file named "targets".
5) Format your microSD card as "FAT"
6) Save the txt file on the card.
7) Insert the card to the ESP32_camera.



To use the ESP32-cam door security system, follow the instruction bellow:

1) Make sure you have wifi network less then 5Ghz and No three phase wifi (no username).
    You will need the name and the password of that network.
2) Connect the ESP32 to your power source.
3) Reset the device.

USING BLOOTOTH CONNECTION:
4) Open Serial Bluetooth app and connect the device DoorLockController.
5) Select the wifi network and input your password.
6) You will get the device IP address.
7) Run main.py  in Project_Interface.
8) Enter the device's IP adress into the popup window and press start.

USING ARDUINO CODE:
4) Open CameraWebServer.ino in "CameraWebServer-no Bluetooth" folder.
5) Download the board esp32 ver1.0.2
6) Choose the "ESP32 Wrover Module" board and the device's communication port.
7) Change the wifi name and password
8) Run the file and open the Serial monitor.
9) Reset the device.
10) You will get the device's IP address.
11) Run main.py  in Project_Interface.
12) Enter the device's IP adress into the popup window and press start.
