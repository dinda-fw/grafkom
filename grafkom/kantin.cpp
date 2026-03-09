
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h> // Untuk exit()

#define PI 3.14159265

// --- Variabel Kamera ---
float angleX = 20.0f;
float angleY = -30.0f;
float camZ = 110.0f;
float transY = -5.0f;

// --- Variabel Animasi ---
float cloudPos = 0.0f; // Posisi awan bergerak

int lastMouseX, lastMouseY;
bool isDragging = false;

// --- Lighting & Material ---
void initLighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // Langit Biru Cerah
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    GLfloat light_pos[] = { 60.0f, 150.0f, 100.0f, 1.0f };
    GLfloat light_amb[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat light_diff[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat light_spec[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// Fungsi bantu menggambar kubus dengan skala
void drawBox(float w, float h, float d) {
    glPushMatrix();
    glScalef(w, h, d);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// ================= ORNAMEN & DETIL OBJEK =================

// 1. Food Stand (Tenda Kecil) - Diperbaiki Geometrinya
void drawFoodStand() {
    // Meja Counter
    glColor3f(0.8f, 0.8f, 0.8f); // Putih
    glPushMatrix(); glTranslatef(0.0f, 0.5f, 0.0f); drawBox(3.0f, 1.0f, 1.5f); glPopMatrix();

    // Etalase Kaca
    glColor3f(0.6f, 0.8f, 1.0f); // Kaca Biru Muda
    glPushMatrix(); glTranslatef(0.0f, 1.25f, 0.2f); drawBox(2.8f, 0.5f, 1.0f); glPopMatrix();

    // Tiang Penyangga Atap
    glColor3f(0.4f, 0.2f, 0.1f); // Coklat
    glPushMatrix(); glTranslatef(1.4f, 1.5f, 0.7f); drawBox(0.1f, 2.0f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.4f, 1.5f, 0.7f); drawBox(0.1f, 2.0f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(1.4f, 1.5f, -0.7f); drawBox(0.1f, 2.0f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.4f, 1.5f, -0.7f); drawBox(0.1f, 2.0f, 0.1f); glPopMatrix();

    // Atap Tenda Belang (Merah Putih)
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    float width = 3.2f;
    float stripeW = width / 6.0f;
    for (int i = 0; i < 6; i++) {
        if (i % 2 == 0) glColor3f(0.9f, 0.1f, 0.1f); // Merah
        else glColor3f(1.0f, 1.0f, 1.0f);       // Putih

        glPushMatrix();
        glTranslatef(-width / 2.0f + i * stripeW + stripeW / 2.0f, 0.0f, 0.0f);

        // Segitiga Depan
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 0.5f, 1.0f);
        glVertex3f(0.0f, 1.0f, 1.0f); // Puncak Depan
        glVertex3f(-stripeW / 2.0f, 0.0f, 1.0f);
        glVertex3f(stripeW / 2.0f, 0.0f, 1.0f);
        glEnd();

        // Segitiga Belakang
        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 0.5f, -1.0f);
        glVertex3f(0.0f, 1.0f, -1.0f); // Puncak Belakang
        glVertex3f(stripeW / 2.0f, 0.0f, -1.0f);
        glVertex3f(-stripeW / 2.0f, 0.0f, -1.0f);
        glEnd();

        // Sisi Miring Kanan
        glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.5f, 0.0f);
        glVertex3f(0.0f, 1.0f, 1.0f);
        glVertex3f(stripeW / 2.0f, 0.0f, 1.0f);
        glVertex3f(stripeW / 2.0f, 0.0f, -1.0f);
        glVertex3f(0.0f, 1.0f, -1.0f);
        glEnd();

        // Sisi Miring Kiri
        glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.5f, 0.0f);
        glVertex3f(0.0f, 1.0f, -1.0f);
        glVertex3f(-stripeW / 2.0f, 0.0f, -1.0f);
        glVertex3f(-stripeW / 2.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 1.0f);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}

// 2. Food Container (Kontainer Modern)
void drawFoodContainer(float r, float g, float b) {
    // Badan Kontainer
    glColor3f(r, g, b);
    glPushMatrix(); glTranslatef(0.0f, 1.25f, 0.0f); drawBox(5.0f, 2.5f, 2.5f); glPopMatrix();

    // Jendela Layanan
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix(); glTranslatef(0.0f, 1.5f, 1.26f); drawBox(3.0f, 1.0f, 0.1f); glPopMatrix();

    // Meja Layanan
    glColor3f(0.5f, 0.3f, 0.1f);
    glPushMatrix(); glTranslatef(0.0f, 1.0f, 1.5f); drawBox(3.2f, 0.1f, 0.6f); glPopMatrix();

    // Kanopi
    glColor3f(r * 0.8f, g * 0.8f, b * 0.8f);
    glPushMatrix();
    glTranslatef(0.0f, 2.3f, 1.8f);
    glRotatef(60, 1, 0, 0);
    drawBox(3.2f, 0.1f, 1.2f);
    glPopMatrix();

    // Pintu
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix(); glTranslatef(2.0f, 1.1f, 1.26f); drawBox(0.8f, 2.0f, 0.05f); glPopMatrix();
}

// 3. Orang-orangan
void drawPerson(float r, float g, float b) {
    glColor3f(0.2f, 0.2f, 0.2f); // Kaki
    glPushMatrix(); glTranslatef(-0.15f, 0.75f, 0.0f); drawBox(0.12f, 1.5f, 0.15f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.15f, 0.75f, 0.0f); drawBox(0.12f, 1.5f, 0.15f); glPopMatrix();
    glColor3f(r, g, b); // Badan
    glPushMatrix(); glTranslatef(0.0f, 1.9f, 0.0f); drawBox(0.5f, 1.1f, 0.3f); glPopMatrix();
    glColor3f(0.9f, 0.8f, 0.7f); // Kepala
    glPushMatrix(); glTranslatef(0.0f, 2.7f, 0.0f); glutSolidSphere(0.25f, 10, 10); glPopMatrix();
}

// 4. Set Meja Makan
void drawTableSet() {
    glColor3f(0.9f, 0.9f, 0.9f);
    glPushMatrix(); glTranslatef(0.0f, 0.8f, 0.0f); glRotatef(-90, 1, 0, 0); glutSolidCone(1.2f, 0.1f, 16, 2); glPopMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix(); glTranslatef(0.0f, 0.4f, 0.0f); drawBox(0.2f, 0.8f, 0.2f); glPopMatrix();
    for (int i = 0; i < 4; i++) {
        glPushMatrix(); glRotatef(i * 90 + 45, 0, 1, 0); glTranslatef(1.4f, 0.0f, 0.0f);
        glColor3f(0.8f, 0.5f, 0.2f); glPushMatrix(); glTranslatef(0.0f, 0.5f, 0.0f); drawBox(0.5f, 0.1f, 0.5f); glPopMatrix();
        glColor3f(0.2f, 0.2f, 0.2f); glPushMatrix(); glTranslatef(0.0f, 0.25f, 0.0f); drawBox(0.1f, 0.5f, 0.1f); glPopMatrix();
        glPopMatrix();
    }
}

// 5. Tiang Lampu
void drawStreetLamp() {
    glColor3f(0.1f, 0.15f, 0.1f); glPushMatrix(); glTranslatef(0.0f, 2.0f, 0.0f); drawBox(0.2f, 4.0f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 3.8f, 0.4f); drawBox(0.1f, 0.1f, 1.0f); glPopMatrix();
    glColor3f(1.0f, 1.0f, 0.8f); glPushMatrix(); glTranslatef(0.0f, 3.6f, 0.8f); glutSolidSphere(0.4f, 8, 8); glPopMatrix();
    glColor3f(0.1f, 0.15f, 0.1f); glPushMatrix(); glTranslatef(0.0f, 4.0f, 0.8f); glRotatef(-90, 1, 0, 0); glutSolidCone(0.5f, 0.3f, 8, 2); glPopMatrix();
}

// 6. Pot Bunga
void drawFlowerPot() {
    glColor3f(0.7f, 0.3f, 0.1f); glPushMatrix(); glTranslatef(0.0f, 0.3f, 0.0f); drawBox(0.5f, 0.6f, 0.5f); glPopMatrix();
    glColor3f(0.1f, 0.6f, 0.1f); glPushMatrix(); glTranslatef(0.0f, 0.7f, 0.0f); glutSolidSphere(0.4f, 6, 6); glPopMatrix();
    glColor3f(1.0f, 0.2f, 0.5f); glPushMatrix(); glTranslatef(0.2f, 0.9f, 0.2f); glutSolidSphere(0.15f, 4, 4); glPopMatrix();
    glColor3f(1.0f, 0.8f, 0.2f); glPushMatrix(); glTranslatef(-0.2f, 0.8f, -0.1f); glutSolidSphere(0.15f, 4, 4); glPopMatrix();
}

// 7. Matahari
void drawSun() {
    glPushMatrix(); glTranslatef(60.0f, 70.0f, -80.0f);
    GLfloat sun_emission[] = { 1.0f, 0.9f, 0.0f, 1.0f }; GLfloat no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission); glColor3f(1.0f, 0.9f, 0.0f); glutSolidSphere(8.0f, 30, 30);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission); glPopMatrix();
}

// 8. Awan
void drawCloud(float x, float y, float z, float scale) {
    glPushMatrix(); glTranslatef(x, y, z); glScalef(scale, scale, scale); glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.0f); glutSolidSphere(3.0f, 10, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(2.5f, 0.5f, 0.0f); glutSolidSphere(2.5f, 10, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(-2.5f, -0.5f, 0.5f); glutSolidSphere(2.8f, 10, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(1.0f, 1.5f, -1.0f); glutSolidSphere(2.2f, 10, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.5f, 1.0f, 1.0f); glutSolidSphere(2.0f, 10, 10); glPopMatrix();
    glPopMatrix();
}

// 9. Elemen Lain (Tong Sampah, Batu, Jalan, Pohon, dll)
void drawTrashBin() {
    glColor3f(0.2f, 0.4f, 0.8f); glPushMatrix(); glRotatef(-90, 1, 0, 0); glutSolidCone(0.5f, 1.2f, 12, 2); glPopMatrix();
    glColor3f(0.1f, 0.1f, 0.1f); glPushMatrix(); glTranslatef(0.0f, 1.2f, 0.0f); glScalef(1.0f, 0.2f, 1.0f); glutSolidSphere(0.5f, 12, 12); glPopMatrix();
}

void drawRock() { glColor3f(0.5f, 0.5f, 0.55f); glPushMatrix(); glScalef(1.2f, 0.7f, 1.0f); glutSolidDodecahedron(); glPopMatrix(); }

void drawWildBush() { glColor3f(0.2f, 0.5f, 0.1f); glPushMatrix(); glScalef(1.5f, 0.8f, 1.2f); glutSolidDodecahedron(); glPopMatrix(); }

void drawRoad(float length, float width) {
    glColor3f(0.2f, 0.2f, 0.23f); glPushMatrix(); glTranslatef(0.0f, 0.05f, 0.0f); drawBox(length, 0.1f, width); glPopMatrix();
    glColor3f(0.9f, 0.9f, 0.9f); float stripeLen = 4.0f; float gap = 4.0f; int numStripes = (int)(length / (stripeLen + gap));
    for (int i = 0; i < numStripes; i++) { glPushMatrix(); float xPos = -length / 2.0f + i * (stripeLen + gap) + stripeLen; glTranslatef(xPos, 0.06f, 0.0f); drawBox(stripeLen, 0.02f, 0.5f); glPopMatrix(); }
}

void drawCurb(float length) {
    float segmentLen = 1.0f; int segments = (int)(length / segmentLen);
    for (int i = 0; i < segments; i++) { if (i % 2 == 0) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.1f, 0.1f, 0.1f); glPushMatrix(); glTranslatef(i * segmentLen - length / 2.0f + segmentLen / 2.0f, 0.0f, 0.0f); drawBox(segmentLen, 0.4f, 0.4f); glPopMatrix(); }
}

void drawLowRockWall(float length) {
    glColor3f(0.45f, 0.45f, 0.5f); glPushMatrix(); glTranslatef(0.0f, 0.6f, 0.0f); drawBox(length, 1.2f, 0.8f); glPopMatrix();
    glColor3f(0.3f, 0.3f, 0.35f); glPushMatrix(); glTranslatef(0.0f, 1.3f, 0.0f); drawBox(length + 0.2f, 0.2f, 1.0f); glPopMatrix();
}

void drawBigTree() {
    glColor3f(0.35f, 0.25f, 0.15f); glPushMatrix(); glTranslatef(0.0f, 2.0f, 0.0f); glScalef(0.6f, 4.0f, 0.6f); glutSolidCube(1.0f); glPopMatrix();
    glColor3f(0.1f, 0.45f, 0.1f); glPushMatrix(); glTranslatef(0.0f, 5.0f, 0.0f); glutSolidSphere(2.5f, 10, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(1.5f, 4.5f, 0.0f); glutSolidSphere(2.0f, 10, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.5f, 4.8f, 0.5f); glutSolidSphere(2.2f, 10, 10); glPopMatrix();
}

// ================= BANGUNAN UTAMA & GAZEBO =================

void drawGazebo() {
    glColor3f(0.55f, 0.4f, 0.25f); glPushMatrix(); glTranslatef(0.0f, 0.2f, 0.0f); drawBox(4.0f, 0.4f, 4.0f); glPopMatrix();
    glColor3f(0.2f, 0.1f, 0.05f); float p = 1.6f; float h = 2.5f;
    glPushMatrix(); glTranslatef(p, h / 2.0f, p); drawBox(0.2f, h, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-p, h / 2.0f, p); drawBox(0.2f, h, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(p, h / 2.0f, -p); drawBox(0.2f, h, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-p, h / 2.0f, -p); drawBox(0.2f, h, 0.2f); glPopMatrix();
    glColor3f(0.65f, 0.3f, 0.15f); glPushMatrix(); glTranslatef(0.0f, 2.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.5f, 1.0f); glVertex3f(0.0f, 1.2f, 0.0f); glVertex3f(-2.5f, 0.0f, 2.5f); glVertex3f(2.5f, 0.0f, 2.5f);
    glNormal3f(1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 1.2f, 0.0f); glVertex3f(2.5f, 0.0f, 2.5f); glVertex3f(2.5f, 0.0f, -2.5f);
    glNormal3f(0.0f, 0.5f, -1.0f); glVertex3f(0.0f, 1.2f, 0.0f); glVertex3f(2.5f, 0.0f, -2.5f); glVertex3f(-2.5f, 0.0f, -2.5f);
    glNormal3f(-1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 1.2f, 0.0f); glVertex3f(-2.5f, 0.0f, -2.5f); glVertex3f(-2.5f, 0.0f, 2.5f);
    glEnd(); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 3.2f, 0.0f); glScalef(0.5f, 0.6f, 0.5f);
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.5f, 1.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(-2.0f, 0.0f, 2.0f); glVertex3f(2.0f, 0.0f, 2.0f);
    glNormal3f(1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f); glVertex3f(2.0f, 0.0f, -2.0f);
    glNormal3f(0.0f, 0.5f, -1.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(2.0f, 0.0f, -2.0f); glVertex3f(-2.0f, 0.0f, -2.0f);
    glNormal3f(-1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(-2.0f, 0.0f, -2.0f); glVertex3f(-2.0f, 0.0f, 2.0f);
    glEnd(); glPopMatrix();
    glColor3f(0.8f, 0.8f, 0.8f); glPushMatrix(); glTranslatef(0.0f, 0.6f, 0.0f); drawBox(1.5f, 0.1f, 1.5f); glPopMatrix();
}

void drawMainGazebo() {
    glColor3f(0.4f, 0.3f, 0.2f); glPushMatrix(); glTranslatef(0.0f, 0.4f, 0.0f); drawBox(8.0f, 0.8f, 8.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.2f, 4.2f); drawBox(3.0f, 0.4f, 1.5f); glPopMatrix();
    glColor3f(0.25f, 0.15f, 0.05f); float p = 3.5f; float h = 4.0f;
    glPushMatrix(); glTranslatef(p, h / 2.0f, p); drawBox(0.4f, h, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(-p, h / 2.0f, p); drawBox(0.4f, h, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(p, h / 2.0f, -p); drawBox(0.4f, h, 0.4f); glPopMatrix();
    glPushMatrix(); glTranslatef(-p, h / 2.0f, -p); drawBox(0.4f, h, 0.4f); glPopMatrix();
    glColor3f(0.3f, 0.2f, 0.1f);
    glPushMatrix(); glTranslatef(p, 1.2f, 0.0f); drawBox(0.1f, 1.0f, 7.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(-p, 1.2f, 0.0f); drawBox(0.1f, 1.0f, 7.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 1.2f, -p); drawBox(7.0f, 1.0f, 0.1f); glPopMatrix();
    glColor3f(0.7f, 0.35f, 0.1f);
    glPushMatrix(); glTranslatef(0.0f, 4.0f, 0.0f); glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.5f, 1.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(-5.0f, 0.0f, 5.0f); glVertex3f(5.0f, 0.0f, 5.0f);
    glNormal3f(1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(5.0f, 0.0f, 5.0f); glVertex3f(5.0f, 0.0f, -5.0f);
    glNormal3f(0.0f, 0.5f, -1.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(5.0f, 0.0f, -5.0f); glVertex3f(-5.0f, 0.0f, -5.0f);
    glNormal3f(-1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(-5.0f, 0.0f, -5.0f); glVertex3f(-5.0f, 0.0f, 5.0f);
    glEnd(); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 5.0f, 0.0f); glScalef(0.7f, 1.0f, 0.7f); glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.5f, 1.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(-4.0f, 0.0f, 4.0f); glVertex3f(4.0f, 0.0f, 4.0f);
    glNormal3f(1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(4.0f, 0.0f, 4.0f); glVertex3f(4.0f, 0.0f, -4.0f);
    glNormal3f(0.0f, 0.5f, -1.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(4.0f, 0.0f, -4.0f); glVertex3f(-4.0f, 0.0f, -4.0f);
    glNormal3f(-1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 1.5f, 0.0f); glVertex3f(-4.0f, 0.0f, -4.0f); glVertex3f(-4.0f, 0.0f, 4.0f);
    glEnd(); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 6.2f, 0.0f); glScalef(0.4f, 0.8f, 0.4f); glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.5f, 1.0f); glVertex3f(0.0f, 2.0f, 0.0f); glVertex3f(-4.0f, 0.0f, 4.0f); glVertex3f(4.0f, 0.0f, 4.0f);
    glNormal3f(1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 2.0f, 0.0f); glVertex3f(4.0f, 0.0f, 4.0f); glVertex3f(4.0f, 0.0f, -4.0f);
    glNormal3f(0.0f, 0.5f, -1.0f); glVertex3f(0.0f, 2.0f, 0.0f); glVertex3f(4.0f, 0.0f, -4.0f); glVertex3f(-4.0f, 0.0f, -4.0f);
    glNormal3f(-1.0f, 0.5f, 0.0f); glVertex3f(0.0f, 2.0f, 0.0f); glVertex3f(-4.0f, 0.0f, -4.0f); glVertex3f(-4.0f, 0.0f, 4.0f);
    glEnd(); glPopMatrix();
    glColor3f(0.9f, 0.9f, 0.9f); glPushMatrix(); glTranslatef(0.0f, 1.0f, 0.0f); drawBox(3.0f, 0.1f, 3.0f); glPopMatrix();
}

void drawWallLamp() {
    glColor3f(0.2f, 0.2f, 0.2f); drawBox(0.3f, 0.3f, 0.4f);
    glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.25f);
    GLfloat emission[] = { 0.9f, 0.9f, 0.6f, 1.0f }; GLfloat no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, emission); glColor3f(1.0f, 1.0f, 0.8f); glutSolidSphere(0.25f, 12, 12);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission); glPopMatrix();
}

void drawPillar() {
    glColor3f(0.2f, 0.2f, 0.25f); glPushMatrix(); glTranslatef(0.0f, 1.0f, 0.0f); drawBox(1.3f, 2.0f, 1.3f); glPopMatrix();
    glColor3f(0.0f, 0.25f, 0.85f); glPushMatrix(); glTranslatef(0.0f, 3.25f, 0.0f); drawBox(0.9f, 2.5f, 0.9f); glPopMatrix();
    glColor3f(0.9f, 0.9f, 0.95f); glPushMatrix(); glTranslatef(0.0f, 4.6f, 0.0f); drawBox(1.1f, 0.3f, 1.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 3.5f, 0.5f); drawWallLamp(); glPopMatrix();
}

void drawStoneWall(float len) {
    float h = 2.2f; glColor3f(0.3f, 0.3f, 0.35f);
    glPushMatrix(); glTranslatef(0.0f, 1.1f, 0.0f); drawBox(len, h, 0.7f); glPopMatrix();
    glColor3f(0.45f, 0.45f, 0.5f); glPushMatrix(); glTranslatef(0.0f, 2.25f, 0.0f); drawBox(len + 0.15f, 0.25f, 0.8f); glPopMatrix();
}

void drawOrangeWall() {
    float w = 4.2f; float h = 4.5f;
    glColor3f(1.0f, 0.45f, 0.0f); glPushMatrix(); glTranslatef(0.0f, h / 2.0f, 0.0f); drawBox(w, h, 0.35f); glPopMatrix();
    glColor3f(0.85f, 0.35f, 0.0f);
    for (float x = -w / 2 + 0.4f; x < w / 2; x += 0.8f) {
        glPushMatrix(); glTranslatef(x, h / 2.0f, 0.2f); drawBox(0.15f, h - 0.5f, 0.1f); glPopMatrix();
    }
    glColor3f(1.0f, 1.0f, 1.0f); glPushMatrix(); glTranslatef(0.0f, h - 0.2f, 0.0f); drawBox(w + 0.2f, 0.4f, 0.45f); glPopMatrix();
}

void drawMainDoor(float faceWidth) {
    glColor3f(0.9f, 0.85f, 0.75f); glPushMatrix(); glTranslatef(0.0f, 2.25f, 0.0f); drawBox(faceWidth + 0.5f, 4.5f, 0.5f); glPopMatrix();
    glColor3f(0.4f, 0.25f, 0.1f); float doorW = 3.0f; float doorH = 3.5f;
    glPushMatrix(); glTranslatef(0.0f, doorH / 2.0f + 0.1f, 0.3f); drawBox(doorW, doorH, 0.2f); glPopMatrix();
    glColor3f(0.2f, 0.3f, 0.4f); glPushMatrix(); glTranslatef(0.0f, doorH / 2.0f + 0.1f, 0.35f); drawBox(doorW - 0.4f, doorH - 0.4f, 0.1f); glPopMatrix();
}

void drawInnerCoreFace(float faceWidth) {
    glColor3f(0.9f, 0.85f, 0.75f); glPushMatrix(); glTranslatef(0.0f, 2.25f, 0.0f); drawBox(faceWidth + 0.5f, 4.5f, 0.5f); glPopMatrix();
    glColor3f(0.55f, 0.35f, 0.15f); glPushMatrix(); glTranslatef(0.0f, 1.4f, 0.4f); drawBox(faceWidth - 0.5f, 0.15f, 0.6f); glPopMatrix();
    glColor3f(0.2f, 0.2f, 0.25f); float windowW = faceWidth * 0.8f;
    glPushMatrix(); glTranslatef(0.0f, 2.5f, 0.3f); drawBox(windowW, 1.5f, 0.1f); glPopMatrix();
    glColor3f(0.8f, 0.8f, 0.8f);
    glPushMatrix(); glTranslatef(0.0f, 2.5f, 0.35f); drawBox(0.1f, 1.5f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 2.5f, 0.35f); drawBox(windowW, 0.1f, 0.1f); glPopMatrix();
}

// ================= SCENE UTAMA =================
void drawBuilding() {
    float R_Outer = 16.0f;
    float R_Inner = 8.5f;
    float apothemOuter = R_Outer * cos(PI / 5.0f);
    float apothemInner = R_Inner;
    float innerFaceW = 2.0f * R_Inner * tan(PI / 5.0f);

    // 1. DASAR TANAH
    glColor3f(0.35f, 0.35f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-80.0f, 0.0f, -80.0f);
    glVertex3f(80.0f, 0.0f, -80.0f);
    glVertex3f(80.0f, 0.0f, 80.0f);
    glVertex3f(-80.0f, 0.0f, 80.0f);
    glEnd();
    glPopMatrix();

    // 2. SELASAR PAVING
    glColor3f(0.6f, 0.6f, 0.65f);
    float pavingSize = 50.0f;
    glPushMatrix(); drawBox(pavingSize, 0.1f, pavingSize); glPopMatrix();

    // 3. TROTOAR & TIANG LAMPU JALAN
    glPushMatrix(); glTranslatef(0.0f, 0.2f, pavingSize / 2.0f + 0.2f); drawCurb(pavingSize); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.2f, -pavingSize / 2.0f - 0.2f); drawCurb(pavingSize); glPopMatrix();
    glPushMatrix(); glTranslatef(pavingSize / 2.0f + 0.2f, 0.2f, 0.0f); glRotatef(90, 0, 1, 0); drawCurb(pavingSize); glPopMatrix();
    glPushMatrix(); glTranslatef(-pavingSize / 2.0f - 0.2f, 0.2f, 0.0f); glRotatef(90, 0, 1, 0); drawCurb(pavingSize); glPopMatrix();

    // Lampu Jalan
    glPushMatrix(); glTranslatef(pavingSize / 2.0f + 1.0f, 0.0f, pavingSize / 2.0f + 1.0f); glRotatef(-45, 0, 1, 0); drawStreetLamp(); glPopMatrix();
    glPushMatrix(); glTranslatef(-pavingSize / 2.0f - 1.0f, 0.0f, pavingSize / 2.0f + 1.0f); glRotatef(45, 0, 1, 0); drawStreetLamp(); glPopMatrix();
    glPushMatrix(); glTranslatef(pavingSize / 2.0f + 1.0f, 0.0f, -pavingSize / 2.0f - 1.0f); glRotatef(-135, 0, 1, 0); drawStreetLamp(); glPopMatrix();
    glPushMatrix(); glTranslatef(-pavingSize / 2.0f - 1.0f, 0.0f, -pavingSize / 2.0f - 1.0f); glRotatef(135, 0, 1, 0); drawStreetLamp(); glPopMatrix();

    // 4. TEMBOK BATU & PARIT
    glPushMatrix(); glTranslatef(0.0f, 0.0f, 35.0f); drawLowRockWall(100.0f); glPopMatrix();
    glColor3f(0.25f, 0.2f, 0.15f);
    glPushMatrix(); glTranslatef(0.0f, -0.4f, 40.0f); drawBox(100.0f, 0.1f, 8.0f); glPopMatrix();

    // 5. JALAN RAYA
    glPushMatrix(); glTranslatef(0.0f, -0.4f, 55.0f); drawRoad(140.0f, 12.0f); glPopMatrix();

    // 6. LINGKUNGAN (POHON)
    for (float x = -40.0f; x <= 40.0f; x += 20.0f) {
        glPushMatrix(); glTranslatef(x, 0.0f, 40.0f); drawBigTree(); glPopMatrix();
    }

    // 7. GAZEBO UTAMA (Belakang)
    glPushMatrix(); glTranslatef(0.0f, 0.0f, -50.0f); drawMainGazebo(); glPopMatrix();

    // 8. GAZEBO KECIL DI SAMPING
    glPushMatrix(); glTranslatef(35.0f, 0.0f, 0.0f); drawGazebo(); glPopMatrix();
    glPushMatrix(); glTranslatef(-35.0f, 0.0f, 0.0f); drawGazebo(); glPopMatrix();

    // 9. FOODCOURT DINING AREA
    for (float x = -15.0f; x <= 15.0f; x += 12.0f) {
        for (float z = -15.0f; z <= 15.0f; z += 12.0f) {
            if (sqrt(x * x + z * z) > 15.0f) {
                glPushMatrix();
                glTranslatef(x, 0.0f, z);
                drawTableSet();
                glPopMatrix();
            }
        }
    }

    // 10. ORANG-ORANGAN (CROWD)
    glPushMatrix(); glTranslatef(-12.0f, 0.0f, -12.0f); drawPerson(0.8f, 0.2f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-13.0f, 0.0f, -13.0f); glRotatef(90, 0, 1, 0); drawPerson(0.2f, 0.2f, 0.8f); glPopMatrix();
    glPushMatrix(); glTranslatef(10.0f, 0.0f, 20.0f); glRotatef(180, 0, 1, 0); drawPerson(0.8f, 0.8f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(30.0f, 0.0f, 5.0f); glRotatef(-90, 0, 1, 0); drawPerson(0.2f, 0.8f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(5.0f, 0.0f, 48.0f); drawPerson(0.5f, 0.5f, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(-20.0f, 0.0f, -20.0f); glRotatef(45, 0, 1, 0); drawPerson(0.8f, 0.5f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-30.0f, 0.0f, 5.0f); glRotatef(-45, 0, 1, 0); drawPerson(0.2f, 0.8f, 0.8f); glPopMatrix();
    glPushMatrix(); glTranslatef(40.0f, 0.0f, 40.0f); drawPerson(0.5f, 0.2f, 0.5f); glPopMatrix();

    // 11. POT BUNGA HIAS
    for (float x = -20.0f; x <= 20.0f; x += 8.0f) {
        glPushMatrix(); glTranslatef(x, 0.0f, 23.0f); drawFlowerPot(); glPopMatrix();
    }

    // 12. JALAN SETAPAK & HIASAN GAZEBO SAMPING
    glPushMatrix(); glTranslatef(30.0f, 0.05f, 0.0f); glColor3f(0.7f, 0.7f, 0.75f); drawBox(10.0f, 0.1f, 2.5f); glPopMatrix();
    for (float x = 26.0f; x < 35.0f; x += 2.0f) {
        glPushMatrix(); glTranslatef(x, 0.0f, 2.0f); drawFlowerPot(); glPopMatrix();
        glPushMatrix(); glTranslatef(x, 0.0f, -2.0f); drawFlowerPot(); glPopMatrix();
    }
    glPushMatrix(); glTranslatef(-30.0f, 0.05f, 0.0f); glColor3f(0.7f, 0.7f, 0.75f); drawBox(10.0f, 0.1f, 2.5f); glPopMatrix();
    for (float x = -34.0f; x < -25.0f; x += 2.0f) {
        glPushMatrix(); glTranslatef(x, 0.0f, 2.0f); drawFlowerPot(); glPopMatrix();
        glPushMatrix(); glTranslatef(x, 0.0f, -2.0f); drawFlowerPot(); glPopMatrix();
    }

    // 13. VENDOR MAKANAN
    // Food Stands
    glPushMatrix(); glTranslatef(20.0f, 0.0f, 23.0f); glRotatef(180, 0, 1, 0); drawFoodStand(); glPopMatrix();
    glPushMatrix(); glTranslatef(-20.0f, 0.0f, 23.0f); glRotatef(180, 0, 1, 0); drawFoodStand(); glPopMatrix();
    glPushMatrix(); glTranslatef(12.0f, 0.0f, 23.0f); glRotatef(180, 0, 1, 0); drawFoodStand(); glPopMatrix();
    glPushMatrix(); glTranslatef(-12.0f, 0.0f, 23.0f); glRotatef(180, 0, 1, 0); drawFoodStand(); glPopMatrix();

    // Food Containers
    glPushMatrix(); glTranslatef(35.0f, 0.0f, 25.0f); glRotatef(-45, 0, 1, 0); drawFoodContainer(0.8f, 0.2f, 0.2f); glPopMatrix();
    glPushMatrix(); glTranslatef(-35.0f, 0.0f, 25.0f); glRotatef(45, 0, 1, 0); drawFoodContainer(0.2f, 0.2f, 0.8f); glPopMatrix();

    // 14. LANGIT & LANSEKAP TAMBAHAN
    drawSun();
    drawCloud(cloudPos - 50.0f, 40.0f, -70.0f, 1.2f);
    drawCloud(cloudPos + 20.0f, 45.0f, -60.0f, 1.0f);
    drawCloud(cloudPos - 90.0f, 35.0f, -50.0f, 0.8f);

    glPushMatrix(); glTranslatef(28.0f, 0.0f, 25.0f); drawRock(); glPopMatrix();
    glPushMatrix(); glTranslatef(-28.0f, 0.0f, 15.0f); drawRock(); glPopMatrix();
    glPushMatrix(); glTranslatef(20.0f, 0.0f, -20.0f); drawRock(); glPopMatrix();
    glPushMatrix(); glTranslatef(18.0f, 0.0f, 18.0f); drawTrashBin(); glPopMatrix();
    glPushMatrix(); glTranslatef(-18.0f, 0.0f, 18.0f); drawTrashBin(); glPopMatrix();
    for (float z = -30.0f; z < 30.0f; z += 15.0f) {
        glPushMatrix(); glTranslatef(35.0f, 0.0f, z + 5.0f); drawWildBush(); glPopMatrix();
        glPushMatrix(); glTranslatef(-35.0f, 0.0f, z + 5.0f); drawWildBush(); glPopMatrix();
    }

    // 15. BANGUNAN UTAMA (PENTAGONAL)
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glRotatef(i * 72.0f, 0.0f, 1.0f, 0.0f);

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, apothemInner);
        if (i == 0) drawMainDoor(innerFaceW);
        else drawInnerCoreFace(innerFaceW);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, apothemOuter - 2.0f);

        float pillarOffset = 3.5f; float orangeOffset = 8.5f; float angleWing = 12.0f;

        // Sayap Kiri
        glPushMatrix();
        glPushMatrix(); glTranslatef(-orangeOffset, 0.0f, -2.5f); glRotatef(-angleWing, 0, 1, 0); drawOrangeWall(); glPopMatrix();
        float connectorX = -(orangeOffset + pillarOffset) / 2.0f - 1.2f;
        glColor3f(0.25f, 0.25f, 0.25f);
        glPushMatrix(); glTranslatef(connectorX, 2.25f, -1.0f); glRotatef(-angleWing / 1.5f, 0, 1, 0); drawBox(0.6f, 4.5f, 0.8f); glPopMatrix();
        glPushMatrix(); glTranslatef(-(orangeOffset + pillarOffset) / 2.0f + 0.8f, 0.0f, -0.8f); glRotatef(-angleWing / 2.0f, 0, 1, 0); drawStoneWall(4.8f); glPopMatrix();
        glPushMatrix(); glTranslatef(-pillarOffset, 0.0f, 1.0f); drawPillar(); glPopMatrix();
        glPopMatrix();

        // Sayap Kanan
        glPushMatrix();
        glScalef(-1.0f, 1.0f, 1.0f);
        glPushMatrix(); glTranslatef(-orangeOffset, 0.0f, -2.5f); glRotatef(-angleWing, 0, 1, 0); drawOrangeWall(); glPopMatrix();
        float connectorX_M = -(orangeOffset + pillarOffset) / 2.0f - 1.2f;
        glColor3f(0.25f, 0.25f, 0.25f);
        glPushMatrix(); glTranslatef(connectorX_M, 2.25f, -1.0f); glRotatef(-angleWing / 1.5f, 0, 1, 0); drawBox(0.6f, 4.5f, 0.8f); glPopMatrix();
        glPushMatrix(); glTranslatef(-(orangeOffset + pillarOffset) / 2.0f + 0.8f, 0.0f, -0.8f); glRotatef(-angleWing / 2.0f, 0, 1, 0); drawStoneWall(4.8f); glPopMatrix();
        glPushMatrix(); glTranslatef(-pillarOffset, 0.0f, 1.0f); drawPillar(); glPopMatrix();
        glPopMatrix();

        glPopMatrix();
        glPopMatrix();
    }

    // Atap Utama
    glColor3f(0.0f, 0.5f, 0.5f); glPushMatrix(); glTranslatef(0.0f, 4.5f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 5.5f, 0.0f);
    for (int i = 0; i <= 5; i++) {
        float theta = i * 72.0f * PI / 180.0f; float rAtap = R_Inner + 9.0f;
        glNormal3f(sin(theta), 0.5f, cos(theta)); glVertex3f(rAtap * sin(theta), 0.0f, rAtap * cos(theta));
    }
    glEnd(); glPopMatrix();
    glColor3f(1.0f, 0.5f, 0.0f); glPushMatrix(); glTranslatef(0.0f, 9.5f, 0.0f); glutSolidSphere(0.9f, 16, 16); glPopMatrix();
}

// Fungsi Idle untuk Animasi
void idle() {
    cloudPos += 0.05f; // Gerakkan awan pelan-pelan
    if (cloudPos > 150.0f) cloudPos = -150.0f; // Reset jika lewat batas
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glLoadIdentity();
    gluLookAt(0.0f, 5.0f, camZ, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glPushMatrix(); glTranslatef(0.0f, transY, 0.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); glRotatef(angleY, 0.0f, 1.0f, 0.0f);
    drawBuilding();
    glPopMatrix(); glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1; glViewport(0, 0, w, h); glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 1.0f, 200.0f); glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) { case 'w': transY -= 0.5f; break; case 's': transY += 0.5f; break; case 'q': camZ -= 1.0f; break; case 'e': camZ += 1.0f; break; case 27: exit(0); break; }
                           glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) { if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { isDragging = true; lastMouseX = x; lastMouseY = y; } else isDragging = false; }
void mouseMotion(int x, int y) { if (isDragging) { angleY += (x - lastMouseX) * 0.5f; angleX += (y - lastMouseY) * 0.5f; lastMouseX = x; lastMouseY = y; glutPostRedisplay(); } }

int main(int argc, char** argv) {
    glutInit(&argc, argv); glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 700); glutInitWindowPosition(100, 100);
    glutCreateWindow("Kantin Baseball UNESA - OpenGL Final Scene");
    initLighting();
    glutDisplayFunc(display); glutReshapeFunc(reshape); glutKeyboardFunc(keyboard); glutMouseFunc(mouse); glutMotionFunc(mouseMotion);
    glutIdleFunc(idle); // Register fungsi animasi
    glutMainLoop(); return 0;
}

