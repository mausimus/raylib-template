#pragma once

#include "stdafx.h"

class Assets
{
public:
    Texture2D spriteTexture;

    Assets();
    void Load();
    void Unload();
};
