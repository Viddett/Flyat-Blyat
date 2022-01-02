
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define radio_Ts 1000
#define servo_Ts 500


SemaphoreHandle_t setpoints_mutex;

volatile float setpoint_pitch;

void setup() {

  Serial.begin(9600);
  Serial.println("LETSGO");

  setpoints_mutex = xSemaphoreCreateMutex();
  if (setpoints_mutex != NULL) {
    Serial.println("Mutex created");
  }

  /**
     Create tasks
  */
  xTaskCreate(setpoint_from_radio, // Task function
              "RadioTask", // Task name for humans
              128,  // stack depth
              1000, // Task parameter
              1, // Task priority (HIGH = VIP, Low = pleb)
              NULL);

  xTaskCreate(servo_ctrl, "ServoTask", 128, 1000, 2, NULL);

}

void loop() {}

void setpoint_from_radio(void *pvParameters){
  //xSemaphoreGive(mutex);
      while(true){
            Serial.println("radio boi");
            vTaskDelay(radio_Ts / portTICK_PERIOD_MS);
      }
      
}

void servo_ctrl(void *pvParameters){
      while(true){
            Serial.println("Servoboi");
            vTaskDelay(servo_Ts / portTICK_PERIOD_MS);
      }

}
