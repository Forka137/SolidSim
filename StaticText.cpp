#pragma once
#include "StaticText.h"
#include "raylib.h"
#include <iostream>
#include <string>

StaticText::StaticText(std::string label, Font font) {
	_label = label;
	ttfFont = font;
	FitInRectangle();
}

StaticText::StaticText(std::string label, Vector2 position, Font font) {
	_label = label;
	RectPosition = position;
	ttfFont = font;
	FitInRectangle();
}

void StaticText::FitInRectangle() {
	Vector2 textSize = MeasureTextEx(ttfFont, _label.c_str(), FontSize, FontSpacing);

	Width = LeftPadding + textSize.x + RightPadding;
	Height = TopPadding + textSize.y + BottomPadding;

	TextPosition.x = LeftPadding + RectPosition.x;
	TextPosition.y = TopPadding + RectPosition.y;
}

void StaticText::SetLabel(std::string label) {
	Show();
	_label = label;
}

std::string StaticText::GetLabel() {
	return _label;
}

void StaticText::Show() {
	TextOpacity = 255;
}

void StaticText::Hide() {
	TextOpacity = 0;
}

void StaticText::Draw() {
	DrawBase();
	if (TextOpacity > 0) {
		DrawTextEx(ttfFont, _label.c_str(), TextPosition, FontSize, FontSpacing, { TextColor.r, TextColor.g, TextColor.b, (unsigned char)TextOpacity});
	}
}


void StaticText::Update(float deltaTime) {
	// Nothing
}
