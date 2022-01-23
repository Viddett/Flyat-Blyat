
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <SPI.h>

#include "imu.cpp"
#include "radio.cpp"
#include "fbservo.cpp"
#include "control.cpp"

#define RADIO_TS 1000
#define CTRL_TS 500

#define TASK_STACK_DPTH 128
#define RADIO_PRIO 4
#define CTRL_PRIO 5 
// Task priority (HIGH = VIP, Low = pleb)

SemaphoreHandle_t msg_mutex;
RadioMsg current_msg;

void setup() {

      current_msg.seq = -1;

      Serial.begin(9600);
      Serial.println("LETSGO");

      msg_mutex = xSemaphoreCreateMutex();


      /**
       Create tasks
      */
      xTaskCreate(setpointFromRadio, "RadioTask", TASK_STACK_DPTH,nullptr, RADIO_PRIO, NULL);
      xTaskCreate(attitudeCtrl, "CtrlTask", TASK_STACK_DPTH, nullptr, CTRL_PRIO, NULL);

}

void loop() {}

void setpointFromRadio(void *pvParameters){

      Radio radio = Radio();
      while(true){
            
            if(radio.msg_avaliable()){
                  xSemaphoreTake(msg_mutex,portMAX_DELAY);
                  radio.read_msg(&current_msg);
                  xSemaphoreGive(msg_mutex);
            }

            vTaskDelay(RADIO_TS / portTICK_PERIOD_MS);
      }
      
}

void attitudeCtrl(void *pvParameters){
      IMU imu = IMU();
      ImuMeas meas;
      RadioMsg internalMsg;

      FBServo ailLeft = FBServo(1);
      FBServo ailRight = FBServo(2);
      FBServo prop = FBServo(3);

      Control ctrl = Control(&ailLeft, &ailRight, &prop);

      while(true){
            
            imu.read(&meas);
            if(xSemaphoreTake(msg_mutex,0) == pdTRUE){
                  internalMsg = current_msg;
                  xSemaphoreGive(msg_mutex);
            }
            
            ctrl.step(internalMsg,meas);

            vTaskDelay(CTRL_TS / portTICK_PERIOD_MS);
      }

}
