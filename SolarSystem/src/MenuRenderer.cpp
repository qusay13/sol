#include "../include/MenuRenderer.h"
#include <GL/glut.h>
#include <string.h>
#include <math.h>

void MenuRenderer::drawText2D(float x, float y, const char* text, void* font) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

void MenuRenderer::drawTextCentered(float y, const char* text, void* font) {
    int len = strlen(text);
    int width = 0;
    for (int i = 0; i < len; i++) {
        width += glutBitmapWidth(font, text[i]);
    }
    drawText2D(400 - width / 2.0f, y, text, font);
}

void MenuRenderer::drawGradientRect(float x, float y, float w, float h, 
                               float r1, float g1, float b1, 
                               float r2, float g2, float b2) {
    glBegin(GL_QUADS);
    glColor3f(r1, g1, b1);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glColor3f(r2, g2, b2);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void MenuRenderer::drawButton(float x, float y, float w, float h, 
                        const char* text, bool selected, float animTime) {
    float glow = selected ? 0.3f + 0.1f * sin(animTime * 5.0f) : 0.0f;
    
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(x + 5, y - 5);
    glVertex2f(x + w + 5, y - 5);
    glVertex2f(x + w + 5, y + h - 5);
    glVertex2f(x + 5, y + h - 5);
    glEnd();
    
    if (selected) {
        drawGradientRect(x, y, w, h, 0.1f + glow, 0.3f + glow, 0.6f + glow, 
                       0.05f + glow, 0.2f + glow, 0.5f + glow);
    } else {
        drawGradientRect(x, y, w, h, 0.15f, 0.15f, 0.25f, 0.1f, 0.1f, 0.2f);
    }
    
    glLineWidth(2.0f);
    if (selected) {
        glColor3f(0.3f + glow, 0.6f + glow, 1.0f);
    } else {
        glColor3f(0.3f, 0.3f, 0.4f);
    }
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
    
    if (selected) {
        glColor3f(1.0f, 1.0f, 1.0f);
    } else {
        glColor3f(0.7f, 0.7f, 0.8f);
    }
    
    int len = strlen(text);
    int textWidth = 0;
    for (int i = 0; i < len; i++) {
        textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    drawText2D(x + (w - textWidth) / 2.0f, y + h / 2.0f - 5, text, GLUT_BITMAP_HELVETICA_18);
}

void MenuRenderer::draw(int selectedButton, float menuAnimTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glBegin(GL_QUADS);
    glColor3f(0.01f, 0.01f, 0.05f);
    glVertex2f(0, 0);
    glVertex2f(800, 0);
    glColor3f(0.05f, 0.05f, 0.15f);
    glVertex2f(800, 600);
    glVertex2f(0, 600);
    glEnd();
    
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
        float x = (i * 73) % 800;
        float y = (i * 137) % 600;
        float brightness = 0.5f + 0.5f * sin(menuAnimTime + i * 0.1f);
        glColor3f(brightness, brightness, brightness);
        glVertex2f(x, y);
    }
    glEnd();
    
    glColor3f(0.2f, 0.4f, 0.8f);
    drawTextCentered(520, "SOLAR SYSTEM", GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.5f + 0.2f * sin(menuAnimTime * 2.0f), 
              0.7f + 0.2f * sin(menuAnimTime * 2.0f), 1.0f);
    drawTextCentered(520, "SOLAR SYSTEM", GLUT_BITMAP_TIMES_ROMAN_24);
    
    glColor3f(0.6f, 0.7f, 0.9f);
    drawTextCentered(480, "3D Interactive Simulation", GLUT_BITMAP_HELVETICA_12);
    
    float buttonWidth = 300;
    float buttonHeight = 50;
    float buttonX = 250;
    float startY = 360;
    float spacing = 70;
    
    const char* buttonLabels[] = {"START", "HOW TO USE", "ABOUT", "EXIT"};
    
    for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
        drawButton(buttonX, startY - i * spacing, buttonWidth, buttonHeight, 
                  buttonLabels[i], selectedButton == i, menuAnimTime);
    }
    
    glColor3f(0.4f, 0.4f, 0.5f);
    drawTextCentered(30, "Use UP/DOWN arrows or mouse to select | ENTER to confirm | F11 for fullscreen", 
                    GLUT_BITMAP_HELVETICA_10);
    
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glutSwapBuffers();
}
