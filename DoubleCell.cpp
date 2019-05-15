#include "DoubleCell.h"

DoubleCell::DoubleCell() :Cell()
{
	value = 0;
}

DoubleCell::DoubleCell(char * cont) :Cell(cont)
{
	setValue();
}

void DoubleCell::setValue()
{
	this->value = atof(getCellContent());
}

double DoubleCell::getValue()
{
	return this->value;
}
void DoubleCell::printCell()
{
	cout << value;
}
