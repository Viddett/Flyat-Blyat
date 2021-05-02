// PWM test code

const int PWM_PIN = 4;
int pwmValue;
int filtVal;
const float A = 0.3;

void setup() {
  pinMode(PWM_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {

// Read pwm input
pwmValue = pulseIn(PWM_PIN, HIGH);


filtVal = pwmValue * A + (1-A)*filtVal;

Serial.print(pwmValue);
Serial.print("    ");
Serial.println(filtVal);


/* // Output 100%/50% Duty cycle 2s, pin-specific frequency
  analogWrite(PWM_PIN, 255);
  delay(1000);
  analogWrite(PWM_PIN, 255/2);
  delay(1000);
*/

}


// #### Max/Min values
// Left stick ( up / down ) ( 818/1650 )
// Left stick ( left / right ) ( / )
// Right stick ( up / down ) ( / ) // Pitch
// Right stick ( left / right ) ( / ) // Yaw
