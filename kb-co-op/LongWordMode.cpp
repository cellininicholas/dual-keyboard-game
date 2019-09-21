#include "LongWordMode.h"
// #include <ctype.h>

void LongWordMode::CommonInit() {
  views = new GameView*[1];
  views[0] = new LongWordGameView(modeDelegate);
  currentView = views[0];

  
}

void LongWordMode::SetupDelegates() {
  LongWordGameView *view = (LongWordGameView *)views[0];
  view->setLongWordDelegate(this);
}

LongWordMode::LongWordMode(GameModeDelegate *del) : GameMode(del) {
  CommonInit();
  
}

void LongWordMode::ResetGameMode() {
  getNewRandomWord();
  modeDelegate->setDisplayDirty(true);
  modeDelegate->setDisplayDirty(false);
}

void LongWordMode::getNewRandomWord() {
  const char* randWord = modeDelegate->getRandBalanced8CharWord();
  if (randWord != NULL) {
    strcpy(currentWord, randWord);
  } else {
    strcpy(currentWord, "?UNKNOWN");
  }
  currentWord[8] = '\0';
  Serial.print("LongWordMode::getNewRandomWord. currentWord: "); Serial.println(currentWord);
}

void LongWordMode::keyPressed(char c, int upperChar, bool isP1) {
  GameMode::keyPressed(c, upperChar, isP1); // Call base method

  if (modeDelegate == NULL) { return; }
  modeDelegate->setDisplayDirty(isP1);
}

char* LongWordMode::getCurrentWord() {
  return currentWord;
}

byte LongWordMode::getCurrentWordMask() {
  return 170;
}

// GameView::GameView(bool btn1On, bool btn2On) : _btn1State(btn1On), _btn2State(btn2On) {
//   CommonInit();
// }

// --------------------
