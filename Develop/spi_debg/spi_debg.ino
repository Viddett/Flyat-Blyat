#ifndef FBRADIO
#define FBRADIO

#include <SPI.h>
#include "RF24.h"
#define RF24_SPI_SPEED 100000


void setup(){


    }



void loop(){
	
	        //TODO
        RF24 _radio = RF24(11, 12,1000); // using pin 7 for the CE pin, and pin 8 for the CSN pin


			//SPI.setClockDivider(SPI_CLOCK_DIV128);		
            if(_radio.begin()){
                //Serial.println("RADIO OK");
            }
                else{
                    //Serial.println("radio failed");
            }
            uint8_t address[][6] = {"1Node", "2Node"};
            bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit
            //bool role = false;  // true = TX role, false = RX role
            //uint8_t payload[3] = {0,0,0}; // 
            //radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes
            _radio.setPALevel(RF24_PA_MIN);
            _radio.setPayloadSize(12); // float datatype occupies 4 bytes
            //_radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
            _radio.openReadingPipe(1, address[!radioNumber]);
            _radio.startListening();
			
	
}




#endif
