#include "stdafx.h"
#include "Game.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#else // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION 100
#endif

constexpr int   screenWidth  = 320;
constexpr int   screenHeight = 240;
constexpr int   initialScale = 3;
bool            firstFrame   = true;
Shader          shader;
RenderTexture2D target;
Rectangle       textureRect {0, 0, screenWidth, -screenHeight};
Rectangle       renderRect {0, 0, 0, 0};
Game            game;

void UpdateDrawFrame(void);

void UpdateRenderSize(Rectangle& renderRect)
{
    auto screenWidth  = GetScreenWidth();
    auto screenHeight = GetScreenHeight();
    renderRect.width  = screenWidth;
    renderRect.height = screenHeight;
    if(renderRect.width * 3 != renderRect.height * 4)
    {
        if(renderRect.width * 3 > renderRect.height * 4)
        {
            renderRect.width = (renderRect.height * 4) / 3;
        }
        else
        {
            renderRect.height = (renderRect.width * 3) / 4;
        }
    }
    renderRect.x = (screenWidth - renderRect.width) / 2;
    renderRect.y = (screenHeight - renderRect.height) / 2;
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth * initialScale, screenHeight * initialScale, "game");
    SetWindowMinSize(screenWidth, screenHeight);
    shader = LoadShader(0, TextFormat("resources/shaders/glsl%i/base.fs", GLSL_VERSION));
    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, FILTER_POINT);
    UpdateRenderSize(renderRect);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}

void UpdateDrawFrame()
{
    if(IsKeyPressed(KEY_F))
    {
        ToggleFullscreen();
        UpdateRenderSize(renderRect);
    }

    game.Tick();

    BeginDrawing();
    {
        bool windowResized = IsWindowResized();
        if(windowResized || firstFrame)
        {
            UpdateRenderSize(renderRect);
        }

        BeginTextureMode(target);
        game.Draw();
        EndTextureMode();

        BeginShaderMode(shader);
        if(windowResized || firstFrame)
        {
            ClearBackground(BLACK);
        }
        DrawTexturePro(target.texture, textureRect, renderRect, (Vector2) {0, 0}, 0, WHITE);
        EndShaderMode();
    }
    EndDrawing();

    firstFrame = false;
}