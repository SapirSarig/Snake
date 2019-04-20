#include "Snake.h"
#include "TheSnakesGame.h"

void Snake::move() {
	if (direction != (-1))
	{
		int i;
		body[size - 1].draw(' ');
		theGame->updateBoard(body[size - 1].getX(), body[size - 1].getY(), ' ');

		for (i = size - 1; i > 0; i--) {
			body[i] = body[i - 1];
			theGame->updateBoard(body[i].getX(), body[i].getY(), figure);
		}

		body[0].move(direction);
		setTextColor(color);
		body[0].draw(figure);
		theGame->updateBoard(body[0].getX(), body[0].getY(), figure);
	}
}

int Snake::getDirection(const char& key) {
	int i;
	for (i = 0; i < 4; i++) {
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}

void Snake::draw()
{
	setTextColor(color);
	for (int i = 0; i < size; i++)
	{
		body[i].draw(figure);
		theGame->updateBoard(body[0].getX(), body[0].getY(), figure);
	}
}

bool Snake::validDirection(const int& newDir)
{
	if ((direction == 0 && newDir == 1) || (direction == 1 && newDir == 0))
		return false;
	else if ((direction == 2 && newDir == 3) || (direction == 3 && newDir == 2))
		return false;
	else
		return true;
}

void Snake::deleteSnake()
{
	for (int i = 0; i < size; i++)
	{
		gotoxy(body[i].getX(), body[i].getY());
		cout << " ";
		theGame->updateBoard(body[i].getX(), body[i].getY(), ' ');
	}
}

void Snake::AppearSnake(vector <LocationAndDir> & LD0, vector <LocationAndDir> & LD1)
{
	int x, y;

	LocationAndDir tempSLD;

	if (!theGame->isReplay()) // not replay
	{
		x = rand() % COLS;
		y = 3 + rand() % 21;
		//enter the rand location into vector for replay
		tempSLD.dir = direction;
		tempSLD.p = Point(x, y);
		if (figure == '@')
			LD0.push_back(tempSLD);
		else
			LD1.push_back(tempSLD);
	}
	else // it's a replay
	{
		if (figure == '@')
		{
			tempSLD = LD0[theGame->getIndexS0()];
			theGame->setIndexS0();
			direction = tempSLD.dir;
		}
		else
		{
			tempSLD = LD1[theGame->getIndexS1()];
			theGame->setIndexS1();
			direction = tempSLD.dir;
		}

		x = tempSLD.p.getX();
		y = tempSLD.p.getY();
	}

	body[0].set(x, y);

	theGame->landOnNum(x, y, direction, figure);
	move();
}