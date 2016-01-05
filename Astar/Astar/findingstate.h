#pragma once
class findingstate
{
public:
	findingstate();
	findingstate(int, int);
	~findingstate();
	int fvalue;
	int gvalue;
	int hvalue;
	int statex, statey;
	int nextfvalue;
	int round;
	findingstate* parent;
	int search = 0;

	bool operator ==(findingstate b);
	void fvalueupdate();
	bool operator ()(findingstate);


};

class greater
{
public:
	bool operator ()(findingstate, findingstate);

};


