#include <Servo.h>

const byte escPin { 3 };
Servo servo;

void setup() {
  Serial.begin( 115200 );
  servo.attach( escPin );
  delay(5000);
  Serial.println("GO");    
  Serial.println("Enter powr 0 - 100(%)");  
}

void loop() {
  static int val = 0;
  if (Serial.available() > 0) {
    int tmp = Serial.parseInt();
    if (tmp != val && val >= 0 && val <= 100) {
      val = tmp;
      Serial.print( "val = " );
      Serial.println( val );
      servo.write( ((float)val * 0.9) + 90 );
      Serial.print( "recomp ");
      Serial.println(((float)val * 0.9) + 90);
    }
  }
}
// Ny ESC/motor har range (90 ~ 117)

