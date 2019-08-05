#if !defined(__HIDKEYBOARDPARSER_H__)
#define __HIDKEYBOARDPARSER_H__

#include <usbhid.h>
#include <hidboot.h>

class KeyEvents {
  public:
    virtual void KeyStateChanged(char c,  bool isDown);
    virtual void ControlKeyStateChanged(MODIFIERKEYS beforeMod, MODIFIERKEYS afterMod);
};

class HIDKeyboardParser : public KeyboardReportParser { // inherits from HIDReportParser
//    void PrintKey(uint8_t mod, uint8_t key);
  KeyEvents *keyEvents; // Delegate for simple event callbacks

  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);

    void OnKeyDown  (uint8_t mod, uint8_t key);
    void OnKeyUp  (uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);

  public:
    // Initialiser
    HIDKeyboardParser(KeyEvents *evt);
  
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif // __HIDKEYBOARDPARSER_H__
