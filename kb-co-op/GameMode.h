#if !defined(__GAMEMODE_H__)
#define __GAMEMODE_H__
#include "GameView.h"

// - - - - - - - - - - -
// GameModeDelegate interface declared inside GameView.h
// - - - - - - - - - - -

class GameMode {
  private:    

  protected:
    virtual void CommonInit();
    GameModeDelegate *modeDelegate;

    GameView **views;
    GameView *currentView;

  public:
  
    virtual void keyPressed(char c, int upperChar, bool isP1);
    void draw(U8G2_ST7920_128X64_1_SW_SPI *disp, bool isDisp1);

    // Initialiser
    GameMode(GameModeDelegate *del);
    // GameMode(bool btn1On, bool btn2On);
  
};

#endif // __GAMEMODE_H__
