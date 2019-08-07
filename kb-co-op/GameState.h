#if !defined(__GAMESTATE_H__)
#define __GAMESTATE_H__

#include "GameMode.h"

// - - - - - - - - - - -
// GameViewDelegate implements GameModeDelegate
// - - - - - - - - - - -

class GameState: public GameViewDelegate {
  private:
    GameMode **gameModes;
    GameMode *currentGameMode;

    const int CHAR_BUFFER_SIZE = 32;
    const int CHAR_WINDOW_SIZE = 8;
  
    // HARDWARE
    int _btn1State, _btn2State;
  
    // -----------
    bool _disp1IsDrawing = false;
    bool _disp2IsDrawing = false;
    bool _disp1DatDirty = true;
    bool _disp2DatDirty = true;
  
    char *_player1CharBuffer;
    char *_player2CharBuffer;
    int _charIndexP1 = 0;
    int _charIndexP2 = 0;
    // The character window is the char* that will be returned...
    // it will point to the last N characters in the right order
    char *_player1CharWindow;
    char *_player2CharWindow;
  
    // how long to spend at each step - higher wait_time = slower rotation
    const int wait_time = 99;
    int _wait_progress = 0;
//    int _curCharIndex = 0;

    void InitCharBuffers();
    char* updateCharWindow(char *buf, char *window, int charIndex);

    // GameViewDelegate
    void setDisplayDirty(bool isDis1);
    char *getCharacterBuffer(bool isP1);
    char *getCharacterWindow(bool isP1);

  protected:

  public:
  
    // Initialiser
    GameState();
    GameState(bool btn1On, bool btn2On);
    void SetupGameModes();

    void draw(U8G2_ST7920_128X64_1_SW_SPI *disp, bool isDisp1);

    bool shouldRedrawDisp1() { return _disp1DatDirty; }
    bool shouldRedrawDisp2() { return _disp2DatDirty; }
//    bool disp1WasDrawn() { _disp1DatDirty = false; }
//    bool disp2WasDrawn() { _disp2DatDirty = false; }

    void update(bool btn1On, bool btn2On);
    void update();
    
    void keyStateChanged(char c,  bool isDown);
    void displayDrawingStateChanged(bool disp1, bool isDrawing);

    char *player1Str();
    char *player2Str();
    bool btn1State() { return _btn1State; }
    bool btn2State() { return _btn2State; }
  
};

#endif // __GAMESTATE_H__
