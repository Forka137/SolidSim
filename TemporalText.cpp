#pragma once
#include "TemporalText.h"
#include "raylib.h"
#include <iostream>
#include <string>

TemporalText::TemporalText(std::string label, Font font) {
	_label = label;
	_screenTime = 1.0;
	ttfFont = font;
}

TemporalText::TemporalText(std::string label, Vector2 position, Font font) {
	_label = label;
	textPosition = position;
	_screenTime = 1.0;
	ttfFont = font;
}


TemporalText::TemporalText(std::string label, Vector2 position, float screenTime, Font font) {
	_label = label;
	textPosition = position;
	_screenTime = screenTime;
	ttfFont = font;
}

void TemporalText::SetLabel(std::string label) {
	Show();
	_label = label;
}

std::string TemporalText::GetLabel() {
	return _label;
}

void TemporalText::SetScreenTime(float time) {
	_screenTime = time;
}

void TemporalText::Show() {
	textOpacity = 255;
}

void TemporalText::Hide() {
	textOpacity = 0;
}

void TemporalText::Draw() {
	// std::cout << "Dibujando texto" << std::endl;
	if (textOpacity > 0) {
		DrawTextEx(ttfFont, _label.c_str(), textPosition, fontSize, fontSpacing, { textColor.r, textColor.g, textColor.b, (unsigned char)textOpacity});
	}
}

void TemporalText::Update(float deltaTime) {
	if (textOpacity > 0) {
		textOpacity = textOpacity - ((deltaTime * 255.0f) / _screenTime);
	}
	if (textOpacity < 0) {
		textOpacity = 0.0f;
	}
}