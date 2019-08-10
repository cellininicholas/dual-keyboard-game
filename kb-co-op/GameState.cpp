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
 P1 Key Mappings 
  ---------------
    Y->T H->G N->B
    U->Y J->H M->N
    I->U K->J ,->M
    O->I L->K .->,
    P->O ;->L /->.
    [->P
 */
int shiftedUpperCaseCharForPlayer1(int inChar) {
  switch(inChar) {
    case 89: return 84; // Y->T
    case 72: return 71; // H->G
    case 78: return 66; // N->B
    case 85: return 89; // U->Y
    case 74: return 72; // J->H
    case 77: return 78; // M->N
    case 73: return 85; // I->U
    case 75: return 74; // K->J
    case 44: return 77; // ,->M
    case 79: return 73; // O->I
    case 76: return 75; // L->K
    case 46: return 44; // .->,
    case 80: return 79; // P->O
    case 59: return 76; // ;->L
    case 47: return 46; // /->.
    case 91: return 80; // [->P
    default: return 46; // .
  }
}

/*
Player 1 Keys
-------------
 Y   H   N   U   J   M   I   K   O   L   P   [   ;   ,   /
 ,   /   ;   H   I   J   K   L   M   N   O   P   U   Y   [   (ordered)
044 047 059 072 073 074 075 076 077 078 079 080 085 089 091
44(1), 47(1), 59(1), 72-80(9), 85(1), 89(1), 91(1)



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
    if ((uc < 65 || uc > 90) && uc != 44 && uc != 46 && uc != 47 && uc != 59 && uc != 91) { return; } // Check if A-Z ( .,/;[ )
    bool isP1Char = !((uc>64 && uc<72) || (uc>80 && uc<85) || (uc>85 && uc<89) || uc==90); // NOT P2 keys

    if (isP1Char) {
      uc = shiftedUpperCaseCharForPlayer1(uc);
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
