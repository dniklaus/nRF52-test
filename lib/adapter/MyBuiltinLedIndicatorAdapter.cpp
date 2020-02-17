/*
 * MyBuiltinLedIndicatorAdapter.cpp
 *
 *  Created on: 04.11.2019
 *      Author: nid
 */

#include <Arduino.h>
#include "MyBuiltinLedIndicatorAdapter.h"

const uint32_t MyBuiltinLedIndicatorAdapter::cledPin = PIN_BUTTON1;  // there seems to be a bug: PIN_LED1 and PIN_BUTTON1 are exchanged in definition.

MyBuiltinLedIndicatorAdapter::MyBuiltinLedIndicatorAdapter()
{
  // initialize built in LED pin as output
  pinMode(cledPin, OUTPUT);

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
  digitalWrite(cledPin, isOn);
}
