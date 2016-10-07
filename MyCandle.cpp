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
  m_varianceDirection = CANDLE_UP;
  m_varChangeLikely = 0;
  m_hueChangeLikely = 0;
  m_hueTargetHigh = 0;
  m_hueTargetLow = 0;
  m_hueDirection = 0;
}

MyCandle::~MyCandle()
{
}

void MyCandle::seeTheRainbow()
{
  hsv2rgb_rainbow(candles, leds, NUM_LEDS);
  FastLED.show();
}

bool MyCandle::init(HSVHue c, uint8_t tl, uint8_t th, uint8_t vcl, uint8_t hcl)
{
    for(uint8_t i = 0; i < NUM_LEDS; i++) {
        candles[i].h = c;
        candles[i].v = 100;
        candles[i].s = 255;
    }
    if (vcl < 4)
      vcl = 4;
    m_varChangeLikely = vcl;

    if (hcl < 4)
      hcl = 4;
    m_hueChangeLikely = hcl;

    m_hueTargetHigh = th;
    m_hueTargetLow = tl;

    return true;
}

void MyCandle::setVariance()
{
  uint8_t rval = 0;

  if (candles[0].v <= 60) {
    m_varianceDirection = CANDLE_UP;
    return;
  }

  if (candles[0].v >= 250) {
    m_varianceDirection = CANDLE_DOWN;
    return;
  }

  rval = random8(0, m_varChangeLikely);
  if (rval == 1) {
    m_varianceDirection = CANDLE_UP;
  }
  if (rval == 2) {
    m_varianceDirection = CANDLE_FLICKER;
  }
  if (rval == 3) {
    m_varianceDirection = CANDLE_DOWN;
  }
}

void MyCandle::setHue()
{
  uint8_t rval = 0;

  if (candles[0].h >= m_hueTargetHigh) {
    m_hueDirection = -1;
    return;
  }

  if (candles[0].h <= m_hueTargetLow) {
    m_hueDirection = 1;
    return;
  }

  rval = random8(0, m_hueChangeLikely);
  switch (rval) {
  case 1:
    m_hueDirection = -1;
    break;
  case 2:
    m_hueDirection = 1;
    break;
  default:
    m_hueDirection = 0;
  }
}

void MyCandle::oscillate()
{
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    candles[i].h += m_hueDirection;
    candles[i].v += m_varianceDirection;
  }
  delay(2);
  seeTheRainbow();
}

void MyCandle::runCandle()
{
  setVariance();
  setHue();
  oscillate();
}

