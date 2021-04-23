#include "Assets.h"

Assets::Assets()
{}

void Assets::Load()
{
    spriteTexture = LoadTexture("resources/sprite.png");
}

void Assets::Unload()
{
    UnloadTexture(spriteTexture);
}
