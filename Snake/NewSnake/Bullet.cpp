#include "Bullet.h"
#include <iostream>
using namespace std;

void Bullet::moveBullet(const Point& p)
{

	if (p.getY() < 3)
		y = 23;

	else if (p.getY() > 23)
		y = 3;

	else
		y = p.getY();

	if (p.getX() < 0)
		x = 79;

	else if (p.getX() > 79)
		x = 0;

	else
		x = p.getX();

	draw();
}


void Bullet::draw()
{
	setTextColor(color);
	gotoxy(x, y);
	cout << figure;
	cout.flush();
	//updateBoard

}
