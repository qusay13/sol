#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

enum GameState {
    MENU,
    SIMULATION,
    HOW_TO_USE,
    ABOUT
};

class GameStateManager {
private:
    GameState currentState;
    int selectedButton;
    float menuAnimTime;

public:
    GameStateManager();
    GameState getCurrentState() const;
    void setCurrentState(GameState state);
    int getSelectedButton() const;
    void setSelectedButton(int button);
    void selectPrevious();
    void selectNext();
    float getMenuAnimTime() const;
    void updateMenuAnimTime(float delta);
};

#endif
