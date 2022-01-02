#include "imu.cpp"
#include "radio.cpp"
#include "fbservo.cpp"

class Control{

    private:
        //TODO
        FBServo* _aileronLeft;
        FBServo* _aileronRight;
        FBServo* _prop;

    public:

        Control(FBServo* leftAil, FBServo* rightAil, FBServo* prop){
            _aileronLeft = leftAil;
            _aileronRight = rightAil;
            _prop = prop;
        }


        void step(RadioMsg radioMsg, ImuMeas imuMeas){
            // TODO send ctrl to servos
        }
};
