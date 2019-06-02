#include "GameState.h"

GameState::GameState() {
  _player1CharBuffer = new char[32];
  _player2CharBuffer = new char[32];
}

GameState::GameState(bool btn1On, bool btn2On) : _btn1State(btn1On), _btn2State(btn2On) {
  //  Serial.println("GameState Init");
  _player1CharBuffer = new char[32];
  _player2CharBuffer = new char[32];
}

void GameState::keyStateChanged(char c,  bool isDown) {
  if (isDown) {
//    line2Str.setCharAt(curCharIndex, toupper(c));
    _curCharIndex = (_curCharIndex + 1) % 32;
  }
}

void GameState::update(bool btn1On, bool btn2On) {

  // read the state of the pushbutton value:
  if (btn1On != _btn1State) { _btn1State = btn1On; _disp1DatDirty = true; }
  if (btn2On != _btn2State) { _btn2State = btn2On; _disp2DatDirty = true; }

  
  bool disp1Update = _wait_progress % 2 == 1;
//  line1Str = disp1Update ? "Byron and..." : "Nick's...";
  
  if (_wait_progress < wait_time) {
    _wait_progress++;   // don't change anything yet
  } else {   // time to move the points
    _wait_progress = 0;
    
    _disp1DatDirty = true;
    _disp2DatDirty = true;
    
    // - = - = - = - = - = - =
//    int indexToChange = random(0, line2Str.length()-1);
//    line2Str.setCharAt(indexToChange, toupper(letters[random(0, 35)]));

  }
}
