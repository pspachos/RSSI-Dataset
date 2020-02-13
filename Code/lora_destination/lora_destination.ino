#include <SPI.h>
#include <RH_RF95.h>
#include <Streaming.h>             //http://arduiniana.org/libraries/streaming/

// Singleton instance of the radio driver
RH_RF95 rf95;
float frequency = 915.0;

void setup()
{
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  //Serial.println("Start LoRa Client");
  if (!rf95.init())
    Serial.println("init failed");
  // Setup ISM frequency
  rf95.setFrequency(frequency);
  // Setup Power,dBm
  rf95.setTxPower(10);
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
}

void loop() {
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  // Should be a reply message for us now
  if (rf95.recv(buf, &len))
  {
    Serial.println((char*)buf);

//    if (strcmp((char*)buf, "A") == 0)
//    {
//      Serial.print("Node A: ");
//      Serial.println(rf95.lastRssi(), DEC);
//    }
//    else if (strcmp((char*)buf, "B") == 0)
//    {
//      Serial.print("Node B: ");
//      Serial.println(rf95.lastRssi(), DEC);
//    }
//    else if (strcmp((char*)buf, "C") == 0)
//    {
//      Serial.print("Node C: ");
//      Serial.println(rf95.lastRssi(), DEC);
//    }
  }
}

