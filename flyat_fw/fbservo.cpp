#ifndef FBSERO
#define FBSERO

/*
 Wrapper-class for each servo for abstraction.
 Also suppports input/output scaling.
*/
class FBServo{

    private: 
        int _servo_pin;
        float _output_offset;
        float _output_scale;

        void config_servo_pin(int pin){
            // TODO... Setup arduino Servo library
        }

        void write_servo(int val){
            // TODO Write servo value, int? 0 - 255?
        }

    public:
        // Default Constructor
        FBServo(int pin){
            _servo_pin = pin;
            _output_offset = 0;
            _output_scale = 1;

            config_servo_pin(pin);
        }

        FBServo(int pin, float output_offset, float output_scale){
            _servo_pin = pin;

            _output_offset = output_offset;
            _output_scale = output_scale;

            config_servo_pin(pin);
        }


        /*
        Sets servo angle/speed, x in [0,1]
        */
        void set(float x){
            float y = x *_output_scale + _output_scale;
            
            write_servo((int) y);
        }

};




#endif