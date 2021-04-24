#pragma once

#include "stdafx.h"

class Assets
{
public:
    Texture2D spriteTexture;
    Color palette[64];

    Assets();
    void Load();
    void Unload();
};
