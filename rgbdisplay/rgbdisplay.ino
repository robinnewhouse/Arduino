
// constants won't change. Used here to set a pin number :
const int r =  3;      // the number of the LED pin
const int g =  5;      // the number of the LED pin
const int b =  6;      // the number of the LED pin
const int rw =  9;      // the number of the LED pin
const int gw =  10;      // the number of the LED pin
const int bw =  11;      // the number of the LED pin

// Variables will change :
int rState = 13;             // ledState used to set the LED
int gState = 200;             // ledState used to set the LED
int bState = 112;             // ledState used to set the LED

int sensorValue;

void setup() {
  // set the digital pin as output:
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(rw, OUTPUT);
  pinMode(gw, OUTPUT);
  pinMode(bw, OUTPUT);

  Serial.begin(9600);


}

void loop() {
  readDials();
  render();

}

void readDials(){
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
}

void render(){
  rState = sensorValue-30;
  gState = sensorValue-100;
  bState = sensorValue+100;
  
  analogWrite(r, rState);
  analogWrite(g, gState);
  analogWrite(b, bState);
  analogWrite(rw, rState);
  analogWrite(gw, gState);
  analogWrite(bw, bState);
}

