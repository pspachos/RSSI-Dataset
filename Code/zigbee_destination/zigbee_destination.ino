// We'll use SoftwareSerial to communicate with the XBee:

#include <XBee.h>                  //http://code.google.com/p/xbee-arduino/
#include <Streaming.h>             //http://arduiniana.org/libraries/streaming/
#include <SoftwareSerial.h>
SoftwareSerial serial1 (2, 3);

//XBee variables
XBee xbee = XBee();                //XBee object
ZBRxResponse rx = ZBRxResponse();  //XBee receive response

void setup() {
  Serial.begin(9600);
  serial1.begin(9600);
  xbee.setSerial(serial1);
}

void loop() {

  int i = 0;
  char str[30] = {NULL};

  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) {
    //Serial.println(xbee.getResponse().getApiId());
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {           //what kind of packet did we get?
      xbee.getResponse().getZBRxResponse(rx);        //get the received data
      //Serial << "Packet received, RSS = -" << _DEC(rss()) << " DB" << endl;
      //Serial << "Distance = " << distance(rssi) << " m" << endl;
      for (i = 0; i < rx.getDataLength(); i++) {
        str[i] = (char)rx.getData(i);
      }
      str[i + 1] = '\0';
      Serial << str << endl;
    }
  }
}


