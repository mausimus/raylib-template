#include "Screen.h"
#include "TestGame.h"

class TestScreen : public Screen
{
public:
    TestScreen(int no, TestGame* game);
    virtual void Load();
    virtual void Enter();
    virtual void Tick(double deltaTime, double totalTime);
    virtual void DrawBackground();
    virtual void DrawPixels(Color* framebuffer, Rectangle *rect, bool* fullFrame);
    virtual void DrawShapes();
    virtual void Exit();
    virtual void Unload();
};
