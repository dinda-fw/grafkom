/*
#include <GL/glut.h>

void drawRhombus(int x, int y, int width, int height, float r, float g, float b) {
    int halfW = width / 2;
    int halfH = height / 2;
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x, y + halfH);   
    glVertex2i(x + halfW, y);    
    glVertex2i(x, y - halfH);    
    glVertex2i(x - halfW, y);    
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawRhombus(150, 200, 80, 80, 1.0, 0.0, 0.0);
    drawRhombus(300, 300, 120, 100, 0.0, 1.0, 0.0);
    drawRhombus(500, 150, 100, 150, 0.0, 0.0, 1.0);

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
    glutCreateWindow("Belah Ketupat");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/

