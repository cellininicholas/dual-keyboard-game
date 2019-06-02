#include <U8g2lib.h>
#include <usbhub.h>

#include "HIDKeyboardParser.h"

// pin definitions - change these to match your wiring
// E =  Green
// RW = Yellow (-> Blue for 1 display)
// RS = Orange
const int D1_PIN_E = 7, D1_PIN_RW = 8, D1_PIN_RS = 5;
const int D2_PIN_E = 3, D2_PIN_RW = 4, D2_PIN_RS = 6;

const int SWITCH_PIN_1 = 4, SWITCH_PIN_2 = 3;

// ------------------------------
// USB KEYBOARD
USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
KeyEvents keyEvents;
HIDKeyboardParser Prs(&keyEvents);
// ------------------------------
// DISPLAYS
// https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#constructor-name
// Prefix:     U8G2
// Display:    ST7920
// DispName:   128X64
// BufferSize: 1 (1,2 or F (full frame buffer))
// Commun:     SW_SPI (Software emulated, SPI (Serial))

//                           ...(rotation, clock, data, cs [, reset])
U8G2_ST7920_128X64_1_SW_SPI disp1(U8G2_R0, D1_PIN_E, D1_PIN_RW, D1_PIN_RS);
U8G2_ST7920_128X64_1_SW_SPI disp2(U8G2_R0, D2_PIN_E, D2_PIN_RW, D2_PIN_RS);
// ------------------------------

const char letters[36] = {'a', 'b', 'c', 'd', 'e', 'f','g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
String line1Str = "Byron and Nick's";
String line2Str = "KB GAMES";
int curCharIndex = 0;
//bool curLine = true;
int btn1State, btn2State;

// how long to spend at each step - higher wait_time = slower rotation
const int wait_time = 99;
int wait_progress = 0;

void setup() {

  // initialize the pushbutton pins as an inputs:
  pinMode(SWITCH_PIN_1, INPUT);
  pinMode(SWITCH_PIN_2, INPUT);

  btn1State = digitalRead(SWITCH_PIN_1);
  btn2State = digitalRead(SWITCH_PIN_2);

  // Displays setup
  disp1.begin();
  disp2.begin();

  // Keyboard setup
  delay(1000);
//  keyboard.begin(Keyboard_DataPin, Keyboard_IRQpin, PS2Keymap_US);
//  keyboard.begin(Keyboard_DataPin, Keyboard_IRQpin);
//  Serial.begin(115200);
//  while (!Serial) yield();
  
  Serial.println("Keyboard Setup Start...");
  if (Usb.Init() == -1) Serial.println("USB OSC did not start.");
  delay( 200 );
  HidKeyboard.SetReportParser(0, &Prs);
}

void drawOnDisplay(U8G2_ST7920_128X64_1_SW_SPI disp, bool isDisp1) {
  //    u8g2.drawLine(c1, r1, c2, r2);   // draw the line from (c1, r1) to (c2, r2)
//    u8g2.setFont(u8g2_font_ncenB14_tr);

    // SetFont
    // ----------
    // The 2 letters are <purpose><char set>
    // PURPOSE
    // t_ - Transparent gylphs with variable width
    // m_ - Monospace/fixed width glyphs
    // h_ - Glyphs with variable width and common height
    // 8_ - Monospace/fixed width glyphs in a 8x8 box
    // CHAR SET
    // _f - The font includes up to 256 glyphs.
    // _r - Only glyphs on the range of the ASCII codes 32 to 127 are included in the font.
    // _u - Only glyphs on the range of the ASCII codes 32 to 95 (uppercase chars) are included in the font.
    // _n - Only numbers and extra glyphs for writing date and time strings are included in the font.

    // Our fonts:
    // https://github.com/olikraus/u8g2/wiki/fntgrpgeoff#tenstamps
    // https://github.com/olikraus/u8g2/wiki/fntgrpgeoff#tenthinnerguys
    // FONT MODE
    // https://github.com/olikraus/u8g2/wiki/u8g2reference#setfontmode

//    u8g2.setFont(u8g2_font_helvR24_te); // tf, tr, tn, te?
//    u8g2.setFont(u8g2_font_helvB18_tf); // tf, tr, tn, te?
    disp.setFont(u8g2_font_tenthinnerguys_tf);
    disp.setFontPosTop();
    
    disp.drawStr(4,7,line1Str.c_str());

//    u8g2.setFont(u8g2_font_crox5tb_tf); // mf, mr
    disp.setFont(u8g2_font_tenstamps_mu); // mu=monospace,uppercase
    disp.drawStr(4,22,line2Str.c_str());


    disp.setFont(u8g2_font_tenthinnerguys_tf);
    disp.drawStr(4,45,"On Display for all");

    
    disp.setFont(u8g2_font_roentgen_nbp_tf);
    disp.drawStr(109,0,String(wait_progress).c_str());

    disp.drawStr(81,56, ("BTN="+String(isDisp1 ? btn2State : btn1State)).c_str());
}

void update() {
  bool disp1Update = wait_progress % 2 == 1;
  line1Str = disp1Update ? "Byron and..." : "Nick's...";
  
  if (wait_progress < wait_time) {
    wait_progress++;   // don't change anything yet
  } else {   // time to move the points
    wait_progress = 0;
    
    // - = - = - = - = - = - =
//    int indexToChange = random(0, line2Str.length()-1);
//    line2Str.setCharAt(indexToChange, toupper(letters[random(0, 35)]));

  }
}

void loop() {
  Usb.Task();
  
  // read the state of the pushbutton value:
  int tmpVal = digitalRead(SWITCH_PIN_1);
  if (tmpVal != btn1State) { btn1State = tmpVal; Serial.println("BTN 1 = " + String(tmpVal)); }

  tmpVal = digitalRead(SWITCH_PIN_2);
  if (tmpVal != btn2State) { btn2State = tmpVal; Serial.println("BTN 2 = " + String(tmpVal)); }

  // -------------------
  // Page buffer mode (Picture Loop)
  
  // ==============================

  disp1.firstPage();
  do {
    drawOnDisplay(disp1, true);
    
  } while ( disp1.nextPage() );

  update();
  
  // ==============================

  disp2.firstPage();
  do {
    drawOnDisplay(disp2, false);
    
  } while ( disp2.nextPage() );

  update();

  // ==============================

}

// ---------------------

void KeyEvents::KeyStateChanged(char c,  bool isDown) {
  Serial.print(c);
  Serial.print(" ");
  Serial.println((isDown ? "DN":"UP"));

  if (isDown) {
    line2Str.setCharAt(curCharIndex, toupper(c));
    curCharIndex = (curCharIndex + 1) % line2Str.length();
  }
}

void KeyEvents::ControlKeyStateChanged(MODIFIERKEYS beforeMod, MODIFIERKEYS afterMod) {
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
}

// ---------------------
