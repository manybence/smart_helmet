//Helmet: Light sensor, Headlight, Display direction, Bluetooth communication, Accelerometer
#include <Wire.h>  // Wire library - used for I2C communication
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include "TinyGPS++.h"
#include <SoftwareSerial.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//NeoPixel settings
#define PIN 13
#define NUMPIXELS 144
#define WIDTH 24
#define HEIGHT 6
#define DELAYVAL 500 // pausetime between pixels
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long right[] = { 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000,
               0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000,
               0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000,
               0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000,
               0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000,
               0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
};

long left[] = { 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000,
                       0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000,
                       0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000,
                       0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000,
                       0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000,
                       0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0x000000, 0x000000, 0x000000, 0x000000, 0xff0000, 0xff0000, 0xff0000, 0xff0000,
};

uint8_t maxR = 50;
uint8_t maxG = 50;
uint8_t maxB = 50;


//GPS settings
static const int RXPin = 25, TXPin = 33;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

//Accelerometer settings
float sum_acc;
float accident_limit = 30;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();


//Smart headlight settings
#define ledPin 16
#define lumen 4
const int ledChannel = 0;
const int freq = 5000;
const int resolution = 8;
int output = 0;

long t0;
char c = ' ';


void setup() {
  Serial.begin(115200);

  //Start bluetooth module in master mode
  SerialBT.begin("Helmet", true);
  SerialBT.connect("Controller");
  Serial.println("Controller connected");

  //Start smart light module
  ledcAttachPin(ledPin, ledChannel);
  ledcSetup(ledChannel, freq, resolution);
  
  //Start GPS module
  ss.begin(GPSBaud);
  Serial.println(F("Ublox Neo-7N GPS Module Test"));

  //Start accelerometer module
  if(!accel.begin())
      Serial.println("No ADXL345 sensor detected.");

  //Start NeoPixel module
  pixels.begin(); // Initialize NeoPixel strip object
  pixels.setBrightness(20);
  pixels.clear();   
  pixels.show();

  t0 = millis();
}

void loop() {

  //Try to reconnect if controller is disconnected
  if (SerialBT.connected()==0)
  {
    SerialBT.connect("Controller"); 
  }


  //Read bluetooth data from controller
  if (SerialBT.available() && c == ' ') {
    c = SerialBT.read();
    Serial.write(c);      
  }
  else  {
    c == ' ';
  }
  
  if (c == 'L') {
    leftAnimation();
    c = ' ';
    SerialBT.flush();
    positionLedOn();
  }
  if (c == 'R') {
    rightAnimation();    
    c = ' ';
    SerialBT.flush();
    positionLedOn();
  }
  if (c == 'B') {
    brakeAnimation();
    c = ' ';
    SerialBT.flush();
    positionLedOn();
  }
  

  //Smart headlight
  int lux = analogRead(lumen);
  if (lux>2900) output = 0;
  else output = (int)((3000-lux)*0.06);
  ledcWrite(ledChannel, output);

  
  //Accelerometer  
  sensors_event_t event;
  accel.getEvent(&event);
  sum_acc = sqrt(pow(event.acceleration.x, 2) + pow(event.acceleration.y, 2) + pow(event.acceleration.z, 2));
  if (sum_acc > accident_limit)
  {
    Serial.print("Accident detected!");
    Serial.print(sum_acc/10);
    Serial.println(" g strong shock");
    fallAnimation();
    positionLedOn();
  }


  //GPS
  if ((millis()-t0)%30000 <= 1000){
    if (ss.available() > 0 && gps.encode(ss.read()))
      displayInfo();   
  }  
}


void displayInfo()
{
  delay(5000);
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.print(" Satellites:");  
  Serial.print(gps.satellites.value());
  Serial.println();
} 


void setPixel(uint8_t x, uint8_t y, uint8_t r,  uint8_t g,  uint8_t b){
  if(x >= WIDTH || x < 0 || y >= HEIGHT || y < 0){
    return;
  }

  if(y%2){  // Impar - Odd
    pixels.setPixelColor(y * WIDTH + x, pixels.Color(r, g, b));
  }
  else{     // EVEN
    pixels.setPixelColor(y * WIDTH + (WIDTH - 1) - x, pixels.Color(r, g, b));
  }
}

void setArray(long pic[]){
  for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
      setPixel(x+5, y, map((pic[WIDTH*y + x] & 0xFF0000) >> 16, 0, 255, 0, maxR) ,
                      map((pic[WIDTH*y + x] & 0x00FF00) >> 8, 0, 255, 0, maxG),
                      map(pic[WIDTH*y + x] & 0x0000FF, 0, 255, 0, maxB));
    }
  }
  
  pixels.show();
}

void setCircularArrayOffset(long pic[], int offset){
  for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
      if(x + offset > WIDTH -1){
        setPixel((x + offset)%WIDTH, y, map((pic[WIDTH*y + x] & 0xFF0000) >> 16, 0, 255, 0, maxR) ,
                              map((pic[WIDTH*y + x] & 0x00FF00) >> 8, 0, 255, 0, maxG),
                              map(pic[WIDTH*y + x] & 0x0000FF, 0, 255, 0, maxB));
      } else if (x + offset < 0){
        setPixel(((x + offset)%WIDTH) + WIDTH, y, map((pic[WIDTH*y + x] & 0xFF0000) >> 16, 0, 255, 0, maxR) ,
                              map((pic[WIDTH*y + x] & 0x00FF00) >> 8, 0, 255, 0, maxG),
                              map(pic[WIDTH*y + x] & 0x0000FF, 0, 255, 0, maxB));
      } else{
        setPixel(x+offset, y, map((pic[WIDTH*y + x] & 0xFF0000) >> 16, 0, 255, 0, maxR) ,
                              map((pic[WIDTH*y + x] & 0x00FF00) >> 8, 0, 255, 0, maxG),
                              map(pic[WIDTH*y + x] & 0x0000FF, 0, 255, 0, maxB));
      }
    }
  }
  
  pixels.show();
}

void rightAnimation(){
  for(int i = 0; i < 50; i++){
    setCircularArrayOffset(right, + i);
    delay(50);
  }
  pixels.clear();   
  pixels.show();
}


void leftAnimation(){
  for(int i = 0; i < 50; i++){
    setCircularArrayOffset(left, -i);
    delay(50);
  }
  pixels.clear();   
  pixels.show();
}

void brakeAnimation(){
  for(int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(maxR*0.75, 0, 0));
  }

  pixels.show();
  delay(500);
  pixels.clear();
  pixels.show();
}

void fallAnimation(){
  for (int j = 0; j < 5; j++){
    for(int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(maxR*0.75, maxG*0.75, 0));
    }
  
    pixels.show();
    delay(500);
    pixels.clear();
    pixels.show();
    delay(500);
  }
}

void positionLedOn(){
  for(int i = 0; i < WIDTH; i++){
    pixels.setPixelColor(i, pixels.Color(maxR*0.5, 0, 0));
  }
  pixels.show();
}
