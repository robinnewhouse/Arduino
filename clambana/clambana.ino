#include <GIFDecoder.h>
#include <FastLED.h>
#include <SD.h>
#include "LEDMap.h"

#define NUM_LEDS 576
#define LED_PER_PIX 4
#define DATA_PIN 6
#define LED_TYPE WS2811
#define DISPLAY_TIME_SECONDS 60
#define GIF_DIRECTORY "/gifs/"
#define SD_CS 4 // depends on shield


// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8

unsigned long futureTime;
CRGB leds[NUM_LEDS];

void screenClearCallback(void) {
  Serial.print("DEBUG");
  return;
}

void updateScreenCallback(void) {
  FastLED.show();
  return;
}


// just for testing now, should do 3d array
int getLed(int x, int y, int i) {
  return myPixelMap [12 * LED_PER_PIX * x + LED_PER_PIX * y + i]; // programmatically gets the right LED
}

void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  // Fill each LED that belongs to this pixel
  if ( x >= 12 || y >= 12) {
    Serial.println("Index out of bounds");
    delay(1000);
    return;
  }

  // draw same color for every LED in this pixel
  for (int i = 0; i < LED_PER_PIX; i++) {
    int led_index = getLed(x, y, i);
    leds[ led_index ].setRGB(red, green, blue);
  }
}


void setup() {
  // initialize serial communication
  Serial.begin(9600);
  delay(600);

  pinMode(13, OUTPUT); // set clock pin (necessary??)

  // set callbacks for gif decoder
  setScreenClearCallback(screenClearCallback);
  setUpdateScreenCallback(updateScreenCallback);
  setDrawPixelCallback(drawPixelCallback);

  // initialize LED array with the proper LED type
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
  
  if (!SD.begin(SD_CS)) {
    Serial.println("initialization failed!");
    return;
  }
  pinMode(SD_CS, OUTPUT); // set sd pin as output
}



void loop() {


    char pathname[30];

  // Do forever
  while (true) {
    // Can clear screen for new animation here, but this might cause flicker with short animations
    // matrix.fillScreen(COLOR_BLACK);
    // matrix.swapBuffers();

    //    getGIFFilenameByIndex(GIF_DIRECTORY, index++, pathname);
    //    if (index >= num_files) {
    //      index = 0;
    //    }
    //    Serial.print("Path name: ");
    //    Serial.print(pathname);
    //    Serial.print("\n");

    // Calculate time in the future to terminate animation

    //    drawPixelCallback(11, 0, 30, 100, 200);

    futureTime = millis() + (DISPLAY_TIME_SECONDS * 1000);

    while (futureTime > millis()) {
      Serial.println("DEBUG 1");
      processGIFFile("/GIFS/IMPORTED.GIF");
      Serial.println("DEBUG 2");
    }
  }
}


