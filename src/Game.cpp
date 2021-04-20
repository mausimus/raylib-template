#include "Game.h"

int framesCounter = 0;
int x             = screenWidth / 2;
int y             = screenHeight / 2;

Animator  animator("Test", 2, 1, 5);
Texture2D cloudsTexture;
Texture2D spriteTexture;
Font      font;

Game::Game() { }

void Game::Start()
{
    cloudsTexture = LoadTexture("resources/clouds.png");
    spriteTexture = LoadTexture("resources/sprite.png");
    font          = LoadFontEx("resources/test1.ttf", 6, 0, 0);
    animator.AssignSprite(spriteTexture);
}

void Game::End()
{
    UnloadTexture(cloudsTexture);
    UnloadTexture(spriteTexture);
    UnloadFont(font);
}

void Game::Tick()
{
    framesCounter++;
    int vx = 0;
    int vy = 0;
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
}

void Game::Draw()
{
    DrawTexture(cloudsTexture, 0, 0, WHITE);
    DrawTextureRec(animator.GetSprite(), animator.GetFrameRec(), (Vector2) {static_cast<float>(x), static_cast<float>(y)}, WHITE);
    DrawTextEx(font, "ABIACBIIAIB", (Vector2) {5, 5}, (float)font.baseSize, 1.0f, WHITE);
}