#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Direcciones I2C
#define FPGA_ADDRESS 0x03  // Dirección I2C de la FPGA (asegúrate de que sea correcta)
#define PCA9685_ADDRESS 0x40  // Dirección I2C de la PCA9685 (esta es la predeterminada)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDRESS);

byte in;
byte out;
int servo1 = 0; // Número del canal para el primer servo

void setup() {
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
      if (out == 0) {
     pwm.setPWM(0, 0, 150);  // Ajusta 123 a la posición deseada
     pwm.setPWM(1, 0, 300);
     pwm.setPWM(2, 0, 300);
     pwm.setPWM(3, 0, 300);
     
      delay(1000);
     pwm.setPWM(servo1, 0, 300);  // Ajusta 123 a la posición deseada
     pwm.setPWM(1, 0, 300);
     pwm.setPWM(2, 0, 300);
     pwm.setPWM(3, 0, 300);
     
      delay(1000);
     pwm.setPWM(servo1, 0, 500);  // Ajusta 123 a la posición deseada 
     pwm.setPWM(1, 0, 300);
     pwm.setPWM(2, 0, 300);
     pwm.setPWM(3, 0, 300);
        
      delay(1000);
      }

  } else {
    // No hay datos en el puerto serial
    Serial.println("Esperando dato del puerto serial...");
    delay(5000); // Esperar un poco antes de comprobar nuevamente
  }
        // Mueve el primer servo en el canal 0

}