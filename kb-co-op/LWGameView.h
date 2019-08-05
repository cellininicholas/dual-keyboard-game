#if !defined(__LWGAMEVIEW_H__)
#define __LWGAMEVIEW_H__

#include "GameView.h"

class LWGameView : public GameView {
  private:
    

  protected:
    void CommonInit() override;
    

  public:
  
    void draw(U8G2_ST7920_128X64_1_SW_SPI *disp, bool isDisp1) override;

    // Initialiser
    LWGameView(GameModeDelegate *del);
    // LWGameView(bool btn1On, bool btn2On);
  
};

#endif // __LWGAMEVIEW_H__
