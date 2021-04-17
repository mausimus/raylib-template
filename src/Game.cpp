#include "Game.h"

int             framesCounter = 0;
int             randValue;

Animator animator("GiveItAName", 5, 5, 5);

Game::Game(){
        randValue = GetRandomValue(-8, 5);
}

void Game::Tick() {
    std::string fdsfds("Fds");
    std::vector<int> vek(5);
    framesCounter++;

    if(((framesCounter / 120) % 2) == 1)
    {
        randValue     = GetRandomValue(-8, 5);
        framesCounter = 0;
    }
}

void Game::Draw()
{
    ClearBackground(RAYWHITE);
    DrawText("Every 2 seconds a new random value is generated:", 40, 30, 10, MAROON);
    DrawText(FormatText("%i", randValue), 120, 60, 25, LIGHTGRAY);
}