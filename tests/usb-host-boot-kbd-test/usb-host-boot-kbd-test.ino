#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
//#ifdef dobogusinclude
//#include <spi4teensy3.h>
//#endif
//#include <SPI.h>

#include "HIDKeyboardParser.h"

USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

//HIDKeyboardParser Prs;
KeyEvents keyEvents;
HIDKeyboardParser Prs(&keyEvents);

// ---------------------

void KeyEvents::KeyStateChanged(char c,  bool isDown) {
  Serial.print(c);
  Serial.print(" ");
  Serial.println((isDown ? "DN":"UP"));
}

void KeyEvents::ControlKeyStateChanged(MODIFIERKEYS beforeMod, MODIFIERKEYS afterMod) {
  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    Serial.println("LeftCtrl changed");
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    Serial.println("LeftShift changed");
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    Serial.println("LeftAlt changed");
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    Serial.println("LeftGUI changed");
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    Serial.println("RightCtrl changed");
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    Serial.println("RightShift changed");
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    Serial.println("RightAlt changed");
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    Serial.println("RightGUI changed");
  }
}

// ---------------------

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  HidKeyboard.SetReportParser(0, &Prs);
}

void loop()
{
  Usb.Task();
}
