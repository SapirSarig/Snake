#include "RowsFlyer.h"

void RowsFlyer::move(int dir)
{
	switch (dir) {
	case 2: // left
	{
		int x = getX()-1;
		if (x < 0) {
			if (getPingPong())
			{
				setDir(3);
				x = 1;
			}
			else
				x = 79;
		}
		setPoint(x, getY());		}
	break;
	case 3: // right
		int x = getX() + 1;
		if ((x > 79)) {
			if (getPingPong())
			{
				setDir(2);
				x = 78;
			}
			else
				x = 0;
		}
		setPoint(x, getY());
		break;
	}
}
