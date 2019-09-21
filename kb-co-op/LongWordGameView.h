#if !defined(__LWGAMEVIEW_H__)
#define __LWGAMEVIEW_H__

#include "GameView.h"

// class LongWordDelegate {
//   public:
//   virtual char* getCurrentWord();
//   virtual byte getCurrentWordMask();
// };

class LongWordGameView : public GameView {
  private:
    // LongWordDelegate *longWordDelegate;

  protected:
    void CommonInit() override;
    

  public:
  
    void keyPressed(char c, int upperChar, bool isP1) override;
    void draw(U8G2_ST7920_128X64_1_SW_SPI *disp, bool isDisp1) override;

    // Initialiser
    LongWordGameView(GameModeDelegate *del);
    // LongWordGameView(bool btn1On, bool btn2On);

    void setLongWordDelegate(LongWordDelegate *newDel);
};

#endif // __LWGAMEVIEW_H__
