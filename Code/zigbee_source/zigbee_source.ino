#include <XBee.h>                  //http://code.google.com/p/xbee-arduino/
#include <Streaming.h>             //http://arduiniana.org/libraries/streaming/
#include <SoftwareSerial.h>
#include "DHT.h"
SoftwareSerial serial1 (2, 3);

// create the XBee object
XBee xbee = XBee();

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

// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x40F4DF71);

void setup() {
  Serial.begin(9600);  
  serial1.begin(9600);
  xbee.setSerial(serial1);
}

void loop() {   
  char payload[100] = {NULL};
  char moistureStr[10];
  char batteryStr[10];
  char humidityStr[10];
  char temperatureStr[10];

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
  ZBTxRequest zbTx = ZBTxRequest(addr64, (uint8_t *)payload, strlen(payload));
  xbee.send(zbTx);

  delay(1000);
}

