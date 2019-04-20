#ifndef __EQUATION_H_
#define __EQUATION_H_
#include "Questions.h"

class Equation : public Questions {

	double A, B, C, D;
	char op1, op2;
	int choose;
	double result;

public:
	virtual void print();
	virtual void isCorrect(int num, bool &res);
	bool isFirst(char ch);
	double cal(double num1, double num2, char ch);
	virtual void randNum();
	char randOp();
	char switchOp(char op);
	double solveFornum1(double &A, double &C, double &D, char &op1, char &op2);
	double solveFornum2(double &A, double &C, double &D, char &op1, char &op2);
	double solveFornum3(double &A, double &B, double &D, char &op1, char &op2);
	double solveFornum4(double &A, double &B, double &C, char &op1, char &op2);
	int equationSolution();
	
};

#endif
