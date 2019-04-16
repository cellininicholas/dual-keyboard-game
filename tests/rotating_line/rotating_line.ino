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
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, D1_PIN_E, D1_PIN_RW, D1_PIN_RS);


// initialize coordinates - row/col for point 1 and 2
int r1 = 0;
int c1 = 32;
int r2 = 64;
int c2 = 96;
// how long to spend at each step - higher wait_time = slower rotation
const int wait_time = 0;
int wait_progress = 0;


void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
}

void loop() {
  // -------------------
  // FULLSCREEN
  u8g2.clearBuffer();
  u8g2.drawLine(c1, r1, c2, r2);   // draw the line from (c1, r1) to (c2, r2)
  u8g2.sendBuffer();

  if (wait_progress < wait_time) {
    wait_progress++;   // don't change anything yet
  } else {   // time to move the points
    wait_progress = 0;

    // these blocks could probably be more elegant
    // point 1
    if (r1 == 0 && c1 < 96)
      c1++;
    else if (r1 == 64 && c1 > 32)
      c1--;
    else if (c1 == 32 && r1 > 0)
      r1--;
    else if (c1 == 96 && r1 < 64)
      r1++;

    // point 2
    if (r2 == 0 && c2 < 96)
      c2++;
    else if (r2 == 64 && c2 > 32)
      c2--;
    else if (c2 == 32 && r2 > 0)
      r2--;
    else if (c2 == 96 && r2 < 64)
      r2++;
  }

  // -------------------
  // Page buffer mode (Picture Loop)
  
//  u8g2.firstPage();
//  do {
//    u8g2.drawLine(c1, r1, c2, r2);   // draw the line from (c1, r1) to (c2, r2)
//  } while ( u8g2.nextPage() );
//
//  if (wait_progress < wait_time) {
//    wait_progress++;   // don't change anything yet
//  } else {   // time to move the points
//    wait_progress = 0;
//
//    // these blocks could probably be more elegant
//    // point 1
//    if (r1 == 0 && c1 < 96)
//      c1++;
//    else if (r1 == 64 && c1 > 32)
//      c1--;
//    else if (c1 == 32 && r1 > 0)
//      r1--;
//    else if (c1 == 96 && r1 < 64)
//      r1++;
//
//    // point 2
//    if (r2 == 0 && c2 < 96)
//      c2++;
//    else if (r2 == 64 && c2 > 32)
//      c2--;
//    else if (c2 == 32 && r2 > 0)
//      r2--;
//    else if (c2 == 96 && r2 < 64)
//      r2++;
//  }
}
