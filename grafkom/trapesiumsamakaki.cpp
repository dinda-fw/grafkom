/*
#include <GL/glut.h>

void drawIsoscelesTrapezoid(int x, int y, int topWidth, int bottomWidth, int height, float r, float g, float b) {
    int offset = (bottomWidth - topWidth) / 2; // supaya simetris
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x, y);                       // kiri bawah
    glVertex2i(x + bottomWidth, y);         // kanan bawah
    glVertex2i(x + bottomWidth - offset, y + height); // kanan atas
    glVertex2i(x + offset, y + height);     // kiri atas
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawIsoscelesTrapezoid(50, 50, 60, 100, 80, 1.0, 0.0, 0.0);
    drawIsoscelesTrapezoid(200, 100, 100, 180, 100, 0.0, 1.0, 0.0);
    drawIsoscelesTrapezoid(400, 150, 50, 120, 120, 0.0, 0.0, 1.0);

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
    glutCreateWindow("Trapesium Sama Kaki");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/