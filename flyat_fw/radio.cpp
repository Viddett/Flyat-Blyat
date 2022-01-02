#ifndef FBRADIO
#define FBRADIO

#include <SPI.h>
#include "RF24.h"


struct RadioMsg{
    float pitch;
    float roll;
    float speed;
    unsigned int mode;
    unsigned int seq;
};


class Radio{

    private:
        //TODO
        RF24 _radio = RF24(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin

        void setup() {            
            
            uint8_t address[][6] = {"1Node", "2Node"};
            bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit
            //bool role = false;  // true = TX role, false = RX role
            //uint8_t payload[3] = {0,0,0}; // 
            //radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes
            _radio.setPayloadSize(sizeof(RadioMsg)); // float datatype occupies 4 bytes
            _radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
            _radio.openReadingPipe(1, address[!radioNumber]);
            _radio.startListening();
    }
    public:

        Radio() {
            setup();
        }

        bool msg_avaliable(){
            // TODO
            uint8_t pipe = 0;
            return _radio.available(&pipe) && _radio.getPayloadSize() == sizeof(RadioMsg);
        }

        void read_msg(RadioMsg * msg){
            uint8_t* msgBytes;
            uint8_t bytes = _radio.getPayloadSize();
            _radio.read(&msgBytes, bytes);
            *msg = *((RadioMsg*)msgBytes);
            
            msg->mode=1;
            //TODO
        }

};




#endif
