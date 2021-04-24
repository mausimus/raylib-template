#include "TestScreen.h"

int x             = screenWidth / 2;
int y             = screenHeight / 2;
int _x = 0;

Animator  animator("Test", 2, 1, 5);
Texture2D cloudsTexture;
Font      font;
Sound     fxOgg;

TestScreen::TestScreen(int no, TestGame *game) : Screen(no, game) { }

void TestScreen::Load()
{
    cloudsTexture = LoadTexture("resources/clouds.png");    
    //font          = LoadFontEx("resources/test1.ttf", 6, 0, 0);
    //font          = LoadFontEx("resources/fonts/prstartk.ttf", 8, 0, 0);    
    font          = LoadFontEx("resources/fonts/Px437_Portfolio_6x8.ttf", 8, 0, 0);
    //font          = LoadFontEx("resources/fonts/joystix.ttf", 16, 0, 0);
    //font          = LoadFont("resources/fonts/alpha_beta.png");
    fxOgg         = LoadSound("resources/sound.ogg");
    animator.AssignSprite(Assets()->spriteTexture);
}

void TestScreen::Enter()
{
}

void TestScreen::Exit()
{
}

void TestScreen::Unload()
{
    UnloadTexture(cloudsTexture);
    UnloadFont(font);
}

void TestScreen::Tick(double deltaTime, double totalTime)
{
    int vx = 0;
    int vy = 0;
    if(IsKeyPressed(KEY_M))
        PlaySoundMulti(fxOgg);
    if(IsKeyDown(KEY_UP))
        vy--;
    if(IsKeyDown(KEY_DOWN))
        vy++;
    if(IsKeyDown(KEY_LEFT))
        vx--;
    if(IsKeyDown(KEY_RIGHT))
        vx++;
    x += vx;
    y += vy;

    animator.Play();

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        x = m_game->m_mouseX;
        y = m_game->m_mouseY;
    }
}

void TestScreen::DrawBackground()
{
    DrawTexture(cloudsTexture, 0, 0, WHITE);
}

void TestScreen::DrawPixels(Color *framebuffer, Rectangle *rect, bool* fullFrame)
{
    *fullFrame = false;
    rect->y = 190.0f;
    rect->height = 50.0f;
    rect->x = 0.0f;
    rect->width = screenWidth;
    framebuffer[_x++] = GREEN;
}

void TestScreen::DrawShapes()
{
    DrawTextureRec(animator.GetSprite(), animator.GetFrameRec(), (Vector2) {static_cast<float>(x), static_cast<float>(y)}, WHITE);
    auto col = Assets()->palette[62];
    DrawTextEx(font, "Score SCORE 134234", (Vector2) {5, 5}, (float)font.baseSize, 1.0f, Assets()->palette[63]);
}
