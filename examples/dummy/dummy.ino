//Dummy testing for the electronics
//Controller: Joystick -> Sensing left/right directions, sending bluetooth message to helmet
//Helmet: Light sensor, Headlight, Display direction, Bluetooth communication, Accelerometer

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define JS 15

void setup() {  
  Serial.begin(115200);
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop() {
  int input = analogRead(JS);
  if (input<=100){
    Serial.println("Lelf");
    SerialBT.write('L');
  }
  if (input>=4000){
    Serial.println("Right");
    SerialBT.write('R');
  }
  delay(250);

   if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available())
  {
    Serial.write(SerialBT.read());
  }
  delay(20);
  

}
