#include <FastLED.h>
/*
 * MyCandle.h
 *
 *  Created on: Jun 13, 2016
 *      Author: pete
 */

#define NUM_LEDS        7
#define CANDLE_DOWN    -1
#define CANDLE_FLICKER  0
#define CANDLE_UP       1

class MyCandle {
public:
  MyCandle();
  ~MyCandle();

  bool init(HSVHue, uint8_t, uint8_t, uint8_t, uint8_t);
  void runCandle();
  void switchDirection();
  void setHueDirection();
  void oscillate();
  void seeTheRainbow();

private:
  CHSV candles[NUM_LEDS];
  uint8_t mDir;
  bool mIsFlickering;
  uint8_t mBaseV;
  uint8_t mLikely;
  uint8_t mHueTargetHigh;
  uint8_t mHueTargetLow;
  uint8_t mHueChange;
  uint8_t mHueUpdate;
  uint8_t m_toUpdateHue;
};

