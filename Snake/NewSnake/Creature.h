#ifndef __CREATURE_H_
#define __CREATURE_H_

#include "Color.h"
#include "Point.h"
#include "Snake.h"
#include "Questions.h"
#include "qManager.h"
class TheSnakesGame;

//enum SPEED{NORMAL=1, DOUBLESP=2};

class Creature {

	int x, y;
	int dir; 
	char figure;
	Color color;
	int speed; // 1 = normal, 2 = double speed
	bool pingPong;
	bool isDead;


public:
	//Creature() {}
	Creature(int _x, int _y, char _figure, Color _color , int _dir, int _speed, bool _pingPong, bool _isDead){
		x = _x;
		y = _y;
		figure = _figure;
		color = _color;
		dir = _dir;
		speed = _speed;
		pingPong = _pingPong;
		isDead = _isDead;
	}
	virtual void move(int dir) = 0;
	int getX() { return x; }
	int getY() { return y; }
	void setPoint(int _x, int _y) { x = _x; y = _y; }
	void setDir(int _dir) { dir = _dir; }
	int getDir() { return dir; }
	void draw();
	int getSpeed() { return speed; }
	void deleteCreature();
	char getFigure() { return figure; }
	bool getPingPong() { return pingPong; }
	void setIsDead(bool res) { isDead = res; }
	bool is_Dead() { return isDead; }
	virtual void isFastWay(NUMBER num, int& dir1, int &dir2,bool &res){}
	virtual void moveAndCheckWay(qManager *q, NUMBER num, Snake* s[2]) {}
	virtual void restSteps() {}
};

#endif // !__CREATURE_H_
