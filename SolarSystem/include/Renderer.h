#ifndef RENDERER_H
#define RENDERER_H

#include "StarField.h"
#include "SolarSystem.h"
#include "Camera.h"

class Renderer {
private:
    StarField* starField;
    SolarSystem* solarSystem;
    Camera* camera;
    
    void getCameraPosition(float& camX, float& camY, float& camZ, 
                          float& lookX, float& lookY, float& lookZ);
    void renderHUD();

public:
    Renderer(StarField* sf, SolarSystem* ss, Camera* cam);
    void initGL();
    void renderSimulation();
};

#endif
