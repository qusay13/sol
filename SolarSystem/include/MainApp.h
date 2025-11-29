#ifndef MAINAPP_H
#define MAINAPP_H

#include "AudioManager.h"
#include "GameStateManager.h"
#include "WindowManager.h"
#include "Camera.h"
#include "StarField.h"
#include "SolarSystem.h"
#include "Renderer.h"
#include "InputHandler.h"

class MainApp {
private:
    AudioManager* audioMgr;
    GameStateManager* gameState;
    WindowManager* windowMgr;
    Camera* camera;
    StarField* starField;
    SolarSystem* solarSystem;
    Renderer* renderer;
    InputHandler* inputHandler;
    
    static MainApp* instance;

public:
    MainApp();
    ~MainApp();
    void init();
    void run();
    void display();
    void update();
    void reshape(int w, int h);
    void setupCallbacks();
    
    static void displayCallback();
    static void reshapeCallback(int w, int h);
    static void updateCallback(int value);
    static void keyboardCallback(unsigned char key, int x, int y);
    static void specialKeysCallback(int key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);
    static void passiveMotionCallback(int x, int y);
};

#endif
