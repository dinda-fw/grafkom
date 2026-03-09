/*
#include <GL/glut.h>

void drawKite(int x, int y, int vertical, int horizontal, float r, float g, float b) {
    int halfV = vertical / 2;
    int halfH = horizontal / 2;
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x, y + halfV);    
    glVertex2i(x + halfH, y);    
    glVertex2i(x, y - halfV);    
    glVertex2i(x - halfH, y);    
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawKite(150, 200, 120, 60, 1.0, 0.0, 0.0);
    drawKite(300, 300, 160, 80, 0.0, 1.0, 0.0);
    drawKite(500, 150, 200, 70, 0.0, 0.0, 1.0);

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
    glutCreateWindow("Layang-Layang");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/

