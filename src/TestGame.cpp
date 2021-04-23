#include "TestGame.h"
#include "TestScreen.h"

TestGame::TestGame() : Game()
{
}

void TestGame::CreateScreens()
{
    int sn = 0;
    m_screens.push_back(new TestScreen(sn++, this));
}

void TestGame::OnTick(double deltaTime, double totalTime)
{    
}

void TestGame::OnSwitchScreen(int prevScreen, int nextScreen)
{    
}