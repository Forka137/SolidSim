#pragma once
#include <string>
#include "Globals.h"
#include <memory>
#include "MainGUI.h"
#include "GridSpace.h"

class Game
{
public:
	Game();
	~Game();

	void Initialize(std::string title);
	void RunLoop();
	void Terminate();

private:
	void ProcessInput();
	void Update();
	void DrawObjects();

	float _secondCounter = 0.0f;
	std::unique_ptr<MainGUI> _mainGUI;
	std::unique_ptr<GridSpace> _space;
};

