#include <avr/power.h>
#include <avr/sleep.h>
#include <FastLED.h>
#include "MyCandle.h"

CRGB leds[NUM_LEDS];
MyCandle candle;

void setup() {
  power_timer1_disable();
  power_adc_disable();
  power_usi_disable();             // Knocks out TinyWire library
  
  delay(2000);
  FastLED.addLeds<WS2812B, 1>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  candle.init(HUE_RED, HUE_RED, HUE_RED + 15, 55, 50, 5);
}

void loop() {
  uint16_t rval = random16(0, 30000);

  if (rval == 13)
    candle.init(HUE_PURPLE, HUE_PURPLE - 10, HUE_PURPLE + 5, 55, 50, 5);
  if (rval == 57)
    candle.init(HUE_RED, HUE_RED, HUE_RED + 15, 55, 50, 5);
  if (rval == 236)
    candle.init(HUE_GREEN, HUE_GREEN - 10, HUE_GREEN + 10, 55, 50, 5);

  candle.runCandle();
  delay(5);
}
