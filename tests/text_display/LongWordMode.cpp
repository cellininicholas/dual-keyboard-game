#include "LongWordMode.h"
// #include <ctype.h>

void LongWordMode::CommonInit() {
  views = new GameView*[1];
  views[0] = new LWGameView();
  currentView = views[0];
}

LongWordMode::LongWordMode() {
  CommonInit();
}

// GameView::GameView(bool btn1On, bool btn2On) : _btn1State(btn1On), _btn2State(btn2On) {
//   CommonInit();
// }

// --------------------
