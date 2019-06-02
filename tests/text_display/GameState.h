#if !defined(__GAMESTATE_H__)
#define __GAMESTATE_H__

class GameState {
  private:
    // HARDWARE
    int _btn1State, _btn2State;
  
    // -----------
    bool _disp1DatDirty = true;
    bool _disp2DatDirty = true;
  
    char *_player1CharBuffer;
    char *_player2CharBuffer;
  
    // how long to spend at each step - higher wait_time = slower rotation
    const int wait_time = 99;
    int _wait_progress = 0;
    int _curCharIndex = 0;

  protected:
    

  public:
  
    // Initialiser
    GameState();
    GameState(bool btn1On, bool btn2On);

    bool shouldRedrawDisp1() { return _disp1DatDirty; }
    bool shouldRedrawDisp2() { return _disp2DatDirty; }
    bool disp1WasDrawn() { _disp1DatDirty = false; }
    bool disp2WasDrawn() { _disp2DatDirty = false; }

    void update(bool btn1On, bool btn2On);
    
    void keyStateChanged(char c,  bool isDown);

    bool btn1State() { return _btn1State; }
    bool btn2State() { return _btn2State; }
  
};

#endif // __GAMESTATE_H__
