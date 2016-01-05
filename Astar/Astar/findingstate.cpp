#include "stdafx.h"
#include "findingstate.h"


findingstate::findingstate()
{
}


findingstate::~findingstate()
{
}

findingstate::findingstate(int x, int y)
{
	statex = x;
	statey = y;


}

bool greater(findingstate a, findingstate b)
{
	return a.fvalue > b.fvalue;
}

bool findingstate::operator ==(findingstate b)
{
	if (statex == b.statex && statey == b.statey)
	{
		return 1;
	}
	return 0;
}

void findingstate::fvalueupdate()
{
	fvalue = gvalue + hvalue;

}

bool findingstate::operator()(findingstate a)
{
	return fvalue > a.fvalue;
}

bool greater::operator()(findingstate a, findingstate b)
{
	if (a.fvalue == b.fvalue)
	{
		return a.gvalue < b.gvalue;
	}
	return a.fvalue > b.fvalue;

}