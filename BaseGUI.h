#pragma once
#include <vector>
#include "GUIElement.h"
#include <memory>

class BaseGUI
{
public:
	BaseGUI(); 
	virtual ~BaseGUI() = 0;		// No permite instancias
	virtual void GetInput();	// Process GUI Input

	void AddElement(GUIElement* element);

	virtual void Update(float deltaTime); // Update GUI Elements and logic
	void Draw();	// Draw GUI Elements

	void Show();	
	void Hide();
	void ToggleShow();

	
protected:
	
	std::vector<GUIElement*> _elements;
	bool _shouldDraw = true;
};

