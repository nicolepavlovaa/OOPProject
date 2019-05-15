#ifndef __EXPRESSIONCELL_H
#define __EXPRESSIONCELL_H
#include "Cell.h"
using namespace std;

class Table;

class ExpressionCell : public Cell
{
	double value;
	bool expressionValid;
public:
	ExpressionCell() :Cell() { value = 0; }
	ExpressionCell(Table& t,char * cont);
	void setValue(double val);
	virtual double getValue();
	bool getExpressionValidity();
	double getfirstArg(Table& t, char * expr);
	double getsecondArg(Table& t, char * expr);
	double getValueOfExpression(Table& t, char * expr);
	double calculate(double first, char op, double second);
	int operatorPosition(char * arr);
	bool divisionByZero(Table& t, char * cont);
	double cellCodeToValue(Table& t, char * code);
	virtual void printCell();
};

#endif