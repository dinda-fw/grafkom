/*
#include <GL/glut.h>

void drawRightTrapezoid(int x, int y, int topWidth, int bottomWidth, int height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x, y);                  
    glVertex2i(x + bottomWidth, y);    
    glVertex2i(x + topWidth, y + height); 
    glVertex2i(x, y + height);         
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawRightTrapezoid(50, 50, 50, 100, 80, 1.0, 0.0, 0.0);
    drawRightTrapezoid(200, 100, 80, 150, 100, 0.0, 1.0, 0.0);
    drawRightTrapezoid(400, 150, 60, 120, 120, 0.0, 0.0, 1.0);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Trapesium Siku-Siku");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/
