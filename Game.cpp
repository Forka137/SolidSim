#pragma once
#include "Game.h"
#include "MainGUI.h"
#include "GridSpace.h"
#include "raylib.h"
#include <iostream>

Game::Game() {
	// Nada de la raylib puede ir antes de InitWindow, por lo tanto el constructor de Game queda vacío
}

Game::~Game() {

}

void Game::Initialize(std::string title) {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(Globals::WindowRect.width, Globals::WindowRect.height, title.c_str());
	// SetTargetFPS(60); // Adjust to screen refresh rate
	// SetExitKey(0); // Disables ESC_KEY for Exit
	_mainGUI = std::make_unique<MainGUI>();
	_space = std::make_unique<GridSpace>();
}

void Game::RunLoop() {
	while (!WindowShouldClose()) {
		ProcessInput();
		Update();
		DrawObjects();
	}
}

void Game::Terminate() {
	CloseWindow();
}

void Game::Update() {
	float deltaTime = GetFrameTime();
	// Prevents HUGE delta times when moving the window, 30 FPS minimum.
	// The bigger the delta, the less accurate the simulation (gains energy).
	if (deltaTime > 0.0333f) deltaTime = 0.0333f;

	if (_secondCounter > 1.0f) {
		_secondCounter = 0.0f;
		_mainGUI->_fpsCounter->SetLabel("FPS: " + std::to_string(int(1.0f / deltaTime)));
	}

	_space->Update(deltaTime);

	_mainGUI->numberOfObjects = _space->GetTotalObjects();
	_mainGUI->Update(deltaTime);

	_secondCounter += deltaTime;
}

// Private Methods
void Game::DrawObjects() {
	BeginDrawing();

	ClearBackground(BLACK);
	_space->Draw();
	_mainGUI->Draw();

	EndDrawing();
}

void Game::ProcessInput() {
	//Keyboard and mouse input
	_space->Input();

	//Global detections
	if (IsKeyPressed(KEY_P)) {
		_space->simPaused = !_space->simPaused;
		if (_space->simPaused) _mainGUI->_pauseMode->TextOpacity = 255;
		else _mainGUI->_pauseMode->TextOpacity = 0;
	}

	if (IsKeyPressed(KEY_R)) {
		_mainGUI->_deletedText->textOpacity = 255;
		_space->Reset();
	}

	if (IsKeyPressed(KEY_UP)) {
		if (Globals::ObjectRadius < 50) Globals::ObjectRadius += 1;
	}

	if (IsKeyPressed(KEY_DOWN)) {
		if (Globals::ObjectRadius > 5) Globals::ObjectRadius -= 1;
	}
}