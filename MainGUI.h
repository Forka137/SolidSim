#pragma once
#include "BaseGUI.h"
#include "GUIElement.h"
#include "raylib.h"
#include "StaticText.h"
#include "TemporalText.h"
#include <memory>
#include <string>
#include "Globals.h"

class MainGUI :
    public BaseGUI
{
public:
    MainGUI();
    std::unique_ptr<StaticText> _signatureText;
    std::unique_ptr<StaticText> _howTo;
    std::unique_ptr<StaticText> _objectCounterText;
    std::unique_ptr<StaticText> _pauseMode;
    std::unique_ptr<StaticText> _fpsCounter;
    std::unique_ptr<StaticText> _objectSize;

    std::unique_ptr<TemporalText> _deletedText;
    std::unique_ptr<GUIElement> _menuRect;

    void Update(float deltaTime);
    int numberOfObjects = 0;
private:
    Font _font = LoadFontEx("resources/anonymous_pro_bold.ttf", 16, 0, 256);
};


