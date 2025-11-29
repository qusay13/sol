#ifndef MENURENDERER_H
#define MENURENDERER_H

const int NUM_MENU_BUTTONS = 4;

class MenuRenderer {
public:
    static void drawText2D(float x, float y, const char* text, void* font);
    static void drawTextCentered(float y, const char* text, void* font);
    static void drawGradientRect(float x, float y, float w, float h, 
                                   float r1, float g1, float b1, 
                                   float r2, float g2, float b2);
    static void drawButton(float x, float y, float w, float h, 
                            const char* text, bool selected, float animTime);
    static void draw(int selectedButton, float menuAnimTime);
};

#endif
