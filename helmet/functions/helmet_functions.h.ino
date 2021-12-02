#define PIN 6
#define NUMPIXELS 144
#define WIDTH 24
#define HEIGHT 6
#define DELAYVAL 500 // pausetime between pixels

long right[];
long left[];
uint8_t maxR;
uint8_t maxG;
uint8_t maxB;
void setPixel(uint8_t x, uint8_t y, uint8_t r,  uint8_t g,  uint8_t b);
void setArray(long pic[]);
void setCircularArrayOffset(long pic[], int offset);
void rightAnimation();
void leftAnimation();
