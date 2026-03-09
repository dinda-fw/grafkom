/*
#include <GL/glut.h>
#include <math.h>

// --- Variabel Global Kamera & Interaksi ---
float angleX = 0.0f;        // Mulai dari sudut pandang datar (Front View)
float angleY = 0.0f;
float camZ = 28.0f;         // Zoom out agar terlihat seluruhnya
float transX = 0.0f, transY = -2.0f; // Geser sedikit ke bawah

int lastMouseX, lastMouseY;
bool isDragging = false;

// --- Setup Pencahayaan ---
void initLighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    // Cahaya Matahari Siang Hari (Putih Terang dari atas depan)
    GLfloat light_pos[] = { 0.0f, 50.0f, 50.0f, 1.0f };
    GLfloat light_amb[] = { 0.6f, 0.6f, 0.6f, 1.0f }; // Ambient terang
    GLfloat light_diff[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
}

// --- FUNGSI MENGGAMBAR OBJEK DASAR ---

void drawBox(float w, float h, float d) {
    glPushMatrix();
    glScalef(w, h, d);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// --- 1. PILAR SPESIFIK (BATU - BIRU - PUTIH) ---
// Sesuai gambar: Bawah batu alam, Tengah Biru, Atas Putih (capit)
void drawPillar() {
    float width = 0.8f;
    float depth = 0.8f;

    // 1. Bawah (Batu Alam - Abu Gelap)
    glColor3f(0.25f, 0.25f, 0.25f);
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f); // Tinggi dasar 2.0 (scale y) / 2
    drawBox(width, 2.0f, depth);
    glPopMatrix();

    // 2. Tengah (Biru Tua UNESA)
    glColor3f(0.0f, 0.15f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, 3.5f, 0.0f); // Naik ke atas batu
    drawBox(0.6f, 3.0f, 0.6f);      // Lebih ramping dari batu
    glPopMatrix();

    // 3. Atas (Putih)
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 5.25f, 0.0f); // Paling atas
    drawBox(0.7f, 0.5f, 0.7f);
    glPopMatrix();
}

// --- 2. DINDING KONTAINER (MERAH BERGELOMBANG) ---
void drawContainerSection() {
    // Dinding Dasar Merah Oranye
    glColor3f(1.0f, 0.25f, 0.05f);
    drawBox(6.0f, 4.0f, 4.0f);

    // Detail Gelombang (Corrugated) - Garis vertikal timbul
    glColor3f(0.8f, 0.2f, 0.0f); // Merah lebih gelap
    for (float i = -2.8f; i <= 2.8f; i += 0.3f) {
        glPushMatrix();
        glTranslatef(i, 0.0f, 2.05f); // Menempel di depan
        drawBox(0.1f, 4.0f, 0.1f);
        glPopMatrix();
    }
}

// --- 3. ATAP KHAS (HIJAU TOSCA + SPLIT ORANYE) ---
void drawRoof() {
    // A. Atap Utama (Hijau Tosca)
    glColor3f(0.0f, 0.8f, 0.7f); // Warna Telur Asin / Tosca

    // Bentuk Limas Terpancung Lebar
    glBegin(GL_QUADS);
    // Sisi Depan
    glNormal3f(0.0f, 0.5f, 1.0f);
    glVertex3f(-14.0f, 0.0f, 6.0f);  // Kiri Bawah Depan
    glVertex3f(14.0f, 0.0f, 6.0f);   // Kanan Bawah Depan
    glVertex3f(2.0f, 3.5f, 0.0f);    // Kanan Atas
    glVertex3f(-2.0f, 3.5f, 0.0f);   // Kiri Atas

    // Sisi Belakang
    glNormal3f(0.0f, 0.5f, -1.0f);
    glVertex3f(14.0f, 0.0f, -6.0f);
    glVertex3f(-14.0f, 0.0f, -6.0f);
    glVertex3f(-2.0f, 3.5f, 0.0f);
    glVertex3f(2.0f, 3.5f, 0.0f);

    // Sisi Kiri
    glNormal3f(-1.0f, 0.5f, 0.0f);
    glVertex3f(-14.0f, 0.0f, -6.0f);
    glVertex3f(-14.0f, 0.0f, 6.0f);
    glVertex3f(-2.0f, 3.5f, 0.0f);
    glVertex3f(-2.0f, 3.5f, 0.0f); // Titik sama (segitiga di sisi)

    // Sisi Kanan
    glNormal3f(1.0f, 0.5f, 0.0f);
    glVertex3f(14.0f, 0.0f, 6.0f);
    glVertex3f(14.0f, 0.0f, -6.0f);
    glVertex3f(2.0f, 3.5f, 0.0f);
    glVertex3f(2.0f, 3.5f, 0.0f);
    glEnd();

    // Tutup Samping Kiri/Kanan agar solid
    glBegin(GL_TRIANGLES);
    // Kiri
    glVertex3f(-14.0f, 0.0f, 6.0f);
    glVertex3f(-14.0f, 0.0f, -6.0f);
    glVertex3f(-2.0f, 3.5f, 0.0f);
    // Kanan
    glVertex3f(14.0f, 0.0f, 6.0f);
    glVertex3f(14.0f, 0.0f, -6.0f);
    glVertex3f(2.0f, 3.5f, 0.0f);
    glEnd();

    // B. Ornamen "Split" Oranye di Puncak
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f); // Naik ke punggung atap

    // Belahan Kiri
    glPushMatrix();
    glTranslatef(-2.5f, 0.5f, 0.0f);
    glRotatef(-15, 0, 0, 1); // Miring ke kiri
    drawBox(4.5f, 0.5f, 5.0f);
    glPopMatrix();

    // Belahan Kanan
    glPushMatrix();
    glTranslatef(2.5f, 0.5f, 0.0f);
    glRotatef(15, 0, 0, 1); // Miring ke kanan
    drawBox(4.5f, 0.5f, 5.0f);
    glPopMatrix();
    glPopMatrix();
}

// --- 4. PAGAR DEPAN & PINTU PAGAR ---
void drawFence() {
    // Tembok Batu Pendek Kiri
    glColor3f(0.4f, 0.4f, 0.45f); // Abu batu
    glPushMatrix();
    glTranslatef(-7.0f, 0.5f, 5.5f);
    drawBox(10.0f, 1.0f, 0.5f);
    glPopMatrix();

    // Tembok Batu Pendek Kanan
    glPushMatrix();
    glTranslatef(7.0f, 0.5f, 5.5f);
    drawBox(10.0f, 1.0f, 0.5f);
    glPopMatrix();

    // Pagar Besi Hitam di Tengah (Gate)
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    // Garis Horizontal Pagar
    for (float y = 0.2f; y <= 1.0f; y += 0.2f) {
        glVertex3f(-2.0f, y, 5.5f);
        glVertex3f(2.0f, y, 5.5f);
    }
    // Garis Vertikal Pagar
    for (float x = -2.0f; x <= 2.0f; x += 0.4f) {
        glVertex3f(x, 0.0f, 5.5f);
        glVertex3f(x, 1.0f, 5.5f);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set Kamera Tampak Depan
    gluLookAt(0.0f, 3.0f, camZ,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f);

    glPushMatrix();
    // Transformasi User
    glTranslatef(transX, transY, 0.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // --- GROUND & RAMP ---
    // Lantai Dasar
    glColor3f(0.6f, 0.6f, 0.6f);
    glPushMatrix();
    glTranslatef(0.0f, -0.1f, 0.0f);
    drawBox(30.0f, 0.2f, 20.0f);
    glPopMatrix();

    // Ramp (Tanjakan di depan pintu pagar)
    glBegin(GL_QUADS);
    glVertex3f(-2.0f, 0.0f, 5.5f);
    glVertex3f(2.0f, 0.0f, 5.5f);
    glVertex3f(3.0f, -1.0f, 9.0f); // Melebar ke bawah
    glVertex3f(-3.0f, -1.0f, 9.0f);
    glEnd();

    // --- STRUKTUR BANGUNAN ---

    // 1. Dinding Kontainer Kiri
    glPushMatrix();
    glTranslatef(-9.0f, 2.0f, 0.0f);
    drawContainerSection();
    glPopMatrix();

    // 2. Dinding Kontainer Kanan
    glPushMatrix();
    glTranslatef(9.0f, 2.0f, 0.0f);
    drawContainerSection();
    glPopMatrix();

    // 3. Dinding Belakang (Krem - Lorong)
    glColor3f(0.9f, 0.85f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, -2.0f);
    drawBox(12.0f, 4.0f, 1.0f);
    glPopMatrix();

    // --- PILAR-PILAR (POSISI DISESUAIKAN FOTO) ---
    // Pilar Utama Tengah Kiri
    glPushMatrix();
    glTranslatef(-3.5f, 0.0f, 4.0f);
    drawPillar();
    glPopMatrix();

    // Pilar Utama Tengah Kanan
    glPushMatrix();
    glTranslatef(3.5f, 0.0f, 4.0f);
    drawPillar();
    glPopMatrix();

    // Pilar Penyangga Kontainer Kiri (Menempel di dinding merah)
    glPushMatrix();
    glTranslatef(-6.0f, 0.0f, 2.5f);
    drawPillar();
    glPopMatrix();

    // Pilar Penyangga Kontainer Kanan
    glPushMatrix();
    glTranslatef(6.0f, 0.0f, 2.5f);
    drawPillar();
    glPopMatrix();

    // Pilar Paling Ujung (Opsional, di sudut bangunan)
    glPushMatrix();
    glTranslatef(-12.0f, 0.0f, 2.0f); // Sedikit mundur
    drawPillar();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(12.0f, 0.0f, 2.0f);
    drawPillar();
    glPopMatrix();

    // --- ATAP ---
    glPushMatrix();
    glTranslatef(0.0f, 5.5f, 0.0f); // Naik ke atas pilar
    drawRoof();
    glPopMatrix();

    // --- PAGAR DEPAN ---
    drawFence();

    glPopMatrix();
    glutSwapBuffers();
}

// --- Input System ---
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': transY += 0.5f; break;
    case 's': transY -= 0.5f; break;
    case 'a': transX -= 0.5f; break;
    case 'd': transX += 0.5f; break;
    case 'q': camZ -= 1.0f; break; // Zoom In
    case 'e': camZ += 1.0f; break; // Zoom Out
    case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isDragging = true;
        lastMouseX = x;
        lastMouseY = y;
    }
    else {
        isDragging = false;
    }
}

void mouseMotion(int x, int y) {
    if (isDragging) {
        angleY += (x - lastMouseX) * 0.5f;
        angleX += (y - lastMouseY) * 0.5f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Kantin Baseball UNESA - Mirip Asli");

    initLighting();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
*/