#if !defined(__LONGWORDMODE_H__)
#define __LONGWORDMODE_H__
#include "LWGameView.h"
#include "GameMode.h"

class LongWordMode : public GameMode {
  private:
    

  protected:
    void CommonInit() override;

  public:

    void keyPressed(char c, int upperChar, bool isP1) override;

    // Initialiser
    LongWordMode(GameModeDelegate *del);
    // LongWordMode(bool btn1On, bool btn2On);
  
};

#endif // __LONGWORDMODE_H__
