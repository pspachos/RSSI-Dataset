#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"

#include<stdlib.h>

#include <Streaming.h>             //http://arduiniana.org/libraries/streaming/
#include <SoftwareSerial.h>
//#include "DHT.h"

int battPin = A0;
int battLevel = 0;
float battery = 0.0;

//#define DHTTYPE DHT22
//#define DHTPIN  A2 

//DHT dht(DHTPIN, DHTTYPE);

float h = 0.0;
float t2 = 0.0;

char* node = "1";
char* comma = ",";

int moisturePin = A0;
int moistureValue = 0;

// Define CC3000 chip pins
#define ADAFRUIT_CC3000_IRQ   2
#define ADAFRUIT_CC3000_VBAT  7
#define ADAFRUIT_CC3000_CS    10

// WiFi network (change with your settings !)
#define WLAN_SSID       "NameOfNetwork"
#define WLAN_PASS       "AardvarkBadgerHedgehog"
#define WLAN_SECURITY   WLAN_SEC_WPA2 // This can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);
uint32_t ip = cc3000.IP2U32(192,168,4,1);
int port = 2010;
//int BUFSIZ = 128;

const unsigned long
dhcpTimeout     = 60L * 1000L, // Max time to wait for address from DHCP
connectTimeout  = 15L * 1000L, // Max time to wait for server connection
responseTimeout = 15L * 1000L; // Max time to wait for data from server

uint32_t   t;
char c;
// PHP's server IP, port, and repository (change with your settings !)

Adafruit_CC3000_Client client;

void setup(void)
{
  Serial.begin(9600);

  Serial.print(F("Initializing..."));
  if(!cc3000.begin()) {
    Serial.println(F("failed. Check your wiring?"));
    return;
  }
  
  Serial.println(F("\nDeleting old connection profiles"));
  if (!cc3000.deleteProfiles()) {
    Serial.println(F("Failed!"));
    while(1);
  }

  Serial.print(F("OK.\r\nConnecting to network..."));
  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
  Serial.println(F("connected!"));

  Serial.print(F("Requesting address from DHCP server..."));
  for(t=millis(); !cc3000.checkDHCP() && ((millis() - t) < dhcpTimeout); delay(250)) {
    //Serial.println("....waiting");
  } 
  if(cc3000.checkDHCP()) {
    Serial.println(F("OK"));
  } 
  else {
    Serial.println(F("failed"));
    return;
  } 

  //Open Socket
  Serial.println("...Connecting to server");
  t = millis();
  do {
    client = cc3000.connectTCP(ip, port);
    delay(100);
  } 
  while((!client.connected()) && ((millis() - t) < connectTimeout));
  
  // Send request
  if (client.connected()) {
    Serial.println("Connected"); 
    Serial.println("...Sending request...");
    client.fastrprint("hello server");
  } 
  else {
    Serial.println(F("Connection failed"));    
    return;
  }
    
}

int i = 0;
void loop(void)
{
  char payload[100] = {NULL};
  char moistureStr[10];
  char batteryStr[10] = {NULL};
  char humidityStr[10] = {NULL};
  char temperatureStr[10] = {NULL};

  moistureValue = analogRead(moisturePin); //read moisture value
  int battLevel = 0;//analogRead(battPin);
  float battery = 0;//battLevel*(4.0/1023.0);
  itoa(moistureValue, moistureStr, 10);

  
  dtostrf(battery, 4, 2, batteryStr);

  strcat(payload, node); //0.1 is added to indicate that the node sending the message is Node 1
  strcat(payload, comma);
  strcat(payload, batteryStr);
  strcat(payload, comma);
  strcat(payload, moistureStr);
  strcat(payload, comma);
  strcat(payload, "0");
  
    Serial.println("Payload");
  Serial.println(payload);
  
  if (client.connected()){
    client.fastrprint(payload);
    Serial.println(payload);  
    }
  //delay(1000);
}
