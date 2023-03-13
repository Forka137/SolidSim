#pragma once
#include "GridSpace.h"
#include "Globals.h"
#include "SolidBall.h"
#include "raymath.h"
#include <iostream>

GridSpace::GridSpace() {
	_dx = Globals::CanvasRect.width / Globals::GridLevel;
	_dy = Globals::CanvasRect.height / Globals::GridLevel;
	ClearGrid();
}

void GridSpace::Input() {
	// Get mouse click
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();

		// Previene crear objetos muy cerca unos de otros
		if (Vector2Length(Vector2Subtract(mousePos, prevMousePos)) > Globals::ObjectRadius * 3) {
			if (IsInsideCanvas(mousePos)) CreateBall(mousePos, Globals::ObjectRadius);
			_cdCounter = 0.0f;
			prevMousePos = mousePos;
		}
		// Evita que se generen demasiado rápido por la misma razón
		else if (_cdCounter > 1.0f * _mouseCoolDown) {
			_cdCounter = 0.0f;
			if (IsInsideCanvas(mousePos)) CreateBall(mousePos, Globals::ObjectRadius);
			prevMousePos = mousePos;
		}
		_cdCounter+= GetFrameTime();
	} 
	else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		Vector2 mousePos = GetMousePosition();
		DeleteBall(mousePos);
	}
}

void GridSpace::CreateBall(Vector2 pos, int radius) {
	Color c = Rainbow(_colorIndex);
	_balls.push_back(std::make_unique<SolidBall>(pos, radius, c));
	_colorIndex++;
	if (_colorIndex > 255) _colorIndex = 0;
}

void GridSpace::DeleteBall(Vector2 pos) {
	Vector2 coords = CoordsToGrid(pos);
	if (!ValidGridPos(coords)) return;

	for (int i = 0; i < _grid[coords.x][coords.y].size(); i++) {
		SolidBall* object = _grid[coords.x][coords.y][i];
		Vector2* circle = &object->currentPosition;
		int* radius = &object->radius;

		Vector2 collisionAxis = Vector2Subtract(pos, *circle);
		float distanceFromCenter = Vector2Length(collisionAxis);

		if (distanceFromCenter < *radius) {
			int index = GetObjectAtPos(*circle);
			// std::cout << index << std::endl;
			_balls.erase(_balls.begin() + index);
		}
	}
}

void GridSpace::Update(float deltaTime) {
	// Acerca del modo pausa
	// Es importante que la grid se siga actualizando, solo que los objetos y su colisión se detenga.

	// Sub-stepping to improve stability
	float subDelta = deltaTime / Globals::SubSteps;
	for (int s = 0; s < Globals::SubSteps; s++) {
		// Remove ball references from grid.
		ClearGrid();

		// Update Ball Movement
		for (int i = 0; i < _balls.size(); i++) {
			if (!simPaused) _balls[i]->Update(subDelta);

			// Subscribe Ball to a position in the grid
			Vector2 coords = CoordsToGrid(_balls[i]->currentPosition);

			// If the object got too much speed and it's outside the grid it will have an index
			// greater than Globals::GridLevel, if that happens, we will delete that object and return the loop.
			if (!ValidGridPos(coords)) {
				_balls.erase(_balls.begin() + i);
				return;
			}
			// Add to grid
			_grid[coords.x][coords.y].push_back(_balls[i].get());

			// Check collisions
			if (!simPaused) ObjectCollision(_balls[i].get(), coords);
			if (!simPaused) WallCollision(_balls[i].get());

			// If after collisions it moved from the grid, updates position in grid.
			Vector2 coordsAfterCollision = CoordsToGrid(_balls[i]->currentPosition);
			if (coordsAfterCollision.x != coords.x || coordsAfterCollision.y != coords.y) {
				RemoveFromGrid(_balls[i].get(), coords);
				_grid[coordsAfterCollision.x][coordsAfterCollision.y].push_back(_balls[i].get());
			}
		}
	}

	_numberOfObjects = _balls.size();
	// Debug
	// PrintGrid();
}

void GridSpace::WallCollision(SolidBall* object) {
	// Pointers for shorter variable names
	Vector2* pos = &object->currentPosition;
	Vector2* oldPos = &object->oldPosition;
	int* radius = &object->radius;

	Vector2 velocity = { pos->x - oldPos->x, pos->y - oldPos->y };
	float max_x = Globals::CanvasRect.x + Globals::CanvasRect.width;
	float max_y = Globals::CanvasRect.y + Globals::CanvasRect.height;

	if (pos->x + *radius > max_x) {
		// Outside from the right
		pos->x = max_x - *radius;
		oldPos->x = pos->x + velocity.x;
	}
	else if (pos->x - *radius < Globals::CanvasRect.x) {
		pos->x = Globals::CanvasRect.x + *radius;
		oldPos->x = pos->x + velocity.x;
	}
	if (pos->y + *radius > max_y) {
		// Outside from the bottom
		pos->y = max_y - *radius;
		oldPos->y = pos->y + velocity.y;
	}
	else if (pos->y - *radius < Globals::CanvasRect.y) {
		pos->y = Globals::CanvasRect.y + *radius;
		oldPos->y = pos->y + velocity.y;
	}
}

void GridSpace::ObjectCollision(SolidBall* object, const Vector2& coords) {
	//LeftTop
	if (coords.x > 0 && coords.y > 0) {
		CheckCollisionAt(object, Vector2{ coords.x - 1, coords.y - 1 });
	}
	//Top
	if (coords.y > 0) {
		CheckCollisionAt(object, Vector2{ coords.x , coords.y - 1 });
	}
	//RightTop
	if (coords.x < Globals::GridLevel-1 && coords.y > 0) {
		CheckCollisionAt(object, Vector2{ coords.x + 1, coords.y - 1 });
	}
	//Left
	if (coords.x > 0) {
		CheckCollisionAt(object, Vector2{ coords.x - 1, coords.y });
	}
	//Center (always can)
		CheckCollisionAt(object, Vector2{ coords.x , coords.y });
	//Right
	if (coords.x < Globals::GridLevel-1) {
		CheckCollisionAt(object, Vector2{ coords.x + 1 , coords.y });
	}
	//LeftBot
	if (coords.x > 0 && coords.y < Globals::GridLevel-1) {
		CheckCollisionAt(object, Vector2{ coords.x - 1 , coords.y + 1 });
	}
	//Bottom
	if (coords.y < Globals::GridLevel-1) {
		CheckCollisionAt(object, Vector2{ coords.x , coords.y + 1 });
	}
	//RightBot
	if (coords.x < Globals::GridLevel-1 && coords.y < Globals::GridLevel-1) {
		CheckCollisionAt(object, Vector2{ coords.x + 1 , coords.y + 1 });
	}
}

void GridSpace::CheckCollisionAt(SolidBall* objectOne, const Vector2& coords) {
	// Needs functions from raymath.h
	// porsiaca
	if (!ValidGridPos(coords)) return;

	for (int i = 0; i < _grid[coords.x][coords.y].size(); i++) {
		SolidBall* objectTwo = _grid[coords.x][coords.y][i];
		Vector2* circleOne = &objectOne->currentPosition;
		int* radiusOne = &objectOne->radius;
		Vector2* circleTwo = &_grid[coords.x][coords.y][i]->currentPosition;
		int* radiusTwo = &_grid[coords.x][coords.y][i]->radius;

		// Check if its itself
		if (circleOne == circleTwo) return;

		Vector2 collisionAxis = Vector2Subtract(*circleOne, *circleTwo);
		float length = Vector2Length(collisionAxis);
		
		// Prevent division by 0
		if (length <= 0) return;

		if (length < *radiusOne + *radiusTwo) {
			Vector2 normal = Vector2Scale(collisionAxis, 1.0f / length);
			float delta = *radiusOne + *radiusTwo - length;

			objectOne->currentPosition.x += Globals::Elasticity * delta * normal.x;
			objectOne->currentPosition.y += Globals::Elasticity * delta * normal.y;

			objectTwo->currentPosition.x -= Globals::Elasticity * delta * normal.x;
			objectTwo->currentPosition.y -= Globals::Elasticity * delta * normal.y;

			// std::cout << "Collision!" << std::endl;
		}
	}
}


Vector2 GridSpace::CoordsToGrid(const Vector2& pos) {
	// First, adjust coords to canvas
	Vector2 transformed_pos = { pos.x - Globals::CanvasRect.x, pos.y - Globals::CanvasRect.y };
	int dx = Globals::CanvasRect.width / Globals::GridLevel;
	int dy = Globals::CanvasRect.height / Globals::GridLevel;

	Vector2 GridCoords;
	GridCoords.x = int(transformed_pos.x / dx);
	GridCoords.y = int(transformed_pos.y / dy);
	return GridCoords;
}

void GridSpace::Draw() {
	for (int i = 0; i < _balls.size(); i++) {
		_balls[i]->Draw();
	}
	DrawGrid();
}

void GridSpace::Reset() {
	_balls.clear();
	ClearGrid();
}

void GridSpace::ClearGrid() {
	// Vaciamos todo
	_grid.clear();
	// Llenamos con listas de SolidBall pointers vacías
	for (int i = 0; i < Globals::GridLevel; i++) {
		_grid.push_back(std::vector<std::vector<SolidBall*>>());
		for (int j = 0; j < Globals::GridLevel; j++) {
			// j no se usa ya que el pushback lo va llenando
			_grid[i].push_back(std::vector<SolidBall*>());
		}
	}
}

void GridSpace::PrintGrid() {
	// función debug
	for (int i = 0; i < _grid.size(); i++) {
		for (int j = 0; j < _grid[i].size(); j++) {
			int objectsInPosition = 0;
			Vector2 pos;
			Vector2 coords;
			for (int k = 0; k < _grid[i][j].size(); k++) {
				pos = _grid[i][j][k]->currentPosition;
				coords = CoordsToGrid(pos);
				objectsInPosition++;
			}
			if(objectsInPosition > 0) std::cout << objectsInPosition << " Objetos en " << "x: " << int(coords.x) << " y: " << int(coords.y) << std::endl;
		}
	}
	std::cout << std::endl;
}

void GridSpace::DrawGrid() {
	for (int i = 0; i <= Globals::GridLevel; i++) {
		int x_start = Globals::CanvasRect.x + i * _dx;
		DrawLine(x_start, Globals::CanvasRect.y, x_start, Globals::CanvasRect.y + Globals::CanvasRect.height, { 245, 245, 245, 120 });
	}
	for (int j = 0; j <= Globals::GridLevel; j++) {
		int y_start = Globals::CanvasRect.y + j * _dy;
		DrawLine(Globals::CanvasRect.x , y_start, Globals::CanvasRect.x + Globals::CanvasRect.width, y_start, { 245, 245, 245, 120 });
	}
}

bool GridSpace::IsInsideCanvas(const Vector2& pos) {
	if (pos.x < Globals::CanvasRect.x || pos.x > Globals::CanvasRect.x + Globals::CanvasRect.width) return false;
	if (pos.y < Globals::CanvasRect.y || pos.y > Globals::CanvasRect.y + Globals::CanvasRect.height) return false;
	return true;
}

int GridSpace::GetTotalObjects() {
	return _numberOfObjects;
}

int GridSpace::GetObjectAtPos(const Vector2& pos) {
	// Referes to the center of the object
	// returns the index from the _balls vector
	for (int i = 0; i < _balls.size(); i++) {
		if (pos.x == _balls[i]->currentPosition.x && pos.y == _balls[i]->currentPosition.y) {
			return i;
		}
	}
}

bool GridSpace::ValidGridPos(const Vector2& pos) {
	if (pos.x > Globals::GridLevel - 1 || pos.x < 0) return false;
	if (pos.y > Globals::GridLevel - 1 || pos.y < 0) return false;
	return true;
}

void GridSpace::RemoveFromGrid(SolidBall* object, const Vector2& coords) {
	// Finds object in grid and remove it

	for (int j = 0; j < _grid[coords.x][coords.y].size(); j++) {
		Vector2 checkPos = { object->currentPosition.x, object->currentPosition.y };
		if (checkPos.x == _grid[coords.x][coords.y][j]->currentPosition.x && checkPos.y == _grid[coords.x][coords.y][j]->currentPosition.y) {
			_grid[coords.x][coords.y].erase(_grid[coords.x][coords.y].begin() + j);
		}
	}
}

Color GridSpace::Rainbow(int index) {
	if (index > 255 || index < 0) return RAYWHITE;
	float tau = PI * 2;

	unsigned char red = 128 + sinf(index * tau / 255 + 0) * 127;
	unsigned char grn = 128 + sinf(index * tau / 255 + tau / 3) * 127;
	unsigned char blu = 128 + sinf(index * tau / 255 + 2 * tau / 3) * 127;
	
	return {red, grn, blu, 255};
}

// Old way
//CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2); 
/*if (CheckCollisionCircles(*circleOne, *radiusOne, *circleTwo, *radiusTwo)) {
			std::cout << "Collision!" << std::endl;
		}*/