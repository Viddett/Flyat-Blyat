
#include <Arduino_FreeRTOS.h> //9500 byte
#include <semphr.h> // 0 byte
#include <SPI.h> // 0 byte

#include "imu.cpp"  // imu + radio + fbservo circus 7000byte
#include "radio.cpp"
#include "fbservo.cpp"
//#include "control.cpp"
#include "sd.cpp" //8000 byte..

#include <Servo.h>  //500 byte

//Total limit is 28K on Micro
//Objects seem to add alot

#define RADIO_TS_MS_MS 5
#define CTRL_TS_MS 50

#define TASK_STACK_DPTH 255 //128

// Task priority (HIGH = VIP, Low = pleb)
#define RADIO_PRIO 4
#define CTRL_PRIO 5 
#define SERVO_PRIO 10

#define servo_pin 10
#define sd_pin 8

SemaphoreHandle_t msg_mutex;
RadioMsg current_msg;
int servo_val = 0; // 0 - 100

int nr_radio_msgs = 0;
Servo servo;
SDcard sdcard = SDcard(sd_pin);

void setup() {
      
      servo.attach(servo_pin);
      servo.write(0);

      //9600
      Serial.begin(115200);

      for(int i=0;i<5;i++){
            delay(1000);
      }
      servo.write(90);

      float GLENN[3];

      //servo.attach(servo_pin, 1000, 2000);


      Serial.println("LETSGO");
      Serial.println(sizeof(RadioMsg));

      msg_mutex = xSemaphoreCreateMutex();

     


      /**
       Create tasks
      */
      xTaskCreate(setpointFromRadio, "RadioTask", TASK_STACK_DPTH,nullptr, RADIO_PRIO, NULL);
      xTaskCreate(attitudeCtrl, "CtrlTask", TASK_STACK_DPTH, nullptr, CTRL_PRIO, NULL);
      //xTaskCreate(servo_task, "SERVO_TASK", TASK_STACK_DPTH, nullptr, SERVO_PRIO, NULL);

}

void loop() {}

void setpointFromRadio(void *pvParameters){

      Radio radio = Radio();
      while(true){
            
            if(radio.msg_available()){
                  xSemaphoreTake(msg_mutex,portMAX_DELAY);
                  nr_radio_msgs += 1;
                  radio.read_msg(&current_msg);
                  // sdcard.logWrite(String(current_msg.pitch));
                  sdcard.logRead();
                  xSemaphoreGive(msg_mutex);
                  //Serial.print("RADIO MSG: ");
            }
            
            //Serial.println("RADIO LOOP");
            //vTaskDelay(RADIO_TS_MS / portTICK_PERIOD_MS);
      }
}


void servo_task(void *pvParameters){
      pinMode(servo_pin, OUTPUT);

      int servo_state = 0;
      float on_time_millis = 1;
      while (1){
            digitalWrite(servo_pin, HIGH);
            if (servo_val < 0 ){
                  servo_val = 0;
            }else if (servo_val > 100){
                  servo_val = 100;
            }

            on_time_millis = servo_val/100 + 1;
            on_time_millis = 1;

            vTaskDelay(on_time_millis / portTICK_PERIOD_MS);
            digitalWrite(servo_pin, LOW);

            vTaskDelay((20 - on_time_millis) / portTICK_PERIOD_MS);
      }

}

void attitudeCtrl(void *pvParameters){
      
      IMU imu = IMU();
      ImuMeas meas;
      RadioMsg internalMsg;
      /*
      FBServo ailLeft = FBServo(1);
      FBServo ailRight = FBServo(2);
      FBServo prop = FBServo(3);

      Control ctrl = Control(&ailLeft, &ailRight, &prop);
      */
      while(true){
            
            //imu.read(&meas);
            if(xSemaphoreTake(msg_mutex,0) == pdTRUE){
                  internalMsg = current_msg;
                  xSemaphoreGive(msg_mutex);
            }
            servo.write((internalMsg.roll + 1)*90.0);
            
            //Serial.print(nr_radio_msgs);
            nr_radio_msgs = 0 ;
            Serial.print(" ");
            Serial.print(internalMsg.pitch);
            Serial.print(" ");
            Serial.print(internalMsg.roll);
            Serial.print(" ");
            Serial.print(internalMsg.speed);
			
			Serial.print(" ");
            Serial.print(internalMsg.mode);
			
			Serial.print(" ");
            Serial.println(internalMsg.seq);

            //ctrl.step(internalMsg,meas);
            
            //Serial.println("Ctrl LOOP");
            vTaskDelay(CTRL_TS_MS / portTICK_PERIOD_MS);
      }

}
