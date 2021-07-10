#include <Servo.h>

// Constants
const int PWMPIN_PITCH_IN = 19;
const int PWMPIN_PITCH_OUT = 5;
const int PWMPIN_YAW_IN = 20;
const int PWMPIN_YAW_OUT = 6;
const int PWMPIN_MOTOR_IN = 18;
const int PWMPIN_MOTOR_OUT = 11;

const int DEG_MAX = 135;
const int PWM_IN_MAX = 1650;
const int PWM_IN_MIN = 818;

// Servo variables
int pwmPitchIn;
int pwmYawIn;
int degPitchOut;
int degYawOut;
Servo servoPitch;
Servo servoYaw;
Servo servoEsc;

// Motor variables
int pwmMotorIn;
int pwmMotorOut;


void setup() {

  // Set pwm pins
  pinMode( PWMPIN_YAW_IN, INPUT );
  pinMode( PWMPIN_PITCH_IN, INPUT );
  pinMode( PWMPIN_MOTOR_IN, INPUT );
  //pinMode( PWMPIN_MOTOR_OUT, OUTPUT );
  
  // Attach servos
  servoYaw.attach( PWMPIN_YAW_OUT );
  servoPitch.attach( PWMPIN_PITCH_OUT );
  servoEsc.attach( PWMPIN_MOTOR_OUT );
  delay(5000);


  Serial.begin( 115200 );
}


int pwmIn2Deg( int pwmIn ) {
  return ( pwmIn - PWM_IN_MIN ) / (float)( PWM_IN_MAX - PWM_IN_MIN ) * DEG_MAX;
}


void loop() {
  // Read pwm input from receiver
  pwmYawIn = pulseIn( PWMPIN_YAW_IN, HIGH );
  pwmPitchIn = pulseIn( PWMPIN_PITCH_IN, HIGH );
  pwmMotorIn = pulseIn( PWMPIN_MOTOR_IN, HIGH );

  // Convert to deg output
  degPitchOut = pwmIn2Deg( pwmPitchIn );
  degYawOut = DEG_MAX - pwmIn2Deg( pwmYawIn );

  // Output to servos
  servoPitch.write( degPitchOut );
  servoYaw.write( degYawOut );
  
  // Output to motor
  pwmMotorOut = 255 - ( ( pwmMotorIn - PWM_IN_MIN ) / (float)( PWM_IN_MAX - PWM_IN_MIN ) * 255 );
  pwmMotorOut = pwmMotorOut < 40 ? 0 : pwmMotorOut;
  pwmMotorOut = pwmMotorOut > 255 ? 255 : pwmMotorOut;
  //analogWrite( PWMPIN_MOTOR_OUT, pwmMotorOut );
  int pwmMotorOutEsc = (pwmMotorOut * 28 / 255)  + 90;
  servoEsc.write( pwmMotorOutEsc );

  

  //Serial.println( degPitchOut );
  //Serial.print(" ");
  //Serial.println( (float)pwmMotorOut * (float)(30/255) );
  Serial.println( pwmMotorOutEsc );

}
