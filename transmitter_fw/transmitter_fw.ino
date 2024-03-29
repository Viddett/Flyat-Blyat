#include <SPI.h>
#include "printf.h"
#include "RF24.h"

// Struct to transmit
typedef struct {
  float pitch;
  float roll;
  float speed;
  int mode;
  int seq;
} RadioMsg;

// Radio parameters
RF24 radio(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin
uint8_t address[][6] = {"1Node", "2Node"}; // Let these addresses be used for the pair
bool radioNumber = 0; // 0 uses address[0] to transmit, 1 uses address[1] to transmit
bool role = true;  // true = TX role, false = RX role
//float transmitData[ 3 ] {0,0,0};
RadioMsg transmitData;
int transmitSize = sizeof(RadioMsg);

unsigned long lastTransmitTime { 0 };

void setup() {
  Serial.begin(9600);

  // Radio setup
  if (!radio.begin()) { // initialize the transceiver on the SPI bus
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}
  }
  radio.setPALevel(RF24_PA_MAX);  // RF24_PA_MAX is default.
  radio.setPayloadSize(transmitSize); // float datatype occupies 4 bytes
  radio.openWritingPipe(address[radioNumber]); // set the TX address of the RX node into the TX pipe (always uses pipe 0)
  //radio.openReadingPipe(1, address[!radioNumber]); // set the RX address of the TX node into a RX pipe using pipe 1
  if (role) {
    radio.stopListening();  // put radio in TX mode
  } else {
    radio.startListening(); // put radio in RX mode
  }
} // setup

void loop() {
  if (millis() - lastTransmitTime >= 1000) {
    int nBytes = Serial.available();
    for (int i = 0; i < nBytes; i++) {
      Serial.read();
    }
    lastTransmitTime = millis();
  }
  else if (Serial.available() >= transmitSize) {
    byte receiveData[transmitSize];
    
    char* req;
    req = (char*)&transmitData;
    Serial.readBytes(req, transmitSize);
   
    radio.write(&transmitData , transmitSize);
    lastTransmitTime = millis();
  }
} // loop
