#include <FastLED.h>
/*
 * MyCandle.h
 *
 *  Created on: Jun 13, 2016
 *      Author: pete
 */

#define NUM_LEDS        1
#define CANDLE_DOWN    -1
#define CANDLE_FLICKER  0
#define CANDLE_UP       1

class MyCandle {
public:
  MyCandle();
  ~MyCandle();

  bool init(HSVHue, uint8_t, uint8_t, uint8_t, uint8_t);
  void runCandle();
  void setVariance();
  void setHue();
  void oscillate();
  void seeTheRainbow();

private:
  CHSV candles[NUM_LEDS];
  uint8_t m_varianceDirection;
  uint8_t m_hueDirection;
  uint8_t m_hueChangeLikely;
  uint8_t m_varChangeLikely;
  uint8_t m_hueTargetLow;
  uint8_t m_hueTargetHigh;
};

