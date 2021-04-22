#include "Game.h"

int framesCounter = 0;
int x             = screenWidth / 2;
int y             = screenHeight / 2;
int mx;
int my;

Animator  animator("Test", 2, 1, 5);
Texture2D cloudsTexture;
Texture2D spriteTexture;
Font      font;
Sound     fxOgg;

Game::Game() { }

void Game::Start()
{
    cloudsTexture = LoadTexture("resources/clouds.png");
    spriteTexture = LoadTexture("resources/sprite.png");
    font          = LoadFontEx("resources/test1.ttf", 6, 0, 0);
    fxOgg         = LoadSound("resources/sound.ogg");
    animator.AssignSprite(spriteTexture);
}

void Game::End()
{
    UnloadTexture(cloudsTexture);
    UnloadTexture(spriteTexture);
    UnloadFont(font);
}

void Game::Tick(double deltaTime, double totalTime)
{
    framesCounter++;
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

    mx = GetMouseX();
    my = GetMouseY();

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        x = mx;
        y = my;
    }

    animator.Play();
}

int _x = 0;

void Game::DrawPixels(Color *framebuffer, Rectangle *rect, bool* fullFrame)
{
    *fullFrame = false;
    rect->y = 190.0f;
    rect->height = 50.0f;
    rect->x = 0.0f;
    rect->width = screenWidth;
    framebuffer[_x++] = GREEN;
}

void Game::DrawShapes()
{
    //DrawTexture(cloudsTexture, 0, 0, WHITE);
    DrawTextureRec(animator.GetSprite(), animator.GetFrameRec(), (Vector2) {static_cast<float>(x), static_cast<float>(y)}, WHITE);
    DrawCircle(mx, my, 5, MAROON);
    DrawTextEx(font, "ABIACBIIAIB", (Vector2) {5, 5}, (float)font.baseSize, 1.0f, WHITE);
}