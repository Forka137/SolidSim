#pragma once
#include "Raylib.h"
#include <memory>
#include <vector>
#include "Globals.h"
#include "SolidBall.h"

class GridSpace {
public:
	GridSpace();

	void Input();
	void Update(float deltaTime);
	void Draw();
	void Reset();
	int GetTotalObjects();

	bool simPaused = false;

private:

	std::vector<std::vector<std::vector<SolidBall* >>> _grid;
	std::vector<std::unique_ptr<SolidBall>> _balls;
	void CreateBall(Vector2 pos, int radius);
	void DeleteBall(Vector2 pos);
	void ClearGrid();
	void DrawGrid();
	Vector2 CoordsToGrid(const Vector2& pos);
	bool IsInsideCanvas(const Vector2& pos);

	void WallCollision(SolidBall* object);
	void ObjectCollision(SolidBall* object, const Vector2& coords);
	void CheckCollisionAt(SolidBall* object, const Vector2& coords);
	void RemoveFromGrid(SolidBall* object, const Vector2& coords);
	void PrintGrid();
	int GetObjectAtPos(const Vector2& pos);
	bool ValidGridPos(const Vector2& coords);

	Color Rainbow(int index);

	int _dx = 1;
	int _dy = 1;
	int _colorIndex = 0;
	int _numberOfObjects = 0;

	Vector2 prevMousePos = { 0.0f, 0.0f };
	float _cdCounter = 0.0f;
	int _mouseCoolDown = 1; // secs
};