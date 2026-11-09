#include <windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "globals.h"
#include "renderer.h"
#include "input_management.h"

int main(int argc, char* argv[]) {
    AfiseazaControaleConsola();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Folosim constexpr-urile din Config!
    glutInitWindowSize(Config::WIN_WIDTH, Config::WIN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Proiect Racheta - OpenGL");

    glutMouseFunc(MouseClick);
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(SpacePress);
    glutKeyboardUpFunc(SpaceRelease);

    glewInit();
    Initialize();

    glutDisplayFunc(RenderFunction);
    glutPassiveMotionFunc(MouseMotion);
    glutTimerFunc(16, TimerFunction, 0);
    glutCloseFunc(Cleanup);

    glutMainLoop();
    return 0;
}