/*
 * MyCandle.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: pete
 */
#include "MyCandle.h"

extern CRGB leds[NUM_LEDS];

MyCandle::MyCandle()
{
  mIsFlickering = false;
  mBaseV = 0;
  mDir = CANDLE_UP;
  mLikely = 100;
  mHueTargetHigh = 0;
  mHueTargetLow = 0;
  mHueChange = 0;
  mHueUpdate = 0;
  m_toUpdateHue = 0;
}

MyCandle::~MyCandle()
{
}

void MyCandle::seeTheRainbow()
{
  hsv2rgb_rainbow(candles, leds, NUM_LEDS);
  FastLED.show();
}

bool MyCandle::init(HSVHue c, uint8_t tl, uint8_t th, uint8_t l, uint8_t h)
{
    for(uint8_t i = 0; i < NUM_LEDS; i++) {
        candles[i].h = c;
        candles[i].v = 100;
        candles[i].s = 255;
    }
    if (l < 4)
      l = 4;
    mLikely = l;

    if (h < 1)
      h = 1;
    mHueChange = h;

    mHueTargetHigh = th;
    mHueTargetLow = tl;

    return true;
}

void MyCandle::switchDirection()
{
  uint8_t rval = 0;

  if (candles[0].v <= 30) {
    mDir = CANDLE_UP;
    return;
  }

  if (candles[0].v >= 200) {
    mDir = CANDLE_DOWN;
    return;
  }

  rval = random8(0, mLikely);
  if (rval == 1) {
    mDir = CANDLE_UP;
  }
  if (rval == 2) {
    mDir = CANDLE_FLICKER;
  }
  if (rval == 3) {
    mDir = CANDLE_UP;
  }
}

void MyCandle::setHueDirection()
{
  uint8_t rval = 0;

  if (candles[0].h >= mHueTargetHigh) {
    mHueUpdate = -1;
    return;
  }

  if (candles[0].h <= mHueTargetLow) {
    mHueUpdate = 1;
    return;
  }

  rval = random8(0, mLikely);
  switch (rval) {
  case 0:
    mHueUpdate = 0;
    break;
  case 1:
    mHueUpdate = -1;
    break;
  case 2:
    mHueUpdate = 1;
    break;
  }
}

void MyCandle::oscillate()
{
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    candles[i].h += mHueUpdate;
    candles[i].v += mDir;
  }
  delay(5);
  seeTheRainbow();
}

void MyCandle::runCandle()
{
  switchDirection();
  if (m_toUpdateHue++ == 4) {
    setHueDirection();
    m_toUpdateHue = 0;
  }
  else {
    mHueUpdate = 0;
  }
  oscillate();
}

