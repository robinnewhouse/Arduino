//#include <GIFDecoder.h>
#include <FastLED.h>
#include <SD.h>
#include "LEDMap.h"

#define NUM_LEDS 50
#define LED_PER_PIX 4
#define DATA_PIN 6
#define LED_TYPE WS2811

int j = 0;
int nFiles = 0;
CRGB leds[NUM_LEDS];

void setup() {
  // initialize serial communication
  Serial.begin(9600);
  // initialize pin type
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
}


void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = 200;
  }
  FastLED.show();
  FastLED.delay(1000);


  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
  FastLED.delay(1000);

    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(0,255,0);
  }
  FastLED.show();
  FastLED.delay(1000);


    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
  FastLED.delay(1000);

    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Purple;
  }
  FastLED.show();
  FastLED.delay(1000);

}


