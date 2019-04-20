#include "Equation.h"

void Equation::print()
{
	
	choose = equationSolution();
	switch (choose)
	{
	case 1:
		cout << " ___ " << op1 << " " << B << " " << op2 << " " << C << " = " << D << endl;
		break;
	case 2:
		cout << A << "  " << op1 << " " << " ___ " << op2 << " " << C << " = " << D << endl;
		break;
	case 3:
		cout << A << "  " << op1 << " " << B << " " << op2 << " ___ " << " = " << D << endl;
		break;
	case 4:
		cout << A << " " << op1 << " " << B << " " << op2 << " " << C << " =  ___ " << endl;
		break;
	
	}
}
void Equation::isCorrect(int num, bool& res)
{

	if (num == result)
		res = true;
	else
		res = false;

}

void Equation::randNum()
{
	A = (getBrange() + rand() % (getTrange() + 1));
	B = (getBrange() + rand() % (getTrange() + 1));
	C = (getBrange() + rand() % (getTrange() + 1));
	D = (getBrange() + rand() % (getTrange() + 1));

}

int Equation::equationSolution()
{
	bool firstOp = false;
	bool stop = false;
	int missingNum = 1 + (rand() % 4); // choose num1 /num2/num3/ num4 to be the missing var

	do
	{
		op1 = randOp();
		op2 = randOp();

		switch (missingNum)
		{
		case 1:
			result = solveFornum1(B, C, D, op1, op2);
			break;
		case 2:
			result = solveFornum2(A, C, D, op1, op2);
			break;
		case 3:
			result = solveFornum3(A, B, D, op1, op2);
			break;
		case 4:
			result = solveFornum4(A,B, C, op1, op2);
			break;
		}

		if (((result == ((int)result) && (result <= 169) && (result >= 0))))
			stop = true;

	} while (!stop);
	return missingNum;

}

bool Equation::isFirst(char ch)
{
	switch (ch)
	{
	case '+':
	{
		return false;
		break;
	}
	case '-':
	{	return false;
	break;

	}
	case '*':
	{
		return true;
		break;
	}

	case '/':
	{
		return true;
		break;
	}
	}
}

double Equation::cal(double num1, double num2, char ch)

{
	switch (ch)
	{
	case '+':
		return (num1 + num2);
		break;

	case '-':
		return (num1 - num2);
		break;

	case '*':
		return (num1*num2);
		break;

	case '/':
		return (num1 / num2);
		break;
	}
}

char Equation::randOp()
{
	int choose = rand() % 4;
	switch (choose)
	{
	case 0:
		return '+';
		break;
	case 1:
		return '-';
		break;
	case 2:
		return '*';
		break;
	case 3:
		return '/';
		break;
	}
}

double Equation::solveFornum1(double &B, double &C, double &D, char& op1, char& op2)
{
	double solve1;
	double tempCal;

	if (isFirst(op1))
	{
		if (isFirst(op2))
			tempCal = cal(B, C, op2);
		else
			tempCal = cal(D, C, switchOp(op2));
		solve1 = cal(D, tempCal, switchOp(op1));
	}
	else
	{
		tempCal = cal(B, C, op2);
		solve1 = cal(D, tempCal, switchOp(op1));
	}

	return solve1;
}

double Equation::solveFornum2(double &A, double &C, double &D, char &op1, char &op2)
{

	double solve2;
	double tempCal;
	

	if (isFirst(op1))
	{
		if (isFirst(op2))
			tempCal = cal(D, C, switchOp(op2));
		else
			tempCal = cal(D, C, switchOp(op2));

		if (op1 == '*')
			solve2 = cal(tempCal, A, switchOp(op1));
		else
			solve2 = cal(A, tempCal, op1);
	}

	else
	{
		if (isFirst(op2))
		{
			tempCal = cal(D, A, '-');
			if (op1 == '-')
				solve2 = (-1)* cal(tempCal, C, switchOp(op2));
			else
				solve2 = cal(tempCal, C, switchOp(op2));
		}
		else
		{
			tempCal = cal(D, C, switchOp(op1));
			if (op1 == '-')
				solve2 = (-1) *cal(tempCal, A, '-');
			else
				solve2 = cal(tempCal, A, '-');
		}
	}

	return solve2;
}

double Equation::solveFornum3(double &A, double &B, double &D, char &op1, char &op2)
{
	double solve3;
	double tempCal;
	
	if (!isFirst(op2))
	{
		tempCal = cal(A, B, op1);
		if (op2 == '-')
			solve3 = (-1) *cal(D, tempCal, '-');
		else
			solve3 = cal(D, tempCal, '-');
	}

	else // if (isFirst(op2))
	{
		if (isFirst(op1))
		{
			tempCal = cal(A, B, op1);
			if (op2 == '/')
				solve3 = cal(tempCal, D, op2);
			else
				solve3 = cal(D, tempCal, switchOp(op2));
		}
		else
		{
			tempCal = cal(D, A, '-');
			if (op2 == '/')
			{
				if (op1 == '-')
					solve3 = cal(B, tempCal, op2) *(-1);
				else
					solve3 = cal(B, tempCal, op2);
			}
			else
			{
				if (op1 == '-')
					solve3 = cal(tempCal, B, switchOp(op2)) *(-1);
				else
					solve3 = cal(tempCal, B, switchOp(op2));
			}
		}
	}

	return solve3;
}

double Equation::solveFornum4(double &A, double &B, double &C, char &op1, char &op2)
{

	double tempCal;
	double solve4;

	
	if (isFirst(op1) || (!isFirst(op1) && !isFirst(op2)))
	{
		tempCal = cal(A, B, op1);
		solve4 = cal(tempCal, C, op2);
	}

	else
	{
		tempCal = cal(B, C, op2);
		solve4 = cal(A, tempCal, op1);
	}

	return solve4;
}

char Equation::switchOp(char op)
{
	switch (op)
	{
	case '+':
		return '-';
		break;
	case '-':
		return '+';
		break;
	case '*':
		return '/';
		break;
	case '/':
		return '*';
		break;
	}
}

