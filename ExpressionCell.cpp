#include "ExpressionCell.h"
#include "Table.h"

ExpressionCell::ExpressionCell(Table& t, char * cont) :Cell(cont)
{
	setType(TYPE_EXPRESSION);
	setValue(getValueOfExpression(t, cont));
	if(divisionByZero(t,cont)==false) expressionValid = true;
	else expressionValid = false;
}

void ExpressionCell::setValue(double val)
{
	this->value = val;
}
double ExpressionCell::getValue()
{
	return this->value;
}
bool ExpressionCell::getExpressionValidity() 
{
	return expressionValid;
}
double ExpressionCell::getfirstArg(Table& t, char * expr) 
{
	char * first = getSubstring(expr, 2, operatorPosition(expr) - 1);
	double fArg = 0;

	if (isDouble(first) || isInt(first))
	{
		fArg = atof(first);
	}
	else fArg = cellCodeToValue(t, first);
	delete[] first;
	return fArg;
}
double ExpressionCell::getsecondArg(Table& t,char * expr) 
{
	char * first = getSubstring(expr, 2, operatorPosition(expr) - 1);
	char * second = getSubstring(expr, operatorPosition(expr) + 2, strlen(expr) - strlen(first) - 1);
	double sArg = 0;
	if (isDouble(second) || isInt(second))
	{
		sArg = atof(second);
	}
	else sArg = cellCodeToValue(t, second);
	delete[] first;
	delete[] second;
	return sArg;
}
double ExpressionCell::getValueOfExpression(Table& t, char * expr) 
{
	char op = expr[operatorPosition(expr)];
	double fArg = getfirstArg(t, expr);
	double sArg = getsecondArg(t, expr);
	double result=0;
	if (op == '/' && sArg == 0)
	{
		result = 0;
	}
	else result = calculate(fArg, op, sArg);
	return result;
}
double ExpressionCell::cellCodeToValue(Table& t, char * code) 
{
	int cellRow=0, cellCol=0, sum=0, counter = 0;
	for (int i = 0; i < strlen(code); i++)
	{
		if (code[i] >= '0' && code[i] <= '9')
		{
			sum = sum * pow(10, counter) + (code[i] - '0');
			counter++;
		}
		if (code[i] == 'C')
		{
			cellRow = sum;
			counter = 0;
			sum = 0;
		}
		if (i == strlen(code) - 1)
		{
			cellCol = sum;
		}
	}

	double val;
	if (cellRow > t.getSize() || cellCol > t.longestRowLength())
	{
		val = 0;
	}
	else val = t.getCellValue(cellRow, cellCol);
	return val;
}

double ExpressionCell::calculate(double first, char op, double second) 
{
	if (op == '+')
	{
		return first + second;
	}
	if (op == '-')
	{
		return first - second;
	}
	if (op == '*')
	{
		return first * second;
	}
	if (op == '/')
	{
		return first / second;
	}
	if (op == '^')
	{
		return pow(first, second);
	}
}
bool isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
int ExpressionCell::operatorPosition(char * arr)
{
	for (int i = 0; i < strlen(arr); i++)
	{
		if (isOperator(arr[i]))
		{
			return i;
		}
	}
}
bool ExpressionCell::divisionByZero(Table& t, char * cont) 
{
	if (getCellContent()[operatorPosition(getCellContent())] == '/' && getsecondArg(t, getCellContent()) == 0)
	{
		return true;
	}
	return false;
}
void ExpressionCell::printCell()
{
	if (getExpressionValidity() == true)
	{
		cout << value;
	}
	else cout << "ERROR";
}