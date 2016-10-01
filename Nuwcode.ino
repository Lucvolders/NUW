// Attiny85 code for making a resistor code clock

#include <Time.h>
#include <Adafruit_NeoPixel.h>

// Which pin on the Attiny85 is connected to the NeoPixels?
#define PIN            1
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      4

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int toets1=0;
int toets2=2;
int toets3=3;
int toets4=4;
int wait;
int tel;
int tel1=0;
int tel2=0;
int i=0;

const int clockcolor[10][3] ={
  // dit array bevat de weerstands codes voor de getallen 0 tot 9
  {000,000,000}, //  0 black {021,000,000}, //  1 brown
  {21,0,0}, //  1 brown
  {255,0,0}, //  2 red
  {255,37,3}, //  3 orange
  {255,255,0}, //  4 yellow
  {0,255,0}, //  5 green
  {0,0,255}, //  6 blue
  {14,1,42}, //  7 purple
  {37,37,37}, //  8 grey
  {255,255,255} //   9 white
};

void setup() 
{
  pinMode(0,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  
  setTime(00, 59, 00, 1, 1, 2015);
  pixels.begin(); // This initializes the NeoPixel library.
  int wait = second();
  for(int i=0;i<NUMPIXELS;i++)
  {
  int wait = second();
  pixels.setPixelColor(i, 0,0,255);
  pixels.show();
  while ((second()-wait)<1)
  {}
  }
}

void loop() 
{
  keyhourl();
  // check keypressed
  // this is for setting the time
  
  setresval();
  
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
}

void setresval()
{
  // first led is hours 0 1 or 2
  int hourh=hour();
  int hourhigh = 0;
  int i;
    for (i=3; i>0; i--)
  {
    hourh = hour()- (i*10);
    if ((hourh<10) && (hourh >-1))
    {
    hourhigh =i;
    }
   pixels.setPixelColor(3,clockcolor[hourhigh][0],clockcolor[hourhigh][1],clockcolor[hourhigh][2]); 
   pixels.show();
  }
  
  // }// second led is hours 0 to 9
  int hourl;
  hourl = hour()-(10*hourhigh);
  pixels.setPixelColor(2,clockcolor[hourl][0],clockcolor[hourl][1],clockcolor[hourl][2]);
  pixels.show();
  
  // third led is miniutes 0,1,2,3,4 or 5
  int minh=minute();
  int minhigh = 0;
  for (i=5; i>0; i--)
  {
    minh = minute()- (i*10);
    if ((minh<10) && (minh >-1))
    {
    minhigh =i;
    }
   pixels.setPixelColor(1,clockcolor[minhigh][0],clockcolor[minhigh][1],clockcolor[minhigh][2]); 
   pixels.show();
  }
  
  
  // fourth led is minutes 0 to 9
  int minl;
  minl = minute()-(10*minhigh);
  pixels.setPixelColor(0,clockcolor[minl][0],clockcolor[minl][1],clockcolor[minl][2]);
  pixels.show();
}

void keyhourl()
{
  if (digitalRead(toets1)==LOW)
  {
    tel1=hour()+1;
    setTime(hour()+1,minute(),second(),1,1,2015);
    delay(200);
  }


  if (digitalRead(toets2)==LOW)
  {
    tel2=minute()+1;
    setTime(hour(),tel2,second(),1,1,2015);
    delay(200);
  }
}
