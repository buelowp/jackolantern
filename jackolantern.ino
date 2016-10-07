#include <FastLED.h>
#include "MyCandle.h"

CRGB leds[NUM_LEDS];
MyCandle candle;

void setup() {
  delay(2000);
  FastLED.addLeds<WS2812B, 1>(leds, NUM_LEDS);
  candle.init(HUE_RED, HUE_RED, HUE_RED + 20, 55, 5);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  candle.runCandle();
}
