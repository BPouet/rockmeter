// Original code https://www.electronics-lab.com/project/arduino-bmp280-based-weather-station/
// Modification by BP NOV 2021
// 

#include <Adafruit_GFX.h>      //Libraries for the OLED and BMP280
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>

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
int DISPLAY_TIME = 100;  // In milliseconds
int buzzPin= 3; // I/O-pin from buzzer connects here


void setup() {  
  
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
  display.print(" ROCKMETER   V1.12");     //Show the name, you can remove it or replace it
  display.setCursor(0,36);
  display.setTextSize(1);          
  display.println("   BP Technologies"); 
  display.setCursor(0,50);
  display.setTextSize(1);          
  display.println("     514-XXX-XXXX"); 
  display.display();
  delay(6000);

  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  {
  pinMode(buzzPin,OUTPUT); // Set buzzer-pin as output
  }
      startAltitude = bmp.readAltitude(1013.25);
      float maxAltitude = (bmp.readAltitude(1013.25) - startAltitude);
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
     
    display.setCursor(0,0);                   //Oled display, just playing with text size and cursor to get the display you want
    display.setTextColor(WHITE);
    display.setTextSize(1); 
    display.print("MAX ALTITUDE");
    
    display.setCursor(0,18);
    display.print(maxAltitude);
    display.setCursor(50,17);
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
    display.print(T,1);
    display.setCursor(105,52);
    display.print("C");
    
    display.display();
    delay(1000);

    if (maxAltitude >= 5 ){
    dot();      // si plus de 2M de haut = beep
    digitalWrite(RED_PIN, HIGH);
    delay(50);
    digitalWrite(RED_PIN, LOW);
    delay(50);
    }  
    else if (maxAltitude < 5) { digitalWrite(buzzPin, LOW);  // si max = zero = pas de beep.
    digitalWrite(GREEN_PIN, HIGH);
    delay(50);
    digitalWrite(GREEN_PIN, LOW);
    delay(50);
  }  
}
