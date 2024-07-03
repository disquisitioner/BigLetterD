#include <FastLED.h>
#include "LEDControl.h"

#define NUM_LEDS 16
#define DATA_PIN  12

CRGB leds[NUM_LEDS];

LEDControl letterD(NUM_LEDS, leds);


void setup() {
  // Initialize LED strip
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);  // Not too bright (mindful of current draw)

  initrainbow();
  FastLED.show();
  delay(2000);

}

void loop() {
  doupdate0();
  FastLED.show();
  delay(100);
}

uint8_t hue;
void initrainbow()
{
  int i, incr;
  hue = 0;
  incr = 256 / NUM_LEDS;  // Color change step size per LED
  
  for (i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV( ((hue + (i * incr))% 256), 255, 255);
  }
}

// Recalculate every time  (But why do that?)
void doupdate()
{
  int i, incr;
  hue++;
  incr = 256 / NUM_LEDS;  // Color change step size per LED
  for (i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV( ((hue + (i * incr))% 256), 255, 255);
  }  
}

// Shift values one LED "upward" -- fast!
void doupdate0()
{
  int i;
  CRGB color;
  color = leds[NUM_LEDS - 1];
  for (i = NUM_LEDS - 1; i > 0; i--) {
    leds[i] = leds[i - 1];
  }
  leds[0] = color;
}
