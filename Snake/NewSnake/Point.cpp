#include "Point.h"

void Point::move(const int& dir) {
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
}