#pragma once

#include "stdafx.h"

constexpr int   screenWidth  = 320;
constexpr int   screenHeight = 240;
constexpr int   aspectH = 4;
constexpr int   aspectV = 3;
constexpr int   initialScale = 3;
constexpr int   screenSize = screenWidth * screenHeight;

#define WINDOW_TITLE "game"
#define FULLSCREEN_KEY KEY_F
//#define SCANLINES
//#define TEXTURE_FILTER FILTER_BILINEAR
#define TEXTURE_FILTER FILTER_POINT
#define TARGET_FPS 60

#define DRAW_PIXELS
#define DRAW_SHAPES
#define DRAW_BACKGROUND

class Screen;
class Assets;

class Game
{
protected:
    std::vector<Screen*> m_screens;
    Screen* m_activeScreen;

    void LoadScreens();

    virtual void CreateScreens() = 0;
    virtual void OnTick(double deltaTime, double totalTime) = 0;
    virtual void OnSwitchScreen(int prevScreen, int nextScreen) = 0;

public:

    Assets* m_assets;

    int m_frameCounter;
    int m_mouseX;
    int m_mouseY;
    double m_screenTime;

    Game();

    void Start();
    void Tick(double deltaTime, double totalTime);
    void DrawBackground();
    void DrawPixels(Color* framebuffer, Rectangle *rect, bool* fullFrame);
    void DrawShapes();
    void End();

    void SwitchScreen(int sn);
};
