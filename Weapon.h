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
    int maxbullet;
    bool readyToFire=true;
    int xSize;
    int ySize;
    YsRawPngDecoder* gunPNGs;
    // int coolDownTime;
    Weapon(int id) {
        switch (id)
        {
        case 0:
            attckPower = 1;
            bullet = 10;
            imgDir = "pistol.png";
            xSize = 40;
            ySize = 20;
            maxbullet = 1000;
            break;
        case 1:
            attckPower = 5;
            bullet = 40;
            imgDir = "rifle.png";
            xSize = 40;
            ySize = 8;
            maxbullet = 40;
            break;
        case 2:
            attckPower = 2;
            bullet = 100;
            imgDir = "machineGun.png";
            xSize = 80;
            ySize = 18;
            maxbullet = 100;
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
        this->gunPNGs = new YsRawPngDecoder[3];
        this->gunPNGs[0].Decode("pistol.png");
        this->gunPNGs[1].Decode("rifle.png");
        this->gunPNGs[2].Decode("machineGun.png");
       /* this->gunPNGs[0].Flip();
        this->gunPNGs[1].Flip();
        this->gunPNGs[2].Flip();*/
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLuint textID;
        glGenTextures(1, &textID);
        
    }
    void drawPng(int x, int y, int dx, int dy, int idd, int mx, int my)
    {
        
        //int idd = id ;
        //cout << idd << endl;
        glBindTexture(GL_TEXTURE_2D, textID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->gunPNGs[idd].wid, this->gunPNGs[idd].hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->gunPNGs[idd].rgba);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(1.0, 1.0, 1.0, 1.0);
        glEnable(GL_TEXTURE_2D);
        float angle;
        if ((mx - x) < 0)
        {
            angle = atan((float)(my - y) / (float)(mx - x)) * 180.0 / PI;
        }
            
        else
            angle = atan((float)(my - y) / (float)(mx - x)) * 180.0 / PI + 180;
        glBindTexture(GL_TEXTURE_2D, textID);
        glPushMatrix();
        glTranslated(x, y, 0);
        glRotatef(angle, 0, 0, 1);
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
    void Draw(int x, int y, int dx, int dy, int idd, int mx, int my)
    {
        
        drawPng(x, y, dx, dy, idd, mx, my);

    }
    void refill() {
        bullet = maxbullet;
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