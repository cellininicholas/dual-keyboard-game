#include <U8g2lib.h>

// pin definitions - change these to match your wiring
const int D1_PIN_E = 13, D1_PIN_RW = 12, D1_PIN_RS = 11;
//const int D1_PIN_RW = 11;
//const int D1_PIN_RS = 10;

// https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#constructor-name
// Prefix:     U8G2
// Display:    ST7920
// DispName:   128X64
// BufferSize: 1 (1,2 or F (full frame buffer))
// Commun:     SW_SPI (Software emulated, SPI (Serial))

//                           ...(rotation, clock, data, cs [, reset])
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, D1_PIN_E, D1_PIN_RW, D1_PIN_RS);

const char letters[36] = {'a', 'b', 'c', 'd', 'e', 'f','g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
String line1Str = "BYRON'S";
String line2Str = "FACE";
bool curLine = true;

// how long to spend at each step - higher wait_time = slower rotation
const int wait_time = 16;
int wait_progress = 0;

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
}

void loop() {
  // -------------------
  // Page buffer mode (Picture Loop)
  
  u8g2.firstPage();
  do {
//    u8g2.drawLine(c1, r1, c2, r2);   // draw the line from (c1, r1) to (c2, r2)
//    u8g2.setFont(u8g2_font_ncenB14_tr);

    // SetFont
    // ----------
    // tx - Transparent gylphs with variable width
    // mx - Monospace/fixed width glyphs
    // hx - Glyphs with variable width and common height
    // 8x - Monospace/fixed width glyphs in a 8x8 box

//    u8g2.setFont(u8g2_font_helvR24_te); // tf, tr, tn, te?
    u8g2.setFont(u8g2_font_helvB18_tf); // tf, tr, tn, te?
    u8g2.setFont(u8g2_font_tenstamps_mu);
    u8g2.setFontPosTop();
    
    u8g2.drawStr(4,2,line1Str.c_str());

//    u8g2.setFont(u8g2_font_crox5tb_tf); // mf, mr
    u8g2.setFont(u8g2_font_tenstamps_mu); // mf, mr
    u8g2.drawStr(4,23,line2Str.c_str());

    u8g2.drawStr(4,44,"ON DISP.");
    
  } while ( u8g2.nextPage() );

  if (wait_progress < wait_time) {
    wait_progress++;   // don't change anything yet
  } else {   // time to move the points
    wait_progress = 0;
    
    int indexToChange = random(0, (curLine ? line1Str : line2Str).length()-1);
    (curLine ? line1Str : line2Str).setCharAt(indexToChange, toupper(letters[random(0, 35)]));
    curLine = !curLine;

  }

  
}
