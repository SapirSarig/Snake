#include "qManager.h"

#include <fstream>

void qManager :: createQuestionsArr( Questions*** qArr, int& size)
{
	Questions** temp;
	ifstream inFile("QuestionsFile.txt");
	char str[256];
	char tempStr[256];
	char tRange[4];
	char dummy, bRange, index, sizeOfArr, sizeOFVarsArr;
	int topRange = 0;
	int j = 0;
	int intIndex, bottomRange;
	sizeOfArr = inFile.get();
	int ArrSize = sizeOfArr - '0';

	temp = new Questions*[ArrSize];
	inFile.getline(tempStr, 256);


	for (int i = 0; i < ArrSize; i++)
	{

		index = inFile.get();
		switch (index)
		{
		case '0':
		{
			temp[i] = new dividesByX();
			break;
		}
		case '1':
		{
			temp[i] = new inRange();
			break;
		}
		case '2':
		{
			temp[i] = new Equation();
			break;
		}
		case '3':
		{
			temp[i] = new sumDigits();
			break;
		}
		default:
		{
			temp[i] = new dividesByAnotB();
			break;
		}

		}
		intIndex = index - '0';
		temp[i]->setIndex(intIndex);
		inFile.getline(tempStr, 256);
		inFile.getline(str, 256);


		temp[i]->setText(str);

		inFile >> bRange;
		bottomRange = bRange - '0';
		temp[i]->setBrange(bottomRange);
		dummy = inFile.get();
		inFile.getline(tRange, 4);
		for (int j = 0; j < 3; j++)
		{
			if (tRange[j] >= '0' && tRange[j] <= '9')
			{
				topRange *= 10;
				topRange += tRange[j] - '0';
			}
		}
		temp[i]->setTrange(topRange);
		topRange = 0;


	}

	inFile.close();
	*qArr = temp;
	size = ArrSize;
}


void qManager::removeNumberFromArr(NUMBER num)
{
	if (num.position.getX() == ClosestNum.position.getX() && num.position.getY() == ClosestNum.position.getY())
	{
		isEatenClosestNum = true;
	}
	for (int i = 0; i < numbersSize; i++)
	{
		if ((numbers[i].position.getX() == num.position.getX()) && (numbers[i].position.getY() == num.position.getY()))
		{
			numbers[i] = numbers[numbersSize - 1];
			numbersSize--;
		}
	}
}

NUMBER qManager::getNum(int x, int y)
{
	for (int i = 0; i < numbersSize; i++)
	{
		if ((numbers[i].position.getX() == x) && (numbers[i].position.getY() == y))
		{
			return numbers[i];
		}
	}
	return numbers[0];
}

NUMBER qManager::getNumByIndex(int index)
{
	return (numbers[index]);
}
bool qManager::insertNum(NUMBER num)
{
	setTextColor(WHITE);
	if (numbersSize <= 59) {
		numbers[numbersSize] = num;
		gotoxy(num.position.getX(), num.position.getY());
		cout << num.value;
		numberOnScreen = true;
		numbersSize++;
		return false;
	}
	
	return true;

}