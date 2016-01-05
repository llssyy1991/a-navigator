#include "findingstate.h"

#ifndef stacks
#define stacks
#include <stack>
#endif

#pragma once


#define blocked 1
#define unblocked 0

class pathfinder
{
public:
	pathfinder(int, int);
	pathfinder();
	~pathfinder();
	int x;
	int y;
	int goalx;
	int goaly;
	int memory[101][101];
	int gvalue[101][101];
	int hvalue[101][101];
	std::stack<findingstate> path;
	void setposition(int, int);
	//path  Àà´ú½¨

	//void getPath();
	void getsurrounding();
	void walktogoal();
	void static showitonmap(int, int);
	int findpath();
	int findpathbackward();
	void clearmemory();
	void clearpath();
	void cleargvalue();
	int adaptivefindpath();


	//void checkPath();

	//void moveTo();
};

