#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int ValorRecibido;
int servo1 = 0; // Número del canal para el primer servo
int servo2 = 1; // Número del canal para el segundo servo
int servo3 = 2;
int servo4 = 3;

const int buttonPins[3] = {2, 3, 4}; // Pines a los que están conectados los botones
int buttonStates[3];                // Array para almacenar el estado de cada botón

    int matrizB[10][4] = {
        {300, 300, 300, 300},
        {361, 368, 300, 300},
        {397, 400, 321, 300},
        {397, 455, 285, 300},
        {397, 455, 285, 375},
        {397, 353, 292, 375},
        {321, 345, 292, 375},
        {281, 360, 403, 375},
        {281, 360, 403, 300},
        {300, 300, 300, 300}
    };

        int matrizA[8][4] = {
        {300, 300, 300, 300},
        {394, 351, 347, 300},
        {402, 424, 227, 300},
        {402, 424, 227, 393},
        {402, 357, 227, 393},
        {314, 357, 221, 393},
        {314, 418, 221, 393},
        {300, 300, 300, 300}
    };

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando");

  // Configura cada pin de botón como entrada con resistencia de pull-up
  for (int i = 0; i < 3; i++) {
       pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pwm.begin();
  pwm.setPWMFreq(50);  // Frecuencia para los servos, típicamente 50-60 Hz


}

void loop() {

  for (int i = 0; i < 3; i++) {
    buttonStates[i] = digitalRead(buttonPins[i]);
  }
//posiscion de servos
//if (ValorRecibido == 1){
for(int i=0;i < 8; i++){
  pwm.setPWM(servo1, 0, matrizA[i][0]);
  pwm.setPWM(servo2, 0,  matrizA[i][1]);
  pwm.setPWM(servo3, 0, matrizA[i][2]);
  pwm.setPWM(servo4, 0,  matrizA[i][3]);
  delay(500);
}

 delay(5000);

 //if (ValorRecibido == 2){
for(int i=0;i < 10; i++){
  pwm.setPWM(servo1, 0, matrizB[i][0]);
  pwm.setPWM(servo2, 0,  matrizB[i][1]);
  pwm.setPWM(servo3, 0, matrizB[i][2]);
  pwm.setPWM(servo4, 0,  matrizB[i][3]);
  delay(500);
}


  delay(5000);
}