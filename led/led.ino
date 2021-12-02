
#define ledPin 16
#define lumen 4
const int ledChannel = 0;
const int freq = 5000;
const int resolution = 8;
int output = 0;


void setup() {
  // put your setup code here, to run once:
  ledcAttachPin(ledPin, ledChannel);
  ledcSetup(ledChannel, freq, resolution);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:


//Smart headlight
  int lux = analogRead(lumen);
  if (lux>2900) output = 0;
  else output = (int)((3000-lux)*0.06);
  ledcWrite(ledChannel, output);
  delay(100);
  Serial.print(lux);
}
