  #include "GameView.h"
// #include <ctype.h>

void GameView::CommonInit() {
  
}

GameView::GameView(GameModeDelegate *del) : viewDelegate((GameViewDelegate *)del) {
  CommonInit();
  timeStrBuf = new char[3];
}

void GameView::keyPressed(char c, int upperChar, bool isP1) {

}

void GameView::drawNHearts(U8G2_ST7920_128X64_1_SW_SPI *disp, int heartCount) {
  drawNHeartsHeight16(disp, heartCount);
}
void GameView::drawNHeartsHeight8(U8G2_ST7920_128X64_1_SW_SPI *disp, int heartCount) {
  // disp->setDrawColor(1);
  disp->setFontPosCenter();
  disp->setFont(u8g2_font_open_iconic_human_1x_t);
  for (int i=0; i<heartCount; ++i) {
    disp->drawGlyph(5+(i*10), 5, 0x0042);
  }
}
void GameView::drawNHeartsHeight16(U8G2_ST7920_128X64_1_SW_SPI *disp, int heartCount) {
  // disp->setDrawColor(1);
  disp->setFontPosCenter();
  disp->setFont(u8g2_font_open_iconic_human_2x_t);
  for (int i=0; i<heartCount; ++i) {
    disp->drawGlyph(2+(i*18), 7, 0x0042);
  }
}

void GameView::drawTimeCounter(U8G2_ST7920_128X64_1_SW_SPI *disp, int secsRemaining) {
  sprintf(timeStrBuf, "%ds", secsRemaining);
  disp->setFontPosCenter();
  
  disp->setFont(u8g2_font_courB10_tr);
  disp->drawStr(2,56,timeStrBuf); //timeStrBuf);
  
//  disp->setFont(u8g2_font_helvB12_te);
//  disp->drawStr(3,56,timeStrBuf); //timeStrBuf);
  
  disp->setFont(u8g2_font_open_iconic_app_2x_t);
//  disp->drawGlyph(2, 54, 0x0045);
//  disp->drawGlyph(23, 54, 0x0045);
  disp->drawGlyph(22, 54, 0x0045);
}

// FONTS
// https://github.com/olikraus/u8g2/wiki/fntgrpgeoff#tenstamps
// https://github.com/olikraus/u8g2/wiki/fntgrpgeoff#tenthinnerguys
// FONT MODE
// https://github.com/olikraus/u8g2/wiki/u8g2reference#setfontmode
void GameView::draw(U8G2_ST7920_128X64_1_SW_SPI *disp, bool isDisp1) {
  // extern const uint8_t u8g2_font_tenstamps_mu[] U8G2_FONT_SECTION("u8g2_font_tenstamps_mu");
  disp->setDrawColor(1);
  disp->setFontPosTop();
  disp->setFont(u8g2_font_tenstamps_mu); // height=15,mu=monospace,uppercase
  disp->drawStr(4,22,"GV::DRAW" );

  if (!isDisp1) {
    drawNHeartsHeight8(disp, 12);
  } else {
    drawNHearts(disp, 7);
  }

  drawTimeCounter(disp, 4); // secsRemaining=8

  // disp->setFont(u8g2_font_open_iconic_human_2x_t);
  // disp->setDrawColor(1);
  // disp.drawGlyph(1, 1, 0x0042);
  // // disp->drawStr(1,1,"B  B  B"); // 66=heart='B'=0x0042
  // disp->setDrawColor(0);
  // disp->drawStr(72,4,"B  B");

  // disp->setFont(u8g2_font_open_iconic_human_2x_t); // height=16
  // disp->setFont(u8g2_font_open_iconic_human_4x_t); // height=32
  // disp->setFont(u8g2_font_open_iconic_human_6x_t); // height=48
  // disp->setFont(u8g2_font_open_iconic_human_8x_t); // height=64

  // disp->setFont(u8g2_font_open_iconic_arrow_4x_t); // height=32
  // disp->setFont(u8g2_font_open_iconic_check_4x_t); // height=32

  // disp->setFont(u8g2_font_7Segments_26x42_mn); // height=42
  // disp->setFont(u8g2_font_iconquadpix_m_all); // height=42
  
  
  
  
}

// GameView::GameView(bool btn1On, bool btn2On) : _btn1State(btn1On), _btn2State(btn2On) {
//   CommonInit();
// }

// --------------------
