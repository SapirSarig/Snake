#include "NumEater.h"

void NumEater::move(int dir)
{
	int y = getY();
	int x = getX();

	switch (dir) {
	case 0: // up	
		--y;
		if (y < 3) {
			y = 23;
		}
		break;
	case 1: // down
		++y;
		if (y > 23) {
			y = 3;
		}
		break;
	case 2: // left
		--x;
		if (x < 0) {
			x = 79;
		}
		break;
	case 3: // right
		++x;
		if (x > 79) {
			x = 0;
		}
		break;
	}

	setPoint(x, y);
}


void NumEater::isFastWay(NUMBER num, int& dir1, int &dir2,bool &res)
{
	int stepsUp = 0;
	int stepsDown = 0;
	int stepsLeft = 0;
	int stepsRight = 0;
	int tempDir1, tempDir2;
	int newSteps = 0;

	int numX = num.position.getX();
	int numY = num.position.getY();

	for (int i = 0; i < 4; i++) // check 4 directions for moving the Numeater
	{
		int eaterX = getX();
		int eaterY = getY();

		if (i == 0 || i == 1)
		{
			while (eaterY != numY)
			{
				if (i == 0)
				{
					if (eaterY - 1 < 3)
						eaterY = 23;
					else
						eaterY--;
					stepsUp++;
				}
				else
				{
					if (eaterY + 1 > 23)
						eaterY = 3;
					else
						eaterY++;
					stepsDown++;
				}
			}
		}
		else
		{
			while (eaterX != numX)
			{
				if (i == 2)
				{
					if (eaterX - 1 < 0)
						eaterX = 79;
					else
						eaterX--;
					stepsLeft++;
				}
				else
				{
					if (eaterX + 1 > 79)
						eaterX = 0;
					else
						eaterX++;
					stepsRight++;
				}
			}
		}


	}

	if (stepsDown < stepsUp)
	{
		tempDir1 = 1; // down
		newSteps = newSteps + stepsDown;
	}
	else
	{
		tempDir1 = 0; // up
		newSteps = newSteps + stepsUp;

	}
	if (stepsLeft < stepsRight)
	{
		tempDir2 = 2; // left
		newSteps = newSteps + stepsLeft;
	}
	else
	{
		tempDir2 = 3; // right
		newSteps = newSteps + stepsRight;
	}

	if (newSteps < steps)
	{
		dir1 = tempDir1;
		dir2 = tempDir2;
		setSteps(newSteps);
		res = true;
	}

	else 
		res = false;
}


void NumEater::moveAndCheckWay(qManager *q, NUMBER num, Snake* s[2])
{
	theGame->updateBoard(getX(),getY(), ' ');
	gotoxy(getX(), getY());
	cout << " ";
	move(getDir());
	loseSteps();
	Point next = Point(getX(), getY());
	if (theGame->isNum(next))
	{
		NUMBER numToRemove = theGame->checkNum(next.getX(), next.getY());
		theGame->clearnNumberFromBoard(numToRemove);
		q->removeNumberFromArr(numToRemove);
		//restSteps();
	}
	else if (theGame->isSnake(next))
	{
		theGame->snakeTouchedNumEater(theGame->whichSnake(next) ,q);

	}
	else if (theGame->isBullet(next))
	{
		bool found = false;
		theGame->updateBoard(next.getX(), next.getY(), ' ');
		gotoxy(next.getX(), next.getY());
		cout << " ";
		for (int i = 0; !found, i < 2; i++)
		{
			Node* curr = s[i]->getList()->getHead();
			while (!found && curr != NULL)
			{
				if (curr->bullet.getBulletX() == next.getX() && curr->bullet.getBulletY() == next.getY())
				{
					found = true;
					curr = s[i]->getList()->removeNodeFromList(curr->bullet.getShotNum());
				}
				else
					curr = curr->next;
			}
		}
	}
	draw();
	theGame->updateBoard(getX(), getY(), getFigure());
}