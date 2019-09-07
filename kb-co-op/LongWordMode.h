#if !defined(__LONGWORDMODE_H__)
#define __LONGWORDMODE_H__
#include "LongWordGameView.h"
#include "GameMode.h"

class LongWordMode : public GameMode {
  private:
    const int LONG_WORD_SIZE = 32;
    const int HISTORY_SIZE = 32;

    // A bitmask to illustrate which player is assigned which character in the current word
    byte characterSplit;
    // char *currentWord;
    // int wordIndexHistory[];

  protected:
    void CommonInit() override;

  public:

    void keyPressed(char c, int upperChar, bool isP1) override;

    // Initialiser
    LongWordMode(GameModeDelegate *del);
    // LongWordMode(bool btn1On, bool btn2On);
  
};

#endif // __LONGWORDMODE_H__
