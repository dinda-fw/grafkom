#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

// --- DEFINISI STRUCT ---
struct Pos2D { float x, z; };
struct Pos3D { float x, z, rot; };

// --- DEKLARASI PROTOTIPE FUNGSI KOSTUM ---
void drawBox(float width, float height, float depth, float r, float g, float b);
void drawStreetLight(float px, float pz);
void drawParkBench(float px, float pz, float rotAngle);
void drawTrashCan(float px, float pz);
void drawCloud(float cx, float cy, float cz);
void drawDetailedWindow(float px, float py, float pz);
void drawLogo(float px, float py, float pz);
void drawTree(float posX, float posZ);
void drawBush(float posX, float posZ);
void drawText3D(const char* text, float x, float y, float z, float r, float g, float b);
void drawFenceWithGate(float center_x, float center_z, float total_length, float gate_width);
void drawBackyardDecoration(float px, float pz);

// -----------------------------------------------------------------

// Variabel kamera
float angle = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = -10.0f;
float z = 40.0f;

// Variabel Animasi
float cloudX = 0.0f;

// Konstanta Material
const GLfloat default_shininess[] = { 0.0f };
const GLfloat no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat default_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat default_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat default_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

// Konfigurasi Pencahayaan
void initLighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    // Cahaya Matahari
    GLfloat ambientLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.8f, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { 10.0f, 50.0f, 30.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
}

// Timer Animasi
void update(int value) {
    cloudX += 0.05f;
    if (cloudX > 60.0f) cloudX = -60.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Fungsi Text 3D
void drawText3D(const char* text, float x, float y, float z, float r, float g, float b) {
    glPushMatrix();
    glColor3f(r, g, b);
    glTranslatef(x, y, z);
    glScalef(0.004f, 0.004f, 0.004f);
    glLineWidth(3.0f);
    for (int i = 0; i < strlen(text); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();
}

// Fungsi Kotak Dasar
void drawBox(float width, float height, float depth, float r, float g, float b) {
    glColor3f(r, g, b);
    glPushMatrix();
    glScalef(width, height, depth);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Fungsi Awan 
void drawCloud(float cx, float cy, float cz) {
    GLfloat cloud_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat cloud_shininess[] = { 50.0f };

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(cx, cy, cz);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cloud_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cloud_shininess);

    glutSolidSphere(1.5f, 10, 10);
    glTranslatef(1.2f, 0.5f, 0.0f);
    glutSolidSphere(1.2f, 10, 10);
    glTranslatef(-2.4f, -0.2f, 0.0f);
    glutSolidSphere(1.3f, 10, 10);
    glTranslatef(1.0f, 0.8f, 0.5f);
    glutSolidSphere(0.8f, 10, 10);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, default_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, default_shininess);

    glPopMatrix();
}

// Fungsi Jendela Detail
void drawDetailedWindow(float px, float py, float pz) {
    glPushMatrix();
    glTranslatef(px, py, pz);
    drawBox(1.5f, 1.5f, 0.2f, 0.2f, 0.2f, 0.3f); // Kaca
    glPopMatrix();
    // Bingkai
    glPushMatrix(); glTranslatef(px, py + 0.7f, pz + 0.05f); drawBox(1.6f, 0.1f, 0.25f, 0.9f, 0.9f, 0.9f); glPopMatrix();
    glPushMatrix(); glTranslatef(px, py - 0.7f, pz + 0.05f); drawBox(1.6f, 0.1f, 0.25f, 0.9f, 0.9f, 0.9f); glPopMatrix();
    glPushMatrix(); glTranslatef(px - 0.7f, py, pz + 0.05f); drawBox(0.1f, 1.5f, 0.25f, 0.9f, 0.9f, 0.9f); glPopMatrix();
    glPushMatrix(); glTranslatef(px + 0.7f, py, pz + 0.05f); drawBox(0.1f, 1.5f, 0.25f, 0.9f, 0.9f, 0.9f); glPopMatrix();
}

// Fungsi Logo Kuning
void drawLogo(float px, float py, float pz) {
    glPushMatrix();
    glTranslatef(px, py, pz);
    glColor3f(1.0f, 0.8f, 0.0f);
    glScalef(1.0f, 1.0f, 0.2f);
    glutSolidSphere(0.8f, 20, 20);
    glPopMatrix();
}

// Fungsi Tiang Lampu Jalan (Tidak dipanggil lagi)
void drawStreetLight(float px, float pz) {
    GLfloat lamp_emission[] = { 1.0f, 1.0f, 0.8f, 1.0f };

    glPushMatrix();
    glTranslatef(px, 0.0f, pz);

    // Tiang Vertikal
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);
    glScalef(0.2f, 6.0f, 0.2f);
    drawBox(1.0f, 1.0f, 1.0f, 0.3f, 0.3f, 0.3f);
    glPopMatrix();

    // Lengan Horizontal
    glPushMatrix();
    glTranslatef(0.0f, 6.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    glScalef(2.0f, 0.15f, 0.15f);
    drawBox(1.0f, 1.0f, 1.0f, 0.3f, 0.3f, 0.3f);
    glPopMatrix();

    // Lampu (Emisi cahaya ditambahkan)
    glPushMatrix();
    glTranslatef(2.0f, 6.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.8f);

    glMaterialfv(GL_FRONT, GL_EMISSION, lamp_emission);
    glutSolidSphere(0.3f, 10, 10);

    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
    glPopMatrix();

    glPopMatrix();
}

// Fungsi Kursi Taman
void drawParkBench(float px, float pz, float rotAngle) {
    glPushMatrix();
    glTranslatef(px, -0.4f, pz);
    glRotatef(rotAngle, 0.0f, 1.0f, 0.0f);

    // Tempat Duduk Kayu
    drawBox(3.0f, 0.1f, 1.0f, 0.6f, 0.4f, 0.2f);

    // Kaki Kursi (Metal)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix(); glTranslatef(-1.4f, -0.25f, 0.4f); drawBox(0.1f, 0.5f, 0.1f, 0.3f, 0.3f, 0.3f); glPopMatrix();
    glPushMatrix(); glTranslatef(1.4f, -0.25f, 0.4f); drawBox(0.1f, 0.5f, 0.1f, 0.3f, 0.3f, 0.3f); glPopMatrix();
    glPushMatrix(); glTranslatef(-1.4f, -0.25f, -0.4f); drawBox(0.1f, 0.5f, 0.1f, 0.3f, 0.3f, 0.3f); glPopMatrix();
    glPushMatrix(); glTranslatef(1.4f, -0.25f, -0.4f); drawBox(0.1f, 0.5f, 0.1f, 0.3f, 0.3f, 0.3f); glPopMatrix();

    glPopMatrix();
}

// Fungsi Tempat Sampah
void drawTrashCan(float px, float pz) {
    glPushMatrix();
    glTranslatef(px, -0.4f, pz);

    // Tabung
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(0.8f, 1.0f, 0.8f);
    drawBox(1.0f, 1.0f, 1.0f, 0.1f, 0.1f, 0.1f);
    glPopMatrix();

    // Tutup
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.0f, 1.05f, 0.0f);
    drawBox(1.0f, 0.1f, 1.0f, 0.3f, 0.3f, 0.3f);
    glPopMatrix();

    glPopMatrix();
}

// Fungsi Hiasan Belakang Gedung (Gazebo & Kolam)
void drawBackyardDecoration(float px, float pz) {
    glPushMatrix();
    glTranslatef(px, 0.0f, pz);

    // 1. Kolam Air
    glColor3f(0.0f, 0.5f, 0.8f); // Biru Air
    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 0.0f); // Sedikit di atas lantai dasar
    drawBox(15.0f, 0.1f, 10.0f, 0.0f, 0.5f, 0.8f);
    glPopMatrix();

    // Pinggiran Kolam (Batu Alam)
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix(); glTranslatef(0.0f, -0.25f, 5.5f); drawBox(16.0f, 0.2f, 1.0f, 0.5f, 0.5f, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, -0.25f, -5.5f); drawBox(16.0f, 0.2f, 1.0f, 0.5f, 0.5f, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(8.0f, -0.25f, 0.0f); drawBox(1.0f, 0.2f, 12.0f, 0.5f, 0.5f, 0.5f); glPopMatrix();
    glPushMatrix(); glTranslatef(-8.0f, -0.25f, 0.0f); drawBox(1.0f, 0.2f, 12.0f, 0.5f, 0.5f, 0.5f); glPopMatrix();

    // 2. Gazebo Sederhana (di belakang kolam)
    float gazeboZ = -10.0f;

    // Lantai Gazebo
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, gazeboZ);
    drawBox(6.0f, 0.2f, 6.0f, 0.6f, 0.4f, 0.2f); // Kayu Coklat

    // Tiang Gazebo
    glColor3f(0.4f, 0.2f, 0.1f); // Coklat Tua
    glPushMatrix(); glTranslatef(-2.5f, 1.5f, -2.5f); drawBox(0.3f, 3.0f, 0.3f, 0.4f, 0.2f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(2.5f, 1.5f, -2.5f); drawBox(0.3f, 3.0f, 0.3f, 0.4f, 0.2f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(-2.5f, 1.5f, 2.5f); drawBox(0.3f, 3.0f, 0.3f, 0.4f, 0.2f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(2.5f, 1.5f, 2.5f); drawBox(0.3f, 3.0f, 0.3f, 0.4f, 0.2f, 0.1f); glPopMatrix();

    // Atap Gazebo (Limas)
    glColor3f(0.8f, 0.2f, 0.2f); // Merah Genteng
    glPushMatrix();
    glTranslatef(0.0f, 3.5f, 0.0f);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glutSolidCone(4.5f, 2.0f, 4, 1); // Bentuk Piramida
    glPopMatrix();

    glPopMatrix(); // End Gazebo

    glPopMatrix();
}

// Fungsi Pagar Besi dengan Celah Masuk (Gate) di Tengah
void drawFenceWithGate(float center_x, float center_z, float total_length, float gate_width) {
    glPushMatrix();
    glTranslatef(center_x, 0.0f, center_z);

    // Warna Pagar (Hitam Metalik seperti di gambar)
    float fenceR = 0.2f, fenceG = 0.2f, fenceB = 0.25f;

    // Dimensi
    float post_height = 1.8f; // Tinggi pagar
    float post_width = 0.2f;
    float rail_thickness = 0.1f;
    float post_spacing = 2.5f;

    // Hitung panjang setiap sisi pagar (Kiri dan Kanan)
    float side_length = (total_length - gate_width) / 2.0f;

    // --- SISI KIRI ---
    // Posisi tengah sisi kiri: geser ke kiri dari tengah global
    float left_pos = -(gate_width / 2.0f) - (side_length / 2.0f);

    glPushMatrix();
    glTranslatef(left_pos, 0.0f, 0.0f); // Pindah ke tengah bagian kiri

    // 1. Rel Atas
    glPushMatrix();
    glTranslatef(0.0f, post_height * 0.9f, 0.0f);
    drawBox(side_length, rail_thickness, rail_thickness, fenceR, fenceG, fenceB);
    glPopMatrix();

    // 2. Rel Bawah
    glPushMatrix();
    glTranslatef(0.0f, post_height * 0.2f, 0.0f);
    drawBox(side_length, rail_thickness, rail_thickness, fenceR, fenceG, fenceB);
    glPopMatrix();

    // 3. Tiang-tiang Vertikal
    int num_posts = (int)(side_length / post_spacing);
    for (int i = 0; i <= num_posts; i++) {
        float x_offset = -(side_length / 2.0f) + (i * (side_length / num_posts));
        glPushMatrix();
        glTranslatef(x_offset, post_height / 2.0f, 0.0f);
        drawBox(post_width, post_height, post_width, fenceR, fenceG, fenceB);
        glPopMatrix();
    }
    glPopMatrix(); // End Sisi Kiri


    // --- SISI KANAN ---
    // Posisi tengah sisi kanan: geser ke kanan dari tengah global
    float right_pos = (gate_width / 2.0f) + (side_length / 2.0f);

    glPushMatrix();
    glTranslatef(right_pos, 0.0f, 0.0f); // Pindah ke tengah bagian kanan

    // 1. Rel Atas
    glPushMatrix();
    glTranslatef(0.0f, post_height * 0.9f, 0.0f);
    drawBox(side_length, rail_thickness, rail_thickness, fenceR, fenceG, fenceB);
    glPopMatrix();

    // 2. Rel Bawah
    glPushMatrix();
    glTranslatef(0.0f, post_height * 0.2f, 0.0f);
    drawBox(side_length, rail_thickness, rail_thickness, fenceR, fenceG, fenceB);
    glPopMatrix();

    // 3. Tiang-tiang Vertikal
    for (int i = 0; i <= num_posts; i++) {
        float x_offset = -(side_length / 2.0f) + (i * (side_length / num_posts));
        glPushMatrix();
        glTranslatef(x_offset, post_height / 2.0f, 0.0f);
        drawBox(post_width, post_height, post_width, fenceR, fenceG, fenceB);
        glPopMatrix();
    }
    glPopMatrix(); // End Sisi Kanan

    glPopMatrix();
}


void drawBuilding() {
    // 1. Lantai Paving Block (DIPERLUAS HINGGA KE BELAKANG)
    float floorY = -0.4f;
    // Loop Z diperluas dari -50 (belakang) sampai 30 (depan)
    for (float zLoop = -50.0f; zLoop < 30.0f; zLoop += 2.0f) {
        for (float xLoop = -15.0f; xLoop < 30.0f; xLoop += 2.0f) {

            // [MODIFIKASI] Logika Paving Block
            // Area asli (depan/samping)
            bool isOriginalArea = (zLoop >= 5.0f);

            if (isOriginalArea) {
                // Logika lama (tetap dipertahankan agar bentuk depan tidak berubah)
                if ((xLoop >= 15.0f && xLoop < 28.0f) && (zLoop < 12.0f)) continue;
                if (xLoop > 1.0f && zLoop < 0.0f) continue;
                if (xLoop < -10.0f && zLoop < 5.0f) continue;
                if (xLoop > 15.0f && zLoop > 28.0f) continue;
            }
            // Area belakang (zLoop < 5.0f) akan digambar penuh (kotak) sesuai loop

            glPushMatrix();
            glTranslatef(xLoop, floorY, zLoop);
            if (((int)zLoop / 2 + (int)xLoop / 2) % 2 == 0)
                drawBox(1.9f, 0.1f, 1.9f, 0.6f, 0.6f, 0.6f);
            else
                drawBox(1.9f, 0.1f, 1.9f, 0.55f, 0.55f, 0.55f);
            glPopMatrix();
        }
    }


    // === GEDUNG UTAMA (TENGAH) ===

    GLfloat building_specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat building_shininess[] = { 10.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, building_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, building_shininess);

    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);
    drawBox(26.0f, 6.0f, 8.0f, 0.95f, 0.95f, 0.90f);
    glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, default_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, default_shininess);


    float startX = -12.0f;
    for (int i = 0; i < 7; i++) {
        float posX = startX + (i * 4.0f);
        if (posX > -3.0f && posX < 3.0f) continue;

        // Pilar Merah Utama
        glPushMatrix();
        glTranslatef(posX, 3.0f, 4.1f);
        drawBox(1.0f, 6.0f, 0.5f, 0.9f, 0.1f, 0.1f);
        glPopMatrix();

        // Jendela
        if (posX + 2.0f < 12.0f) {
            drawDetailedWindow(posX + 2.0f, 4.5f, 4.05f);
            drawDetailedWindow(posX + 2.0f, 1.5f, 4.05f);
        }
    }

    // === TROTOAR TERAS DEPAN (MODEL TANGGA) ===
    // 1. Platform Utama (Paling Atas - Menempel Pintu)
    glColor3f(0.9f, 0.9f, 0.92f); // Warna Putih Marmer
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 6.5f);
    drawBox(8.0f, 0.3f, 3.5f, 0.9f, 0.9f, 0.92f);
    glPopMatrix();

    // 2. Anak Tangga 1 (Tengah)
    glColor3f(0.85f, 0.85f, 0.87f);
    glPushMatrix();
    glTranslatef(0.0f, -0.15f, 8.25f);
    drawBox(9.0f, 0.2f, 1.5f, 0.85f, 0.85f, 0.87f);
    glPopMatrix();

    // 3. Anak Tangga 2 (Bawah)
    glColor3f(0.8f, 0.8f, 0.82f);
    glPushMatrix();
    glTranslatef(0.0f, -0.3f, 9.0f);
    drawBox(10.0f, 0.2f, 1.5f, 0.8f, 0.8f, 0.82f);
    glPopMatrix();


    // Pintu Utama & Teras
    glPushMatrix(); glTranslatef(0.0f, 2.5f, 5.0f); drawBox(6.0f, 5.0f, 4.0f, 0.9f, 0.9f, 0.9f); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 1.0f, 7.01f); drawBox(3.0f, 2.0f, 0.1f, 0.2f, 0.2f, 0.3f); glPopMatrix(); // Kaca Pintu

    // Papan Nama Merah
    glPushMatrix(); glTranslatef(0.0f, 4.2f, 7.1f); drawBox(5.5f, 1.5f, 0.2f, 0.9f, 0.1f, 0.1f); glPopMatrix();
    // Tiang Teras Merah
    glPushMatrix(); glTranslatef(-2.5f, 1.5f, 6.5f); drawBox(0.8f, 3.0f, 0.8f, 0.8f, 0.1f, 0.1f); glPopMatrix();
    glPushMatrix(); glTranslatef(2.5f, 1.5f, 6.5f); drawBox(0.8f, 3.0f, 0.8f, 0.8f, 0.1f, 0.1f); glPopMatrix();

    drawLogo(0.0f, 5.8f, 7.2f);
    drawText3D("FAKULTAS HUKUM", -2.8f, 4.0f, 7.22f, 1.0f, 1.0f, 1.0f);

    // Atap Utama
    float roofY = 6.0f;
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glTranslatef(0.0f, roofY + (i * 0.5f), 0.0f);
        drawBox(28.0f - (i * 2.5f), 0.5f, 10.0f - (i * 1.0f), 0.7f, 0.25f, 0.1f);
        glPopMatrix();
    }
    for (int i = 0; i < 5; i++) {
        glPushMatrix(); glTranslatef(0.0f, 5.0f + (i * 0.4f), 5.0f); drawBox(6.5f - (i * 1.2f), 0.4f, 5.0f - (i * 0.8f), 0.7f, 0.25f, 0.1f); glPopMatrix();
    }

}

// Fungsi Pohon
void drawTree(float posX, float posZ) {
    glPushMatrix();
    glTranslatef(posX, 1.4f, posZ);
    drawBox(0.8f, 4.0f, 0.8f, 0.5f, 0.35f, 0.2f); // Batang
    glColor3f(0.1f, 0.6f, 0.1f); // Daun
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 1.5f + (i * 1.5f), 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glutSolidCone(3.0f - (i * 0.7f), 3.5f, 12, 4);
        glPopMatrix();
    }
    glPopMatrix();
}

void drawBush(float posX, float posZ) {
    glPushMatrix();
    glTranslatef(posX, 0.5f, posZ);
    glColor3f(0.2f, 0.8f, 0.2f);
    glutSolidSphere(0.8f, 8, 8);
    glPopMatrix();
}

void display() {
    GLfloat asphalt_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat asphalt_shininess[] = { 5.0f };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(x, 2.5f, z, x + lx, 2.5f, z + lz, 0.0f, 1.0f, 0.0f);

    // 1. Tanah Rumput Luas
    glColor3f(0.15f, 0.45f, 0.15f); // Warna hijau rumput
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-300.0f, -0.6f, -300.0f); // Perluas ke segala arah lebih jauh
    glVertex3f(-300.0f, -0.6f, 300.0f);
    glVertex3f(300.0f, -0.6f, 300.0f);
    glVertex3f(300.0f, -0.6f, -300.0f);
    glEnd();

    // 2. Jalan Raya
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, asphalt_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, asphalt_shininess);
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix(); glTranslatef(0.0f, -0.55f, 35.0f); drawBox(100.0f, 0.1f, 10.0f, 0.2f, 0.2f, 0.2f); glPopMatrix();

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, default_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, default_shininess);

    // [PAGAR BESI] dengan celah 15 unit
    drawFenceWithGate(0.0f, 23.0f, 100.0f, 15.0f);

    drawBuilding();

    // MENAMBAHKAN HIASAN AREA BELAKANG
    drawBackyardDecoration(0.0f, -25.0f); // Posisikan di belakang gedung

    // Awan
    drawCloud(cloudX - 20.0f, 15.0f, -10.0f);
    drawCloud(cloudX + 10.0f, 18.0f, -20.0f);
    drawCloud(cloudX + 40.0f, 16.0f, 0.0f);

    // Tempat sampah tambahan
    drawTrashCan(4.0f, 26.0f);
    drawTrashCan(-1.0f, 29.0f);

    // Kursi Taman Tambahan
    drawParkBench(-18.0f, 10.0f, 0.0f);
    drawParkBench(-5.0f, -15.0f, 90.0f);
    drawParkBench(10.0f, 26.0f, 180.0f);

    // Vegetasi Depan (di samping pagar)
    drawTree(-18.0f, 5.0f);
    drawTree(-25.0f, 15.0f);
    drawBush(-15.0f, 0.0f); drawBush(-18.0f, -5.0f);

    drawTree(35.0f, 5.0f);
    drawTree(30.0f, 15.0f);
    drawBush(35.0f, -5.0f);

    for (float bx = -15.0f; bx <= 30.0f; bx += 2.5f) {
        if (bx > -4.0f && bx < 4.0f) continue;
        if (bx > 8.0f && bx < 30.0f) continue;
        drawBush(bx, 22.0f); // Di dekat pagar
    }

    // Vegetasi di Taman Belakang (lebih banyak dan tersebar)
    drawTree(-45.0f, -80.0f); drawTree(-25.0f, -90.0f); drawTree(-5.0f, -75.0f);
    drawTree(15.0f, -85.0f); drawTree(35.0f, -70.0f); drawTree(40.0f, -95.0f);
    drawTree(-60.0f, -60.0f); drawTree(60.0f, -60.0f);

    drawBush(-35.0f, -60.0f); drawBush(-15.0f, -70.0f); drawBush(5.0f, -65.0f);
    drawBush(25.0f, -75.0f); drawBush(45.0f, -60.0f);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}

void processSpecialKeys(int key, int xx, int yy) {
    float fraction = 1.5f;
    switch (key) {
    case GLUT_KEY_LEFT: angle -= 0.05f; lx = sin(angle); lz = -cos(angle); break;
    case GLUT_KEY_RIGHT: angle += 0.05f; lx = sin(angle); lz = -cos(angle); break;
    case GLUT_KEY_UP: x += lx * fraction; z += lz * fraction; break;
    case GLUT_KEY_DOWN: x -= lx * fraction; z -= lz * fraction; break;
    }
    glutPostRedisplay();
}

void mouseControl(int button, int state, int mx, int my) {
    if (state == GLUT_DOWN) {
        float fraction = 1.5f;
        if (button == GLUT_LEFT_BUTTON) {
            x += lx * fraction;
            z += lz * fraction;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            x -= lx * fraction;
            z -= lz * fraction;
        }
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1200, 700);
    glutCreateWindow("Gedung FH UNESA - Final Scene");

    initLighting();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(mouseControl);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}