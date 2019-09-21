#if !defined(__LONGWORDMODE_H__)
#define __LONGWORDMODE_H__
#include "LongWordGameView.h"
#include "GameMode.h"

class LongWordMode : public GameMode, LongWordDelegate {
  private:

  protected:
    void CommonInit() override;

  public:

    // -------------------------------
    // LongWordDelegate
    char* getCurrentWord();
    byte getCurrentWordMask();

    // -------------------------------
    void ResetGameMode() override;
    void getNewRandomWord();

    // -------------------------------
    void keyPressed(char c, int upperChar, bool isP1) override;

    // Initialiser
    LongWordMode(GameModeDelegate *del);
    // LongWordMode(bool btn1On, bool btn2On);
    void SetupDelegates() override;
  
};

#endif // __LONGWORDMODE_H__
