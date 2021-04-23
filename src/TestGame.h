#pragma once

#include "Game.h"

class TestGame : public Game
{
protected:
    virtual void CreateScreens();
    virtual void OnTick(double deltaTime, double totalTime);
    virtual void OnSwitchScreen(int prevScreen, int nextScreen);

public:
    TestGame();
};