#include "stdafx.h"

constexpr int   screenWidth  = 320;
constexpr int   screenHeight = 240;
constexpr int   initialScale = 3;

#define WINDOW_TITLE "game"
#define FULLSCREEN_KEY KEY_F
#define SCANLINES
#define TEXTURE_FILTER FILTER_BILINEAR // FILTER_POINT

class Game
{
public:
    Game();
    void Start();
    void Tick();
    void Draw();
    void End();
};
