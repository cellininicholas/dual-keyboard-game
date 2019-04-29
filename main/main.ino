#include <U8g2lib.h>

// pin definitions - change these to match your wiring
// E =  Green
// RW = Yellow (-> Blue for 1 display)
// RS = Orange
const int D1_PIN_E = 13, D1_PIN_RW = 12, D1_PIN_RS = 11;
const int D2_PIN_E = 7, D2_PIN_RW = 6, D2_PIN_RS = 5;

// https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#constructor-name
// Prefix:     U8G2
// Display:    ST7920
// DispName:   128X64
// BufferSize: 1 (1,2 or F (full frame buffer))
// Commun:     SW_SPI (Software emulated, SPI (Serial))

//                           ...(rotation, clock, data, cs [, reset])
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, D1_PIN_E, D1_PIN_RW, D1_PIN_RS);


void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  u8g2.firstPage();
  do {
    u8g2.drawLine(c1, r1, c2, r2);   // draw the line from (c1, r1) to (c2, r2)
  } while ( u8g2.nextPage() );

  
}
