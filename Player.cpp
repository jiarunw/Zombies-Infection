#include "Player.h"
#include <math.h>
#define PI 3.1415926
Player::Player(int x, int y)
{
	initialize(x, y);
}
void Player::initialize(int x, int y)
{
	this->weaponList.push_back(new Weapon(10));
	this->state = 1;
	this->x = x;
	this->y = y;
	this->dx = 0;
	this->dy = 0;
	this->vx = 5;
	this->vy = 5;
	this->HP = 300;
	this->xSize = 25;
	this->ySize = 25;
	this->currentWeaponID = 0;
}

void Player::move(int key)
{
	if (FSKEY_W == key) {
		dx = 0;
		dy = -1;
		this->y += dy * this->vy;
	}
	else if (FSKEY_A == key) {
		dx = -1;
		dy = 0;
		this->x += dx * this->vx;
	}
	else if (FSKEY_S == key) {
		dx = 0;
		dy = 1;
		this->y += dy * this->vy;
	}
	else if (FSKEY_D == key) {
		dx = 1;
		dy = 0;
		this->x += dx * this->vx;;
	}
}

void Player::drawHPBar() const
{
	double len = 30;
	double wid = 5;
	len = double(this->HP) / this->maxHP * len;
	//cout << this->HP << "\n";
	//cout << len << "\n";
	int start = x - 15;
	int end = y - 15;
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glLineWidth(1);
	glVertex2i(start - 2, end - 2);
	glVertex2i(start + 32, end - 2);
	glVertex2i(start + 32, end + 5);
	glVertex2i(start - 2, end + 5);
	glEnd;
	glColor3f(1, 0, 0);

	glBegin(GL_QUADS);
	
	glVertex2i(start, end);
	glVertex2i(start + len, end);
	glVertex2i(start + len, end + 3);
	glVertex2i(start, end + 3);
	glEnd();

	
}
void Player::draw() const
{
	//this->curT += 1;
	glColor4ub(250, 0, 0, 255);
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

	Weapon* currentWeapon = weaponList[currentWeaponID];

	drawHPBar();
	//currentWeapon.draw(this->x, this->y);
}
void Player::switchWeapon(int key)
{
	if (FSKEY_Q == key) {
		if (currentWeaponID == 0) {
			currentWeaponID == weaponList.size() - 1;
		}
		else {
			currentWeaponID--;
		}
	}
	else if (FSKEY_E == key) {
		if (currentWeaponID == weaponList.size() - 1) {
			currentWeaponID = 0;
		}
		else {
			currentWeaponID++;
		}
	}
}
void Player::addWeapon(Weapon* weapon)
{
	for (int i = 0; i < weaponList.size(); i++) {
		if (weapon->id == weaponList[i]->id) {
			//refill the original weapon
			// weaponList[i]->refill();
			//switch to this weapon
			currentWeaponID = i;
			return;
		}
	}
	this->weaponList.push_back(weapon);
	currentWeaponID = weaponList.size() - 1;
}
void Player::dropWeapon()
{
	if (currentWeaponID == 0) {
		return;
	}
	else {
		for (auto weaponiter = weaponList.begin();
			weaponiter != weaponList.end();
			weaponiter++) {
			if (*weaponiter == weaponList[currentWeaponID]) {
				weaponList.erase(weaponiter);
				currentWeaponID--;
				return;
			}
		}
	}
}



void Player::updateHP(int attack)
{
	this->HP -= attack;
	if (HP <= 0) {
		this->state = 0;
	}
	if (HP >= this->maxHP) {
		HP = maxHP;
	}
}

Bullet* Player::fire(int evt, double mx, double my)
{
	if (FSMOUSEEVENT_LBUTTONDOWN == evt) {
		Weapon* currentWeapon = weaponList[currentWeaponID];
		if (!currentWeapon->readyToFire) {
			return nullptr;
		}
		double dx = double(mx - this->x);
		double dy = double(my - this->y);
		double dis = sqrt(dx * dx + dy * dy);
		double thetaX = dx / dis;
		double thetaY = dy / dis;
		int id = currentWeapon->id;
		return bulletGenerator(id, this->x, this->y, thetaX, thetaY);
	}
	return nullptr;
}

Bullet* Player::bulletGenerator(int id, double x, double y, double thetaX, double thetaY){
	/*if(id == 0){
		new pistolBullet(x, y, thetaX, thetaY);
	}
	else if(id == 1){
		new rifleBullet(x, y, thetaX, thetaY);
	}
	else if(id == 2){
		new machineGunBullet(x, y, thetaX, thetaY);
	}*/
	return new Bullet(x, y, thetaX, thetaY);
}