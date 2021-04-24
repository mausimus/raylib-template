#include "Assets.h"
#include "../extras/atari64.h"

Assets::Assets()
{
    for(int i = 0; i < 64; i++)
    {
        palette[i].r = _atari64[i] >> 16;
        palette[i].g = (_atari64[i] >> 8) & 255;
        palette[i].b = _atari64[i] & 255;
        palette[i].a = 255;
    }
}

void Assets::Load()
{
    spriteTexture = LoadTexture("resources/sprite.png");
}

void Assets::Unload()
{
    UnloadTexture(spriteTexture);
}
