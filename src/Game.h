#include "stdafx.h"

constexpr int   screenWidth  = 320;
constexpr int   screenHeight = 240;
constexpr int   initialScale = 3;

#define WINDOW_TITLE "game"
#define FULLSCREEN_KEY KEY_F
//#define SCANLINES
//#define TEXTURE_FILTER FILTER_BILINEAR
#define TEXTURE_FILTER FILTER_POINT
#define TARGET_FPS 10

#define DRAW_PIXELS
#define DRAW_SHAPES

class Game
{
public:
    Game();
    void Start();
    void Tick(double deltaTime, double totalTime);
    void DrawPixels(Color* framebuffer, Rectangle *rect, bool* fullFrame);
    void DrawShapes();
    void End();
};
