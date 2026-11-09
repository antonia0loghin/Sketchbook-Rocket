#include "input_management.h"
#include "globals.h"
void MouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isFlying = true;
    }
}
void SpacePress(unsigned char key, int x, int y) {
    if (key == ' ') {
        isTurbo = true;
        turboTimer = 0.25f;
    }
    if (key == 'd' || key == 'D') {
        indexCuloare = (indexCuloare + 1) % 7;
        glutPostRedisplay();
    }
    if (key == 'a' || key == 'A') {
        indexCuloare = (indexCuloare - 1 + 7) % 7;
        glutPostRedisplay();
    }
};

void SpaceRelease(unsigned char key, int x, int y) {
    if (key == ' ') {
        isTurbo = false;
        turboTimer = 0.0f;
    }
}
void MouseMotion(int x, int y) {
    mouseX = (float)x / (Config::WIN_WIDTH / 2.0f) - 1.0f;
    mouseY = 1.0f - (float)y / (Config::WIN_HEIGHT / 2.0f);
}

