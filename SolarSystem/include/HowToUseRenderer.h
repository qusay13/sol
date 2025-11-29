#ifndef HOWTOUSERENDERER_H
#define HOWTOUSERENDERER_H

class HowToUseRenderer {
private:
    static void drawInstruction(float col, float& y, const char* key, const char* desc, float spacing);

public:
    static void draw();
};

#endif
