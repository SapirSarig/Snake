#ifndef __COLSFLYER_H_
#define __COLSFLYER_H_

#include "Creature.h"

class ColsFlyer: public Creature {

public:
	ColsFlyer(int x, int y, char figure, Color color, int dir, int speed, bool pingPong, bool isDead) :Creature(x, y, figure, color, dir, speed, pingPong, isDead) {}
	virtual void move(int dir);

};



#endif // !__COLSFLYER_H_


