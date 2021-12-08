//Controller: Joystick -> Sensing left/right/break directions, sending bluetooth message to helmet

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define JS_X 15
#define JS_Y 2

void setup() {  
  Serial.begin(115200);
  SerialBT.begin("Controller");
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop() {
  int input_x = analogRead(JS_X);
  if (input_x <= 100){
    Serial.println("Break");
    SerialBT.write('B');
  }

  int input_y = analogRead(JS_Y);
  if (input_y <= 100){
    Serial.println("Left");
    SerialBT.write('L');
  }

  if (input_y >= 3800){
    Serial.println("Right");
    SerialBT.write('R');
  }
  delay(250);
}
