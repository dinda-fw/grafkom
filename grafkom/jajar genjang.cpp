/*
#include <GL/glut.h>

void drawParallelogram(int x, int y, int width, int height, int offset, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2i(x, y);                  
    glVertex2i(x + width, y);          
    glVertex2i(x + width + offset, y + height); 
    glVertex2i(x + offset, y + height);        
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawParallelogram(50, 50, 100, 60, 30, 1.0, 0.0, 0.0);
    drawParallelogram(200, 100, 120, 80, 20, 0.0, 1.0, 0.0);
    drawParallelogram(400, 150, 80, 100, 40, 0.0, 0.0, 1.0);

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
    glutCreateWindow("Jajar Genjang");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/

