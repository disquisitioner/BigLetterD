#include <FastLED.h>
#include "LEDControl.h"

#define NUM_LEDS 8
#define DATA_PIN  12

// Create the array we need for handling LED color/hue settings
CRGB leds[NUM_LEDS];

// Create the LED Control library object, which is how we set
// the various animations to be displayed. For more info see LEDControl.h. 
// LEDControl builds on top of the FastLED library, including using the leds
// array.
LEDControl letterD(NUM_LEDS, leds);

void setup() {

  // randomSeed(analogRead(0));
  Serial.begin(115200);
  
  // Initialize LED strip
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);  // Not too bright (mindful of current draw)

  letterD.setFlowRev();  // Default pattern
  letterD.update();
  FastLED.show();
  delay(100);

}

unsigned int counter = 0;
boolean cyclePattern = true;  // Cycle through the various LEDControl animations?

void loop() {

  unsigned long bitmap;
  int cycle_len;

  // Marquee pattern.  Length (in bits) should match the number of LEDs, 
  // but can't be larger than 32 given limitations of current implementation
  bitmap = 0b1100110011001100;

  cycle_len = 4*NUM_LEDS;  // Four full runs of each animation pattern
  
  if(cyclePattern) {
      // Cycle through patterns, with cycle_len updates for each
      if( (counter % cycle_len) == 0) {
        switch((counter/cycle_len)%10) {
          case 0: letterD.setRunFwd(CRGB::Orange);    break;
          case 1: letterD.setRunRev(CRGB::Teal);       break;
          case 2: letterD.setRainbowRev();            break;
          case 3: letterD.setCylon(CRGB::Red);        break;
          case 4: 
            letterD.setMarquee(CRGB::Yellow,bitmap);  break;
          case 5: letterD.setOneColor(CRGB::Purple);  break;
          case 6: letterD.setBreathe(CRGB::Blue);     break;
          case 7: letterD.setRainbowFwd();            break;
          case 8: letterD.setFlowFwd();               break;
          case 9: letterD.setFlowRev();               break;
            
          default: letterD.setOneColor(CRGB::Orange); break;  // should never see this
        }
      }
      counter++;
      letterD.update();    
  }
  else {
    letterD.update();
  }

  FastLED.show();
  delay(100);
}

void pushFwd()
{
  for(int i=NUM_LEDS-1;i>0;i--) {
    leds[i] = leds[i-1];
  }
  leds[0] = CHSV(random(0,256),255,255);
}
