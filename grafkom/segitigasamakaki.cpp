/*
#include <GL/glut.h>

void drawIsoscelesTriangle(int x, int y, int base, int height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2i(x, y);              
    glVertex2i(x + base, y);         
    glVertex2i(x + base / 2, y + height); 
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawIsoscelesTriangle(50, 50, 100, 80, 1.0, 0.0, 0.0);  
    drawIsoscelesTriangle(200, 100, 150, 100, 0.0, 1.0, 0.0); 
    drawIsoscelesTriangle(400, 150, 80, 120, 0.0, 0.0, 1.0); 

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
    glutCreateWindow("Segitiga Sama Kaki");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/