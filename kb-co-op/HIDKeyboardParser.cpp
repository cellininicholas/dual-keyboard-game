#include "HIDKeyboardParser.h"

HIDKeyboardParser::HIDKeyboardParser(KeyEvents *evt) : keyEvents(evt) {
  
}


//void HIDKeyboardParser::PrintKey(uint8_t m, uint8_t key)
//{
//  MODIFIERKEYS mod;
//  *((uint8_t*)&mod) = m;
//  Serial.print((mod.bmLeftCtrl   == 1) ? "C" : " ");
//  Serial.print((mod.bmLeftShift  == 1) ? "S" : " ");
//  Serial.print((mod.bmLeftAlt    == 1) ? "A" : " ");
//  Serial.print((mod.bmLeftGUI    == 1) ? "G" : " ");
//
//  Serial.print(" >");
//  PrintHex<uint8_t>(key, 0x80);
//  Serial.print("< ");
//
//  Serial.print((mod.bmRightCtrl   == 1) ? "C" : " ");
//  Serial.print((mod.bmRightShift  == 1) ? "S" : " ");
//  Serial.print((mod.bmRightAlt    == 1) ? "A" : " ");
//  Serial.println((mod.bmRightGUI    == 1) ? "G" : " ");
//};

void HIDKeyboardParser::OnKeyDown(uint8_t mod, uint8_t key)
{
//  Serial.print("DN ");
//  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  if (c) OnKeyPressed(c);
  keyEvents->KeyStateChanged((char)c, true);
}

void HIDKeyboardParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

//  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
//    Serial.println("LeftCtrl changed");
//  }
//  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
//    Serial.println("LeftShift changed");
//  }
//  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
//    Serial.println("LeftAlt changed");
//  }
//  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
//    Serial.println("LeftGUI changed");
//  }
//
//  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
//    Serial.println("RightCtrl changed");
//  }
//  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
//    Serial.println("RightShift changed");
//  }
//  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
//    Serial.println("RightAlt changed");
//  }
//  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
//    Serial.println("RightGUI changed");
//  }
  
  keyEvents->ControlKeyStateChanged(beforeMod, afterMod);
}

void HIDKeyboardParser::OnKeyUp(uint8_t mod, uint8_t key)
{
//  Serial.print("UP ASCII: ");
  uint8_t c = OemToAscii(mod, key);
//  Serial.println((char)c);
  
//  PrintKey(mod, key);
  keyEvents->KeyStateChanged((char)c, false);
}

void HIDKeyboardParser::OnKeyPressed(uint8_t key)
{
//  Serial.print("ASCII: ");
//  Serial.println((char)key);
};


void HIDKeyboardParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  // On error - return
  if (buf[2] == 1) {
    Serial.println("Error 1");
    return;
  }
  
  //KBDINFO       *pki = (KBDINFO*)buf;
  
  // provide event for changed control key state
  if (prevState.bInfo[0x00] != buf[0x00]) {
    OnControlKeysChanged(prevState.bInfo[0x00], buf[0x00]);
  }
  
  for (uint8_t i = 2; i < 8; i++) {
    bool down = false;
    bool up = false;
  
    for (uint8_t j = 2; j < 8; j++) {
      if (buf[i] == prevState.bInfo[j] && buf[i] != 1) down = true;
      if (buf[j] == prevState.bInfo[i] && prevState.bInfo[i] != 1) up = true;
    }
    if (!down) {
      HandleLockingKeys(hid, buf[i]);
      OnKeyDown(*buf, buf[i]);
    }
    if (!up) OnKeyUp(prevState.bInfo[0], prevState.bInfo[i]);
  }
  for (uint8_t i = 0; i < 8; i++) {
    prevState.bInfo[i] = buf[i];
  }
  
};
