#include <Wire.h>  // Wire library - used for I2C communication
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>

float sum_acc;
float accident_limit = 25;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  
   if(!accel.begin())
   {
      Serial.println("No ADXL345 sensor detected.");
      while(1);
   }
}

void loop() {
//Accelerometer 
  sensors_event_t event; 
  accel.getEvent(&event);
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
  Serial.println("m/s^2 ");
  sum_acc = sqrt(pow(event.acceleration.x, 2) + pow(event.acceleration.y, 2) + pow(event.acceleration.z, 2));
  if (sum_acc > accident_limit){
    Serial.print("Accident detected!");
    Serial.print(sum_acc);  
    Serial.println("m/s^2 ");
  }
  else {
    Serial.print(sum_acc);  
    Serial.println("m/s^2 ");
  }
  delay(500);
  
}
