#include "Globals.h"

namespace Globals {
	Rectangle WindowRect = {0.0f, 0.0f, 1280.0f, 720.0f};
	Rectangle CanvasRect = {480.0f, 0.0f, 800.0f, 720.0f};

	int ObjectRadius = 10;
	int GridLevel = 8;		// 1, 2, 4, 5, 8, 10, 16, 20, 40, 80
	float Gravity = 300.0f;
	float Elasticity = 0.5f; // Afecta bastante la estabilidad

	int SubSteps = 2;
}