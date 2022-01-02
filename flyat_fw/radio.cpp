#ifndef FBRADIO
#define FBRADIO


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
    public:

        bool msg_avaliable(){
            // TODO
            return 0;
        }

        void read_msg(RadioMsg * msg){
            msg->mode=1;
            //TODO
        }

};




#endif
