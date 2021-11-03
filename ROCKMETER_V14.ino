// Original code https://www.electronics-lab.com/project/arduino-bmp280-based-weather-station/
// Vcc code https://github.com/Yveaux/Arduino_Vcc/blob/master/examples/VccSimple/VccSimple.ino
// Modification by BP NOV 2021
// V12 = recode everything to get real altitude
// V14 = Get voltage and % of battery but only on USB ... I know.

#include <Adafruit_GFX.h>      //Libraries for the OLED and BMP280
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <Vcc.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire); //Declaring the display name (display)
Adafruit_BMP280 bmp;

float startAltitude = 0;
float maxAltitude;

const int wpm = 20; // Morse speed in WPM
const int dotL = 1200/wpm; // Calculated dot-length
const int dashL = 3*dotL; // Dash = 3 x dot
const int sPause = dotL; // Symbol pause = 1 dot
const int lPause = dashL; // Letter pause = 3 dots
const int wPause = 7*dotL; // Word pause = 7 dots
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
int DISPLAY_TIME = 100;  // In milliseconds
int buzzPin= 3; // I/O-pin from buzzer connects here

const float VccMin   = 4.8;           // Minimum expected Vcc level, in Volts.
const float VccMax   = 5.2;           // Maximum expected Vcc level, in Volts.
const float VccCorrection = 1.0/1.0;  // Measured Vcc by multimeter divided by reported Vcc
// this is used to give % of battery but doesn't work if not using a divider.

Vcc vcc(VccCorrection);

void setup() {  
  
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {
    Serial.println("BMP init failed!");
    while (1);
  }
  else Serial.println("BMP init success! Excellent");
              
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
  display.setTextSize(2); 
  display.print(" ROCKMETER   V1.14");     //Show the name, you can remove it or replace it
  display.setCursor(0,36);
  display.setTextSize(1);          
  display.println("   BP Technologies"); 
  display.setCursor(0,50);
  display.setTextSize(1);          
  display.println("     514-XXX-XXXX"); 
  display.display();
  
  digitalWrite(BLUE_PIN, HIGH);
  delay(6000);
  dot();      
  dot();      // confirm setup is ok

  {
  pinMode(buzzPin,OUTPUT); // Set buzzer-pin as output
  }
      startAltitude = bmp.readAltitude(1013.25);
      float maxAltitude = (bmp.readAltitude(1013.25) - startAltitude);
     
      digitalWrite(BLUE_PIN, LOW);
}

void dot(){
digitalWrite(buzzPin, HIGH); // Tone ON
delay(dotL); // Tone length
digitalWrite(buzzPin, LOW); // Tone OFF
delay(50); // Symbol pause
return;
}

void loop() {

    display.clearDisplay();
    float T = bmp.readTemperature();           //Read temperature in C
    float P = bmp.readPressure()/100;         //Read Pressure in Pa and conversion to hPa
    float A = (bmp.readAltitude(1013.25) - startAltitude);      //Calculating the Altitude, the "1019.66" is the pressure in (hPa) at sea level at day in your region
      if ( A > maxAltitude) {
        maxAltitude = A;                                        //If you don't know it just modify it until you get the altitude of your place
     }

float v = vcc.Read_Volts();
float p = vcc.Read_Perc(VccMin, VccMax);

     
    display.setCursor(0,0);                   //Oled display, just playing with text size and cursor to get the display you want
    display.setTextColor(WHITE);
    display.setTextSize(1); 
    display.print("MAX ALTITUDE + VOLT");
    
    display.setCursor(0,18);
    display.print(maxAltitude);
    display.setCursor(50,18);
    display.setTextSize(1);
    display.print("m");

    display.setTextSize(1);
    display.setCursor(0,35);
    display.print("CURRENT ALT + TEMP");
    display.setCursor(0,52);
    display.print(A,2);
    display.setCursor(50,52);
    display.print("m");

    display.setCursor(80,52);
    display.print(T,1);  // p = % of the battery  // T = Temperature on BMP280
    display.setCursor(110,52);
    display.print("C");

    display.setCursor(80,18);
    display.print(v);  //set voltage
    display.setCursor(110,18);
    display.print("V");
    
    display.display();
    delay(500);

    if (maxAltitude >= 5 ){
    dot();      // if higher than 5m = BEEP and RED LED
    digitalWrite(RED_PIN, HIGH);
    delay(50);
    digitalWrite(RED_PIN, LOW);
    delay(50);
    }  
    else if (maxAltitude < 5) { digitalWrite(buzzPin, LOW);  // if lower than 5M = GREEN LED - No BEEP
    digitalWrite(GREEN_PIN, HIGH);
    delay(50);
    digitalWrite(GREEN_PIN, LOW);
    delay(50);
  }  
  
}
