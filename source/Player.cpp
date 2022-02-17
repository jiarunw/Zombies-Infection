#include "Player.h"
#include <math.h>
#define PI 3.1415926
Player::Player(int x, int y, YsRawPngDecoder* gunPNGs)
{
	initialize(x, y, gunPNGs);
}
void Player::initialize(int x, int y, YsRawPngDecoder* gunPNGs)
{
	this->weaponList.push_back(new Weapon(0, gunPNGs));
	this->state = 1;
	this->x = x;
	this->y = y;
	this->dx = 0;
	this->dy = 0;
	this->vx = 5;
	this->vy = 5;
	this->HP = 300;
	this->xSize = 38;
	this->ySize = 58;
	this->currentWeaponID = 0;
	this->playerPNGs = new YsRawPngDecoder[4];
	this->playerPNGs[0].Decode("player_w.png");
	this->playerPNGs[1].Decode("player_d.png");
	this->playerPNGs[2].Decode("player_s.png");
	this->playerPNGs[3].Decode("player_a.png");
	this->playerPNGs[0].Flip();
	this->playerPNGs[1].Flip();
	this->playerPNGs[2].Flip();
	this->playerPNGs[3].Flip();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLuint textID;
	glGenTextures(1, &textID);
	
	
}

void Player::move(int key)
{
	if (FSKEY_W == key) {
		dx = 0;
		dy = -1;
		this->y += dy * this->vy;
		direction = 0;
	}
	else if (FSKEY_A == key) {
		dx = -1;
		dy = 0;
		this->x += dx * this->vx;
		direction = 1;
	}
	else if (FSKEY_S == key) {
		dx = 0;
		dy = 1;
		this->y += dy * this->vy;
		direction = 2;
	}
	else if (FSKEY_D == key) {
		dx = 1;
		dy = 0;
		this->x += dx * this->vx;
		direction = 3;
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
	int end = y - 15-ySize / 2;
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	//glLineWidth(0.5);
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
void Player::draw(int mx, int my) const
{
	glBindTexture(GL_TEXTURE_2D, textID2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	/*if (dx > 0)
	{
		
		if (dy >= 0)
			direction = 0;
		else
			direction = 1;
	}
	else
	{
		if (dy >= 0)
			direction = 2;
		else
			direction = 3;
	}*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->playerPNGs[direction].wid, this->playerPNGs[direction].hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->playerPNGs[direction].rgba);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glBindTexture(GL_TEXTURE_2D, textID2);
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
	Weapon* currentWeapon = weaponList[currentWeaponID];

	drawHPBar();
	currentWeapon->drawPng(this->x, this->y, dx, dy, weaponList[currentWeaponID]->id, mx, my);
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
	//cout << currentWeaponID << endl;
}
void Player::addWeapon(Weapon* weapon)
{
	for (int i = 0; i < weaponList.size(); i++) {
		if (weapon->id == weaponList[i]->id) {
			//refill the original weapon
			 weaponList[i]->refill();
			//switch to this weapon
			currentWeaponID = i;
			delete weapon;
			weapon = nullptr;
			return;
		}
		
	}
	cout << weapon->id << "added" << endl;
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
				delete* weaponiter;
				*weaponiter = nullptr;
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
		if (currentWeaponID != 0) {
			currentWeapon->bullet--;
			cout << currentWeapon->bullet << endl;
		}
		if (currentWeapon->bullet <= 0) {
			dropWeapon();
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

int Player::getBulletNum()
{
	return weaponList[this->currentWeaponID]->bullet;
}
int Player::getWeaponID()
{
	return weaponList[this->currentWeaponID]->id;
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
//
//int Player::getBulletNum() {
//	return this->weaponList[this->currentWeaponID].bullet;
//}