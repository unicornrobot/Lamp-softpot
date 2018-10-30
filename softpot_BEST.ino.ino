#include <Adafruit_NeoPixel.h>
#define PIN            2
#define NUMPIXELS      8//64
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500;

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int aindex = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int val = 0;
int analogPin = A0;

void setup()
{
  Serial.begin(115200); 
  pinMode(analogPin, INPUT); 
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(0);
                  
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;          
}

void loop() {
  
  
  // subtract the last reading:
  total= total - readings[aindex];         
  // read from the sensor:
  val = analogRead(analogPin);
  if (val > 55)  // threshold?
  readings[aindex] = val; 
  // add the reading to the total:
  total= total + readings[aindex];       
  // advance to the next position in the array:  
  aindex = aindex + 1;                    

  // if we're at the end of the array...
  if (aindex >= numReadings)              
    // ...wrap around to the beginning: 
    aindex = 0;                           

  // calculate the average:
  average = total / numReadings;         
  // send it to the computer as ASCII digits
  //Serial.println(average);   
  //delay(1);        // delay in between reads for stability 

  // Map the 0-1023 value to 0-40
  int softPotPosition = map(average, 0, 1023, 0, 200);
  //Serial.println(" "); 
  Serial.println(softPotPosition);     

  
  for(int p=0;p<NUMPIXELS;p++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(p, pixels.Color(255,0,0)); // full white
    }
    if (softPotPosition < 20)
     pixels.setBrightness(0); 
     else
    pixels.setBrightness(softPotPosition);
     
    pixels.show(); // This sends the updated pixel color to the hardware.
  
}





/*
#include <Adafruit_NeoPixel.h>
#define PIN            2
#define NUMPIXELS      64
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500;

const int SOFT_POT_PIN = A0; // Pin connected to softpot wiper
const int GRAPH_LENGTH = 40; // Length of line graph
int softPotADC;
int touched;

void setup() 
{
  Serial.begin(115200);
  pinMode(SOFT_POT_PIN, INPUT);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(64);
}

void loop() 
{

  Serial.print(analogRead(SOFT_POT_PIN));
  Serial.print(" ");
  Serial.print(touched);
  // Only Read in the soft pot's ADC value if its not 0
  //ONLY UPDATE THE VARIABLE WHEN POT IS TOUCHED
  if (analogRead(SOFT_POT_PIN) < 15){ //NOT TOUCHED
      touched = 0;
  }else{
      touched = 1;
  }
    
  // Map the 0-1023 value to 0-40
  int softPotPosition = map(analogRead(SOFT_POT_PIN), 5, 1023, 0, GRAPH_LENGTH);

  // Print a line graph:
  Serial.print("<"); // Starting end
  for (int i=0; i<GRAPH_LENGTH; i++)
  {
    if (i == softPotPosition) Serial.print("|");
    else Serial.print("-");
  }
  Serial.println("> (" + String(softPotPosition) + ")");

  //delay(500);

  for(int p=0;p<NUMPIXELS;p++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(p, pixels.Color(255,0,0)); // full white
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  if (analogRead(SOFT_POT_PIN) > 15)
  pixels.setBrightness(softPotPosition); 
    else
    pixels.setBrightness(0);
 
}

*/


