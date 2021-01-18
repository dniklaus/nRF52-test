/*
 * wiring-skeleton.cpp
 *
 *  Created on: 15.03.2017
 *      Author: niklausd
 */

#include <Arduino.h>

// patch for missing nRF52840DK pinmap
#undef PIN_BUTTON1
#undef PIN_BUTTON2
#undef PIN_BUTTON3
#undef PIN_BUTTON4
#define PIN_BUTTON1          (0)  
#define PIN_BUTTON2          (1)  
#define PIN_BUTTON3          (12) 
#define PIN_BUTTON4          (13) 

// PlatformIO libraries
#include <SerialCommand.h>  // pio lib install 173, lib details see https://github.com/kroimon/Arduino-SerialCommand
#include <SpinTimer.h>      // pio lib install 1699, lib details see https://github.com/dniklaus/spin-timer

// private libraries
#include <ProductDebug.h>
#include <Button.h>
#include <DetectorStrategy.h>

// local components (lib folder)
#include <Indicator.h>
#include <MyBuiltinLedIndicatorAdapter.h>
#include <Button.h>
#include <DetectorStrategy.h>
#include <ButtonEdgeDetector.h>
#include <MyButtonAdapter.h>
#include <ArduinoDigitalInPinSupervisor.h>

SerialCommand* sCmd = 0;

// indicator implementation for built in LED
Indicator* led1 = 0;
Indicator* led2 = 0;
Indicator* led3 = 0;
Indicator* led4 = 0;

void setup()
{
  // setup basic debug environment (heap usage printer, trace ports & dbg cli)
  setupProdDebugEnv();

  // indicator LEDs
  led1 = new Indicator("led1", "Built in LED1.");
  led1->assignAdapter(new MyBuiltinLedIndicatorAdapter(1));

  led2 = new Indicator("led2", "Built in LED2.");
  led2->assignAdapter(new MyBuiltinLedIndicatorAdapter(2));

  led3 = new Indicator("led3", "Built in LED3.");
  led3->assignAdapter(new MyBuiltinLedIndicatorAdapter(3));

  led4 = new Indicator("led4", "Built in LED4.");
  led4->assignAdapter(new MyBuiltinLedIndicatorAdapter(4));

  // Buttons
  new Button(new ArduinoDigitalInPinSupervisor(PIN_BUTTON1), new ButtonEdgeDetector("btn1"), new MyButtonAdapter(led1));
  new Button(new ArduinoDigitalInPinSupervisor(PIN_BUTTON2), new ButtonEdgeDetector("btn2"), new MyButtonAdapter(led2));
  new Button(new ArduinoDigitalInPinSupervisor(PIN_BUTTON3), new ButtonEdgeDetector("btn3"), new MyButtonAdapter(led3));
  new Button(new ArduinoDigitalInPinSupervisor(PIN_BUTTON4), new ButtonEdgeDetector("btn4"), new MyButtonAdapter(led4));
}

void loop()
{
  if (0 != sCmd)
  {
    sCmd->readSerial();     // process serial commands
  }
  scheduleTimers();         // process Timers
}
