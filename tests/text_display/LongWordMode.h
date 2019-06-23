#if !defined(__LONGWORDMODE_H__)
#define __LONGWORDMODE_H__
#include "LWGameView.h"
#include "GameMode.h"

class LongWordMode : public GameMode {
  private:
    

  protected:
    void CommonInit() override;

  public:

    // Initialiser
    LongWordMode();
    // LongWordMode(bool btn1On, bool btn2On);
  
};

#endif // __LONGWORDMODE_H__
