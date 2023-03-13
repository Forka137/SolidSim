#pragma once
#include "MainGUI.h"
#include "GUIElement.h"
#include "StaticText.h"
#include <memory>
#include <string>
#include <iostream>
#include "Globals.h"


MainGUI::MainGUI() {
	_signatureText = std::make_unique<StaticText>(
		"Forka137 - 2023 ",
		Vector2{ 20.0, Globals::WindowRect.height - 30 }, _font);

	_howTo = std::make_unique<StaticText>(
		"Controls\n\n"
		"Left Click:    Create objects \n"
		"Right Click:   Delete an object\n"
		"Arrow UP:      Increase object size\n"
		"Arrow Down:    Decrease object size\n\n"

		"R Key:         Resets the screen\n"
		"P Key:         Pauses the simulation",
		Vector2{ 20.0, Globals::WindowRect.y + 100 }, _font);

	_signatureText->TextColor = GOLD;

	// Separación
	_menuRect = std::make_unique<GUIElement>(0.0, 0.0, 480, 720);
	_menuRect->BorderColor = RAYWHITE;
	_menuRect->ShowBorders = true;
	_menuRect->TopBorderThickness = 0;
	_menuRect->BottomBorderThickness = 0;
	_menuRect->LeftBorderThickness = 0;

	_objectCounterText = std::make_unique<StaticText>(
		"Number of objects: 0",
		Vector2{ 20.0, Globals::WindowRect.y + 20.0f}, _font);
	_objectCounterText->FontSize = 16;

	_objectSize = std::make_unique<StaticText>(
		"Object size: 10",
		Vector2{ 20.0, Globals::WindowRect.y + 40.0f }, _font);
	_objectSize->FontSize = 16;

	_pauseMode = std::make_unique<StaticText>(
		"Simulation Paused",
		Vector2{ 60.0, float(Globals::WindowRect.height) - 120 }, _font);
	_pauseMode->FontSize = 32;
	_pauseMode->TextOpacity = 0;

	_fpsCounter = std::make_unique<StaticText>(
		"FPS: 0",
		Vector2{ 300.0, Globals::WindowRect.height - 30.0f }, _font);

	_deletedText = std::make_unique<TemporalText>(
		"Deleted all objects",
		Vector2{ 70.0, float(Globals::WindowRect.height) - 160 }, _font);
	_deletedText->fontSize = 24;
	_deletedText->textColor = RED;
	_deletedText->textOpacity = 0;

	// Elements added for its Update and Draw
	AddElement(_signatureText.get());
	AddElement(_menuRect.get());
	AddElement(_pauseMode.get());
	AddElement(_deletedText.get());
	AddElement(_fpsCounter.get());
	AddElement(_objectSize.get());
	AddElement(_objectCounterText.get());
	AddElement(_howTo.get());
}

// Override method
void MainGUI::Update(float deltaTime) {
	for (int i = 0; i < _elements.size(); i++) {
		_elements[i]->Update(deltaTime);
	}
	_objectCounterText->SetLabel("Number of objects: " + std::to_string(numberOfObjects));
	_objectSize->SetLabel("Object size: " + std::to_string(Globals::ObjectRadius));
}