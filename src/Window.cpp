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

#ifdef SCANLINES
#define SHADER_PATH "resources/shaders/glsl%i/scanlines.fs"
#else
#define SHADER_PATH "resources/shaders/glsl%i/base.fs"
#endif

bool            firstFrame = true;
Shader          shader;
RenderTexture2D target;
Rectangle       textureRect {0, 0, screenWidth, -screenHeight};
Rectangle       renderRect {0, 0, 0, 0};
Game            game;
Vector2         topLeft{0,0};

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
    InitWindow(screenWidth * initialScale, screenHeight * initialScale, WINDOW_TITLE);
    SetWindowMinSize(screenWidth, screenHeight);
    shader = LoadShader(0, TextFormat(SHADER_PATH, GLSL_VERSION));
    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER);
    UpdateRenderSize(renderRect);
    game.Start();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    game.End();
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}

void UpdateDrawFrame()
{
#ifdef FULLSCREEN_KEY
    if(IsKeyPressed(FULLSCREEN_KEY))
    {
        ToggleFullscreen();
        UpdateRenderSize(renderRect);
    }
#endif

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
            firstFrame = false;
        }
        DrawTexturePro(target.texture, textureRect, renderRect, topLeft, 0, WHITE);
        EndShaderMode();
    }
    EndDrawing();
}