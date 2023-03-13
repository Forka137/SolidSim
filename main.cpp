#pragma once
#include "raylib.h"
#include "Game.h"

int main()
{
    Game game;
    game.Initialize("Solid Simulator v1.2");
    game.RunLoop();
    return 0;
}