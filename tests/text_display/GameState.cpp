#include "GameState.h"
#include <ctype.h>

void GameState::InitCharBuffers() {
  _player1CharBuffer = new char[CHAR_BUFFER_SIZE];
  _player2CharBuffer = new char[CHAR_BUFFER_SIZE];
  _player1CharWindow = new char[CHAR_WINDOW_SIZE];
  _player2CharWindow = new char[CHAR_WINDOW_SIZE];
  for (int i=0; i<CHAR_BUFFER_SIZE; ++i) {
    _player1CharBuffer[i] = '*';
    _player2CharBuffer[i] = '*';
    if (i<CHAR_WINDOW_SIZE) {
      _player1CharWindow[i] = ' ';
      _player2CharWindow[i] = ' ';
    }
  }
}

GameState::GameState() {
  InitCharBuffers();
}

GameState::GameState(bool btn1On, bool btn2On) : _btn1State(btn1On), _btn2State(btn2On) {
  //  Serial.println("GameState Init");
  InitCharBuffers();
}

// --------------------
char* GameState::updateCharWindow(char *buf, char *window, int charIndex) {
  for (int i=0; i<CHAR_WINDOW_SIZE; ++i) {
    int bufIndex = i+1 + charIndex - CHAR_WINDOW_SIZE;
    if (bufIndex < 0) { bufIndex += CHAR_BUFFER_SIZE; }
    window[i] = buf[bufIndex];
  }
}

// TODO: take parameters, use _charIndexP1 and return a copy of the buffer
char* GameState::player1Str() {
  // V- Function below is called from GameState::displayDrawingStateChanged()
//  updateCharWindow(_player1CharBuffer, _player1CharWindow, _charIndexP1);
  
  return _player1CharWindow;
}
char* GameState::player2Str() {
  // V- Function below is called from GameState::displayDrawingStateChanged()
//  updateCharWindow(_player2CharBuffer, _player2CharWindow, _charIndexP2);
  
  return _player1CharWindow;
}
// --------------------

void GameState::keyStateChanged(char c,  bool isDown) {
  if (isDown) {
//    line2Str.setCharAt(curCharIndex, toupper(c));
    int nextIndexP1 = (_charIndexP1 + 1) % CHAR_BUFFER_SIZE;
    int nextIndexP2 = (_charIndexP2 + 1) % CHAR_BUFFER_SIZE;
    
    _player1CharBuffer[nextIndexP1] = toupper(c);
    _player2CharBuffer[nextIndexP2] = toupper(c);
    _charIndexP1 = nextIndexP1;
    _charIndexP2 = nextIndexP2;

    _disp1DatDirty = true;
    _disp2DatDirty = true;
  }
}

void GameState::displayDrawingStateChanged(bool disp1, bool isDrawing) {
  if (disp1) {
    if (!_disp1IsDrawing && isDrawing) { updateCharWindow(_player1CharBuffer, _player1CharWindow, _charIndexP1); }
    _disp1IsDrawing = isDrawing;
  } else {
    if (!_disp2IsDrawing && isDrawing) { updateCharWindow(_player2CharBuffer, _player2CharWindow, _charIndexP2); }
    _disp2IsDrawing = isDrawing;
  }
}

void GameState::update() {
  bool disp1Update = _wait_progress % 2 == 1;
//  line1Str = disp1Update ? "Byron and..." : "Nick's...";
  
  if (_wait_progress < wait_time) {
    _wait_progress++;   // don't change anything yet
  } else {   // time to move the points
    _wait_progress = 0;
    
//    _disp1DatDirty = true;
//    _disp2DatDirty = true;
    
    // - = - = - = - = - = - =
//    int indexToChange = random(0, line2Str.length()-1);
//    line2Str.setCharAt(indexToChange, toupper(letters[random(0, 35)]));

  }
}

void GameState::update(bool btn1On, bool btn2On) {

  // read the state of the pushbutton value:
  if (btn1On != _btn1State) { _btn1State = btn1On; _disp1DatDirty = true; }
  if (btn2On != _btn2State) { _btn2State = btn2On; _disp2DatDirty = true; }

  update();
}
