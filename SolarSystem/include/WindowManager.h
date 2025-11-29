#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

class WindowManager {
private:
    bool isFullscreen;
    int windowWidth;
    int windowHeight;
    int windowPosX;
    int windowPosY;

public:
    WindowManager();
    void toggleFullscreen();
    bool getIsFullscreen() const;
};

#endif
