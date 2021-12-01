#ifndef BULLET_H
#define BULLET_H

#include "fssimplewindow.h"
#include "yssimplesound.h"
#include <vector>
#include <iostream>

using namespace std;

#define PI 3.1415926

#define    MAXO(A, B)    ((A) > (B) ? (A) : (B))

#define    MINO(A, B)    ((A) < (B) ? (A) : (B))

#define GETMAPINDEX(X, Y, XSIZE, YSIZE) ((Y)*XSIZE + (X))


class Bullet {
public:
    Bullet(double x, double y, double thetaX, double thetaY) {
        this->x = x;
        this->y = y;
        this->thetaX = thetaX;
        this->thetaY = thetaY;
        initialize();
    };

    ~Bullet() {
    };

    void initialize() {
        this->xSize = 10;
        this->ySize = 10;
        this->v = 5;
        this->ATK = 1;
        this->type = 1;
        this->state = 1;//0:dead ;1: alive
        this->startT = 0;
        this->curT = 0;
    };

    double getX() const {
        return this->x;
    };

    double getY() const {
        return this->y;
    };

    double getXSize() const {
        return this->xSize;
    };

    double getYSize() const {
        return this->ySize;
    };

    double getV() const {
        return this->v;
    };

    int getATK() const {
        return this->ATK;
    };

    int getType() const {
        return this->type;
    };


    int getState() const {
        return this->state;
    };

    void move() {
        x += thetaX * v;
        y += thetaY * v;
    };


    void draw(int id) {
        this->curT += 1;
        // cout << this->state << endl;
        switch (state) {
        case 0:
            break;
        case 1:
            drawAlive(id);
            break;
        default:
            drawAlive(id);
            break;
        }

    };

    void drawAlive(int id) {
        if (id == 0) {
            // enemy bullet
            glColor4ub(0, 255, 0, 255);
        }
        else {
            // bullet
            glColor4ub(255, 0, 0, 255);
        }
        
        double r1 = 3;
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 64; i++)
        {
            double angle = (double)i * PI * 2 / 64.0;
            double X = (double)x + cos(angle) * (double)r1;
            double Y = (double)y + sin(angle) * (double)r1;
            glVertex2d(X, Y);

        }
        glEnd();

        
    };




private:
    double xSize, ySize, x, y, v, thetaX, thetaY;
    int ATK;
    int type;
    int state;
    int startT, curT;
};

#endif
