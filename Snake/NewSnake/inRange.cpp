#include "inRange.h"

void inRange::print()
{
	string text = getText();
	int len = text.size();

	for (int i = 0; i < len; i++)
	{
		if (text[i] != 'x')
			cout << text[i];
		else
			cout << x;
	}
}
void inRange::isCorrect(int num, bool& res)
{

	if ((num > x) && (num < x*x))
		res = true;
	else
		res = false;

}
void inRange::randNum()
{
	x = (getBrange() + rand() % (getTrange() + 1));

}