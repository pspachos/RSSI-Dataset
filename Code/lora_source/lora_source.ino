/*
  LoRa Simple Client for Arduino :
  Support Devices: LoRa Shield + Arduino 
  
  Example sketch showing how to create a simple messageing client, 
  with the RH_RF95 class. RH_RF95 class does not provide for addressing or
  reliability, so you should only use RH_RF95 if you do not need the higher
  level messaging abilities.

  It is designed to work with the other example LoRa Simple Server

  modified 16 11 2016
  by Edwin Chen <support@dragino.com>
  Dragino Technology Co., Limited
*/
#include <Streaming.h>             //http://arduiniana.org/libraries/streaming/
#include <SoftwareSerial.h>
#include "DHT.h"
#include <SPI.h>
#include <RH_RF95.h>

int battPin = A0;
int battLevel = 0;
float battery = 0.0;

#define DHTTYPE DHT22
#define DHTPIN  A2 

DHT dht(DHTPIN, DHTTYPE);

float h = 0.0;
float t = 0.0;

char* node = "1";
char* comma = ",";

int moisturePin = A5;
int moistureValue = 0;

// Singleton instance of the radio driver
RH_RF95 rf95;
float frequency = 915.0;

void setup() 
{
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  Serial.println("Starting LoRa Client Node A");
  if (!rf95.init())
    Serial.println("init failed");
  // Setup ISM frequency
  rf95.setFrequency(frequency);
  // Setup Power,dBm
  rf95.setTxPower(10);
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
}

void loop()
{
  char payload[100] = {NULL};
  char moistureStr[10];
  char batteryStr[10] = {NULL};
  char humidityStr[10] = {NULL};
  char temperatureStr[10] = {NULL};

  moistureValue = analogRead(moisturePin); //read moisture value
  int battLevel = analogRead(battPin);
  float battery = battLevel*(4.0/1023.0);
  itoa(moistureValue, moistureStr, 10);

//  h = dht.readHumidity();
//  dtostrf(h, 4, 2, humidityStr);
//  t = dht.readTemperature();
//  dtostrf(t, 4, 2, temperatureStr);
  dtostrf(battery, 4, 2, batteryStr);

  strcat(payload, node); //0.1 is added to indicate that the node sending the message is Node 1
  strcat(payload, comma);
  strcat(payload, batteryStr);
  strcat(payload, comma);
  strcat(payload, moistureStr);
  strcat(payload, comma);
  strcat(payload, "0");

  Serial.println(payload);

  
  
  // Send a message to LoRa Server
  rf95.send(payload, sizeof(payload));
  
  rf95.waitPacketSent();
  delay(1000);
}


