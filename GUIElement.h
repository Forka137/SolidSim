#pragma once
#include "raylib.h"
// By default it has the properties of a rectangle.
// Una clase con almenos un elemento virtual puro es abstracta.
class GUIElement
{
public:
	GUIElement();
	GUIElement(float x_pos, float y_pos);
	GUIElement(float x_pos, float y_pos, unsigned int width, unsigned int height);
	virtual ~GUIElement();
	Vector2 RectPosition = { 0.0 , 0.0 };
	Color BackgroundColor = RAYWHITE;
	Color BorderColor = GOLD;
	unsigned int TopBorderThickness		= 1;
	unsigned int RightBorderThickness	= 1;
	unsigned int BottomBorderThickness	= 1;
	unsigned int LeftBorderThickness	= 1;

	unsigned char BackgroundOpacity = 0;

	unsigned int Width = 0;
	unsigned int Height = 0;

	virtual void Update(float deltaTime);
	void DrawBase();
	virtual void Draw();

	
	bool ShowBorders = false;
};

