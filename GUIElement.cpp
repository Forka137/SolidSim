#include "GUIElement.h"

GUIElement::GUIElement() {

}

GUIElement::GUIElement(float x_pos, float y_pos) {
	RectPosition.x = x_pos;
	RectPosition.y = y_pos;
}

GUIElement::GUIElement(float x_pos, float y_pos, unsigned int width, unsigned int height) {
	RectPosition.x = x_pos;
	RectPosition.y = y_pos;
	Width = width;
	Height = height;
}

GUIElement::~GUIElement() {

}

void GUIElement::Update(float deltaTime) {

}

void GUIElement::Draw() {
	DrawBase();
}

void GUIElement::DrawBase() {
	if (BackgroundOpacity > 0) {
		DrawRectangle(RectPosition.x, RectPosition.y, Width, Height, { BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, (unsigned char)BackgroundOpacity});
	}

	if (ShowBorders) {
		if (TopBorderThickness > 0) DrawLineEx({ RectPosition.x, RectPosition.y }, { RectPosition.x + Width, RectPosition.y }, TopBorderThickness, BorderColor);
		if (RightBorderThickness > 0) DrawLineEx({ RectPosition.x + Width, RectPosition.y }, { RectPosition.x + Width, RectPosition.y + Height }, RightBorderThickness, BorderColor);
		if (BottomBorderThickness > 0) DrawLineEx({ RectPosition.x + Width, RectPosition.y + Height }, { RectPosition.x, RectPosition.y + Height }, BottomBorderThickness, BorderColor);
		if (LeftBorderThickness > 0) DrawLineEx({ RectPosition.x, RectPosition.y + Height }, { RectPosition.x, RectPosition.y }, LeftBorderThickness, BorderColor);
	}
}

//void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);