/*
 * MyBuiltinLedIndicatorAdapter.cpp
 *
 *  Created on: 04.11.2019
 *      Author: nid
 */

#include <Arduino.h>
#include "MyBuiltinLedIndicatorAdapter.h"

// patch for missing nRF52840DK pinmap
#undef PIN_LED1
#undef PIN_LED2
#undef PIN_LED3
#undef PIN_LED4
#undef LED_BUILTIN
#define PIN_LED1             (2) 
#define PIN_LED2             (3) 
#define PIN_LED3             (4) 
#define PIN_LED4             (5) 
#define LED_BUILTIN          PIN_LED1


const uint32_t MyBuiltinLedIndicatorAdapter::cledPin = LED_BUILTIN;  

MyBuiltinLedIndicatorAdapter::MyBuiltinLedIndicatorAdapter(unsigned int index /* = 0 */)
: m_ledPin((index == 1) ? PIN_LED1 : (index == 2) ? PIN_LED2 : (index == 3) ? PIN_LED3 : (index == 4) ? PIN_LED4 : cledPin)
{
  // initialize built in LED pin as output
  pinMode(m_ledPin, OUTPUT);

  // switch LED off
  setLed(false);
}

MyBuiltinLedIndicatorAdapter::~MyBuiltinLedIndicatorAdapter()
{ }

void MyBuiltinLedIndicatorAdapter::notifyStatusChange(bool status)
{
  setLed(status);
}

void MyBuiltinLedIndicatorAdapter::setLed(bool isOn)
{
#if defined(ESP8266) or defined(NRF52)
  // the built-in LED logic on ESP8266 and NRF52 modules are inverted!
  isOn = !isOn;
#endif
  digitalWrite(m_ledPin, isOn);
}
