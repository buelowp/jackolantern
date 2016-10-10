#include <FastLED.h>
/*
 * MyCandle.h
 *
 *  Created on: Jun 13, 2016
 *      Author: pete
 */

#define NUM_LEDS        1
#define CANDLE_DOWN    -1
#define CANDLE_LEVEL    0
#define CANDLE_UP       1
#define HUE_DOWN        -1
#define HUE_LEVEL       0
#define HUE_UP          1

class MyCandle {
public:
  MyCandle();
  ~MyCandle();

  void init(HSVHue, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  void runCandle();
  void setVariance();
  void setHue();
  void oscillate();

private:
  CHSV m_candles[NUM_LEDS];
  int m_varianceDirection;
  int m_hueDirection;
  uint8_t m_hueChangeLikely;
  uint8_t m_varChangeLikely;
  uint8_t m_hueTargetLow;
  uint8_t m_hueTargetHigh;
  uint8_t m_huePriority;
  uint8_t m_huePrioCount;
};

