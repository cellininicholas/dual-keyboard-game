#if !defined(__GAMEVIEW_H__)
#define __GAMEVIEW_H__

#include <U8g2lib.h>

class GameModeDelegate {
  public:
  virtual void setDisplayDirty(bool isDis1);
  virtual bool isDisplayDrawing(bool disp1);

  virtual char* getCurrentGameString(bool getDrawBufData);
  virtual bool* getCharacterSplit();
  virtual long getTimeElapsed(bool getDrawBufData);

  virtual char *getCharacterBuffer(bool isP1);
  virtual char *getCharacterWindow(bool isP1);

  virtual const char *getRandBalanced8CharWord();
};

class GameViewDelegate: public GameModeDelegate {
  public:
  virtual char* getCurrentWord();
  virtual byte getCurrentWordMask();
};

class GameView {
  private:
    

  protected:
    GameViewDelegate *viewDelegate;
  
    virtual void CommonInit();
    void drawNHearts(U8G2_ST7920_128X64_1_SW_SPI *disp, int heartCount);
    void drawNHeartsHeight8(U8G2_ST7920_128X64_1_SW_SPI *disp, int heartCount);
    void drawNHeartsHeight16(U8G2_ST7920_128X64_1_SW_SPI *disp, int heartCount);
    void drawTimeCounter(U8G2_ST7920_128X64_1_SW_SPI *disp, int secsRemaining);
    

  public:
  
    virtual void keyPressed(char c, int upperChar, bool isP1);
    virtual void draw(U8G2_ST7920_128X64_1_SW_SPI *disp, bool isDisp1);

    // Initialiser
    GameView(GameModeDelegate *del);
    // GameView(bool btn1On, bool btn2On);
  
};

#endif // __GAMEVIEW_H__
