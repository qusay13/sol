#ifndef CAMERA_H
#define CAMERA_H

class Camera {
private:
    float distance;
    float angleX;
    float angleY;
    int lastMouseX;
    int lastMouseY;
    bool mousePressed;
    int focusedPlanet;
    float focusDistance;
    bool autoRotate;

public:
    Camera();
    float getDistance() const;
    float getAngleX() const;
    float getAngleY() const;
    int getFocusedPlanet() const;
    float getFocusDistance() const;
    bool getAutoRotate() const;
    void setDistance(float d);
    void setAngleX(float a);
    void setAngleY(float a);
    void setFocusedPlanet(int p);
    void setFocusDistance(float d);
    void toggleAutoRotate();
    void zoomIn(float amount);
    void zoomOut(float amount);
    void startDrag(int x, int y);
    void stopDrag();
    void drag(int x, int y);
    bool isMousePressed() const;
};

#endif
