#include <GIFDecoder.h>

#include <OctoWS2811.h>
//#include <FastLED.h>
#include <SD.h>
#include "LEDMap.h"

#define NUM_LEDS_PER_STRIP 144
#define NUM_STRIPS 8
const int NUM_LEDS = NUM_LEDS_PER_STRIP * NUM_STRIPS;
#define LED_PER_PIX 8
//#define DATA_PIN 6
#define LED_TYPE OCTOWS2811
#define DISPLAY_TIME_SECONDS 1
#define GIF_DIRECTORY "/gifs/"
#define SD_CS 3 // depends on shield
// need to set SD_CS to 3 for modified hardware


#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF
#define BLACK  0x000000

DMAMEM int displayMemory[NUM_LEDS_PER_STRIP * 6];
int drawingMemory[NUM_LEDS_PER_STRIP * 6];

const int config = WS2811_RGB; // color config is on the PC side

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8

int num_files;
int renderTime;
//int fileIndex; // file index
int controlFlag = 0;
unsigned long futureTime;

//CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
OctoWS2811 leds(NUM_LEDS_PER_STRIP, displayMemory, drawingMemory, config);

void screenClearCallback(void) {
  for (int i = 0; i <= NUM_LEDS; i++) {
    //    leds[i] = CRGB::Black;
    leds.setPixel(i, BLACK);
  }

}

void updateScreenCallback(void) {
  leds.show();
}

void startDrawingCallback(void) {
}

// just for testing now, should do 3d array
int getLed(int x, int y, int i) {
  //  return myPixelMap [12 * LED_PER_PIX * x + LED_PER_PIX * y + i]; // programmatically gets the right LED
  return myPixelMap [x][ y][i];

}

void drawPixelCallback(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue) {
  // Fill each LED that belongs to this pixel
  if ( x >= 12 || y >= 12) {
    Serial.println("Index out of bounds");
    delay(1000);
    return;
  }

  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(": [");
  // draw same color for every LED in this pixel
  for (int i = 0; i < LED_PER_PIX; i++) {
    int led_index = myPixelMap [x][y][i];
    Serial.print(led_index);
    Serial.print(", ");

    // converts rgb to hex
    leds.setPixel(led_index, ((red << 16) | (green << 8) | blue));
  }
  Serial.println("]");

}


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //  while (!Serial); // wait for serial port to connect. Needed for native USB port only

  Serial.println("Serial initialized");

  //  pinMode(13, OUTPUT); // set clock pin (necessary??)


  // set callbacks for gif decoder
  setScreenClearCallback(screenClearCallback);
  setUpdateScreenCallback(updateScreenCallback);
  setDrawPixelCallback(drawPixelCallback);
  setStartDrawingCallback(startDrawingCallback);

  // initialize LED array with the proper LED type
  //  FastLED.addLeds<LED_TYPE>(leds, NUM_LEDS_PER_STRIP);
  renderTime = micros();
  leds.begin();
  leds.show();


  if (!SD.begin(SD_CS)) {
    Serial.println("initialization failed!");
    return;
  }
  //  pinMode(SD_CS, OUTPUT); // set sd pin as output

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
    int fileIndex = random(num_files);

    // Party forever
    while (true) {
      // Strangely this number must be continully updated
      num_files = enumerateGIFFiles(GIF_DIRECTORY, false);

      // random
      //      fileIndex = random(num_files);
      // sequential
      getGIFFilenameByIndex(GIF_DIRECTORY, fileIndex, pathname);
      if (fileIndex >= num_files - 1)
        fileIndex = 0;
      else fileIndex++;

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


