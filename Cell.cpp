#include "Cell.h"

int Cell::getType() const
{
	return this->type;
}
void Cell::setType(int t)
{
	this->type = t;
}
Cell::Cell() :content(nullptr)
{
	setCellContent("");
	setType(TYPE_EMPTY);
}

Cell::Cell(const char * other) :content(nullptr)
{
	setCellContent(other);
	setType(determineContentType());
}
Cell::Cell(const Cell& other) : content(nullptr)
{
	setCellContent(other.getCellContent());
	setType(other.getType());
}
Cell & Cell::operator=(const Cell& c)
{
	if (this != &c)
	{
		setCellContent(c.getCellContent());
		setType(c.getType());
	}
	return *this;
}
Cell::~Cell()
{
	delete[] content;
}
bool Cell::isExpression(const char * content) const
{
	regex reg("^=(R[1-9][0-9]*C[1-9][0-9]*|[0-9]+)[+*\/^-](R[1-9][0-9]*C[1-9][0-9]*|[0-9]+)");
	if (regex_match(content, reg))
	{
		return true;
	}
	return false;
}

bool Cell::isDouble(const char * content) const
{
	regex reg("^([+-]?[1-9][0-9]*\.[0-9]+|0\.([0-9])+)");
	if (regex_match(content, reg))
	{
		return true;
	}
	return false;

}
bool Cell::isInt(const char * content) const
{
	regex reg("^([+-]?[1-9][0-9]{0,8}[0-7]?|0)");
	if (regex_match(content, reg))
	{
		return true;
	}
	return false;
}
bool Cell::isString(const char * content) const
{
	regex reg("^\".*\"");
	if (regex_match(content, reg))
	{
		return true;
	}
	return false;
}

void Cell::setCellContent(const char * cont)
{
	delete[] content;
	const int length = strlen(cont);
	content = new char[length + 1];
	strcpy(this->content, cont);
}
char * Cell::getCellContent() const
{
	return this->content;
}
int Cell::determineContentType() const
{
	if (content == nullptr) return TYPE_EMPTY;
	else if (isInt(content)) return TYPE_INT;
	else if (isDouble(content)) return TYPE_DOUBLE;
	else if (isString(content)) return TYPE_STRING;
	else if (isExpression(content)) return TYPE_EXPRESSION;
	else return TYPE_EMPTY;
}
char * Cell::getSubstring(char * string, int position, int length) const
{
	int c = 0;
	char * substring = new char[length + 1];
	while (c < length)
	{
		substring[c] = string[position + c - 1];
		c++;
	}
	substring[c] = '\0';
	return substring;
	//delete[] substring;
}

