/*
 * Original source: https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
 * 
 * This is the Arduino code PAC6985 16 channel servo controller
 * watch the video for details (V1) and demo http://youtu.be/y8X9X10Tn1k
 *  This code is #1 for V2 Video Watch the video :https://youtu.be/bal2STaoQ1M
 *  I have got 3 codes as follow:
   #1-Arduino Code to run one by one all servos from 0 to 180°   
   #2-Arduino Code to control specific servos with specific angle
   #3-Arduino Code to run 2 or all servos at together
   
 * Written/updated by Ahmad Shamshiri for Robojax Video channel www.Robojax.com
 * Date: Dec 16, 2017, in Ajax, Ontario, Canada

 * Watch video for this code: 
 * 
 * Related Videos
V5 video of PCA9685 32 Servo with ESP32 with WiFi https://youtu.be/bvqfv-FrrLM
V4 video of PCA9685 32 Servo with ESP32 (no WiFi): https://youtu.be/JFdXB8Za5Os
V3 video of PCA9685 how to control 32 Servo motors https://youtu.be/6P21wG7N6t4
V2 Video of PCA9685 3 different ways to control Servo motors: https://youtu.be/bal2STaoQ1M
V1 Video introduction to PCA9685 to control 16 Servo  https://youtu.be/y8X9X10Tn1k

 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * this code has been downloaded from http://robojax.com/learn/arduino/
 
 * Get this code and other Arduino codes from Robojax.com
Learn Arduino step by step in structured course with all material, wiring diagram and library
all in once place. Purchase My course on Udemy.com http://robojax.com/L/?id=62

****************************
Get early access to my videos via Patreon and have  your name mentioned at end of very 
videos I publish on YouTube here: http://robojax.com/L/?id=63 (watch until end of this video to list of my Patrons)
****************************

or make donation using PayPal http://robojax.com/L/?id=64

 *  * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see .
 */

/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 16 servos, one after the other

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> 

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
// Watch video V1 to understand the two lines below: http://youtu.be/y8X9X10Tn1k
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!"); 

  pwm.begin();
  
  pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

  
}

// the code inside loop() has been updated by Robojax
void loop() {

//watch video for details: https://youtu.be/bal2STaoQ1M
for(int i=0; i<5; i++)
  {
    for( int angle =0; angle<90; angle +=5){
      delay(50);
        pwm.setPWM(i, 0, angleToPulse(angle) );
        // see YouTube video for details (robojax)
       
    }
 
  }
 
  // robojax PCA9865 16 channel Servo control
  delay(1000);// wait for 1 second
 
}

/*
/* angleToPulse(int ang)
 * @brief gets angle in degree and returns the pulse width
 * @param "ang" is integer represending angle from 0 to 180
 * @return returns integer pulse width
 * Usage to use 65 degree: angleToPulse(65);
 * Written by Ahmad Shamshiri on Sep 17, 2019. 
 * in Ajax, Ontario, Canada
 * www.Robojax.com 
 */
 
int angleToPulse(int ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);// map angle of 0 to 180 to Servo min and Servo max 
   Serial.print("Angle: ");Serial.print(ang);
   Serial.print(" pulse: ");Serial.println(pulse);
   return pulse;
}
