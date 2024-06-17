#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> 


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
//uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates
  pwm.setPWM(0, 0, angleToPulse(10) ); //Base
  pwm.setPWM(1, 0, angleToPulse(65) ); //Waist
  pwm.setPWM(2, 0, angleToPulse(120) ); //Shoulder
  pwm.setPWM(3, 0, angleToPulse(100) ); //Elbow
  pwm.setPWM(4, 0, angleToPulse(100) ); //Wrist
  pwm.setPWM(5, 0, angleToPulse(30) ); //Effector
}

void loop(){
  delay(2000);

//PICK Movement
//Servo Base
for( int angle =10; angle<=150; angle +=2 ){
      delay(20);
        pwm.setPWM(0, 0, angleToPulse(angle) );      
    }
delay(1000);

//Servo Waist 
for( int angle =65; angle<=90; angle +=1){
      delay(70);
        pwm.setPWM(1, 0, angleToPulse(angle) );  
    }
delay(1000);

//Servo Shoulder
for( int angle =120; angle>=90; angle -=2){
      delay(50);
        pwm.setPWM(2, 0, angleToPulse(angle) );   
    }
delay(1000);

//Servo Elbow
for( int angle =100; angle<=150; angle +=1){
      delay(20);
        pwm.setPWM(3, 0, angleToPulse(angle) ); 
    } 
delay(1000);

//Servo Wrist
for( int angle =100; angle<=150; angle +=2){
      delay(40);
        pwm.setPWM(4, 0, angleToPulse(angle) ); 
    }
delay(1000);

//Servo Effector
for( int angle =30; angle<=80; angle +=2){
      delay(40);
        pwm.setPWM(5, 0, angleToPulse(angle) );  
    }
delay(1000);

//PLACE Movement
//Shoulder    
for( int angle =90; angle<=120; angle +=2){
      delay(50);
        pwm.setPWM(2, 0, angleToPulse(angle) );   
    }
delay(1000);

//Elbow
for( int angle =150; angle>=100; angle -=1){
      delay(20);
        pwm.setPWM(3, 0, angleToPulse(angle) );  
    }
delay(1000);

//Waist
for( int angle =90; angle>=65; angle -=1){
      delay(70);
        pwm.setPWM(1, 0, angleToPulse(angle) ); 
    }
delay(1000);

//Wrist
for( int angle =150; angle>=100; angle -=1){
      delay(20);
        pwm.setPWM(4, 0, angleToPulse(angle) ); 
    }
delay(1000);

//Base
 for( int angle =150; angle>=10; angle -=2){
      delay(20);
        pwm.setPWM(0, 0, angleToPulse(angle) );  
    }
delay(1000);

//Effector
for( int angle =80; angle>=30; angle -=2){
      delay(40);
        pwm.setPWM(5, 0, angleToPulse(angle) );  
    }
delay(1000);
}

int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}
