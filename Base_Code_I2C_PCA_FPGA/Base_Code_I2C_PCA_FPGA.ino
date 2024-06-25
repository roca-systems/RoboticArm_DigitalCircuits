#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Direcciones I2C
#define FPGA_ADDRESS 0x03  // Dirección I2C de la FPGA (asegúrate de que sea correcta)
#define PCA9685_ADDRESS 0x40  // Dirección I2C de la PCA9685 (esta es la predeterminada)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDRESS);

const int ledPin = 10;

int matrizB[12][4] = {
        {300, 300, 300, 390},
        {422, 342, 366, 390},
        {422, 397, 288, 390},
        {423, 410, 274, 390},
        {423, 410, 274, 498},
        {423, 410, 225, 498},
        {423, 339, 305, 498},
        {332, 339, 305, 498},
        {332, 339, 305, 498},
        {332, 339, 305, 390},
        {340, 338, 245, 390},
        {300, 300, 300, 390}
    };

        int matrizA[9][4] = {
        {300, 300, 300, 390},
        {398, 327, 373, 390},
        {394, 441, 300, 390},
        {394, 441, 300, 498},
        {399, 360, 300, 498},
        {281, 360, 300, 498},
        {281, 345, 400, 498},
        {281, 345, 400, 390},
        {300, 300, 300, 390}
    };


byte in;
byte out;
int servo1 = 0; // Número del canal para el primer servo

void setup() {
    pinMode(ledPin, OUTPUT);
  // Inicializa el bus I2C
  Wire.begin();

  // Inicializa la comunicación serial para el monitor serial
  Serial.begin(115200);

  // Inicializa la PCA9685
  pwm.begin();
  pwm.setPWMFreq(50);  // Frecuencia para los servos, típicamente 50-60 Hz

  Serial.println("Iniciando...");
}

void loop() {
  if (Serial.available()) {
    in = Serial.read() - '0';
    Serial.print("Dato recibido del puerto serial: ");
    Serial.println(in);

    // Enviar dato a la FPGA
    Serial.print("Enviando a la FPGA: ");
    Serial.println(in);
    Wire.beginTransmission(FPGA_ADDRESS);
    Wire.write(in);
    Wire.endTransmission();

    delay(100); // Aumentar el tiempo de espera a 100ms

    // Solicitar respuesta de la FPGA
    Wire.requestFrom(FPGA_ADDRESS, 1);
    if (Wire.available()) {
      out = Wire.read();
    }

    Serial.print("Recibiendo de la FPGA: ");
    Serial.println(out, DEC);

    // Controla el servo motor basado en el valor recibido
//posiscion de servos
if (out == 1){
  
for(int i=0;i < 9; i++){
  pwm.setPWM(0, 0, matrizA[i][0]);
  pwm.setPWM(1, 0, matrizA[i][1]);
  pwm.setPWM(2, 0, matrizA[i][2]);
  pwm.setPWM(3, 0, matrizA[i][3]);
  delay(1000);
}
}

 delay(5000);

 if (out == 2){
for(int i=0;i <12; i++){
  if(i==9){
    analogWrite(ledPin, 100);
    delay(300);
    analogWrite(ledPin, 0);
    delay(100);
    analogWrite(ledPin, 100);
    delay(300);
    analogWrite(ledPin, 0);
    delay(100);
      }
  pwm.setPWM(0, 0, matrizB[i][0]);
  pwm.setPWM(1, 0, matrizB[i][1]);
  pwm.setPWM(2, 0, matrizB[i][2]);
  pwm.setPWM(3, 0, matrizB[i][3]);
  delay(1000);
}
 }

  } else {
    // No hay datos en el puerto serial
    Serial.println("Esperando dato del puerto serial...");
    delay(5000); // Esperar un poco antes de comprobar nuevamente
  }

}