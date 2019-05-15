#include "Table.h"
#include "ExpressionCell.h"


int Table::getSize() const
{
	return this->size;
}
Table::Table()
{
	size = 0;
	table = nullptr;
}
Table::Table(const Table& t) :size(t.getSize())
{
	deleteTable();
	for (int i = 0; i < t.getSize(); i++)
	{

		int j = 0;
		//this->table[i] = t.table[i];
		for (vector<Cell*>::iterator it = t.table[i].begin(); it != t.table[i].end(); ++it)
		{
			table[i][j] = *(new Cell*());
			*table[i][j] = *(*it);
			j++;
		}
	}
}

void Table::setSize(int s)
{
	this->size = s;
}
int Table::longestRowLength()
{
	int max = 0;
	for (int i = 0; i < getSize(); i++)
	{
		if ((int)table[i].size() > max)
		{
			max = (int)table[i].size();
		}
	}
	return max;
}
void Table::resizee(int r, int c)
{
	vector<Cell*> * newTable = new vector<Cell*>[r + 1];
	Cell* cell = nullptr;
	for (int i = 0; i < r + 1; i++)
	{
		newTable[i]=vector<Cell*>(c + 1);
		for (vector<Cell*>::iterator it = newTable[i].begin(); it != newTable[i].end(); ++it)
		{
			*it = new EmptyCell();
		}
	}

		for (int i = 0; i < getSize(); i++)
		{
			for (auto j = 0; j < table[i].size(); j++)
			{
				newTable[i][j] = table[i][j];
			}
		}
		delete[] table;
		this->table = newTable;
		setSize(r + 1);
	//cout << this->getSize();
	//setSize(r);
}
Cell* Table::createInstance(int t, char * c)
{
	if (t == TYPE_EMPTY) return new EmptyCell();
	if (t == TYPE_INT) return new IntegerCell(c);
	if (t == TYPE_DOUBLE) return new DoubleCell(c);
	if (t == TYPE_STRING) return new StringCell(c);
	if (t == TYPE_EXPRESSION) return new ExpressionCell(*this, c);
}
void Table::addCell(int r, int c, const char * cont)
{
	if (r-1 >= getSize()-1 && c-1>=longestRowLength()-1)
	{
		resizee(r-1 , c-1);
	}
	else if (r-1 >= getSize()-1 && c-1 <= longestRowLength())
	{
		resizee(r-1, longestRowLength());
	}
	else if (r-1 <= getSize() - 1 && c-1 >= longestRowLength()-1)
	{
		resizee(getSize()-1, c-1);
	}
	else if (r-1 <= getSize() - 1 && c-1 <= longestRowLength())
	{
		resizee(getSize()-1, longestRowLength()-1);
	}


	table[r-1][c-1]->setCellContent(cont);
	if (table[r-1][c-1]->determineContentType() == TYPE_EMPTY)
	{
		table[r-1][c-1] = this->createInstance(TYPE_EMPTY, table[r-1][c-1]->getCellContent());
	}
	else if (table[r-1][c-1]->determineContentType() == TYPE_INT)
	{
		table[r-1][c-1] = this->createInstance(TYPE_INT, table[r-1][c-1]->getCellContent());
	}
	else if (table[r-1][c-1]->determineContentType() == TYPE_DOUBLE)
	{
		table[r-1][c-1] = this->createInstance(TYPE_DOUBLE, table[r-1][c-1]->getCellContent());
	}
	else if (table[r-1][c-1]->determineContentType() == TYPE_STRING)
	{
		table[r-1][c-1] = this->createInstance(TYPE_STRING, table[r-1][c-1]->getCellContent());
	}
	else if (table[r-1][c-1]->determineContentType() == TYPE_EXPRESSION)
	{
		table[r-1][c-1] = this->createInstance(TYPE_EXPRESSION, table[r-1][c-1]->getCellContent());
	}
}
Cell * Table::getCell(int r, int c)
{
	return table[r-1][c-1];
}
vector<Cell*> * Table::getTable()
{
	return this->table;
}
Table& Table::operator=(const Table& t)
{
	if (this != &t)
	{
		deleteTable();
		cout << t.getSize();
		table=new vector<Cell*>[t.getSize()];
		for (int i = 0; i < t.getSize(); i++)
		{
			table[i] = vector<Cell*>(t.table[i].size());
			for (auto j = 0; j < table[i].size(); j++)
			{
				table[i][j] = t.table[i][j];
			}
		}
		setSize(t.getSize());
	}
	return *this;
}

Table::~Table()
{
	deleteTable();
}
void Table::deleteTable()
{
	for (int i = 0; i < getSize(); i++)
	{
		for (vector<Cell*>::iterator it = table[i].begin(); it < table[i].end(); ++it)
		{
			delete (*it);
		}
		table[i].clear();
	}
	delete[] table;
}
double Table::getCellValue(int r, int c)
{
	return getCell(r, c)->getValue();
}

int Table::getLongestColumnContent(int c) const
{
	char str[50];
	int max = 0;
	for (int i = 0; i < getSize(); i++)
	{
		if (printValueLength(table[i][c]) >= max)
		{
			max = printValueLength(table[i][c]);
		}
	}
	return max;
}
int Table::printValueLength(Cell* c) const
{
	char str[50];
	if (c->getType() == TYPE_EXPRESSION)
	{
		if (((ExpressionCell*)c)->getExpressionValidity() == true) {
			sprintf(str, "%g", c->getValue());
			return strlen(str);
		}
		else return strlen("ERROR");
	}
	if (c->getType() == TYPE_STRING)
	{
		return strlen(c->getCellContent()) - 2;
	}
	if (c->getType() == TYPE_EMPTY)
	{
		return 0;
	}
	if (c->getType() == TYPE_INT || c->getType() == TYPE_DOUBLE)
	{
		sprintf(str, "%g", c->getValue());
		return strlen(str);
	}
	else 
	{
		return strlen(c->getCellContent());
	}
}
void Table::printTable() 
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			if(table[i][j]->getType() == TYPE_EXPRESSION)
			((ExpressionCell*)table[i][j])->setValue(((ExpressionCell*)table[i][j])->getValueOfExpression(*this, table[i][j]->getCellContent()));
			//table[i][j]->printCell();
			cout << setw(getLongestColumnContent(j)+1);
			table[i][j]->printCell(); //setw?
			cout << " |";
		}
		cout << endl;
	}
}
