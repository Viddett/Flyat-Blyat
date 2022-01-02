#ifndef FBIMU
#define FBIMU


struct ImuMeas{
    float pitch_rate;
    float roll_rate;
    float yaw_rate;
    float acc_x;
    float acc_y;
    float acc_z;
};

class IMU{

    private:
        //TODO
    public:
        
        void read(ImuMeas * meas){
            //TODO
        }
};

#endif