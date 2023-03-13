#pragma once
#include "BaseGUI.h"
#include "GUIElement.h"
#include <memory>
#include <string>

BaseGUI::BaseGUI(){

}

BaseGUI::~BaseGUI() {

}

void BaseGUI::AddElement(GUIElement* element) {
	_elements.push_back(element);
}

void BaseGUI::Draw() {
	if (_shouldDraw) {
		for (int i = 0; i < _elements.size(); i++) {
			_elements[i]->Draw();
		}
	}
}

void BaseGUI::GetInput() {
	// Add your own logic in derivated class
}

void BaseGUI::Update(float deltaTime) {
	for (int i = 0; i < _elements.size(); i++) {
		_elements[i]->Update(deltaTime);
	}
}

void BaseGUI::Show() {
	_shouldDraw = true;
}

void BaseGUI::Hide() {
	_shouldDraw = false;
}

void BaseGUI::ToggleShow() {
	if (_shouldDraw) {
		_shouldDraw = false;
	}
	else {
		_shouldDraw = true;
	}
}




