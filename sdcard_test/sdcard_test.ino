#include <SD.h>

// teensy
const int cs = 4;

void setup()
{
  Serial.begin(9600);

  delay(1);

  
  Serial.print("debug...");


  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);   // reset the WIZ820io
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);  // de-select WIZ820io
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);   // de-select the SD Card


  Serial.print("Initializing card...");
  // make sure that the default chip select pin is declared OUTPUT
  pinMode(cs, OUTPUT);
  
  // see if the card is present
  if (!SD.begin(cs)) 
  {
    Serial.println("Card failed to initialize, or not present");
  
    return;
  }
  Serial.println("card initialized.");
  
  // open the file named ourfile.txt
  
  File myfile = SD.open("/test/1.jpg");

  // if the file is available, read the file
  if (myfile) 
  {
    while (myfile.available())
    {
      Serial.write(myfile.read());
    }
    myfile.close();
  }  
  // if the file cannot be opened give error report
  else {
    Serial.println("error opening the text file");
  } 
}

void loop()
{
}

                  
