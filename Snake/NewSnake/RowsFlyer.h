#ifndef __ROWSFLYER_H_
#define __ROWSFLYER_H_

#include "Creature.h"
#include "Color.h"

class RowsFlyer: public Creature {
public:
	RowsFlyer(int x, int y, char figure,Color color, int dir, int speed, bool pingPong, bool isDead) :Creature(x, y, figure, color , dir, speed, pingPong, isDead) {}
	virtual void move(int dir);

};

#endif // !__ROWSFLYER_H_
