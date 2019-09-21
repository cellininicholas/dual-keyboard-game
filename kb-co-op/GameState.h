#if !defined(__GAMESTATE_H__)
#define __GAMESTATE_H__

#include "Words.h"
#include "GameMode.h"
#include "pRNG.h"

// - - - - - - - - - - -
// GameViewDelegate implements GameModeDelegate
// - - - - - - - - - - -

class GameState: public GameViewDelegate {
  private:
    const int CHAR_BUFFER_SIZE = 16;
    const int CHAR_WINDOW_SIZE = 8;
    const int GAME_STR_SIZE = 64;
    const int HISTORY_SIZE = 32;
    
    // ------------------------------
    // <p>retty <R>andom <N>umber <G>enerator
    pRNG *prng; 

    GameMode **gameModes;
    GameMode *currentGameMode;

    // HARDWARE
    int _btn1State, _btn2State;

    // -----------
    bool *_characterSplit;

    char *_curGameString;
    char *_curGameStringDrawBuffer;

    long _timeElapsed;
    long _timeElapsedDrawBuffer;
    
    // char* timeStrBuf;
    // int wordIndexHistory[];
    // -----------
  
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

    void CommonInit();
    char* updateCharWindow(char *buf, char *window, int charIndex);

  protected:

  public:
  
    // -------------------------------
    // GameViewDelegate
    void setDisplayDirty(bool isDis1);
    bool isDisplayDrawing(bool disp1);
    char* getCurrentGameString(bool getDrawBufData);
    bool* getCharacterSplit();
    long getTimeElapsed(bool getDrawBufData);
    char *getCharacterBuffer(bool isP1);
    char *getCharacterWindow(bool isP1);
    uint16_t randomInt();
    uint16_t randomInt(uint16_t min, uint16_t max);
    const char *getRandBalanced8CharWord();
    
    // -------------------------------
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
