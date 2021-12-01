#ifndef ENEMY_H
#define ENEMY_H

#endif

#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include "AStar.h"
#include "Bullet.h"
#include <vector>
#include <iostream>

using namespace std;

#define PI 3.1415926

#define MAXO(A, B) ((A) > (B) ? (A) : (B))

#define MINO(A, B) ((A) < (B) ? (A) : (B))

#define GETMAPINDEX(X, Y, XSIZE, YSIZE) ((Y)*XSIZE + (X))

class Enemy
{
public:
    Enemy(double* map, int mapSizeX, int mapSizeY, int type)
    {
        this->map = map;
        this->mapSizeX = mapSizeX;
        this->mapSizeY = mapSizeY;
        this->type = type;
        this->planner = new AStar(map, mapSizeX, mapSizeY, v);
        initialize();
    };

    ~Enemy() {};

    void initialize()
    {
        while (1)
        {
            this->x = rand() % mapSizeX;
            this->y = rand() % mapSizeY;
            if (map[GETMAPINDEX((int)this->x, (int)this->y, mapSizeX, mapSizeY)] != 1)
            {
                break;
            }
        }
        // zombie visualization size
        this->xSize = 50;
        this->ySize = 50;
        this->dx = 0;
        this->dy = 1;
        this->state = 1; //0:dead ;1: alive; 2: attacking; 3: attacked
        this->startT = 0;
        this->curT = 0;
        this->attackReady = 0;
        //        this->bodyPNG.Decode("zombie_left.png");
        //        this->bodyPNG.Flip();
        this->bodyPNGs = new YsRawPngDecoder[8];
        this->bodyPNGs[0].Decode("zombie1_left.png");
        this->bodyPNGs[0].Flip();
        this->bodyPNGs[1].Decode("zombie1_right.png");
        this->bodyPNGs[1].Flip();
        this->bodyPNGs[2].Decode("zombie2_left.png");
        this->bodyPNGs[2].Flip();
        this->bodyPNGs[3].Decode("zombie2_right.png");
        this->bodyPNGs[3].Flip();
        this->bodyPNGs[4].Decode("zombie3_left.png");
        this->bodyPNGs[4].Flip();
        this->bodyPNGs[5].Decode("zombie3_right.png");
        this->bodyPNGs[5].Flip();
        this->bodyPNGs[6].Decode("zombie4_left.png");
        this->bodyPNGs[6].Flip();
        this->bodyPNGs[7].Decode("zombie4_right.png");
        this->bodyPNGs[7].Flip();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glGenTextures(1, &textID);
        set();
    };

    void set()
    {
        switch (this->type)
        {
        case 1:
            //Speed
            this->v = 4;
            this->HP = 10;
            this->ATK = 1;
            this->attackRange = 100;
            break;
        case 2:
            //ATK
            this->v = 1;
            this->HP = 10;
            this->ATK = 5;
            this->attackRange = 100;
            break;
        case 3:
            //HP
            this->v = 2;
            this->HP = 20;
            this->ATK = 3;
            this->attackRange = 100;
            break;
        case 4:
            //RANGE
            this->v = 4;
            this->HP = 10;
            this->ATK = 1;
            this->attackRange = 200;
            break;
        }
    }

    double getX() const
    {
        return this->x;
    };

    double getY() const
    {
        return this->y;
    };

    double getXSize() const
    {
        return this->xSize;
    };

    double getYSize() const
    {
        return this->ySize;
    };

    double getV() const
    {
        return this->v;
    };

    int getHP() const
    {
        return this->HP;
    };

    int getATK() const
    {
        return this->ATK;
    };

    int getType() const
    {
        return this->type;
    };

    double getDx() const
    {
        return this->dx;
    };

    double getDy() const
    {
        return this->dy;
    };
    int getCurT() const {
        return this->curT;
    }

    int getState() const
    {
        return this->state;
    };

    int getAttackReady() const
    {
        return this->attackReady;
    }

    void setType(int type)
    {
        this->type = type;
    }

    void setATK(int ATK)
    {
        this->ATK = ATK;
    }

    void setV(double v)
    {
        this->v = v;
    }

    void setAttackRange(double attackRange)
    {
        this->attackRange = attackRange;
    }

    void setHP(int HP)
    {
        this->HP = HP;
    };

    void setMap(double* map)
    {
        this->map = map;
        this->planner = new AStar(map, mapSizeX, mapSizeY, v);
    };

    void move(double* target)
    {
        plan(target);
        checkCollision();
        updateAttackReady(target);
        x += dx * v;
        y += dy * v;
    };

    Bullet* attacking(double* target)
    {
        /*if (this->attackReady == 0 || this->state == 0) {
            return nullptr;
        }*/

        if (this->state != 0)
        {
            this->state = 2;
        }
        double distX = target[0] - x;
        double distY = target[1] - y;
        double distance = sqrt(distX * distX + distY * distY);

        double thetaX = distX / distance;
        double thetaY = distY / distance;
        Bullet* newBullet = new Bullet(x, y, thetaX, thetaY);
        return newBullet;
    }

    int attacked(int ATK)
    {
        this->HP -= ATK;
        if (HP <= 0)
        {
            this->state = 0;
        }
        if (this->state != 0)
        {
            this->state = 3;
        }
        return this->HP;
    }

    void draw()
    {
        YsRawPngDecoder* png;
        if (dx >= 0) {
            png = &bodyPNGs[2 * (type - 1)];
        } 
        else {
            png = &bodyPNGs[2 * (type - 1) + 1];
        }
        this->curT += 1;
        // cout << this->state << endl;
        switch (state)
        {
        case 0:
           //drawAlive(png);
            break;
        case 1:
            drawAlive(png);
            break;
        case 2:
            drawAlive(png);
            this->state = 1;
            break;
        case 3:
            drawAlive(png);
            this->state = 1;
            break;
        default:
            drawAlive(png);
            break;
        }
        //delete png;
        //png = nullptr;
    };

    void drawAlive(YsRawPngDecoder* png) {

        glBindTexture(GL_TEXTURE_2D, textID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png->wid, png->hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png->rgba);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    
        glColor4d(1.0, 1.0, 1.0, 1.0);
        
        glEnable(GL_TEXTURE_2D);

        glBegin(GL_QUADS);
        glTexCoord2d(1.0, 1.0);
        glVertex2i(x - xSize / 2, y - ySize / 2);
        glTexCoord2d(0.0, 1.0);
        glVertex2i(x + xSize / 2, y - ySize / 2);
        glTexCoord2d(0.0, 0.0);
        glVertex2i(x + xSize / 2, y + ySize / 2);
        glTexCoord2d(1.0, 0.0);
        glVertex2i(x - xSize / 2, y + ySize / 2);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

    void drawAliveBallBody()
    {

        glColor4ub(250, 0, 0, 255);
        if (this->attackReady == 1)
        {
            glColor4ub(250, 255, 0, 255);
        }
        double r1 = 10;
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 64; i++)
        {
            double angle = (double)i * PI * 2 / 64.0;
            double X = (double)x + cos(angle) * (double)r1;
            double Y = (double)y + sin(angle) * (double)r1;
            glVertex2d(X, Y);
        }
        glEnd();

        double d = 15;

        glColor4ub(0, 255, 0, 255);
        double r2 = 5;
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 64; i++)
        {
            double angle = (double)i * PI * 2 / 64.0;
            double X = (double)x + cos(angle) * (double)r2 + dx * d;
            double Y = (double)y + sin(angle) * (double)r2 + dy * d;
            glVertex2d(X, Y);
        }
        glEnd();
    };

    void drawAttacking()
    {
        glColor4ub(0, 255, 0, 255);
        double r1 = 10;
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 64; i++)
        {
            double angle = (double)i * PI * 2 / 64.0;
            double X = (double)x + cos(angle) * (double)r1;
            double Y = (double)y + sin(angle) * (double)r1;
            glVertex2d(X, Y);
        }
        glEnd();

        double d = 15;

        glColor4ub(0, 255, 0, 255);
        double r2 = 5;
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 64; i++)
        {
            double angle = (double)i * PI * 2 / 64.0;
            double X = (double)x + cos(angle) * (double)r2 + dx * d;
            double Y = (double)y + sin(angle) * (double)r2 + dy * d;
            glVertex2d(X, Y);
        }
        glEnd();
    };

    void drawAttacked()
    {
        glColor4ub(0, 0, 255, 255);
        double r1 = 10;
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 64; i++)
        {
            double angle = (double)i * PI * 2 / 64.0;
            double X = (double)x + cos(angle) * (double)r1;
            double Y = (double)y + sin(angle) * (double)r1;
            glVertex2d(X, Y);
        }
        glEnd();

        double d = 15;

        glColor4ub(0, 255, 0, 255);
        double r2 = 5;
        glBegin(GL_POLYGON);
        for (int i = 0; i <= 64; i++)
        {
            double angle = (double)i * PI * 2 / 64.0;
            double X = (double)x + cos(angle) * (double)r2 + dx * d;
            double Y = (double)y + sin(angle) * (double)r2 + dy * d;
            glVertex2d(X, Y);
        }
        glEnd();
    };

    bool checkCollision()
    {
        double xNew = x + dx * v;
        double yNew = y + dy * v;
        bool collide = false;
        if (xNew <= 0 || xNew >= mapSizeX)
        {
            dx *= -1;
            collide = true;
        }
        else if (yNew <= 0 || yNew >= mapSizeY)
        {
            dy *= -1;
            collide = true;
        }
        else if (map[GETMAPINDEX((int)xNew, (int)yNew, mapSizeX, mapSizeY)] == 1)
        {
            if (map[GETMAPINDEX((int)xNew, (int)y, mapSizeX, mapSizeY)] == 0)
            {
                dy *= -1;
                collide = true;
            }
            else if (map[GETMAPINDEX((int)x, (int)yNew, mapSizeX, mapSizeY)] == 0)
            {
                dx *= -1;
                collide = true;
            }
        }
        return collide;
    };

    void selectDirection(double theta)
    {
        if (theta <= 30 && theta >= -30)
        {
            dx = 1;
            dy = 0;
        }
        else if (theta <= 60 && theta >= 30)
        {
            dx = 1;
            dy = 1;
        }
        else if (theta <= 120 && theta >= 60)
        {
            dx = 0;
            dy = 1;
        }
        else if (theta <= 150 && theta >= 120)
        {
            dx = -1;
            dy = 1;
        }
        else if (theta <= -150 || theta >= 150)
        {
            dx = -1;
            dy = 0;
        }
        else if (theta <= -120 && theta >= -150)
        {
            dx = -1;
            dy = -1;
        }
        else if (theta <= -60 && theta >= -120)
        {
            dx = 0;
            dy = -1;
        }
        else if (theta <= -30 && theta >= -60)
        {
            dx = 1;
            dy = -1;
        }
        else
        {
            dx = 0;
            dy = 0;
            cout << "this should not happen! theta= " << theta << endl;
        }
    }

    bool heuristicPlan(double* start, double* target)
    {
        int x_diff = target[0] - start[0];
        int y_diff = target[1] - start[1];
        double theta = atan2(y_diff, x_diff) * 180 / PI;
        bool success = true;
        selectDirection(theta);
        if (checkCollision())
        {
            selectDirection(theta + 60);
            if (checkCollision())
            {
                selectDirection(theta - 60);
            }
        }
        if (checkCollision())
        {
            success = false;
        }
        return success;
    }

private:
    GLuint textID;
    double xSize, ySize, x, y;
    double v;
    double attackRange;
    int mapSizeX, mapSizeY;
    int HP, ATK;
    int type;
    int state;
    int startT, curT;
    int dx, dy;
    double* map;
    int attackReady;
    AStar* planner;
   // YsRawPngDecoder bodyPNG;
    YsRawPngDecoder* bodyPNGs;

    void plan(double* target)
    {
        double* start = new double[2];
        start[0] = x;
        start[1] = y;

        if (start[0] == target[0] && start[1] == target[1])
        {
            dx = 0;
            dy = 0;
        }
        else
        {
            if (!heuristicPlan(start, target))
            {
                planner->search(start, target);

                vector<int> direction = planner->getDirection();
                //cout << direction[0] << ' ' << direction[1] << endl;

                dx = direction[0];
                dy = direction[1];
            }
        }
        delete[] start;

        int r = rand() % 10;
        if (r < 7) {
            dx = dx;
            dy = dy;
        }
        else {
            dx = dx * (rand() % 2 );
            dy = dy * (rand() % 2 );
        }


        
    };

    void updateAttackReady(double* target)
    {
        if (pow((x - target[0]), 2), pow((y - target[1]), 2) <= pow((this->attackRange), 2))
        {

            int sampleNum = 20;
            double di = (target[0] - x) / (double)sampleNum;
            double dj = (target[1] - y) / (double)sampleNum;
            for (int t = 0; t <= sampleNum; ++t)
            {
                double curX = x + di * t;
                double curY = y + dj * t;
                //cout << x << ' ' << y << ' ' << curX << ' ' << curY << endl;
                if (map[GETMAPINDEX((int)curX, (int)curY, mapSizeX, mapSizeY)] != 0)
                {
                    this->attackReady = 0;

                }
            }
            this->attackReady = 1;
            return;
        }
    }
};