#ifndef _BULLET_H_
#define _BULLET_H_

#include "Point.h"

class Bullet {

	int x, y;
	char figure = '*';
	Color color;
	int snakeNum;
	int dir;
	int shotNum = 0;

public:
	Bullet() {};
	Bullet(int _x, int _y, Color _color, int _snakeNum, int _dir, int _shotNum) {
		x = _x;
		y = _y;
		color = _color;
		snakeNum = _snakeNum;
		dir = _dir;
		shotNum = _shotNum;
	}

	void moveBullet(const Point& p);
	void setBulletX(const int& _x)
	{
		x = _x;
	}
	void setBulletY(const int& _y)
	{
		y = _y;
	}
	void setBulletColor(const Color& _color)
	{
		color = _color;
	}
	void setBulletdir(const int& _dir)
	{
		dir = _dir;
	}
	void setBulletSnakeNum(const int& _snakeNum)
	{
		snakeNum = _snakeNum;
	}
	int getBulletX() {
		return x;
	}
	int getBulletY() {
		return y;
	}
	int getBulletDir() {
		return dir;
	}

	int getSnakeNum() {
		return snakeNum;
	}
	void draw();

	char getBulletFigure()
	{
		return figure;
	}
	int getShotNum()
	{
		return shotNum;
	}
	void setShotNum()
	{
		shotNum++;
	}
};

#endif