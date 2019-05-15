#include "StringCell.h"

void StringCell::setValue()
{
	setPrintValue();
	regex reg1("^([+-]?[1-9][0-9]*\.[0-9]+|0\.([0-9])+)");
	regex reg2("^([+-]?[1-9][0-9]{0,8}[0-7]?|0)");
	if (regex_match(printValue, reg1))
	{
		this->value = atof(printValue);
	}
	else if (regex_match(printValue, reg2))
	{
		this->value=atoi(printValue);
	}
	else this->value = 0;
}
void StringCell::setPrintValue()
{
	this->printValue = getSubstring(getCellContent(), 2, strlen(getCellContent()) - 2);
}

double StringCell::getValue()
{
	return this->value;
}
void StringCell::printCell()
{
	cout << printValue;
}

StringCell::StringCell() :Cell()
{
	value = 0;
}

StringCell::StringCell(char * cont) :Cell(cont)
{
	setType(TYPE_STRING);
	setValue();
}
StringCell::~StringCell()
{
	delete[] printValue;
}