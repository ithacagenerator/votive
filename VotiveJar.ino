#include <Adafruit_NeoPixel.h>

#define PIN 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// orange = 255, 100, 0
// violet = 255, 0, 255
// yellow = 255, 255, 0


//#define ORANGE_YELLOW
#define RED_VIOLET
//#define VIOLET_BLUE

#ifdef ORANGE_YELLOW
  #define GREEN_HIGH 120
  #define GREEN_LOW  90
  #define RED_HIGH 255
  #define RED_LOW  255
  #define BLUE_HIGH 0
  #define BLUE_LOW  0
  #define DELAY      20
  #define OTHER_DELAY 50
  uint16_t green = GREEN_LOW;
  int16_t green_step_size = 1;
  uint16_t red = RED_LOW;
  int16_t red_step_size = 0;
  uint16_t blue = BLUE_LOW;
  int16_t blue_step_size = 0;
#endif


#ifdef RED_VIOLET
  #define GREEN_HIGH 0
  #define GREEN_LOW  0
  #define RED_HIGH 255
  #define RED_LOW  255
  #define BLUE_HIGH 255
  #define BLUE_LOW  0
  #define DELAY      10
  #define OTHER_DELAY 1 
  uint16_t green = GREEN_LOW;
  int16_t green_step_size = 0;
  uint16_t red = RED_LOW;
  int16_t red_step_size = 0;
  uint16_t blue = BLUE_LOW;
  int16_t blue_step_size = 1;
#endif

#ifdef VIOLET_BLUE
  #define GREEN_HIGH 0
  #define GREEN_LOW  0
  #define RED_HIGH 255
  #define RED_LOW  0
  #define BLUE_HIGH 220
  #define BLUE_LOW  220
  #define DELAY      15
  #define OTHER_DELAY 1  
  uint16_t green = GREEN_LOW;
  int16_t green_step_size = 0;
  uint16_t red = RED_LOW;
  int16_t red_step_size = 1;
  uint16_t blue = BLUE_LOW;
  int16_t blue_step_size = 0;
#endif

void loop() {
  colorWipe(strip.Color(red, green, blue), OTHER_DELAY); // Red
  delay(DELAY);
  green += green_step_size;
  if((green >= GREEN_HIGH) || (green <= GREEN_LOW)){
    green_step_size *= -1;   
  }
  red += red_step_size;
  if((red >= RED_HIGH) || (red <= RED_LOW)){
    red_step_size *= -1;   
  }
  blue += blue_step_size;
  if((blue >= BLUE_HIGH) || (blue <= BLUE_LOW)){
    blue_step_size *= -1;   
  }  
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

