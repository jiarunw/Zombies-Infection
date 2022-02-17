#include <stdlib.h>
#include <vector>
#include "Bullet.h"
#include "Weapon.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"

using namespace std;

class Player {
private:
	GLuint textID2;
	YsRawPngDecoder* playerPNGs;
	int state;
	int x;
	int y;
	int dx;
	int dy;
	int xSize;
	int ySize;
	int HP;
	int maxHP = 300;
	double vx;
	double vy;
	int direction;
	//the index of current weapon
	//not the same as the id inside the weapon class
	
	vector<Weapon*> weaponList;
public:
	int currentWeaponID;
	Player(int x, int y, YsRawPngDecoder* gunPNGs);
	void initialize(int x, int y, YsRawPngDecoder* gunPNGs);
	void move(int key);
	void draw(int mx, int my)const;
	void switchWeapon(int key);
	void addWeapon(Weapon*);
	void dropWeapon();
	void drawHPBar() const;
	void updateHP(int attack);
	Bullet* fire(int evt, double mx, double my);
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	int getHP() {
		return this->HP;
	}
	double getvx() {
		return this->vx;
	}
	double getvy() {
		return this->vy;
	}

	int getxSize(){
		return this->xSize;
	}

	int getySize(){
		return this->ySize;
	}

	int getBulletNum();
	int getWeaponID();
	Bullet* bulletGenerator(int id, double x, double y, double thetaX, double thetaY);
};