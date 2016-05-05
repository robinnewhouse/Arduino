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

  // initialize pin type
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
  // initialize serial communication
  Serial.begin(9600);
  //
  //  pinMode(SD_CS, OUTPUT);
  //
  //  // we'll use the initialization code from the utility libraries
  //  // since we're just testing if the card is working!
  //  if (!card.init(SPI_HALF_SPEED, SD_CS)) {
  //    Serial.println("initialization failed.");
  //    return;
  //  } else {
  //    Serial.println("Wiring is correct and a card is present.");
  //  }


}


void loop() {
  if (j >= 2) j = 0;
  j++;
  for (int i = 0; i <= NUM_LEDS; i++) {

//    if (((i+j) % 3) == 0)
//      leds[i] = CRGB::Aqua;
//    if (((i+j) % 3) == 1)
      leds[i].setRGB(255,255,255);
//    if (((i+j) % 3) == 2)
//      leds[i] = CRGB::Black;
  }

  FastLED.show();
  delay(20);


}


