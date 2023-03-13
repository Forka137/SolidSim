#pragma once
#include "GUIElement.h"
#include "raylib.h"
#include <string>
class StaticText : public GUIElement
{
public:
	StaticText(std::string label, Font font);
	StaticText(std::string label, Vector2 position, Font font);

	void Draw();
	void Update(float deltaTime);

	Color TextColor = RAYWHITE;

	void Show();
	void Hide();
	void SetLabel(std::string label);
	std::string GetLabel();
	Font ttfFont;
	float FontSize = 16;
	float FontSpacing = 2;
	Vector2 TextPosition = { 0, 0 };

	unsigned int LeftPadding = 4;
	unsigned int RightPadding = 4;
	unsigned int TopPadding = 2;
	unsigned int BottomPadding = 2;
	unsigned char TextOpacity = 255;

	// Add font size method
private:
	
	void FitInRectangle();
	std::string _label;
};