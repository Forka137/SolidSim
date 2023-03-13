#pragma once
#include "SolidBall.h"
#include "Globals.h"
#include <iostream>


SolidBall::SolidBall(Vector2 pos, int r) {
	oldPosition = pos;
	currentPosition = pos;
	radius = r;
}

SolidBall::SolidBall(Vector2 pos, int r, Color c) {
	oldPosition = pos;
	currentPosition = pos;
	radius = r;
	color = c;
}

SolidBall::~SolidBall() {
	// std::cout << "Object deleted" << std::endl;
}

void SolidBall::Draw() {
	DrawCircle(currentPosition.x, currentPosition.y, radius, color);
}

void SolidBall::Update(float deltaTime) {
	Vector2 acceleration = {0.0f, Globals::Gravity };
	Vector2 implicitVelocity = {0.0f, 0.0f};
	implicitVelocity.x = currentPosition.x - oldPosition.x;
	implicitVelocity.y = currentPosition.y - oldPosition.y;

	oldPosition = currentPosition;
	currentPosition.x += implicitVelocity.x + acceleration.x * deltaTime * deltaTime;
	currentPosition.y += implicitVelocity.y + acceleration.y * deltaTime * deltaTime;
}

// DrawCircle(int centerX, int centerY, float radius, Color color);


// currentPosition - oldPosition = maxSpeed
// oldPosition = currentPosition - maxSpeed;