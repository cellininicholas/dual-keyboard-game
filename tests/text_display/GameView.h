#if !defined(__GAMEVIEW_H__)
#define __GAMEVIEW_H__

#include <U8g2lib.h>

class GameView {
  private:
    

  protected:
    void CommonInit();
    void drawNHearts(U8G2_ST7920_128X64_1_SW_SPI *disp, int heartCount);
    void drawNHeartsHeight8(U8G2_ST7920_128X64_1_SW_SPI *disp, int heartCount);
    void drawNHeartsHeight16(U8G2_ST7920_128X64_1_SW_SPI *disp, int heartCount);
    void drawTimeCounter(U8G2_ST7920_128X64_1_SW_SPI *disp, int secsRemaining);
    

  public:
  
    void draw(U8G2_ST7920_128X64_1_SW_SPI *disp, bool isDisp1);

    // Initialiser
    GameView();
    // GameView(bool btn1On, bool btn2On);
  
};

#endif // __GAMEVIEW_H__
