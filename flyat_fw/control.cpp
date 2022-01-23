#include "imu.cpp"
#include "radio.cpp"
#include "fbservo.cpp"
#include <math.h>
#define MIN_PID_OUTPUT = -0.5;
#define MAX_PID_OUTPUT = 0.5;
#define PID_TO_SERVO_OFFSET = 0.5;
#define DT = 20.0;
#define ROLL_FACTOR = 0.5;
#define PITCH_FACTOR = 0.5;


class Control{

    private:
        //TODO
        FBServo* _aileronLeft;
        FBServo* _aileronRight;
        FBServo* _prop;
        float roll;
        float pitch;
        
        /**
        * Calculates the roll & pitch from the accelerometer reading
        */
        void anglesFromAcc(float[] acc, float *roll, float *pitch){ //acc is [x,y,z]
            float norm = sqrtf(powf(acc[0],2) + powf(acc[1],2) + powf(acc[2],2));
            float[] normAcc = {acc[0]/norm, acc[1]/norm, acc[2]/norm};
            *roll = atan2f(normAcc[1],normAcc[2])*180.0/M_PI;

            double denom = sqrtf(powf(normAcc[1],2) + powf(normAcc[2],2));
            *pitch = atan2f(-normAcc[0],denom)*180.0/M_PI;
        }        

    public:

        Control(FBServo* leftAil, FBServo* rightAil, FBServo* prop){
            _aileronLeft = leftAil;
            _aileronRight = rightAil;
            _prop = prop;

            double Kp = 1;
            double Kd = 0;
            double Ki = 0;
            PID pitchPid = PID(DT, MAX_PID_OUTPUT, MIN_PID_OUTPUT, Kp, Kd, Ki);
            PID rollPid = PID(DT, MAX_PID_OUTPUT, MIN_PID_OUTPUT, Kp, Kd, Ki);
        }


        void step(RadioMsg radioMsg, ImuMeas imuMeas){
            // imuMeas.yaw_rate;   // new controller who dis
            // imuMeas.pitch_rate; // too many states for PID :o
            // imuMeas.roll_rate; 
        
            float wantedPitch = radioMsg.pitch;
            float wantedRoll = radioMsg.roll;
            float wantedSpeed = radioMsg.speed;
            float acc[] = {imuMeas.acc_x, imuMeas.acc_y, imuMeas.acc_z};

            // Calculate roll & pitch from accelerometer reading
            anglesFromAcc(acc, &roll, &pitch);

            float pitchDiff = (wantedPitch - pitch);
            float rollDiff = (wantedRoll - roll);

            //                   L   R 
            //full roll left --> 1 / 0   
            //full roll right --> 0 / 1
            //full pitch up --> 0 / 0
            //full pitch down --> 1 / 1
          
            double pitchVal = pitchPid.calculate(wantedPitch, pitch) + PID_TO_SERVO_OFFSET;
            double rollVal = rollPid.calculate(wantedRoll, roll);
            _aileronLeft.set(PITCH_FACTOR * pitchVal + ROLL_FACTOR * abs(rollVal - PID_TO_SERVO_OFFSET));  
            _aileronRight.set(PITCH_FACTOR * pitchVall + ROLL_FACTOR * rollVal + PID_TO_SERVO_OFFSET); 
            // _prop.set() 
        }     
};
