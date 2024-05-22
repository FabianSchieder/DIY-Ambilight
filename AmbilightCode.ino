#include "FastLED.h"
#define NUM_LEDS 120
#define DATA_PIN D3

#define serialRate 230400

uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;

CRGB leds[NUM_LEDS];

void setup() 
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
  Serial.begin(serialRate);
  Serial.print("Ada\n");
}

void loop() 
{ 
  for(i = 0; i < sizeof prefix; ++i) 
  {
    waitLoop: while (!Serial.available()) ;;

    if(prefix[i] == Serial.read()) continue;
    i = 0;

    goto waitLoop;
  }
  
  while (!Serial.available()) ;;
  hi = Serial.read();
  while (!Serial.available()) ;;
  lo = Serial.read();
  while (!Serial.available()) ;;
  chk = Serial.read();
  
  if (chk != (hi ^ lo ^ 0x55)) 
  {
    i=0;
    goto waitLoop;
  }
  
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));

  for (uint8_t i = 0; i < NUM_LEDS; i++) 
  {
    byte r, g, b;    
    while(!Serial.available());
    r = Serial.read();
    while(!Serial.available());
    g = Serial.read();
    while(!Serial.available());
    b = Serial.read();
    leds[i].r = r;
    leds[i].g = g;
    leds[i].b = b;
  }
  
  FastLED.show();
}