# Rockmeter
![body](https://user-images.githubusercontent.com/61804891/139777671-14e50a7c-51be-490f-9f41-423e66c0467b.png)

Rockmeter is a custom altimeter for your low or medium power rocket.  
The arduino NANO read the data from a BMP280.  
It gives ALTITUDE + MAX ALTITUDE + TEMPERATURE  
When at least a 5meters is detected the GREEN LED turn RED and a buzzer BEEP.  
The objective was to make a low budget altimeter as you sometimes lose a rocket and you don't want to say bye bye to your 100$ altimeter.  
![screen](https://user-images.githubusercontent.com/61804891/139777685-26f79e2d-b0f1-4461-8b79-f373da2a02dd.png)

PARTS NEEDED

- Arduino NANO
- BMP280
- 2 PINS CONNECTOR
- BUZZER
- 3X 330K RESISTORS
- RGB LED
- 128X64 OLED SCREEN

CODES AND LIBRARY  

- Rockmeter V12 CODE
- Library
- PCB FILE ( GERBER AND EASYEDA)  

![Capture d’écran, le 2021-11-01 à 10 22 41 p m](https://user-images.githubusercontent.com/61804891/139776459-003e992c-ead2-462d-8a2f-2987d4e22869.png)


PINNOUT  

RED LED = 9  
Green LED = 10  
BUZZ = 3  
SDA = 4  
SCL = 5  


ADDRESS  

- BMP280 0x76
- OLED 0x3C

** Do not contact me for parts not detected. Usual problem is to check if the address are good in I2C ( USE I2C SCAN) and change the address in original library if needed/

*** Did some test and the unit seems to have a 3% error margin.  

REFERENCE  
https://www.electronics-lab.com/project/arduino-bmp280-based-weather-station/



