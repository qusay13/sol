#ifndef STARFIELD_H
#define STARFIELD_H

const int NUM_STARS = 300;

class StarField {
private:
    float stars[NUM_STARS][3];

public:
    StarField();
    void init();
    void draw(float time);
};

#endif
