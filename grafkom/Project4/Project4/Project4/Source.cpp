//#include <GL/glut.h>
//#include <GL/glu.h>
//#include <math.h>
//#include <stdlib.h>
//#include <vector>
//
//// --- Definisi Struct untuk Objek ---
//struct Pos3D { float x, z, rot; };
//struct Pos2D { float x, z; };
//
//// --- DATA GEOMETRI FOODCOURT ---
//// Posisi Pilar Utama Depan
//const std::vector<Pos2D> FRONT_PILLARS = {
//    {-18.0f, 6.0f}, {-12.0f, 6.0f}, {-6.0f, 6.0f},
//    { 0.0f, 6.0f}, { 6.0f, 6.0f}, { 12.0f, 6.0f}, {18.0f, 6.0f}
//};
//// Posisi Dinding Stan (Warung) 
//const std::vector<Pos2D> STALL_WALLS = {
//    {-18.0f, -6.0f}, {-12.0f, -6.0f}, {-6.0f, -6.0f},
//    { 0.0f, -6.0f}, { 6.0f, -6.0f}, { 12.0f, -6.0f}
//};
//// Posisi Meja dan Kursi di Area Terbuka
//const std::vector<Pos3D> TABLES = {
//    {-15.0f, 12.0f, 0.0f}, {-5.0f, 12.0f, 0.0f}, {5.0f, 12.0f, 0.0f},
//    {-15.0f, 20.0f, 0.0f}, {-5.0f, 20.0f, 0.0f}, {5.0f, 20.0f, 0.0f}
//};
//// Posisi Lampu Jalan
//const std::vector<Pos2D> LIGHTS = {
//    {-25.0f, 25.0f}, {0.0f, 25.0f}, {25.0f, 25.0f}
//};
//
//// --- Variabel Kamera dan Animasi ---
//float angle = 0.0f;
//float lx = 0.0f, lz = -1.0f;
//float x = -10.0f; // Posisi awal kamera
//float z = 30.0f;
//
//// Untuk interaksi pagar pintu masuk
//float leftGateRotation = 0.0f;
//float rightGateRotation = 0.0f;
//bool isGateOpen = false;
//
//// Konstanta Material
//const GLfloat default_shininess[] = { 0.0f };
//const GLfloat no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//const GLfloat default_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//const GLfloat default_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
//const GLfloat default_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
//
//// Pointer untuk GLUquadric
//GLUquadricObj* quadratic;
//
//// --- PROTOTIPE FUNGSI UTAMA ---
//void drawBox(float width, float height, float depth, float r, float g, float b);
//void drawCylinderCustom(float radius, float height, float r, float g, float b);
//void drawPillar(float px, float py, float pz, float height, float radius, float r, float g, float b);
//void drawStall(float px, float pz);
//void drawTableSet(float px, float pz, float rotAngle);
//void drawStreetLight(float px, float pz);
//void drawTree(float posX, float posZ);
//void drawBush(float posX, float posZ);
//
//// --- FUNGSI UTILITY ---
//void initLighting() {
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_NORMALIZE);
//
//    GLfloat ambientLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
//    GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.8f, 1.0f };
//    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
//    GLfloat position[] = { 10.0f, 50.0f, 30.0f, 1.0f };
//
//    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
//    glLightfv(GL_LIGHT0, GL_POSITION, position);
//
//    glShadeModel(GL_SMOOTH);
//
//    glClearColor(0.8f, 0.95f, 1.0f, 1.0f); // Langit Biru Muda
//
//    quadratic = gluNewQuadric();
//    gluQuadricNormals(quadratic, GLU_SMOOTH); // Normals untuk shading
//    gluQuadricDrawStyle(quadratic, GLU_FILL); // Mode gambar
//}
//
//void drawBox(float w, float h, float d, float r, float g, float b) {
//    glColor3f(r, g, b);
//    glPushMatrix();
//    glScalef(w, h, d);
//    glutSolidCube(1.0f);
//    glPopMatrix();
//}
//
//// Fungsi kustom untuk menggambar silinder menggunakan GLUquadric
//void drawCylinderCustom(float radius, float height, float r, float g, float b) {
//    glColor3f(r, g, b);
//    glPushMatrix();
//    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Orientasi silinder agar berdiri tegak
//    gluCylinder(quadratic, radius, radius, height, 16, 16); // body silinder
//    gluDisk(quadratic, 0.0f, radius, 16, 16); // Tutup bawah
//    glTranslatef(0.0f, 0.0f, height);
//    gluDisk(quadratic, 0.0f, radius, 16, 16); // Tutup atas
//    glPopMatrix();
//}
//
//// Menggunakan drawCylinderCustom untuk pilar
//void drawPillar(float px, float py, float pz, float height, float radius, float r, float g, float b) {
//    glPushMatrix();
//    glTranslatef(px, py, pz);
//    drawCylinderCustom(radius, height, r, g, b);
//    glPopMatrix();
//}
//
//void drawStreetLight(float px, float pz) {
//    GLfloat lamp_emission[] = { 1.0f, 1.0f, 0.8f, 1.0f };
//
//    glPushMatrix();
//    glTranslatef(px, 0.0f, pz);
//
//    drawBox(0.2f, 6.0f, 0.2f, 0.3f, 0.3f, 0.3f); // Tiang
//
//    glPushMatrix();
//    glTranslatef(1.5f, 6.0f, 0.0f);
//    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
//    drawBox(3.0f, 0.15f, 0.15f, 0.3f, 0.3f, 0.3f); // Lengan
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslatef(3.0f, 6.0f, 0.0f);
//    glMaterialfv(GL_FRONT, GL_EMISSION, lamp_emission);
//    glutSolidSphere(0.3f, 10, 10); // Lampu
//    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
//    glPopMatrix();
//
//    glPopMatrix();
//}
//
//// Stan dengan detail meja dan jendela
//void drawStall(float px, float pz) {
//    glPushMatrix();
//    glTranslatef(px, 0.0f, pz);
//
//    // Dinding Belakang Stan (Cokelat/Merah bata)
//    drawBox(5.0f, 4.0f, 1.0f, 0.7f, 0.4f, 0.3f);
//
//    // Meja Konter Depan
//    glPushMatrix();
//    glTranslatef(0.0f, -1.0f, 0.5f);
//    drawBox(5.0f, 2.0f, 1.0f, 0.5f, 0.3f, 0.0f); // Kayu Cokelat
//    glPopMatrix();
//
//    // Kanopi Stan Kecil (Hijau)
//    glPushMatrix();
//    glTranslatef(0.0f, 2.5f, 0.5f);
//    drawBox(6.0f, 0.2f, 2.0f, 0.2f, 0.6f, 0.2f);
//    glPopMatrix();
//
//    // Jendela/Area Layanan (Garis Hitam)
//    glDisable(GL_LIGHTING);
//    glColor3f(0.1f, 0.1f, 0.1f);
//    glLineWidth(2.0f);
//    glPushMatrix();
//    glTranslatef(0.0f, 0.5f, -0.01f);
//    glScalef(2.5f, 2.0f, 1.0f);
//    glutWireCube(1.0f);
//    glPopMatrix();
//    glEnable(GL_LIGHTING);
//
//    glPopMatrix();
//}
//
//void drawTableSet(float px, float pz, float rotAngle) {
//    glPushMatrix();
//    glTranslatef(px, -0.4f, pz);
//    glRotatef(rotAngle, 0.0f, 1.0f, 0.0f);
//
//    // Meja (Stainless Steel/Perak)
//    GLfloat table_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
//    GLfloat table_shininess[] = { 100.0f };
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, table_specular);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, table_shininess);
//    drawBox(2.0f, 0.1f, 2.0f, 0.7f, 0.7f, 0.7f);
//
//    // Kaki Meja
//    drawBox(0.2f, 0.8f, 0.2f, 0.3f, 0.3f, 0.3f);
//
//    // Kursi Plastik (Hijau) - Sesuai gambar referensi
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, default_specular);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, default_shininess);
//    float r = 0.0f, g = 0.5f, b = 0.0f; // Hijau terang
//
//    // Kursi 1
//    glPushMatrix(); glTranslatef(1.5f, -0.2f, 0.0f); drawBox(0.5f, 0.5f, 0.5f, r, g, b); glPopMatrix();
//    // Kursi 2
//    glPushMatrix(); glTranslatef(-1.5f, -0.2f, 0.0f); drawBox(0.5f, 0.5f, 0.5f, r, g, b); glPopMatrix();
//    // Kursi 3
//    glPushMatrix(); glTranslatef(0.0f, -0.2f, 1.5f); drawBox(0.5f, 0.5f, 0.5f, r, g, b); glPopMatrix();
//    // Kursi 4
//    glPushMatrix(); glTranslatef(0.0f, -0.2f, -1.5f); drawBox(0.5f, 0.5f, 0.5f, r, g, b); glPopMatrix();
//
//    glPopMatrix();
//}
//
//void drawTree(float posX, float posZ) {
//    glPushMatrix();
//    glTranslatef(posX, 0.0f, posZ); // Posisi batang di tanah
//    drawCylinderCustom(0.4f, 5.0f, 0.5f, 0.35f, 0.2f); // Batang Cokelat
//
//    glColor3f(0.1f, 0.6f, 0.1f); // Daun Hijau
//    for (int i = 0; i < 3; i++) {
//        glPushMatrix();
//        glTranslatef(0.0f, 5.0f + (i * 1.5f), 0.0f); // Mulai daun dari atas batang
//        glRotatef(-90, 1.0f, 0.0f, 0.0f);
//        glutSolidCone(3.0f - (i * 0.7f), 3.5f, 12, 4);
//        glPopMatrix();
//    }
//    glPopMatrix();
//}
//
//void drawBush(float posX, float posZ) {
//    glPushMatrix();
//    glTranslatef(posX, 0.5f, posZ);
//    glColor3f(0.2f, 0.8f, 0.2f); // Hijau Cerah
//    glutSolidSphere(0.8f, 8, 8);
//    glPopMatrix();
//}
//
//// --- FUNGSI UTAMA DISPLAY ---
//
//void drawFoodcourt() {
//    // Tanah Rumput Luas (Area background)
//    glColor3f(0.15f, 0.45f, 0.15f);
//    glBegin(GL_QUADS);
//    glNormal3f(0.0f, 1.0f, 0.0f);
//    glVertex3f(-100.0f, -0.7f, -100.0f);
//    glVertex3f(-100.0f, -0.7f, 100.0f);
//    glVertex3f(100.0f, -0.7f, 100.0f);
//    glVertex3f(100.0f, -0.7f, -100.0f);
//    glEnd();
//
//    // Paving Block Utama (Area depan foodcourt)
//    float baseFloorY = -0.6f;
//    for (float zLoop = -10.0f; zLoop < 25.0f; zLoop += 2.0f) {
//        for (float xLoop = -25.0f; xLoop < 25.0f; xLoop += 2.0f) {
//            glPushMatrix();
//            glTranslatef(xLoop, baseFloorY, zLoop);
//            if (((int)zLoop / 2 + (int)xLoop / 2) % 2 == 0)
//                drawBox(1.9f, 0.1f, 1.9f, 0.8f, 0.75f, 0.7f); // Paving terang
//            else
//                drawBox(1.9f, 0.1f, 1.9f, 0.75f, 0.7f, 0.65f); // Paving gelap
//            glPopMatrix();
//        }
//    }
//
//    // Bangunan Belakang Utama (Dinding Kuning - Sesuai Gambar)
//    glPushMatrix();
//    glTranslatef(0.0f, 4.0f, -6.0f); // Posisi pusat dinding
//    drawBox(40.0f, 8.0f, 5.0f, 0.95f, 0.8f, 0.2f); // Tinggi 8.0f
//    glPopMatrix();
//
//    // Pilar-pilar Depan Utama (Biru dan Kuning/Oranye)
//    for (int i = 0; i < FRONT_PILLARS.size(); ++i) {
//        const auto& p = FRONT_PILLARS[i];
//        if (i % 2 == 0) { // Pilar Biru
//            drawPillar(p.x, 0.0f, p.z, 8.0f, 0.7f, 0.1f, 0.4f, 0.8f); // Tinggi 8.0f
//        }
//        else { // Pilar Kuning/Oranye
//            drawPillar(p.x, 0.0f, p.z, 8.0f, 0.7f, 0.9f, 0.7f, 0.2f);
//        }
//    }
//
//    // Atap Kanopi Oranye (menjorok ke depan)
//    glColor3f(1.0f, 0.5f, 0.0f);
//    glPushMatrix();
//    glTranslatef(0.0f, 8.0f, 0.0f);
//    glRotatef(-3.0f, 1.0f, 0.0f, 0.0f);
//    drawBox(45.0f, 0.2f, 35.0f, 1.0f, 0.5f, 0.0f); // Kanopi lebih lebar dan tipis
//    glPopMatrix();
//
//    // Atap Putih di Atas Bangunan Belakang (lebih tinggi dari kanopi oranye)
//    glColor3f(1.0f, 1.0f, 1.0f);
//    glPushMatrix();
//    glTranslatef(0.0f, 9.5f, -5.0f);
//    glRotatef(-8.0f, 1.0f, 0.0f, 0.0f);
//    drawBox(45.0f, 0.4f, 25.0f, 1.0f, 1.0f, 1.0f); // Atap lebih besar dan tinggi
//    glPopMatrix();
//
//    // Dinding samping Stan
//    glPushMatrix(); glTranslatef(-20.5f, 4.0f, -6.0f); drawBox(3.0f, 8.0f, 5.0f, 0.95f, 0.8f, 0.2f); glPopMatrix();
//    glPushMatrix(); glTranslatef(20.5f, 4.0f, -6.0f); drawBox(3.0f, 8.0f, 5.0f, 0.95f, 0.8f, 0.2f); glPopMatrix();
//
//    // Stan-stan Makanan (Warung) di belakang pilar
//    for (const auto& stall : STALL_WALLS) { // Menggunakan STALL_WALLS yang benar
//        drawStall(stall.x, stall.z);
//    }
//
//    // Meja dan Kursi di Area Terbuka
//    for (const auto& table : TABLES) {
//        drawTableSet(table.x, table.z, table.rot);
//    }
//
//    // Lampu Penerangan
//    for (const auto& light : LIGHTS) {
//        drawStreetLight(light.x, light.z);
//    }
//
//    // Pagar Pintu Masuk (biru-oranye)
//    float fenceY = 0.0f;
//    // Pagar Kiri
//    glPushMatrix();
//    glTranslatef(-2.5f, fenceY, 8.0f);
//    glRotatef(leftGateRotation, 0.0f, 1.0f, 0.0f);
//    drawBox(1.0f, 2.0f, 0.2f, 0.1f, 0.1f, 0.8f);
//    glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.01f); drawBox(0.8f, 1.8f, 0.1f, 1.0f, 0.6f, 0.0f); glPopMatrix();
//    glPopMatrix();
//
//    // Pagar Kanan
//    glPushMatrix();
//    glTranslatef(2.5f, fenceY, 8.0f);
//    glRotatef(rightGateRotation, 0.0f, 1.0f, 0.0f);
//    drawBox(1.0f, 2.0f, 0.2f, 0.1f, 0.1f, 0.8f);
//    glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.01f); drawBox(0.8f, 1.8f, 0.1f, 1.0f, 0.6f, 0.0f); glPopMatrix();
//    glPopMatrix();
//
//    // Area rumput di samping
//    drawTree(-30.0f, 10.0f);
//    drawTree(-35.0f, 0.0f);
//    drawTree(30.0f, 15.0f);
//    drawTree(38.0f, 5.0f);
//    drawBush(-28.0f, 5.0f);
//    drawBush(-20.0f, 20.0f);
//    drawBush(20.0f, 18.0f);
//    drawBush(28.0f, 0.0f);
//
//    // Tambahan pagar tanaman
//    glColor3f(0.1f, 0.4f, 0.1f);
//    glPushMatrix(); glTranslatef(-10.0f, 0.5f, -10.0f); drawBox(30.0f, 1.0f, 1.0f, 0.1f, 0.4f, 0.1f); glPopMatrix();
//    glPushMatrix(); glTranslatef(10.0f, 0.5f, -10.0f); drawBox(30.0f, 1.0f, 1.0f, 0.1f, 0.4f, 0.1f); glPopMatrix();
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//
//    // Tinggi kamera diturunkan menjadi 5.0f untuk sudut pandang yang lebih realistis
//    gluLookAt(x, 5.0f, z, x + lx, 5.0f, z + lz, 0.0f, 1.0f, 0.0f);
//
//    drawFoodcourt();
//
//    glutSwapBuffers();
//}
//
//void reshape(int w, int h) {
//    if (h == 0) h = 1;
//    float ratio = w * 1.0 / h;
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glViewport(0, 0, w, h);
//    gluPerspective(60.0f, ratio, 0.1f, 200.0f);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void processSpecialKeys(int key, int xx, int yy) {
//    float fraction = 1.0f;
//    switch (key) {
//    case GLUT_KEY_LEFT: angle -= 0.05f; lx = sin(angle); lz = -cos(angle); break;
//    case GLUT_KEY_RIGHT: angle += 0.05f; lx = sin(angle); lz = -cos(angle); break;
//    case GLUT_KEY_UP: x += lx * fraction; z += lz * fraction; break;
//    case GLUT_KEY_DOWN: x -= lx * fraction; z -= lz * fraction; break;
//    }
//    glutPostRedisplay();
//}
//
//void mouse(int button, int state, int mx, int my) {
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        isGateOpen = !isGateOpen;
//        if (isGateOpen) {
//            leftGateRotation = 90.0f;
//            rightGateRotation = -90.0f;
//        }
//        else {
//            leftGateRotation = 0.0f;
//            rightGateRotation = 0.0f;
//        }
//        glutPostRedisplay();
//    }
//}
//
//int main(int argc, char** argv) {
//    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
//    glutInit(&argc, argv);
//    glutInitWindowPosition(100, 100);
//    glutInitWindowSize(1200, 700);
//    glutCreateWindow("Foodcourt UNESA Ketintang - Imajinasi V4");
//
//    initLighting();
//
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutSpecialFunc(processSpecialKeys);
//    glutMouseFunc(mouse);
//
//    glutMainLoop();
//
//    // Pastikan GLUquadric dihapus
//    gluDeleteQuadric(quadratic);
//    return 0;
//}