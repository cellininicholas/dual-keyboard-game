#include <U8g2lib.h>
//#include <usbhub.h>

#include "HIDKeyboardParser.h"
#include "GameState.h"

// pin definitions - change these to match your wiring
// E =  Green
// RW = Yellow (-> Blue for 1 display)
// RS = Orange
const int D1_PIN_E = 7, D1_PIN_RW = 8, D1_PIN_RS = 5;
const int D2_PIN_E = 3, D2_PIN_RW = 4, D2_PIN_RS = 6;

const int SWITCH_PIN_1 = 9, SWITCH_PIN_2 = 10;

// ------------------------------
// USB KEYBOARD
USB     Usb;
//USBHub     Hub(&Usb);
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
String line1Str = "Nick's";
//bool curLine = true;


// =========
GameState game;
// =========

void setup() {

  // initialize the pushbutton pins as an inputs:
  // pinMode(SWITCH_PIN_1, INPUT);
  // pinMode(SWITCH_PIN_2, INPUT);
  game.SetupGameModes();
  game.update();
//  game = GameState(digitalRead(SWITCH_PIN_1), digitalRead(SWITCH_PIN_2));

  // Displays setup
  disp1.begin();
  disp2.begin();

  // Keyboard setup
 delay(1000);
 Serial.begin(115200);
 while (!Serial) yield();
  
  Serial.println("Keyboard Setup Start...");
  if (Usb.Init() == -1) { 
    Serial.println("USB OSC did not start.");
  }
  delay( 200 );
  HidKeyboard.SetReportParser(0, &Prs);
}

// void drawOnDisplay(U8G2_ST7920_128X64_1_SW_SPI disp, bool isDisp1) {
//   //    u8g2.drawLine(c1, r1, c2, r2);   // draw the line from (c1, r1) to (c2, r2)
// //    u8g2.setFont(u8g2_font_ncenB14_tr);

//     // SetFont
//     // ----------
//     // The 2 letters are <purpose><char set>
//     // PURPOSE
//     // t_ - Transparent gylphs with variable width
//     // m_ - Monospace/fixed width glyphs
//     // h_ - Glyphs with variable width and common height
//     // 8_ - Monospace/fixed width glyphs in a 8x8 box
//     // CHAR SET
//     // _f - The font includes up to 256 glyphs.
//     // _r - Only glyphs on the range of the ASCII codes 32 to 127 are included in the font.
//     // _u - Only glyphs on the range of the ASCII codes 32 to 95 (uppercase chars) are included in the font.
//     // _n - Only numbers and extra glyphs for writing date and time strings are included in the font.

//     // Our fonts:
//     // https://github.com/olikraus/u8g2/wiki/fntgrpgeoff#tenstamps
//     // https://github.com/olikraus/u8g2/wiki/fntgrpgeoff#tenthinnerguys
//     // FONT MODE
//     // https://github.com/olikraus/u8g2/wiki/u8g2reference#setfontmode

// //    u8g2.setFont(u8g2_font_helvR24_te); // tf, tr, tn, te?
// //    u8g2.setFont(u8g2_font_helvB18_tf); // tf, tr, tn, te?
//     disp.setFont(u8g2_font_tenthinnerguys_tf);
//     disp.setFontPosTop();
    
// //    disp.drawStr(4,7,line1Str.c_str());
//     disp.drawStr(4,7, !isDisp1 ? "The Best..." : "...Typing Game");
    

// //    u8g2.setFont(u8g2_font_crox5tb_tf); // mf, mr
//     disp.setFont(u8g2_font_tenstamps_mu); // mu=monospace,uppercase
// //    disp.drawStr(4,22,game.line2Str.c_str());
// //    disp.drawStr(4,22,"FIX ME");
//     disp.drawStr(4,22,isDisp1 ? game.player1Str() : game.player2Str() );
// //    disp.drawStr(4,22,game.player1Str());

//     disp.setFont(u8g2_font_tenthinnerguys_tf);
//     disp.drawStr(4,45,"On Display for all");

// //    disp.setFont(u8g2_font_roentgen_nbp_tf);
// //    disp.drawStr(109,0,String(wait_progress).c_str());

// //    disp.setFont(u8g2_font_roentgen_nbp_tf);
// //    disp.drawStr(81,56, ("BTN="+String(isDisp1 ? game.btn2State() : game.btn1State())).c_str());
// }

void loop() {
  
  Usb.Task();

  // -------------------
  // Page buffer mode (Picture Loop)
  
  // ==============================
  game.update(digitalRead(SWITCH_PIN_1), digitalRead(SWITCH_PIN_2));

  // Never Redraw both displays in the same loop!
  // Let's reserve time for the Usb.Task() to run
  // It's more important that our data is correct, rather than the displays are UpToDate
  // - - - - - - - - - - -
  // TODO: Try different methods to draw the displays...
  
  if (game.shouldRedrawDisp1()) {
    Serial.println("Draw Display 1");
    game.displayDrawingStateChanged(true, true);
    disp1.firstPage();
    do {
      Usb.Task();
      // drawOnDisplay(disp1, true);
      game.draw(&disp1, true);
    } while ( disp1.nextPage() );
    game.displayDrawingStateChanged(true, false);
  }

  // TODO: If we are running a Usb.Task() during the display draw loop, the data could change, resulting in inconsistent data displayed
  //       We need to store the data while the displays are updating
  
  if (game.shouldRedrawDisp2()) {
    Serial.println("Draw Display 2");
    game.displayDrawingStateChanged(false, true);
    disp2.firstPage();
    do {
      Usb.Task();
      // drawOnDisplay(disp2, false);
      game.draw(&disp2, false);
    } while ( disp2.nextPage() ); 
    game.displayDrawingStateChanged(false, false);
  }
}

// ---------------------

void KeyEvents::KeyStateChanged(char c,  bool isDown) {
//  Serial.print(c);
//  Serial.print(" ");
//  Serial.println((isDown ? "DN":"UP"));
//  int upperC = toupper(c);
//  Serial.print(upperC);
//  Serial.println(c);
  game.keyStateChanged(c, isDown);
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
