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
  m_huePriority = 0;
  m_huePrioCount = 0;
}

MyCandle::~MyCandle()
{
}

bool MyCandle::init(HSVHue c, uint8_t tl, uint8_t th, uint8_t vcl, uint8_t hcl, uint8_t prio)
{
    for(uint8_t i = 0; i < NUM_LEDS; i++) {
        m_candles[i].h = c;
        m_candles[i].v = 100;
        m_candles[i].s = 255;
    }
    if (vcl < 4)
      vcl = 4;
    m_varChangeLikely = vcl;

    if (hcl < 4)
      hcl = 4;
    m_hueChangeLikely = hcl;

    m_hueTargetHigh = th;
    m_hueTargetLow = tl;
    m_huePriority = prio;

    return true;
}

void MyCandle::setVariance()
{
  uint8_t rval = 0;

  if (m_candles[0].v <= 80) {
    m_varianceDirection = CANDLE_UP;
    return;
  }

  if (m_candles[0].v >= 250) {
    m_varianceDirection = CANDLE_DOWN;
    return;
  }

  rval = random8(0, m_varChangeLikely);
  switch (rval) {
  case 1:
    m_varianceDirection = CANDLE_DOWN;
    break;
  case 2:
    m_varianceDirection = CANDLE_UP;
    break;
  case 3:
    m_varianceDirection = CANDLE_LEVEL;
    break;    
  }
}

void MyCandle::setHue()
{
  uint8_t rval = 0;

  if (m_candles[0].h >= m_hueTargetHigh) {
    m_hueDirection = HUE_DOWN;
    return;
  }

  if (m_candles[0].h <= m_hueTargetLow) {
    m_hueDirection = HUE_UP;
    return;
  }

  rval = random8(0, m_hueChangeLikely);
  switch (rval) {
  case 1:
    m_hueDirection = HUE_DOWN;
    break;
  case 2:
    m_hueDirection = HUE_UP;
    break;
  case 3:
    m_hueDirection = HUE_LEVEL;
    break;
  }
}

void MyCandle::oscillate()
{
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    if ((m_huePrioCount++ % m_huePriority) == 0)
      m_candles[i].h += m_hueDirection;
      
    m_candles[i].v += m_varianceDirection;
  }
  hsv2rgb_rainbow(m_candles, leds, NUM_LEDS);
  FastLED.show();
}

void MyCandle::runCandle()
{
  setVariance();
  setHue();
    
  oscillate();
}

