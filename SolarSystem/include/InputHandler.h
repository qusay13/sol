#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "GameStateManager.h"
#include "WindowManager.h"
#include "Camera.h"
#include "SolarSystem.h"

class InputHandler {
private:
    GameStateManager* gameState;
    WindowManager* windowMgr;
    Camera* camera;
    SolarSystem* solarSystem;
    
    void handleMenuKeyboard(unsigned char key);
    void handleSimulationKeyboard(unsigned char key);
    void handleMenuMouse(int button, int state, int x, int y);

public:
    InputHandler(GameStateManager* gs, WindowManager* wm, Camera* cam, SolarSystem* ss);
    void handleKeyboard(unsigned char key, int x, int y);
    void handleSpecialKeys(int key, int x, int y);
    void handleMouse(int button, int state, int x, int y);
    void handleMouseMotion(int x, int y);
    void handlePassiveMotion(int x, int y);
};

#endif
