#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        13
#define NUMPIXELS 144
#define WIDTH 24
#define HEIGHT 6

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // pausetime between pixels

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

uint8_t maxR = 255;
uint8_t maxG = 255;
uint8_t maxB = 255;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(20);  // light intensity

  pixels.clear(); // Set all pixel colors to 'off'

  //setPixel(2,0, 100, 0 ,0);
  
  //pixels.show();   // Send the updated pixel colors to the hardware.
  
  //setCircularArrayOffset(left, -30);
  
  pixels.show();
}

void loop() {
  rightAnimation();
  leftAnimation();
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
}


void leftAnimation(){
  for(int i = 0; i < 50; i++){
    setCircularArrayOffset(left, -i);
    delay(50);
  }
}
