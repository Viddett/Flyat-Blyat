#ifndef FBRADIO
#define FBRADIO

#include <SPI.h>
#include "RF24.h"


typedef struct{
    float pitch;
    float roll;
    float speed;
    int mode;
    int seq;
} RadioMsg;


class Radio{

    private:
        //TODO
        RF24 _radio = RF24(11, 12); // using pin 7 for the CE pin, and pin 8 for the CSN pin

        //float rec_buffer[3];

        void setup() {

            SPI.begin();

            if(_radio.begin()){
                Serial.println("RADIO OK");
            } else {
                Serial.println("radio failed");
            }
            uint8_t address[][6] = {"1Node", "2Node"};
            bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit
            //bool role = false;  // true = TX role, false = RX role
            //uint8_t payload[3] = {0,0,0}; // 
            //radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes
            _radio.setPALevel(RF24_PA_MIN);
            _radio.setPayloadSize(sizeof(RadioMsg)); // float datatype occupies 4 bytes
            //_radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
            _radio.openReadingPipe(1, address[!radioNumber]);
            _radio.startListening();
			
    }
    public:

        Radio() {
            setup();
        }

        bool msg_available(){
            // TODO
            uint8_t pipe = 0;
            return _radio.available(&pipe);// && _radio.getPayloadSize() == sizeof(RadioMsg);
        }

        void read_msg(RadioMsg * msg){
            //uint8_t* msgBytes;
            //uint8_t bytes = _radio.getPayloadSize();

			//_radio.read(rec_buffer, sizeof(rec_buffer));
			
			//msg->roll = rec_buffer[0];
			//msg->pitch = rec_buffer[1];
			//msg->speed = rec_buffer[2];
			
			_radio.read(msg, sizeof(RadioMsg));
            
        }

};




#endif
