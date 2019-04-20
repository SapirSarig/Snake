#include "Creature.h"
using namespace std;
#include <iostream>

void Creature::draw()
{
	gotoxy(x, y);
	setTextColor(color);
	cout << figure;
	//theGame->updateBoard(x,y,figure);
}

void Creature::deleteCreature() {
	gotoxy(x,y);
	cout << " ";
	//theGame->updateBoard(x, y, ' ');
}
