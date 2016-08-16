#include <FastLED.h>
#include "MyCandle.h"

CRGB leds[NUM_LEDS];
MyCandle candle;

void setup() {
  delay(2000);
  FastLED.addLeds<NEOPIXEL, 1>(leds, NUM_LEDS);
  candle.init(HUE_PURPLE, HUE_PURPLE - 20, HUE_PURPLE + 20, 25, 10);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  candle.runCandle();
}
