#include "../include/AboutRenderer.h"
#include "../include/MenuRenderer.h"
#include <GL/glut.h>

void AboutRenderer::draw() {
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
    glColor3f(0.02f, 0.02f, 0.08f);
    glVertex2f(0, 0);
    glVertex2f(800, 0);
    glColor3f(0.08f, 0.08f, 0.18f);
    glVertex2f(800, 600);
    glVertex2f(0, 600);
    glEnd();
    
    glColor3f(0.5f, 0.7f, 1.0f);
    MenuRenderer::drawTextCentered(550, "ABOUT", GLUT_BITMAP_TIMES_ROMAN_24);
    
    glColor3f(0.1f, 0.1f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(50, 50);
    glVertex2f(750, 50);
    glVertex2f(750, 500);
    glVertex2f(50, 500);
    glEnd();
    
    glColor3f(0.3f, 0.5f, 0.8f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(50, 50);
    glVertex2f(750, 50);
    glVertex2f(750, 500);
    glVertex2f(50, 500);
    glEnd();
    
    glColor3f(0.9f, 0.9f, 1.0f);
    MenuRenderer::drawTextCentered(450, "REALISTIC 3D SOLAR SYSTEM SIMULATION", GLUT_BITMAP_HELVETICA_18);
    
    glColor3f(0.7f, 0.8f, 0.9f);
    float y = 410;
    float lineSpacing = 28;
    
    MenuRenderer::drawTextCentered(y, "An interactive 3D visualization of our solar system", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing * 0.9f;
    MenuRenderer::drawTextCentered(y, "featuring all 8 planets with realistic orbital mechanics", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing * 1.8f;
    
    glColor3f(0.5f, 0.7f, 1.0f);
    MenuRenderer::drawTextCentered(y, "- - - - -  K E Y   F E A T U R E S  - - - - -", GLUT_BITMAP_HELVETICA_18);
    y -= lineSpacing * 1.5f;
    
    glColor3f(0.7f, 0.8f, 0.9f);
    MenuRenderer::drawTextCentered(y, "Realistic Sun with Dynamic Corona Effect", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing;
    MenuRenderer::drawTextCentered(y, "Accurate Relative Orbital Speeds and Distances", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing;
    MenuRenderer::drawTextCentered(y, "Natural Satellites for Earth, Jupiter, and Saturn", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing;
    MenuRenderer::drawTextCentered(y, "Beautiful Saturn Ring System", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing;
    MenuRenderer::drawTextCentered(y, "Interactive Camera with Focus Mode", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing;
    MenuRenderer::drawTextCentered(y, "Animated Starfield Background", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing;
    MenuRenderer::drawTextCentered(y, "Smooth Lighting and Shading Effects", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing * 1.8f;
    
    glColor3f(0.5f, 0.6f, 0.8f);
    MenuRenderer::drawTextCentered(y, "Built with OpenGL & GLUT", GLUT_BITMAP_HELVETICA_12);
    y -= lineSpacing * 0.9f;
    MenuRenderer::drawTextCentered(y, "Version 2.0 - 2024", GLUT_BITMAP_HELVETICA_12);
    
    glColor3f(0.6f, 0.7f, 0.9f);
    MenuRenderer::drawTextCentered(20, "Press ESC or ENTER to return to menu", GLUT_BITMAP_HELVETICA_12);
    
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glutSwapBuffers();
}
