#include <Wire.h>  // Wire library - used for I2C communication
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

int ADXL345 = 0x53; // The ADXL345 sensor I2C address
float sum_acc;
float accident_limit = 20;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
//Accelerometer 
  sensors_event_t event; 
  accel.getEvent(&event);
  sum_acc = sqrt(pow(event.acceleration.x, 2) + pow(event.acceleration.y, 2) + pow(event.acceleration.z, 2));
  delay(250);
  if (sum_acc > accident_limit) Serial.print("Accident detected!");
  else Serial.println(sum_acc);
}
