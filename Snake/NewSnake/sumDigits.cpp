#include "sumDigits.h"

void sumDigits::print()
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
void sumDigits::isCorrect(int num, bool& res)
{

	int sum = 0;
	while (num != 0)
	{
		sum += (num % 10);
		num /= 10;
	}
	if (sum%x == 0)
		res = true;
	else
		res = false;

}
void sumDigits :: randNum()
{
	x = (getBrange() + rand() % (getTrange() + 1));

}