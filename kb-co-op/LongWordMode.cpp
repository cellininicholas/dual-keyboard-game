#include "LongWordMode.h"
// #include <ctype.h>

void LongWordMode::CommonInit() {
  views = new GameView*[1];
  views[0] = new LWGameView(modeDelegate);
  currentView = views[0];
}

LongWordMode::LongWordMode(GameModeDelegate *del) : GameMode(del) {
  CommonInit();
  
}

void LongWordMode::keyPressed(char c, int upperChar, bool isP1) {
  GameMode::keyPressed(c, upperChar, isP1); // Call base method

  if (modeDelegate == NULL) { return; }
  modeDelegate->setDisplayDirty(isP1);
}

// GameView::GameView(bool btn1On, bool btn2On) : _btn1State(btn1On), _btn2State(btn2On) {
//   CommonInit();
// }

// --------------------
