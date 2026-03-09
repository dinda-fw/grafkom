/*
#include <GL/glut.h>

void drawTriangle(int x, int y, int base, int height, float r, float g, float b) {
    glColor3f(r, g, b); 
    glBegin(GL_TRIANGLES);
    glVertex2i(x, y);           
    glVertex2i(x + base, y);    
    glVertex2i(x, y + height);  
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawTriangle(50, 50, 100, 80, 1.0f, 0.0f, 0.0f);   
    drawTriangle(200, 150, 150, 100, 0.0f, 1.0f, 0.0f); 
    drawTriangle(400, 100, 80, 150, 0.0f, 0.0f, 1.0f);  

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
    glutCreateWindow("Segitiga Siku-Siku 2D");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
*/