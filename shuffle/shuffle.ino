#include <FastLED.h>
#include <LEDControl.h>

#define NUM_LEDS  8
#define DATA_PIN  12

CRGB leds[NUM_LEDS];
LEDControl bigD(NUM_LEDS,leds);

void setup() {

  Serial.begin(115200);
  
  // Randomly seed our random number generator
  randomSeed(analogRead(0));
  
  // Initialize LED strip
  FastLED.addLeds<WS2812B,DATA_PIN,RGB>(leds,NUM_LEDS);

  bigD.setOneColor(CRGB::Blue);
  bigD.update();
  FastLED.show();

  delay(2000);
}

void loop() {
  int i, j, w, shuffle[NUM_LEDS];

  // Generate a shuffle of integer values from 0 to NUM_LEDS-1
  for(i=0;i<NUM_LEDS;i++) { shuffle[i] = i; }
  
  for(i=NUM_LEDS-1;i>0;i--) {
    j = random(i+1);
    w = shuffle[i];
    shuffle[i] = shuffle[j];
    shuffle[j] = w;
  }

  // Light up the LEDs in shuffled order
  for(i=0;i<NUM_LEDS;i++) {
    leds[shuffle[i]] = randomColor();
    // leds[shuffle[i]] = randomRGB(leds[shuffle[i]]);
    FastLED.show();
    delay(500);
  }
}

CRGB randomColor()
{
  static int hue = random(256);

  hue = (hue + (random(8)*16) + random(32))%256;
  // Serial.println(hue);
  return(CHSV(hue,255,255));
}

CRGB randomRGB(CRGB color)
{
  CRGB delta;

  delta = CHSV(random(256),256,256);
  delta = color + delta;
  return(delta);
}
