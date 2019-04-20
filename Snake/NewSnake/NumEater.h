#ifndef __NUMEATER_H_
#define __NUMEATER_H_

#include "Creature.h"
#include "Questions.h"
#include "TheSnakesGame.h"

class Snake;
class List;

class NumEater: public Creature {
	int steps;
	TheSnakesGame* theGame;
public:
	NumEater(int x, int y, char figure, Color color, int dir, int speed, bool pingPong, bool isDead, int _steps, TheSnakesGame* _theGame):
		Creature(x, y, figure, color, dir, speed, pingPong, isDead),steps(_steps),theGame(_theGame){}
	virtual void move(int dir);
	virtual void isFastWay(NUMBER num, int& dir1, int &dir2, bool &res);
	virtual void moveAndCheckWay(qManager *q, NUMBER num, Snake* s[2]);
	void loseSteps() { steps--; }
	virtual void restSteps() { steps = ROWS*COLS; }
	void setSteps(int _steps) { steps = _steps; }
};


#endif // !__NUMEATER_H_
