#include "../include/InputHandler.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

const int NUM_MENU_BUTTONS = 4;

InputHandler::InputHandler(GameStateManager* gs, WindowManager* wm, Camera* cam, SolarSystem* ss)
    : gameState(gs), windowMgr(wm), camera(cam), solarSystem(ss) {}

void InputHandler::handleKeyboard(unsigned char key, int x, int y) {
    GameState state = gameState->getCurrentState();
    
    switch (state) {
        case MENU:
            handleMenuKeyboard(key);
            break;
        case SIMULATION:
            handleSimulationKeyboard(key);
            break;
        case HOW_TO_USE:
        case ABOUT:
            if (key == 13 || key == 27) {
                gameState->setCurrentState(MENU);
                gameState->setSelectedButton(0);
            }
            break;
    }
}

void InputHandler::handleSpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_F11) {
        windowMgr->toggleFullscreen();
        return;
    }
    
    if (gameState->getCurrentState() == MENU) {
        switch (key) {
            case GLUT_KEY_UP:
                gameState->selectPrevious();
                break;
            case GLUT_KEY_DOWN:
                gameState->selectNext();
                break;
        }
        glutPostRedisplay();
    }
}

void InputHandler::handleMouse(int button, int state, int x, int y) {
    if (gameState->getCurrentState() == MENU) {
        handleMenuMouse(button, state, x, y);
        return;
    }
    
    if (gameState->getCurrentState() == SIMULATION) {
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                camera->startDrag(x, y);
            } else {
                camera->stopDrag();
            }
        }
        
        if (state == GLUT_DOWN) {
            if (button == 3) {
                camera->zoomIn(2.0f);
                glutPostRedisplay();
            } else if (button == 4) {
                camera->zoomOut(2.0f);
                glutPostRedisplay();
            }
        }
    }
}

void InputHandler::handleMouseMotion(int x, int y) {
    if (gameState->getCurrentState() == SIMULATION) {
        camera->drag(x, y);
        glutPostRedisplay();
    }
}

void InputHandler::handlePassiveMotion(int x, int y) {
    if (gameState->getCurrentState() == MENU) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y;
        
        float buttonWidth = 300;
        float buttonHeight = 50;
        float buttonX = 250;
        float startY = 360;
        float spacing = 70;
        
        for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
            float by = startY - i * spacing;
            if (x >= buttonX && x <= buttonX + buttonWidth &&
                y >= by && y <= by + buttonHeight) {
                if (gameState->getSelectedButton() != i) {
                    gameState->setSelectedButton(i);
                    glutPostRedisplay();
                }
                return;
            }
        }
    }
}

void InputHandler::handleMenuKeyboard(unsigned char key) {
    switch (key) {
        case 13:
            switch (gameState->getSelectedButton()) {
                case 0:
                    gameState->setCurrentState(SIMULATION);
                    printf("Starting simulation...\n");
                    break;
                case 1:
                    gameState->setCurrentState(HOW_TO_USE);
                    break;
                case 2:
                    gameState->setCurrentState(ABOUT);
                    break;
                case 3:
                    printf("Exiting...\n");
                    exit(0);
                    break;
            }
            break;
        case 27:
            exit(0);
            break;
    }
}

void InputHandler::handleSimulationKeyboard(unsigned char key) {
    switch (key) {
        case 'w':
        case 'W':
            camera->zoomIn(1.0f);
            break;
        case 's':
        case 'S':
            camera->zoomOut(1.0f);
            break;
        case '+':
        case '=':
            solarSystem->increaseSpeed();
            break;
        case '-':
        case '_':
            solarSystem->decreaseSpeed();
            break;
        case '0':
            camera->setFocusedPlanet(-1);
            camera->setFocusDistance(15.0f);
            camera->setAngleX(20.0f);
            camera->setAngleY(0.0f);
            printf("Focused on: Sun\n");
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            {
                int planetIdx = key - '1';
                camera->setFocusedPlanet(planetIdx);
                camera->setAngleX(15.0f);
                camera->setAngleY(0.0f);
                Planet* planet = solarSystem->getPlanet(planetIdx);
                if (planet) {
                    printf("Focused on: %s\n", planet->getName());
                }
            }
            break;
        case '9':
            camera->setFocusedPlanet(-2);
            camera->setDistance(50.0f);
            camera->setAngleX(20.0f);
            camera->setAngleY(0.0f);
            printf("Overview mode\n");
            break;
        case 'a':
        case 'A':
            camera->toggleAutoRotate();
            printf("Auto-rotate: %s\n", camera->getAutoRotate() ? "ON" : "OFF");
            break;
        case 27:
            gameState->setCurrentState(MENU);
            gameState->setSelectedButton(0);
            printf("Returned to menu\n");
            break;
    }
    glutPostRedisplay();
}

void InputHandler::handleMenuMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y;
        
        float buttonWidth = 300;
        float buttonHeight = 50;
        float buttonX = 250;
        float startY = 360;
        float spacing = 70;
        
        for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
            float by = startY - i * spacing;
            if (x >= buttonX && x <= buttonX + buttonWidth &&
                y >= by && y <= by + buttonHeight) {
                gameState->setSelectedButton(i);
                handleMenuKeyboard(13);
                break;
            }
        }
    }
}
