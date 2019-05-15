#include "EmptyCell.h"

void EmptyCell::setValue()
{
	this->value = 0;
}

double EmptyCell::getValue()
{
	return (double)this->value;
}

EmptyCell::EmptyCell() :Cell()
{
	setValue();
}
void EmptyCell::printCell()
{
	cout << " ";
}