#include "dividesByAnotB.h"

void dividesByAnotB::print()
{
	
	string text = getText();
	int len = text.size();

	for (int i = 0; i < len; i++)
	{
		if (text[i] == 'A')
			cout << A;
		else if (text[i] == 'B')
			cout << B;
		else
			cout << text[i];
	}
}
void dividesByAnotB::isCorrect(int num, bool& res)
{

	if ((num%A == 0) && (num%B != 0))
		res = true;
	else
		res = false;

}
void dividesByAnotB::randNum()
{
	A = (getBrange() + rand() % (getTrange() + 1));
	do {

		B = (getBrange() + rand() % (getTrange() + 1));

	} while (A == B);


}