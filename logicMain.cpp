#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<vector>
#include<math.h>
#include "Enemy.h"
#include "Player.h"
#include"fssimplewindow.h"
#include"Bullet.h"
#include"resource.h"
#include<list>

int mapWidth = 800;
int mapHeight = 600;

using namespace std;

#define GETMAPINDEX(X, Y, XSIZE, YSIZE) ((Y)*XSIZE + (X))

// BackGround Part
void initObstacle(double map[], int xObstacle[], int yObstacle[], int xObstacleSize[], int yObstacleSize[]) {
	int obstacleNum = 10;
	cout << obstacleNum << "\n";
	for (int i = 0; i < obstacleNum; i++) {
		// out iteration
		int curX = xObstacle[i];
		int curY = yObstacle[i];
		int curXsize = xObstacleSize[i];
		int curYsize = yObstacleSize[i];
		for (int j = 0; j < curXsize; j++) {
			for (int k = 0; k < curYsize; k++) {
				int tempX = j + curX;
				int tempY = k + curY;
				map[GETMAPINDEX(tempX, tempY, mapWidth, mapHeight)] = 1;
			}
		}
	}
}

void drawObstacle(double map[]) {
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			if (map[GETMAPINDEX(i, j, mapWidth, mapHeight)] == 1) {
				glColor3ub(0, 0, 0);
				glBegin(GL_QUADS);
				glVertex2i(i, j);
				glVertex2i(i + 1, j);
				glVertex2i(i + 1, j + 1);
				glVertex2i(i, j + 1);
				glEnd();
			}
		}
	}
}

void initBackGround(double map[], list<Resource*>& resourceList) {
	// init map
	for (int i = 0; i < mapWidth * mapHeight; i++) {
		map[i] = 0.0;
	}
	// update map resources
	// set obstacle position
	int xObstacle[] = { 50, 425, 50, 425, 300, 450, 300, 300, 100, 650 };
	int yObstacle[] = { 25, 25, 525, 525, 225, 225, 150, 400, 150, 150 };
	int xObstacleSize[] = { 325, 325, 325, 325, 50, 50, 200, 200, 50, 50 };
	int yObstacleSize[] = { 50, 50, 50, 50, 150, 150, 50, 50, 300, 300 };
	initObstacle(map, xObstacle, yObstacle, xObstacleSize, yObstacleSize);

	// get resource position and resource id from resource.h
	int id2Num = 3;
	int id3Num = 3;
	int id4Num = 3;
	int id5Num = 3;

	for (int i = 0; i < 12; i++) {
		if (i / 3 == 0) {
			Hprecover* curResource = new Hprecover();
			while (1) {
				curResource->init();
				int curX = curResource->GetX();
				int curY = curResource->GetY();
				if (map[GETMAPINDEX(curX, curY, mapWidth, mapHeight)] != 1) {
					break;
				}
			}
			resourceList.push_back(curResource);
		}
		if (i / 3 == 1) {
			Bomb* curResource = new Bomb();
			while (1) {
				curResource->init();
				int curX = curResource->GetX();
				int curY = curResource->GetY();
				if (map[GETMAPINDEX(curX, curY, mapWidth, mapHeight)] != 1) {
					break;
				}
			}
			resourceList.push_back(curResource);
		}
		if (i / 3 == 2) {
			Green* curResource = new Green();
			while (1) {
				curResource->init();
				int curX = curResource->GetX();
				int curY = curResource->GetY();
				if (map[GETMAPINDEX(curX, curY, mapWidth, mapHeight)] != 1) {
					break;
				}
			}
			resourceList.push_back(curResource);
		}
		if (i / 3 == 3) {
			Box* curResource = new Box();
			while (1) {
				curResource->init();
				int curX = curResource->GetX();
				int curY = curResource->GetY();
				if (map[GETMAPINDEX(curX, curY, mapWidth, mapHeight)] != 1) {
					break;
				}
			}
			resourceList.push_back(curResource);
		}
	}
}

void drawResource(list<Resource*> resourceList) {
	for (Resource* curResource : resourceList) {
		curResource->Draw();
	}
}

// Enemy Part
void initEnemy(double map[], vector<Enemy*>& enemyList, int enemyNum, int mapWidth, int mapHeight) {
	//void initEnemy(double map[], vector<Enemy>& enemyList, int enemyNum, int mapWidth, int mapHeight) {
	enemyList.clear();
	// initlize enemy
	for (int i = 0; i < mapWidth * mapHeight; ++i) {
		//cout << map[i] << endl;
		if (map[i] == 1) {
			//cout << i / mapWidth <<' '<< i % mapWidth<< endl;
		}
	}
	while (enemyList.size() < enemyNum) {
		int typeEnemy = rand() % 3 + 1;
		Enemy* curEnemy = new Enemy(map, mapWidth, mapHeight, 3);
		//Enemy curEnemy = Enemy(map, mapWidth, mapHeight);
		enemyList.push_back(curEnemy);
	}
}

void drawEnemy(vector<Enemy*> enemyList, int enemyNum) {
	// draw enemy
	for (int i = 0; i < enemyNum; i++) {
		enemyList[i]->draw();
		//enemyList.at(i).draw();
	}
}

// Player Part
Player initPlayer(double map[], int mapWidth, int mapHeight) {
	int playerX, playerY;
	while (true) {
		playerX = rand() % mapWidth;
		playerY = rand() % mapHeight;
		if (map[GETMAPINDEX((int)playerX, (int)playerY, mapWidth, mapHeight)] != 1) {
			break;
		}
	}
	Player myPlayer = Player(playerX, playerY);
	return myPlayer;
}

void drawPlayer(Player myPlayer) {
	myPlayer.draw();
}

// enemy Bullet Part, Bullet Part
void drawBullet(list<Bullet*> enemyBulletList, list<Bullet*> bulletList) {
	for (Bullet* curBullet : enemyBulletList) {
		curBullet->draw();
	}
	for (Bullet* curBullet : bulletList) {
		curBullet->draw();
	}
}


// Move Part
void moveAll(vector<Enemy*> enemyList, double map[], Player& myPlayer, int key,
	int mapWidth, int mapHeight, list<Bullet*>& enemyBulletList, list<Bullet*>& bulletList) {
	// move enemy
	double target[2] = { myPlayer.getX(), myPlayer.getY() };
	for (int i = 0; i < enemyList.size(); i++) {
		enemyList[i]->move(target);
		//enemyList[i].move(target);
	}
	// move player
	int vx = myPlayer.getvx();
	int vy = myPlayer.getvy();
	if (key == FSKEY_W && (int)myPlayer.getY() - vy > 1 && map[GETMAPINDEX((int)myPlayer.getX(), (int)myPlayer.getY() - vy, mapWidth, mapHeight)] != 1
		) {
		// up
		myPlayer.move(key);
	}
	if (key == FSKEY_S && (int)myPlayer.getY() + vy < mapHeight - 1 && map[GETMAPINDEX((int)myPlayer.getX(), (int)myPlayer.getY() + vy, mapWidth, mapHeight)] != 1
		) {
		// down
		myPlayer.move(key);
	}
	if (key == FSKEY_A && (int)myPlayer.getX() - vx > 1 && map[GETMAPINDEX((int)myPlayer.getX() - vx, (int)myPlayer.getY(), mapWidth, mapHeight)] != 1
		) {
		// left
		myPlayer.move(key);
	}
	if (key == FSKEY_D && (int)myPlayer.getX() + vx < mapWidth - 1 && map[GETMAPINDEX((int)myPlayer.getX() + vx, (int)myPlayer.getY(), mapWidth, mapHeight)] != 1
		) {
		// right
		myPlayer.move(key);
	}

	// move bullet
	for (Bullet* curBullet : enemyBulletList) {
		curBullet->move();
	}

	for (Bullet* curBullet : bulletList) {
		curBullet->move();
	}
}


// Check Collision. 
// Enemy - Player
void colliEP(Enemy* curEnemy, Player& myPlayer, list<Bullet*>& enemyBulletList) {
	double enemyX = curEnemy->getX();
	double enemyY = curEnemy->getY();
	double playerX = myPlayer.getX();
	double playerY = myPlayer.getY();
	double target[2] = { myPlayer.getX(), myPlayer.getY() };
	double enemyXsize = curEnemy->getXSize();
	double enemyYsize = curEnemy->getYSize();
	if (curEnemy->getCurT() % 10 == 0) {
		if (curEnemy->getHP() > 0) {
			Bullet* curBullet = curEnemy->attacking(target);
			if (curBullet != nullptr) {
				enemyBulletList.push_back(curBullet);
			}
		}
	}

}

// Resource - Player - Enemy
void colliRP(Player& myPlayer, list<Resource*>& resourceList, vector<Enemy*>& enemyList) {
	int playerX = myPlayer.getX();
	int playerY = myPlayer.getY();
	double playerXsize = myPlayer.getxSize();
	double playerYsize = myPlayer.getySize();
	// TODO: check map resource id, update player state
	// player needs updateHP, update weaponList function
	list<Resource*>::iterator it;
	for (it = resourceList.begin(); it != resourceList.end(); ) {
		Resource* curResource = *it;
		int reX = (int)curResource->GetX();
		int reY = (int)curResource->GetY();
		int reXsize = curResource->GetXsize();
		int reYsize = curResource->GetYsize();
		int curReId = curResource->GetId();
		// check bomb and enemy
		if (curReId == 3) {
			vector<Enemy*>::iterator itEnemy;
			for (itEnemy = enemyList.begin(); itEnemy != enemyList.end();) {
				Enemy* curEnemy = *itEnemy;
				double enemyX = curEnemy->getX();
				double enemyY = curEnemy->getY();
				double enemyXsize = curEnemy->getXSize();
				double enemyYsize = curEnemy->getYSize();
				if (abs(enemyX - reX) < reXsize && abs(enemyY - reY) < reYsize) {
					curEnemy->attacked(10);
				}
				++itEnemy;
			}
		}
		// check resource and player
		if (abs(playerX - reX) < reXsize && abs(playerY - reY) < reYsize) {
			curResource->Action();
			if (curReId == 2) {
				// HPrecover
				myPlayer.updateHP(-1 * curResource->GetValue());
				it = resourceList.erase(it);
			}
			else if (curReId == 3) {
				// bomb
				myPlayer.updateHP(curResource->GetValue());
				it = resourceList.erase(it);
			}
			//else if (curReId == 4) {
			//	// grass
			//}
			else if (curReId == 5) {
				// box, add weapon
				int weaponId = curResource->GetValue();
				// cout << weaponId << "\n";
				Weapon* curWeapon = new Weapon(weaponId);
				myPlayer.addWeapon(curWeapon);
				it = resourceList.erase(it);
			}
			else {
				++it;
			}
		}
		else {
			++it;
		}
	}
}

// Resource - Enemy

//void removeBullet(list<Bullet*> bulletList, Bullet* deletingBullet) {
//	list<Bullet*>::iterator it;
//	for (it = bulletList.begin(); it != bulletList.end(); it++) {
//		if (*it == deletingBullet) {
//			cout << bulletList.size() << "\n";
//			bulletList.remove(*it);
//			break;
//		}
//	}
//}

// Bullet - Enemy
void colliBE(Enemy* curEnemy, list<Bullet*>& bulletList, double map[]) {
	double enemyX = curEnemy->getX();
	double enemyY = curEnemy->getY();
	double enemyXsize = curEnemy->getXSize();
	double enemyYsize = curEnemy->getYSize();

	list<Bullet*>::iterator it;
	for (it = bulletList.begin(); it != bulletList.end(); ) {
		Bullet* curBullet = *it;
		int buX = (int)curBullet->getX();
		int buY = (int)curBullet->getY();
		// check enemybullet out of range
		if (buX <= 1 || buX >= mapWidth - 1 || buY <= 1 || buY >= mapHeight - 1) {
			//removeBullet(enemyBulletList, curBullet);
			delete* it;
			*it = nullptr;
			it = bulletList.erase(it);
		}
		// here, 1 or others should be id of obstacle resource
		// check enemyBullet and obstacle
		// This check should be modified
		else if (map[GETMAPINDEX(buX, buY, mapWidth, mapHeight)] == 1) {
			delete* it;
			*it = nullptr;
			it = bulletList.erase(it);
			// removeBullet(enemyBulletList, curBullet);

		}
		// check enemyBullet and player
		else if (abs(enemyX - buX) < enemyXsize && abs(enemyY - buY) < enemyYsize) {
			// cout << abs(playerX - buX) << "\n";
			int ATK = curBullet->getATK();
			curEnemy->attacked(ATK);
			delete* it;
			*it = nullptr;
			it = bulletList.erase(it);

		}
		else {
			++it;
		}
	}

}

// enemyBullet - Player, obstacle
void coliEBP(list<Bullet*>& enemyBulletList, Player& myPlayer, double map[], int xSize, int ySize) {
	int playerX = myPlayer.getX();
	int playerY = myPlayer.getY();
	double playerXsize = myPlayer.getxSize();
	double playerYsize = myPlayer.getySize();

	list<Bullet*>::iterator it;

	for (it = enemyBulletList.begin(); it != enemyBulletList.end(); ) {
		Bullet* curBullet = *it;
		int buX = (int)curBullet->getX();
		int buY = (int)curBullet->getY();
		// check enemybullet out of range
		if (buX <= 1 || buX >= mapWidth - 1 || buY <= 1 || buY >= mapHeight - 1) {
			//removeBullet(enemyBulletList, curBullet);
			delete* it;
			*it = nullptr;
			it = enemyBulletList.erase(it);

		}
		// here, 1 or others should be id of obstacle resource
		// check enemyBullet and obstacle
		// This check should be modified
		else if (map[GETMAPINDEX(buX, buY, xSize, ySize)] == 1) {
			delete* it;
			*it = nullptr;
			it = enemyBulletList.erase(it);
			// removeBullet(enemyBulletList, curBullet);

		}
		// check enemyBullet and player
		else if (abs(playerX - buX) < playerXsize && abs(playerY - buY) < playerYsize) {
			// cout << abs(playerX - buX) << "\n";
			int ATK = curBullet->getATK();
			// myPlayer.updateHP(ATK);
			delete* it;
			*it = nullptr;
			it = enemyBulletList.erase(it);

		}
		else {
			++it;
		}
	}


	//list<Bullet*>::iterator it;
	//for(it = enemyBulletList.begin(); it != enemyBulletList.end(); it++)
}


// Shoot
void shoot(list<Bullet*>& bulletList, Player myPlayer, int evt, int mx, int my) {
	// question: shall myplayer has a shoot function or I can directly use Bullet class here.
	// I think former way is better
	Bullet* curBullet = myPlayer.fire(evt, mx, my);
	if (curBullet != nullptr) {
		bulletList.push_back(curBullet);
	}

}


int main() {
	// window
	int windowWidth = 800;
	int windowHeight = 600;
	FsOpenWindow(50, 50, windowWidth, windowHeight, 1);

	// game parameters
	// enemy part

	int enemyNum = 10;
	vector<Enemy*> enemyList;

	// bullet part
	list<Bullet*> bulletList;

	// enemyBullet
	list<Bullet*> enemyBulletList;

	// resource list
	list<Resource*> resourceList;


	// map
	double* map = new double[windowWidth * windowHeight];
	// game components, generate players, enemies, resources

	// init
	initBackGround(map, resourceList);
	initEnemy(map, enemyList, enemyNum, windowWidth, windowHeight);
	Player myPlayer = initPlayer(map, windowWidth, windowHeight);

	// time part
	time_t startPoint = time(NULL);

	while (true) {
		FsPollDevice();
		auto key = FsInkey();
		if (key == FSKEY_ESC) {
			break;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Draw part
		drawObstacle(map);
		drawEnemy(enemyList, enemyNum);
		drawPlayer(myPlayer);
		drawResource(resourceList);
		drawBullet(enemyBulletList, bulletList);

		// Move part
		moveAll(enemyList, map, myPlayer, key, windowWidth, windowHeight, enemyBulletList, bulletList);

		// Check collision part
		// enemy - player
		// bullet - enemy
		for (int i = 0; i < enemyList.size(); i++) {
			colliEP(enemyList[i], myPlayer, enemyBulletList);
			colliBE(enemyList[i], bulletList, map);
		}
		// player - enemy bullet
		coliEBP(enemyBulletList, myPlayer, map, windowWidth, windowHeight);
		// player - resource
		colliRP(myPlayer, resourceList, enemyList);

		// cout << bulletList.size() << "\n";
		// cout << myPlayer.getHP() << "\n";
		// Shoot part, give mouse position
		int lb, mb, rb, mx, my;
		auto evt = FsGetMouseEvent(lb, mb, rb, mx, my);
		// shoot(bulletList, myPlayer, lb, mx, my);
		shoot(bulletList, myPlayer, evt, mx, my);

		// Check gamestate
		// cout << myPlayer.getHP() << "\n";
		if (myPlayer.getHP() <= 0) {
			// TODO : add player dead effect, UI
			cout << "game over" << "\n";
			break;
		}
		FsSwapBuffers();
		FsSleep(25);
	}
}