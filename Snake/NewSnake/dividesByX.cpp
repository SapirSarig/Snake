#include "dividesByX.h"

void dividesByX::print()
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
void dividesByX::isCorrect(int num, bool& res)
{
	
	if (num % x == 0)
		res = true;
	else
		res = false;
	
 }
void dividesByX::randNum()
{
	x = (getBrange() + rand() % (getTrange() + 1));

}