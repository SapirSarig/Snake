#include "ColsFlyer.h"

void ColsFlyer::move(int dir)
{
	switch (dir) {
	case 0: // up
	{
		int y = getY()-1;
		if (y < 3) {
			if (getPingPong())
			{
				setDir(1);
				y = 4;
			}
			else
				y = 23;
		}

		setPoint(getX(), y);
	}
	break;
	case 1: // down
		int y = getY()+1;
		if (y > 23) {
			if (getPingPong())
			{
				setDir(0);
				y = 22;
			}
			else
				y = 3;
		}
		setPoint(getX(), y);
		break;

	}
}

