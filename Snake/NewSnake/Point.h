#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"

using namespace std;

class Point {
	int x, y;
public:
	Point(int _x = 1, int _y = 1) {
		x = _x;
		y = _y;
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void set(const int& _x, const int& _y) {
		x = _x;
		y = _y;
	}
	void draw(const char& ch) {
		gotoxy(x, y);
		cout << ch;
		cout.flush();
	}
	void move(const int& direction);
	Point next(const int& direction) {
		Point next = *this;
		next.move(direction);
		return next;
	}
};

#endif