/*
 * Adaptation by Jan Pieter Duhen of
 * 
 * Christmas tree by designer2k2.at
 * Stephan Martin 2016
 * http://www.designer2k2.at
 * https://github.com/designer2k2/xmas-tree
 * 
 * This code is made to run on a Digispark
 * Feeding Neopixel strip on a tree ornament
 * 
 * Brightness is reduced as there is only USB power supply.
 * 
 *
 * Needs Adafruit NeoPixel Lib to work: https://github.com/adafruit/Adafruit_NeoPixel
 * Use the build in Library manager in the Arduino IDE: "Adafruit NeoPixel"
 * 
 */


#include <Adafruit_NeoPixel.h>    //needed for the WS2812
#include <avr/pgmspace.h>		      //needed for PROGMEM

#define PIN 1					            //Pin 1 is DATA In on the first pixel
#define BRIGHTNESS 70 			      // brightness reduced (about 180mA max, 100mA average)


//Lookups for the X-M-A-S Letters viewed from above:
 const unsigned int charX[] PROGMEM = 
 { 
  1,5,9,13,17,21,25,29,33,37,41,45,49,53
 };
 const unsigned int charM[] PROGMEM = 
 { 
  54,50,46,42,38,34,30,26,22,18,14,10,6,2
 };
  const unsigned int charA[] PROGMEM = 
 { 
  3,7,11,15,19,23,27,31,35,39,43,47,51,55
 };
  const unsigned int charS[] PROGMEM = 
 { 
  56,52,48,44,40,36,32,28,24,20,16,12,8,4
 };

 //Lookup for the Candle light
 const unsigned int candles[] PROGMEM = 
 { 
  2,55,3,54,4,53,6,51,7,50,10,47,11,46,13,44,14,43,17,40,18,39,20,37,21,36
 };


// Parameter 1 = number of pixels in strip
// Parameter 2 = ATTiny pin number (P0-P4 are valid, P5 is often configured as RESET)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(56, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  pinMode(PIN, OUTPUT);
  strip.begin();
  strip.setBrightness(BRIGHTNESS); // set brightness
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop() {
  
  //XMAS Letters:
  xmas();
  delay(2000);
  
  //Tree light:
  tree();
  delay(2000);

  //Color crazy:
  colorcrazy();
  delay(2000);

  warpdrive();
  comet_ccw();
  comet_cw();
  

  /*
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127,   0,   0), 50); // Red
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
*/
}

//Sub-----------------------------------------------------------------------

//Comet CouterClockWise
void comet_ccw(){
  for(uint16_t i=strip.numPixels(); i>0; i--) {
     strip.setPixelColor(i,strip.Color(0, 0, BRIGHTNESS));
     fadethemall(10);
     fadethemall(10);
  }
}

//Comet ClockWise
void comet_cw(){
  for(uint16_t i=0; i<strip.numPixels(); i++) {
     strip.setPixelColor(i,strip.Color(0, 0, BRIGHTNESS));
     fadethemall(10);
     fadethemall(10);
  }
}

//From top down white pulses
void warpdrive(){

  //Top Led
  strip.setPixelColor(0,strip.Color(255, 255, 255));
  strip.show();
  //fade a bit
  for (int i = 0; i < 20; i++)
  {
    fadethemall(20);
  } 

  //tree-top
  for (int i = 1; i < 9; i++)
  {
    strip.setPixelColor(i,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));    
    strip.setPixelColor(56-i,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  }
  strip.show();
  //fade a bit
  for (int i = 0; i < 20; i++)
  {
    fadethemall(20);
  } 

  //tree-mid
  for (int i = 9; i < 16; i++)
  {
    strip.setPixelColor(i,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));    
    strip.setPixelColor(56-i,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  }
  strip.show();
  //fade a bit
  for (int i = 0; i < 20; i++)
  {
    fadethemall(20);
  } 

  //tree-low
  for (int i = 16; i < 21; i++)
  {
    strip.setPixelColor(i,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));    
    strip.setPixelColor(56-i,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  }
  strip.show();
  //fade a bit
  for (int i = 0; i < 20; i++)
  {
    fadethemall(20);
  }

  //tree-bottom
  for (int i = 22; i < 28; i++)
  {
    strip.setPixelColor(i,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));    
    strip.setPixelColor(56-i,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
  }
  strip.show();
  //fade a bit
  for (int i = 0; i < 20; i++)
  {
    fadethemall(20);
  }
}

//This reduces the brightness of all leds
void fadethemall(uint8_t wait){
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      uint32_t color = strip.getPixelColor(i);
      int r;
      int g;
      int b;
      r = (uint8_t)(color >> 16);
      g = (uint8_t)(color >>  8);
      b = (uint8_t)color;

      if(r>0)
      {
        r = r - 1;
      }
      else
      {
        r = 0;
      }

      if(g>0)
      {
        g = g - 1;
      }
      else
      {
        g = 0;
      }

      if(b>0)
      {
        b = b - 1;
      }
      else
      {
        b = 0;
      }
      
      strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
  delay(wait);
}

//This drives the WS2812 in a crazy pattern, fun!
void colorcrazy(){ 
  colorWipe(strip.Color(BRIGHTNESS, 0, 0), 25); // Red
  colorWipe(strip.Color(0, BRIGHTNESS, 0), 25); // Green
  colorWipe(strip.Color(0, 0, BRIGHTNESS), 25); // Blue  
  theaterChaseRainbow(5);
}

//This lights up the tree in green, then add the white "candles"
void tree(){

  colorWipe(strip.Color(0, BRIGHTNESS, 0), 50); // Green

  //light "candles"
  //Show the S:
  for (int i = 0; i < 24; i++)
  {
    strip.setPixelColor(pgm_read_word(&candles[i])-1,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
    strip.show();
    delay(50);
  }

}

//This shows the X-M-A-S when viewed from above
void xmas(){

  colorWipe(strip.Color(0, 0, 0), 0); // blank

  
  //The size of the PROGMEM is hardcoded, as the sizeof does return crap on the ATtiny.
  
  //Show the X:
  for (int i = 0; i < 14; i++)
  {
    strip.setPixelColor(pgm_read_word(&charX[i])-1,strip.Color(BRIGHTNESS, 0, 0));
        strip.show();
    delay(50);
  }
  delay(1000);
  //colorWipe(strip.Color(0, 0, 0), 0); // blank

  //Show the M:
  for (int i = 0; i < 14; i++)
  {
    strip.setPixelColor(pgm_read_word(&charM[i])-1,strip.Color(0, BRIGHTNESS, 0));
    strip.show();
    delay(50);
  }
  delay(1000);
  //colorWipe(strip.Color(0, 0, 0), 0); // blank

  //Show the A:
  for (int i = 0; i < 14; i++)
  {
    strip.setPixelColor(pgm_read_word(&charA[i])-1,strip.Color(0, 0, BRIGHTNESS));
    strip.show();
    delay(50);
  }
  delay(1000);
  //colorWipe(strip.Color(0, 0, 0), 0); // blank

  //Show the S:
  for (int i = 0; i < 14; i++)
  {
    strip.setPixelColor(pgm_read_word(&charS[i])-1,strip.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS));
    strip.show();
    delay(50);
  }
  delay(1000);
  colorWipe(strip.Color(0, 0, 0), 0); // blank
  
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

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
