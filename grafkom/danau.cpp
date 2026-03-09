
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// --- STRUKTUR DATA ---
struct Point { float x, z; };

// --- VARIABEL GLOBAL ---
std::vector<Point> lakeShape;
float camX = 0.0f, camY = 60.0f, camZ = 100.0f;
float angle = 0.0f, pitch = -0.6f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
bool isLeftClick = false, isRightClick = false;
int xOrigin = -1, yOrigin = -1;

// --- PALET WARNA UPDATE ---
const float COLOR_WATER[] = { 0.1f, 0.4f, 0.6f, 0.9f };
const float COLOR_PAVING[] = { 0.85f, 0.85f, 0.85f, 1.0f };

// PERUBAHAN 1: ALAS JADI ABU TUA
const float COLOR_GRASS[] = { 0.3f, 0.3f, 0.3f, 1.0f }; // Abu Tua

// PERUBAHAN 2: ATAP GEDUNG PANJANG JADI PUTIH (Sesuai Request)
const float COLOR_ROOF_A[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Atap Putih

// Warna Bangunan Lain
const float COLOR_WALL_MAROON[] = { 0.55f, 0.1f, 0.1f, 1.0f };
const float COLOR_WALL_WHITE[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const float COLOR_DOME[] = { 0.1f, 0.6f, 0.3f, 1.0f };
const float COLOR_TRUNK[] = { 0.4f, 0.25f, 0.1f, 1.0f };
const float COLOR_LEAF[] = { 0.1f, 0.55f, 0.1f, 1.0f };
const float COLOR_FENCE[] = { 0.2f, 0.2f, 0.2f, 1.0f };

// --- INISIALISASI BENTUK DANAU ---
void initLakeShape() {
    lakeShape.clear();
    lakeShape.push_back({ 40.0f, -30.0f });
    lakeShape.push_back({ 40.0f,  20.0f });
    lakeShape.push_back({ 20.0f,  35.0f });
    float curveCenterX = -20.0f;
    float curveCenterZ = 35.0f;
    float radius = 15.0f;
    for (int i = 0; i <= 180; i += 10) {
        float rad = i * M_PI / 180.0f;
        float px = curveCenterX + cos(rad) * radius;
        float pz = curveCenterZ - sin(rad) * radius * 0.8f;
        lakeShape.push_back({ px, pz });
    }
    lakeShape.push_back({ -40.0f,  20.0f });
    lakeShape.push_back({ -40.0f, -30.0f });
    lakeShape.push_back({ -30.0f, -40.0f });
    lakeShape.push_back({ 30.0f, -40.0f });
}

// --- FUNGSI GAMBAR ---
void drawCube() {
    glutSolidCube(1.0f);
}

void drawFenceSegment(Point p1, Point p2) {
    float dx = p2.x - p1.x;
    float dz = p2.z - p1.z;
    float dist = sqrt(dx * dx + dz * dz);
    float rotAngle = atan2(dz, dx) * 180.0f / M_PI;
    glPushMatrix();
    glTranslatef(p1.x + dx / 2.0f, 0.6f, p1.z + dz / 2.0f);
    glRotatef(-rotAngle, 0.0f, 1.0f, 0.0f);
    glColor3fv(COLOR_FENCE);
    glPushMatrix(); glTranslatef(0, 0.3, 0); glScalef(dist, 0.1, 0.1); drawCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(0, -0.2, 0); glScalef(dist, 0.1, 0.1); drawCube(); glPopMatrix();
    float postSpacing = 1.5f; int numPosts = (int)(dist / postSpacing); if (numPosts < 1) numPosts = 1;
    for (int i = 0; i <= numPosts; i++) {
        float offset = -dist / 2.0f + i * (dist / (float)numPosts);
        glPushMatrix(); glTranslatef(offset, 0.0, 0); glScalef(0.15, 1.3, 0.15); drawCube(); glPopMatrix();
    }
    glPopMatrix();
}

void drawTree(float x, float z, float hScale) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glScalef(hScale, hScale, hScale);
    glColor3fv(COLOR_TRUNK);
    glPushMatrix(); glScalef(0.6f, 2.5f, 0.6f); glRotatef(-90, 1, 0, 0); glutSolidCone(0.5, 2.0, 8, 2); glPopMatrix();
    glColor3fv(COLOR_LEAF);
    glPushMatrix(); glTranslatef(0, 1.5, 0); glRotatef(-90, 1, 0, 0); glutSolidCone(2.5, 4.0, 8, 2); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 2.5, 0); glRotatef(-90, 1, 0, 0); glutSolidCone(2.0, 3.5, 8, 2); glPopMatrix();
    glPopMatrix();
}

// --- FUNGSI BANGUNAN ---

// GAPURA (Putih)
void drawGate() {
    glPushMatrix();
    glColor3fv(COLOR_WALL_WHITE);
    glPushMatrix(); glTranslatef(-4.0f, 4.0f, 0.0f); glScalef(2.0f, 8.0f, 2.0f); drawCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(4.0f, 4.0f, 0.0f); glScalef(2.0f, 8.0f, 2.0f); drawCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 7.0f, 0.0f); glScalef(10.0f, 2.0f, 4.0f); drawCube(); glPopMatrix();
    glPopMatrix();
}

// MASJID (Putih, Kubah Hijau)
void drawMosque() {
    glPushMatrix();
    glColor3fv(COLOR_WALL_WHITE);
    glPushMatrix(); glTranslatef(0.0f, 5.0f, 0.0f); glScalef(15.0f, 10.0f, 15.0f); drawCube(); glPopMatrix();
    glColor3fv(COLOR_DOME);
    glPushMatrix(); glTranslatef(0.0f, 10.0f, 0.0f); glutSolidSphere(6.0f, 20, 20); glPopMatrix();
    glPopMatrix();
}

// GEDUNG PANJANG (Maroon, Atap Putih)
void drawBuilding(float w, float l, float h) {
    glPushMatrix();
    // Dinding Maroon
    glColor3fv(COLOR_WALL_MAROON);
    glPushMatrix(); glTranslatef(0, h / 2.0f, 0); glScalef(w, h, l); drawCube(); glPopMatrix();

    // Atap Putih (COLOR_ROOF_A sekarang putih)
    glColor3fv(COLOR_ROOF_A);
    glPushMatrix(); glTranslatef(0, h, 0); glScalef(w + 2, h * 0.7f, l + 2);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0.5, 0); glVertex3f(-0.5, -0.5, 0.5); glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0, 0.5, 0); glVertex3f(0.5, -0.5, 0.5); glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0, 0.5, 0); glVertex3f(0.5, -0.5, -0.5); glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0, 0.5, 0); glVertex3f(-0.5, -0.5, -0.5); glVertex3f(-0.5, -0.5, 0.5);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}

void drawMonument() {
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix(); glScalef(1.0f, 0.1f, 1.0f); glutSolidSphere(5.0f, 20, 20); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 3, 0); glScalef(1.5f, 6.0f, 1.5f); drawCube(); glPopMatrix();
    glPushMatrix(); glTranslatef(0, 6.5, 0); glutSolidSphere(1.0f, 10, 10); glPopMatrix();
    glPopMatrix();
}

void drawScene() {
    // Environment (Alas sekarang Abu Tua)
    glColor3fv(COLOR_GRASS); glPushMatrix(); glTranslatef(0, -0.3, 0); glScalef(300, 0.1, 300); drawCube(); glPopMatrix();
    glColor3fv(COLOR_PAVING); glPushMatrix(); glTranslatef(0.0f, -0.1f, 0.0f);
    glBegin(GL_POLYGON); for (Point p : lakeShape) glVertex3f(p.x * 1.3f, 0.0f, p.z * 1.3f); glEnd(); glPopMatrix();

    // Danau & Pagar
    glColor3fv(COLOR_WATER); glBegin(GL_POLYGON); for (Point p : lakeShape) glVertex3f(p.x, 0.0f, p.z); glEnd();
    for (size_t i = 0; i < lakeShape.size(); i++) drawFenceSegment(lakeShape[i], lakeShape[(i + 1) % lakeShape.size()]);

    // Objek
    glPushMatrix(); glTranslatef(-25.0f, 0.0f, 40.0f); drawMonument(); glPopMatrix();
    glPushMatrix(); glTranslatef(5, 0, 5); glColor3f(0.4f, 0.3f, 0.2f); glutSolidSphere(3.5, 15, 15); drawTree(0.0f, 2.5f, 1.3f); glPopMatrix();

    // Gedung
    glPushMatrix(); glTranslatef(55.0f, 0.0f, 0.0f); glRotatef(90.0f, 0.0f, 1.0f, 0.0f); drawGate(); glPopMatrix();
    glPushMatrix(); glTranslatef(85.0f, 0.0f, 0.0f); drawMosque(); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.0f, -70.0f); drawBuilding(80.0f, 20.0f, 12.0f); glPopMatrix();

    // Pohon
    for (int z = -60; z <= 60; z += 15) drawTree(-65.0f, (float)z, 1.3f);
    for (int x = -50; x <= 50; x += 15) drawTree((float)x, -85.0f, 1.3f);
    for (int x = -40; x <= 60; x += 15) drawTree((float)x, 55.0f, 1.2f);
    for (int z = -50; z <= 50; z += 20) { if (z > -10 && z < 10) continue; drawTree(85.0f, (float)z, 1.2f); drawTree(100.0f, (float)z, 1.4f); }
}

// --- SISTEM KAMERA & KONTROL ---
void updateCameraVectors() { lx = sin(angle); ly = sin(pitch); lz = -cos(angle); }
void renderScene(void) {
    // Membersihkan layar dengan warna background yang sudah diset (Biru Muda)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, camX + lx, camY + ly, camZ + lz, 0.0f, 1.0f, 0.0f);
    drawScene(); glutSwapBuffers();
}
void changeSize(int w, int h) {
    if (h == 0)h = 1; float r = 1.0 * w / h; glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45, r, 1, 1000); glMatrixMode(GL_MODELVIEW);
}
void processNormalKeys(unsigned char k, int x, int y) {
    float s = 2.0f;
    switch (k) {
    case 27: exit(0); break; case '1': camX = 0; camY = 60; camZ = 100; angle = 0; pitch = -0.6; break; case '2': camX = 0; camY = 180; camZ = 1; angle = 0; pitch = -1.56; break;
    case 'w': camX += lx * s; camZ += lz * s; break; case 's': camX -= lx * s; camZ -= lz * s; break; case 'a': camX += lz * s; camZ -= lx * s; break; case 'd': camX -= lz * s; camZ += lx * s; break; case 'q': camY += s; break; case 'e': camY -= s; break;
    }
    updateCameraVectors(); glutPostRedisplay();
}
void mouseButton(int b, int s, int x, int y) { if (b == GLUT_LEFT_BUTTON) { isLeftClick = (s == GLUT_DOWN); xOrigin = x; yOrigin = y; } else if (b == GLUT_RIGHT_BUTTON) { isRightClick = (s == GLUT_DOWN); yOrigin = y; } }
void mouseMove(int x, int y) {
    if (isLeftClick) { angle += (x - xOrigin) * 0.005f; pitch -= (y - yOrigin) * 0.005f; xOrigin = x; yOrigin = y; updateCameraVectors(); }
    if (isRightClick) { float d = (y - yOrigin) * 0.8f; camX -= lx * d; camZ -= lz * d; camY -= ly * d; yOrigin = y; } glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100); glutInitWindowSize(1024, 768);
    glutCreateWindow("Danau Unesa Final - Langit Biru & Alas Abu");
    glEnable(GL_DEPTH_TEST);

    // PERUBAHAN 3: SET WARNA BACKGROUND (LANGIT) JADI BIRU MUDA
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    initLakeShape(); updateCameraVectors();
    glutDisplayFunc(renderScene); glutReshapeFunc(changeSize); glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys); glutMouseFunc(mouseButton); glutMotionFunc(mouseMove);
    std::cout << "Kontrol: WASD (Geser), QE (Naik/Turun), Mouse Kiri (Lihat), 1/2 (Preset)" << std::endl;
    glutMainLoop(); return 1;
}
