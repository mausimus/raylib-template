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
Vector2         topLeft {0, 0};
double          totalTime;

#ifdef DRAW_PIXELS
Color     framebuffer[screenWidth * screenHeight];
Rectangle bufferRect;
bool      fullFrame;
#endif

void UpdateDrawFrame(void);

void UpdateRenderSize(Rectangle& renderRect)
{
    auto viewportWidth  = GetScreenWidth();
    auto viewportHeight = GetScreenHeight();
    renderRect.width    = viewportWidth;
    renderRect.height   = viewportHeight;
    auto scale          = screenWidth / static_cast<float>(GetScreenWidth());
    if(renderRect.width * 3 != renderRect.height * 4)
    {
        if(renderRect.width * 3 > renderRect.height * 4)
        {
            renderRect.width = (renderRect.height * 4) / 3;
            scale            = screenHeight / static_cast<float>(GetScreenHeight());
        }
        else
        {
            renderRect.height = (renderRect.width * 3) / 4;
        }
    }
    renderRect.x = (viewportWidth - renderRect.width) / 2;
    renderRect.y = (viewportHeight - renderRect.height) / 2;
    SetMouseScale(scale, scale);
    SetMouseOffset(-renderRect.x, -renderRect.y);
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth * initialScale, screenHeight * initialScale, WINDOW_TITLE);
    InitAudioDevice();
    SetWindowMinSize(screenWidth, screenHeight);
    shader = LoadShader(0, TextFormat(SHADER_PATH, GLSL_VERSION));
    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER);
    UpdateRenderSize(renderRect);
#ifdef DRAW_PIXELS
    for(int q = 0; q < screenWidth * screenHeight; q++)
        framebuffer[q] = BLACK;
#endif
    HideCursor();
    game.Start();
    totalTime = GetTime();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, TARGET_FPS, 1);
#else
    SetTargetFPS(TARGET_FPS);
    while(!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    game.End();
    UnloadRenderTexture(target);
    CloseAudioDevice();
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

    auto currentTime = GetTime();
    game.Tick(currentTime - totalTime, currentTime);
    totalTime = currentTime;

    BeginDrawing();
    {
        bool windowResized = IsWindowResized();
        if(windowResized || firstFrame)
        {
            UpdateRenderSize(renderRect);
        }

#ifdef DRAW_PIXELS
        game.DrawPixels(framebuffer, &bufferRect, &fullFrame);
        if(fullFrame)
            UpdateTexture(target.texture, framebuffer);
        else
            UpdateTextureRec(target.texture, bufferRect, framebuffer);
#endif

#ifdef DRAW_SHAPES
        BeginTextureMode(target);
        game.DrawShapes();
        EndTextureMode();
#endif

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