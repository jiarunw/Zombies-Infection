#include <string>
#include<string.h>
#include "yspng.h"
using namespace std;

class Weapon
{
public:
    unsigned int id;
    GLuint textID;
    string imgDir;
    int attckPower;
    int bullet;
    bool readyToFire=true;
    int xSize;
    int ySize;
    YsRawPngDecoder gunPNGs;
    // int coolDownTime;
    Weapon(int id) {
        switch (id)
        {
        case 10:
            attckPower = 2;
            bullet = 10;
            imgDir = "pistol.png";
            xSize = 40;
            ySize = 20;
            break;
        case 11:
            attckPower = 5;
            bullet = 4;
            imgDir = "rifle.png";
            xSize = 40;
            ySize = 8;
            break;
        case 12:
            attckPower = 1;
            bullet = 20;
            imgDir = "machineGun.png";
            xSize = 25;
            ySize = 9;
            break;
        default:
            break;
        }
        this->xSize = xSize;
        this->ySize = ySize;
        this->id = id;
        this->imgDir = imgDir;
        this->attckPower = attckPower;
        this->bullet = bullet;
        if (id == 0)
            this->gunPNGs.Decode("pistol.png");
        else if (id == 1)
            this->gunPNGs.Decode("rifle.png");
        else
            this->gunPNGs.Decode("machineGun.png");
        this->gunPNGs.Flip();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLuint textID;
        glGenTextures(1, &textID);
        
    }
    void drawPng(int x, int y, int dx, int dy)
    {
        glBindTexture(GL_TEXTURE_2D, textID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->gunPNGs.wid, this->gunPNGs.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->gunPNGs.rgba);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(1.0, 1.0, 1.0, 1.0);

        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, textID);
        glPushMatrix();
        glTranslated(x, y, 0);
        glRotated(50, 0, 0, 1);
        glTranslated(-x, -y, 0);
        
        glBegin(GL_QUADS);
        glTexCoord2d(1.0, 1.0);
        
        glVertex2i(x - this->xSize / 2, y - this->ySize / 2);
        glTexCoord2d(0.0, 1.0);
        glVertex2i(x + this->xSize / 2, y - this->ySize / 2);
        glTexCoord2d(0.0, 0.0);
        glVertex2i(x + this->xSize / 2, y + this->ySize / 2);
        glTexCoord2d(1.0, 0.0);
        glVertex2i(x - this->xSize / 2, y + this->ySize / 2);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    void Draw(int x, int y, int dx, int dy)
    {
        
        drawPng(x, y, dx, dy);

    }
};
//class Pistol : public Weapon
//{
//public:
//    //id = 0;
//    //attckPower = 2;
//    //bullet = 10;
//    //imgDir = "pistol.png";
//    Pistol() : Weapon(0, "pistol.png", 2, 10, 40, 20){
//        
//    }
//};
//class Rifle : public Weapon
//{
//    /*id = 1;
//    attckPower = 5;
//    bullet = 4;
//    string imgDir = "rifle.png";*/
//    Rifle() : Weapon(1, "rifle.png", 5, 4, 40, 8) {
//
//    }
//};
//class MachineGun : public Weapon
//{
//    /*id = 2;
//    attckPower = 1;
//    bullet = 20;
//    string imgDir = "machineGun.png";*/
//MachineGun(): Weapon(2, "machineGun.png", 1, 20, 25, 9) {
//
//}
//};