#include <BluetoothSerial.h>
#include "esp_bt_device.h"
BluetoothSerial SerialBT;


bool found = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Helmet", true);
  Serial.println("Bluetooth Started! Ready to pair...");
  const uint8_t* point = esp_bt_dev_get_address();
  for (int i = 0; i< 6; i++){
    char str[3];
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);

    if (i<5) Serial.print(":");
  }
  Serial.println();

  SerialBT.connect("Controller");

}

void loop() {
  
  if (SerialBT.connected()>0 && !found)
  {
    Serial.println("Bluetooth connected");
    found = true;
  }

  if (SerialBT.connected()==0 && found)
  {
    Serial.println("Bluetooth disconnected");
    found = false;
  }
    
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
}
