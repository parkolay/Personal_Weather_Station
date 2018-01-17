/*
 
 This sketch sends Temp and Humidity data recieved by an ESP8266 to Weather Underground and a ThingSpeak
 channel.
 
 Requirements:
 
   * ESP8266 Wi-Fi Device
   * Arduino 1.6.9+ IDE
   * Additional Boards URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
   * Library: esp8266 by ESP8266 Community
 
 ThingSpeak Setup (ThingSpeak API (https://www.mathworks.com/help/thingspeak)):
 
   * Sign Up for New User Account - https://thingspeak.com/users/sign_up
   * Create a new Channel by selecting Channels, My Channels, and then New Channel
   * Enable a couple of fields
   * Note the Channel ID and Write API Key
    
 Setup Wi-Fi:
  * Enter SSID
  * Enter Password

  WeatherUnderground Setup:
  * Sign Up for New User Account -  https://www.wunderground.com/personal-weather-station/signup
  * Note the PWS ID and Password
   
 Created: Jan 6, 2018 by Dan Parkolay (with a lot of help from a lot of other people)
*/

#include <ESP8266WiFi.h>
#include <Wire.h> 
#include "SSD1306Wire.h"
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;

//initialize the DHT12 Temp/%RH sensor
const int DHT12 = 0x5C;
char DHT12Data[5];    //setup array for data read from DHT12
float DHT12_Humidity = 0;
float DHT12_Temp = 0;
float TempInF = 0;
float DS18B20TempinC = 0;
float DS18B20TempinF = 0;

// Display Settings
const int I2C_DISPLAY_ADDRESS = 0x3C;

const int SDA_PIN = 4;
const int SCL_PIN = 5;
SSD1306Wire     display(I2C_DISPLAY_ADDRESS, SDA_PIN, SCL_PIN);
LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display

// Wi-Fi Settings
const char* ssid = "PUT YOUR SSID HERE"; // your wireless network name (SSID)
const char* password = "PUT YOUR PASSWORD HERE"; // your Wi-Fi network password


//---------------------WU PSW ID-------------------
const char* host = "weatherstation.wunderground.com";
const char* WUID    = "PUT YOUR ID HERE";
const char* WUPASS   = "PUT YOUR PASSWORD HERE";

WiFiClient client;

// ThingSpeak Settings
const int channelID = PUT YOUR CHANNEL ID HERE; //this is for my channel ID, you need to change
String writeAPIKey = "PUT YOUR API KEY HERE"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 10 * 1000; // post data every 20 seconds (post then wait 10 seconds then post to next service then wait 10 seconds)

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Wire.begin(SDA_PIN,SCL_PIN);         //setup I2C pins on ESP8266

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
  }

  // initialize the lcd 
  lcd.init();                      
  lcd.backlight();

  DS18B20setup();
  lcd.print("DS18B20 has been setup");
  
  delay(5000);
}

void loop() 
{
  UpdateDS18B20();
  UpdateThingspeak();
  delay(postingInterval);
  UpdateWeatherUnderground();
  GetDHT12Data();

  // wait and then post again
  delay(postingInterval);
}
