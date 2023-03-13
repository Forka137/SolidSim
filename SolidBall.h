#pragma once
#include "Raylib.h"

class SolidBall {
public:
	SolidBall(Vector2 pos, int r);
	SolidBall(Vector2 pos, int r, Color c);
	~SolidBall();
	void Draw();
	void Update(float deltaTime);

	int radius = 10;
	float maxSpeed = 100.0f;
	Vector2 oldPosition = { 0.0f, 0.0f };
	Vector2 currentPosition = { 0.0f, 0.0f };

	Color color = SKYBLUE;

};