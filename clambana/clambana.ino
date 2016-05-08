#include <GIFDecoder.h>
#include <FastLED.h>
#include <SD.h>
#include "LEDMap.h"

#define NUM_LEDS 576
#define LED_PER_PIX 4
#define DATA_PIN 6
#define LED_TYPE WS2811
#define DISPLAY_TIME_SECONDS 10
#define GIF_DIRECTORY "/gifs/"
#define SD_CS 4 // depends on shield

long num_files;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8

unsigned long futureTime;
CRGB leds[NUM_LEDS];

void screenClearCallback(void) {
  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

void updateScreenCallback(void) {
  FastLED.show();
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
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial initialized");

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

  Serial.println("Setup Complete");
  Serial.println("========================");

}



void loop() {
  // Do forever
  while (true) {
    // get the number of files in the directory
    num_files = enumerateGIFFiles(GIF_DIRECTORY, false);

    Serial.print(num_files);
    Serial.println(" animations present.");


    unsigned long futureTime;
    char pathname[30];
    // start on a random file
    randomSeed(analogRead(2)); // initialize random generator
    int index = random(num_files);

    // Party forever
    while (true) {
      // Strangely this number must be continully updated
      num_files = enumerateGIFFiles(GIF_DIRECTORY, false);

      // random
      //      index = random(num_files);
      // sequential
      getGIFFilenameByIndex(GIF_DIRECTORY, index, pathname);
      if (index >= num_files)
        index = 0;
      else index++;

      Serial.print("Now playing: ");
      Serial.println(pathname);

      // Calculate time in the future to terminate animation
      futureTime = millis() + (DISPLAY_TIME_SECONDS * 1000);

      while (futureTime > millis()) {
        processGIFFile(pathname);
      }
    }
  }
}


