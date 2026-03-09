/*
#include <GL/glut.h>
#include <math.h>

void drawCircle(int x, int y, int radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 180; i < 360; i++) {
        float theta = i * 3.14159265 / 180;
        glVertex2f(x + radius * cos(theta), y + radius * sin(theta));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawCircle(150, 200, 40, 1.0, 0.0, 0.0);
    drawCircle(300, 300, 60, 0.0, 1.0, 0.0);
    drawCircle(500, 150, 50, 0.0, 0.0, 1.0);

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
    glutCreateWindow("Lingkaran");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/
