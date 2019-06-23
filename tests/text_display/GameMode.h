#if !defined(__GAMEMODE_H__)
#define __GAMEMODE_H__
#include "GameView.h"

class GameMode {
  private:
    

  protected:
    virtual void CommonInit();

    GameView **views;
    GameView *currentView;

  public:
  
    void draw(U8G2_ST7920_128X64_1_SW_SPI *disp, bool isDisp1);

    // Initialiser
    GameMode();
    // GameMode(bool btn1On, bool btn2On);
  
};

#endif // __GAMEMODE_H__
