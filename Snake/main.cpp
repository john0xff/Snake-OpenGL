#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "map.h"

char keys[256];

Map map;

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    map.drawPlayer();

    map.drawPoint();

    glFlush();
    glutSwapBuffers();
}

void reshapre(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    map.ortho2Dfunc();
}

void keyDown(unsigned char key, int x, int y)
{
    keys[key] = true;
}

void keyUp(unsigned char key, int x, int y)
{
    keys[key] = false;
}

void idle()
{
    map.updatePlayer(keys);

    map.mapContition();

   // map.playerCondition();

    if(map.mapContition() == false)
        exit(0);

    if(map.playerCondition() == false)
        exit(0);

    glutPostRedisplay();

    Sleep(100);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("BoulderDash2");

    glutKeyboardUpFunc(keyUp);
    glutKeyboardFunc(keyDown);

    glutDisplayFunc(display);
    glutReshapeFunc(reshapre);

    glutIdleFunc(idle);


    glutMainLoop();

    return 0;
}
