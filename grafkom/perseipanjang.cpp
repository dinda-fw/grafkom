/*
#include <GL/glut.h>

void drawRectangle(int x, int y, int width, int height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawRectangle(50, 50, 100, 50, 1.0f, 0.0f, 0.0f);   // merah
    drawRectangle(200, 100, 150, 80, 0.0f, 1.0f, 0.0f); // hijau
    drawRectangle(400, 150, 80, 120, 0.0f, 0.0f, 1.0f); // biru

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
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Persegi Panjang 2D");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/