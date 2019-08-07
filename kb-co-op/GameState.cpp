#include "GameState.h"
#include <ctype.h>
#include "LongWordMode.h"

void GameState::setDisplayDirty(bool isDis1) {
  if (isDis1) { _disp1DatDirty = true; } 
  else        { _disp2DatDirty = true; }
}

char * GameState::getCharacterBuffer(bool isP1) {
  return isP1 ? _player1CharBuffer : _player2CharBuffer;
}
char * GameState::getCharacterWindow(bool isP1) {
  return isP1 ? _player1CharWindow : _player2CharWindow;
}

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

void GameState::SetupGameModes() {
  gameModes = new GameMode*[1];
  gameModes[0] = new LongWordMode(this);
  currentGameMode = gameModes[0];
}

void GameState::draw(U8G2_ST7920_128X64_1_SW_SPI *disp, bool isDisp1) {
  if (currentGameMode == NULL) { return; }

  currentGameMode->draw(disp, isDisp1);
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

/*
Player 1 Keys
-------------
 T   G   B   Y   H   N   U   J   M   I   K   O   L   P
 B   G   H   I   J   K   L   M   N   O   P   T   U   Y   (ordered)
066 071 072 073 074 075 076 077 078 079 080 084 085 089
66(1), 71-80(10), 84-85(2), 89(1)

Player 2 Keys
-------------
 T   G   B   Q   A   Z   W   S   X   E   D   C   R   F   V   
 A   B   C   D   E   F   G   Q   R   S   T   V   W   X   Z
065 066 067 068 069 070 071 081 082 083 084 086 087 088 090
65-71(7), 81-84(4), 86-88(3), 90(1)
 */
void GameState::keyStateChanged(char c,  bool isDown) {
  
  if (isDown) {
    int uc = toupper(c);
    if (uc < 65 || uc > 90) { return; } // Check if A-Z
    bool isP1Char = (uc>70 && uc<81) || (uc>83 && uc<86) || uc==66 || uc==89;

    if (isP1Char) {
      int nextIndexP1 = (_charIndexP1 + 1) % CHAR_BUFFER_SIZE;
      _player1CharBuffer[nextIndexP1] = uc;
      _charIndexP1 = nextIndexP1;
      // _disp1DatDirty = true;
    } else {
      int nextIndexP2 = (_charIndexP2 + 1) % CHAR_BUFFER_SIZE;
      _player2CharBuffer[nextIndexP2] = uc;
      _charIndexP2 = nextIndexP2;
      // _disp2DatDirty = true;
    }
    if (currentGameMode == NULL) { return; }
    currentGameMode->keyPressed(c, uc, isP1Char);
  }
}

void GameState::displayDrawingStateChanged(bool disp1, bool isDrawing) {
  if (disp1) {
    if (!_disp1IsDrawing && isDrawing) { updateCharWindow(_player1CharBuffer, _player1CharWindow, _charIndexP1); }
    _disp1IsDrawing = isDrawing;
    if (isDrawing) { _disp1DatDirty = false; }
  } else {
    if (!_disp2IsDrawing && isDrawing) { updateCharWindow(_player2CharBuffer, _player2CharWindow, _charIndexP2); }
    _disp2IsDrawing = isDrawing;
    if (isDrawing) { _disp2DatDirty = false; }
  }
}

void GameState::update() {

}

void GameState::update(bool btn1On, bool btn2On) {

  // read the state of the pushbutton value:
//  if (btn1On != _btn1State) { _btn1State = btn1On; _disp1DatDirty = true; }
//  if (btn2On != _btn2State) { _btn2State = btn2On; _disp2DatDirty = true; }

  update();
}
