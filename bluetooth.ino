
// largely copied from: https://gist.github.com/sukinull/3cc498cf468a8453e8e6

// https://www.bananarobotics.com/shop/How-to-use-the-HG7881-%28L9110%29-Dual-Channel-Motor-Driver-Module
/*
  HG7881_Motor_Driver_Example - Arduino sketch
   
  This example shows how to drive a motor with using HG7881 (L9110) Dual
  Channel Motor Driver Module.  For simplicity, this example shows how to
  drive a single motor.  Both channels work the same way.
   
  This example is meant to illustrate how to operate the motor driver
  and is not intended to be elegant, efficient or useful.
   
  Connections:
   
    Arduino digital output D10 to motor driver input B-IA.
    Arduino digital output D11 to motor driver input B-IB.
    Motor driver VCC to operating voltage 5V.
    Motor driver GND to common ground.
    Motor driver MOTOR B screw terminals to a small motor.
     
  Related Banana Robotics items:
   
    BR010038 HG7881 (L9110) Dual Channel Motor Driver Module
    https://www.BananaRobotics.com/shop/HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 
  https://www.BananaRobotics.com
*/

// wired connections
#define HG7881_B_IA  9 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 10 // D11 --> Motor B Input B --> MOTOR B -
#define HG7881_A_IA 11
#define HG7881_A_IB 12

// functional connections
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction
#define MOTOR_A_PWM HG7881_A_IA
#define MOTOR_A_DIR HG7881_A_IB

#define LIGHT 13

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 50  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 200 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes

#define BACK LOW
#define FORW HIGH
#define ON HIGH
#define OFF LOW

void setup()
{
  Serial.begin( 9600 );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  pinMode( 13, OUTPUT );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
}
void setL (int dir, int pwm) {
  digitalWrite(MOTOR_B_DIR, dir);
  if (dir == BACK) {
    digitalWrite(MOTOR_B_PWM, pwm == ON ? ON : OFF);
  } else {
    digitalWrite(MOTOR_B_PWM, pwm == ON ? OFF : ON);
  }
}
void setR (int dir, int pwm) {
  digitalWrite(MOTOR_A_DIR, dir);
  if (dir == BACK) {
    digitalWrite(MOTOR_A_PWM, pwm == ON ? ON : OFF);
  } else {
    digitalWrite(MOTOR_A_PWM, pwm == ON ? OFF : ON);
  }
}

void stop () {
  setL(BACK, OFF);
  setR(BACK, OFF);
}

void loop()
{
  boolean isValidInput;
  do
  {
    byte c;
    // get the next character from the serial port
    while( !Serial.available() ); // LOOP...
    c = Serial.read();
    //Serial.println(c);
    Serial.write(c);
    isValidInput = true;
    // execute the menu option based on the character recieved
    switch( c )
    {
      case 's': // backward
        setL(BACK, ON);
        setR(BACK, ON);
        Serial.println("backward");
        break;
    	case 'w': // forward
    		//setL(HIGH, HIGH);
        setL(FORW, ON);
        setR(FORW, ON);
        Serial.println("forward");
    		break;
      case 'a':
        setR(FORW, ON);
        setL(BACK, ON);
        Serial.println("left");
        break;
      case 'd':
        setR(BACK, ON);
        setL(FORW, ON);
        Serial.println("right");
      break;
      case '0':
    	case 'o':
    		stop();
        Serial.println("stop");
    		break;
      case 'f':
        for (int i = 0; i<10; i++) {
          digitalWrite( 13, HIGH );
          delay(50);
          digitalWrite( 13, LOW  );
          delay(50);
        }
        break;
      case 't':
      // middle c: 261.625565
        double middle_c = 261.625565;
        double high_c = middle_c;
        double root2 = sqrt(2);
        double g = high_c * pow(root2, 7);
        tone(6, (int)high_c, 200);
        delay(200);
        tone(6, (int)g, 200);
        delay(200);
        Serial.println("speaker");
        break;
      // case '1': // 1) Fast forward
      //   Serial.println( "Fast forward..." );
      //   // always stop motors briefly before abrupt changes
      //   digitalWrite( MOTOR_B_DIR, LOW );
      //   digitalWrite( MOTOR_B_PWM, LOW );
      //   delay( DIR_DELAY );
      //   // set the motor speed and direction
      //   digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      //   analogWrite( MOTOR_B_PWM, 255-PWM_FAST ); // PWM speed = fast
      //   isValidInput = true;
      //   break;
         
      // case '2': // 2) Forward      
      //   Serial.println( "Forward..." );
      //   // always stop motors briefly before abrupt changes
      //   digitalWrite( MOTOR_B_DIR, LOW );
      //   digitalWrite( MOTOR_B_PWM, LOW );
      //   delay( DIR_DELAY );
      //   // set the motor speed and direction
      //   digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
      //   analogWrite( MOTOR_B_PWM, 255-PWM_SLOW ); // PWM speed = slow
      //   isValidInput = true;
      //   break;
         
      // case '3': // 3) Soft stop (preferred)
      //   Serial.println( "Soft stop (coast)..." );
      //   digitalWrite( MOTOR_B_DIR, LOW );
      //   digitalWrite( MOTOR_B_PWM, LOW );
      //   isValidInput = true;
      //   break;      
 
      // case '4': // 4) Reverse
      //   Serial.println( "Fast forward..." );
      //   // always stop motors briefly before abrupt changes
      //   digitalWrite( MOTOR_B_DIR, LOW );
      //   digitalWrite( MOTOR_B_PWM, LOW );
      //   delay( DIR_DELAY );
      //   // set the motor speed and direction
      //   digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse
      //   analogWrite( MOTOR_B_PWM, PWM_SLOW ); // PWM speed = slow
      //   isValidInput = true;
      //   break;      
         
      // case '5': // 5) Fast reverse
      //   Serial.println( "Fast forward..." );
      //   // always stop motors briefly before abrupt changes
      //   digitalWrite( MOTOR_B_DIR, LOW );
      //   digitalWrite( MOTOR_B_PWM, LOW );
      //   delay( DIR_DELAY );
      //   // set the motor speed and direction
      //   digitalWrite( MOTOR_B_DIR, LOW ); // direction = reverse      
      //   analogWrite( MOTOR_B_PWM, PWM_FAST ); // PWM speed = fast
      //   isValidInput = true;
      //   break;
         
      // case '6': // 6) Hard stop (use with caution)
      //   Serial.println( "Hard stop (brake)..." );
      //   digitalWrite( MOTOR_B_DIR, HIGH );
      //   digitalWrite( MOTOR_B_PWM, HIGH );
      //   isValidInput = true;
      //   break;      
         
      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
  } while( isValidInput == true );
 
  // repeat the main loop and redraw the menu...
}
/*EOF*/
