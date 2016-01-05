#include "stdafx.h"
#include "pathfinder.h"
#include <queue>
#include <vector>

//#ifndef iostreams
//#define iostreams
//#include <iostream>
//#endif

#ifndef stacks
#define stacks
#include <stack>
#endif

#ifndef stdlibs
#define stdlibs
#include <stdlib.h>
#endif

#define infinite 2147483647;

extern int map[101][101];
extern int steps;

using namespace std;



pathfinder::pathfinder(int x, int y)
{
	this->x = x;
	this->y = y;
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			memory[i][j] = unblocked;
		}
	}
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			hvalue[i][j] = 0;
		}
	}
}


pathfinder::~pathfinder()
{}

void pathfinder::setposition(int x, int y)
{
	this->x = x;
	this->y = y;
}

pathfinder::pathfinder()
{
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			memory[i][j] = unblocked;
		}
	}
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			hvalue[i][j] = 0;
		}
	}
}

void pathfinder::getsurrounding()
{
	if (x != 0)
	{
		memory[x - 1][y] = map[x - 1][y];

	}
	if (x != 100)
	{
		memory[x + 1][y] = map[x + 1][y];
		//if 
	}
	if (y != 0)
	{
		memory[x][y - 1] = map[x][y - 1];
	}
	if (y != 101)
	{
		memory[x][y + 1] = map[x][y + 1];
	}
}

int pathfinder::findpath()
{
	int counter = 0;
	findingstate start(x, y);
	findingstate goal(goalx, goaly);

	counter++;
	start.gvalue = 0;
	start.search = counter;
	start.hvalue = abs(start.statex - goal.statex) + abs(start.statey - goal.statey);
	start.fvalueupdate();
	start.parent = NULL;
	goal.gvalue = infinite;
	goal.search = counter;
	priority_queue<findingstate, vector<findingstate>, greater>  open;
	stack<findingstate> close;
	open.push(start);

	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			gvalue[i][j] = 0;
		}
	}

	while (open.top().hvalue != 0)
	{
		//close.push(open.top());
		findingstate* stateexpand = new findingstate(open.top().statex, open.top().statey);
		stateexpand->parent = open.top().parent;
		stateexpand->gvalue = open.top().gvalue;
		close.push(*stateexpand);
		steps++;
		open.pop();
		if (stateexpand->gvalue == gvalue[stateexpand->statex][stateexpand->statey])
		{

			if (stateexpand->statex < 100 && memory[stateexpand->statex + 1][stateexpand->statey] != blocked)
			{
				findingstate stateright(stateexpand->statex + 1, stateexpand->statey);

				stateright.parent = stateexpand;
				stateright.gvalue = stateexpand->gvalue + 1;
				stateright.hvalue = abs(stateright.statex - goal.statex) + abs(stateright.statey - goal.statey);
				stateright.fvalueupdate();
				if (stateright.gvalue<gvalue[stateright.statex][stateright.statey] || gvalue[stateright.statex][stateright.statey] == 0)
				{
					open.push(stateright);
					gvalue[stateright.statex][stateright.statey] = stateright.gvalue;
				}
			}
			if (stateexpand->statex>0 && memory[stateexpand->statex - 1][stateexpand->statey] != blocked)
			{
				findingstate stateleft(stateexpand->statex - 1, stateexpand->statey);

				stateleft.parent = stateexpand;
				stateleft.gvalue = stateexpand->gvalue + 1;
				stateleft.hvalue = abs(stateleft.statex - goal.statex) + abs(stateleft.statey - goal.statey);
				stateleft.fvalueupdate();
				if (stateleft.gvalue<gvalue[stateleft.statex][stateleft.statey] || gvalue[stateleft.statex][stateleft.statey] == 0)
				{
					open.push(stateleft);
					gvalue[stateleft.statex][stateleft.statey] = stateleft.gvalue;
				}

			}
			if (stateexpand->statey>0 && memory[stateexpand->statex][stateexpand->statey - 1] != blocked)
			{
				findingstate stateup(stateexpand->statex, stateexpand->statey - 1);

				stateup.parent = stateexpand;
				stateup.gvalue = stateexpand->gvalue + 1;
				stateup.hvalue = abs(stateup.statex - goal.statex) + abs(stateup.statey - goal.statey);
				stateup.fvalueupdate();
				if (stateup.gvalue < gvalue[stateup.statex][stateup.statey] || gvalue[stateup.statex][stateup.statey] == 0)
				{
					open.push(stateup);
					gvalue[stateup.statex][stateup.statey] = stateup.gvalue;
				}
			}
			if (stateexpand->statey < 100 && memory[stateexpand->statex][stateexpand->statey + 1] != blocked)
			{
				findingstate statedown(stateexpand->statex, stateexpand->statey + 1);

				statedown.parent = stateexpand;
				statedown.gvalue = stateexpand->gvalue + 1;
				statedown.hvalue = abs(statedown.statex - goal.statex) + abs(statedown.statey - goal.statey);
				statedown.fvalueupdate();
				if (statedown.gvalue < gvalue[statedown.statex][statedown.statey] || gvalue[statedown.statex][statedown.statey] == 0)
				{
					open.push(statedown);
					gvalue[statedown.statex][statedown.statey] = statedown.gvalue;
				}
			}
		}
		if (open.size() == 0)
		{
			return 0;// 找不到
		}

	}
	close.push(open.top());
	open.pop();
	findingstate state = close.top();
	path.push(state);
	while (state.parent != NULL)
	{
		state = *(state.parent);
		path.push(state);

	}

	return 1;


}

int pathfinder::findpathbackward()
{
	int counter = 0;
	findingstate start(goalx, goaly);
	findingstate goal(x, y);

	counter++;
	start.gvalue = 0;
	start.search = counter;
	start.hvalue = abs(start.statex - goal.statex) + abs(start.statey - goal.statey);
	start.fvalueupdate();
	start.parent = NULL;
	goal.gvalue = infinite;
	goal.search = counter;
	priority_queue<findingstate, vector<findingstate>, greater>  open;
	stack<findingstate> close;
	open.push(start);

	cleargvalue();

	while (open.top().hvalue != 0)
	{
		//close.push(open.top());
		findingstate* stateexpand = new findingstate(open.top().statex, open.top().statey);
		stateexpand->parent = open.top().parent;
		stateexpand->gvalue = open.top().gvalue;
		close.push(*stateexpand);
		steps++;
		open.pop();
		if (stateexpand->gvalue == gvalue[stateexpand->statex][stateexpand->statey])
		{

			if (stateexpand->statex < 100 && memory[stateexpand->statex + 1][stateexpand->statey] != blocked)
			{
				findingstate stateright(stateexpand->statex + 1, stateexpand->statey);

				stateright.parent = stateexpand;
				stateright.gvalue = stateexpand->gvalue + 1;
				stateright.hvalue = abs(stateright.statex - goal.statex) + abs(stateright.statey - goal.statey);
				stateright.fvalueupdate();
				if (stateright.gvalue<gvalue[stateright.statex][stateright.statey] || gvalue[stateright.statex][stateright.statey] == 0)
				{
					open.push(stateright);
					gvalue[stateright.statex][stateright.statey] = stateright.gvalue;
				}
			}
			if (stateexpand->statex>0 && memory[stateexpand->statex - 1][stateexpand->statey] != blocked)
			{
				findingstate stateleft(stateexpand->statex - 1, stateexpand->statey);

				stateleft.parent = stateexpand;
				stateleft.gvalue = stateexpand->gvalue + 1;
				stateleft.hvalue = abs(stateleft.statex - goal.statex) + abs(stateleft.statey - goal.statey);
				stateleft.fvalueupdate();
				if (stateleft.gvalue<gvalue[stateleft.statex][stateleft.statey] || gvalue[stateleft.statex][stateleft.statey] == 0)
				{
					open.push(stateleft);
					gvalue[stateleft.statex][stateleft.statey] = stateleft.gvalue;
				}

			}
			if (stateexpand->statey>0 && memory[stateexpand->statex][stateexpand->statey - 1] != blocked)
			{
				findingstate stateup(stateexpand->statex, stateexpand->statey - 1);

				stateup.parent = stateexpand;
				stateup.gvalue = stateexpand->gvalue + 1;
				stateup.hvalue = abs(stateup.statex - goal.statex) + abs(stateup.statey - goal.statey);
				stateup.fvalueupdate();
				if (stateup.gvalue < gvalue[stateup.statex][stateup.statey] || gvalue[stateup.statex][stateup.statey] == 0)
				{
					open.push(stateup);
					gvalue[stateup.statex][stateup.statey] = stateup.gvalue;
				}
			}
			if (stateexpand->statey < 100 && memory[stateexpand->statex][stateexpand->statey + 1] != blocked)
			{
				findingstate statedown(stateexpand->statex, stateexpand->statey + 1);

				statedown.parent = stateexpand;
				statedown.gvalue = stateexpand->gvalue + 1;
				statedown.hvalue = abs(statedown.statex - goal.statex) + abs(statedown.statey - goal.statey);
				statedown.fvalueupdate();
				if (statedown.gvalue < gvalue[statedown.statex][statedown.statey] || gvalue[statedown.statex][statedown.statey] == 0)
				{
					open.push(statedown);
					gvalue[statedown.statex][statedown.statey] = statedown.gvalue;
				}
			}
		}
		if (open.size() == 0)
		{
			return 0;// 找不到
		}

	}
	close.push(open.top());
	open.pop();
	findingstate state = close.top();
	stack<findingstate> swap;
	swap.push(state);
	while (state.parent != NULL)
	{
		state = *(state.parent);
		swap.push(state);

	}
	while (!swap.empty())
	{
		path.push(swap.top());
		swap.pop();
	}
	return 1;
}

void pathfinder::clearpath()
{
	while (!path.empty())
	{
		path.pop();
	}

}

void pathfinder::clearmemory()
{
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			memory[i][j] = 0;
		}
	}
}



void pathfinder::cleargvalue()
{
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			gvalue[i][j] = 0;
		}
	}
}

int pathfinder::adaptivefindpath()
{
	int counter = 0;
	findingstate start(x, y);
	findingstate goal(goalx, goaly);

	counter++;
	start.gvalue = 0;
	start.search = counter;
	start.hvalue = abs(start.statex - goal.statex) + abs(start.statey - goal.statey);
	start.fvalueupdate();
	start.parent = NULL;
	goal.gvalue = infinite;
	goal.search = counter;
	priority_queue<findingstate, vector<findingstate>, greater>  open;
	stack<findingstate> close;
	open.push(start);

	cleargvalue();

	while (open.top().hvalue != 0)
	{
		//close.push(open.top());
		findingstate* stateexpand = new findingstate(open.top().statex, open.top().statey);
		stateexpand->parent = open.top().parent;
		stateexpand->gvalue = open.top().gvalue;
		stateexpand->hvalue = open.top().hvalue;
		steps++;
		close.push(*stateexpand);
		open.pop();
		if (stateexpand->gvalue == gvalue[stateexpand->statex][stateexpand->statey])
		{

			if (stateexpand->statex < 100 && memory[stateexpand->statex + 1][stateexpand->statey] != blocked)
			{
				findingstate stateright(stateexpand->statex + 1, stateexpand->statey);

				stateright.parent = stateexpand;
				stateright.gvalue = stateexpand->gvalue + 1;
				if (hvalue[stateright.statex][stateright.statey] == 0)
				{
					stateright.hvalue = abs(stateright.statex - goal.statex) + abs(stateright.statey - goal.statey);
				}
				if (hvalue[stateright.statex][stateright.statey] != 0)
				{
					stateright.hvalue = hvalue[stateright.statex][stateright.statey];
				}
				stateright.fvalueupdate();
				if (stateright.gvalue<gvalue[stateright.statex][stateright.statey] || gvalue[stateright.statex][stateright.statey] == 0)
				{
					open.push(stateright);
					gvalue[stateright.statex][stateright.statey] = stateright.gvalue;
				}
			}
			if (stateexpand->statex>0 && memory[stateexpand->statex - 1][stateexpand->statey] != blocked)
			{
				findingstate stateleft(stateexpand->statex - 1, stateexpand->statey);

				stateleft.parent = stateexpand;
				stateleft.gvalue = stateexpand->gvalue + 1;
				if (hvalue[stateleft.statex][stateleft.statey] == 0)
				{
					stateleft.hvalue = abs(stateleft.statex - goal.statex) + abs(stateleft.statey - goal.statey);
				}
				if (hvalue[stateleft.statex][stateleft.statey] != 0)
				{
					stateleft.hvalue = hvalue[stateleft.statex][stateleft.statey];
				}
				stateleft.fvalueupdate();
				if (stateleft.gvalue<gvalue[stateleft.statex][stateleft.statey] || gvalue[stateleft.statex][stateleft.statey] == 0)
				{
					open.push(stateleft);
					gvalue[stateleft.statex][stateleft.statey] = stateleft.gvalue;
				}

			}
			if (stateexpand->statey>0 && memory[stateexpand->statex][stateexpand->statey - 1] != blocked)
			{
				findingstate stateup(stateexpand->statex, stateexpand->statey - 1);

				stateup.parent = stateexpand;
				stateup.gvalue = stateexpand->gvalue + 1;
				if (hvalue[stateup.statex][stateup.statey] == 0)
				{
					stateup.hvalue = abs(stateup.statex - goal.statex) + abs(stateup.statey - goal.statey);
				}
				if (hvalue[stateup.statex][stateup.statey] != 0)
				{
					stateup.hvalue = hvalue[stateup.statex][stateup.statey];
				}
				stateup.fvalueupdate();
				if (stateup.gvalue < gvalue[stateup.statex][stateup.statey] || gvalue[stateup.statex][stateup.statey] == 0)
				{
					open.push(stateup);
					gvalue[stateup.statex][stateup.statey] = stateup.gvalue;
				}
			}
			if (stateexpand->statey < 100 && memory[stateexpand->statex][stateexpand->statey + 1] != blocked)
			{
				findingstate statedown(stateexpand->statex, stateexpand->statey + 1);

				statedown.parent = stateexpand;
				statedown.gvalue = stateexpand->gvalue + 1;
				if (hvalue[statedown.statex][statedown.statey] == 0)
				{
					statedown.hvalue = abs(statedown.statex - goal.statex) + abs(statedown.statey - goal.statey);
				}
				if (hvalue[statedown.statex][statedown.statey] != 0)
				{
					statedown.hvalue = hvalue[statedown.statex][statedown.statey];
				}
				statedown.fvalueupdate();
				if (statedown.gvalue < gvalue[statedown.statex][statedown.statey] || gvalue[statedown.statex][statedown.statey] == 0)
				{
					open.push(statedown);
					gvalue[statedown.statex][statedown.statey] = statedown.gvalue;
				}
			}
		}
		if (open.size() == 0)
		{
			return 0;// 找不到
		}

	}
	close.push(open.top());
	open.pop();
	findingstate state = close.top();

	path.push(state);

	while (state.parent != NULL)
	{
		state = *(state.parent);
		path.push(state);

	}
	int goaldistance = path.size() - 1;

	//while (!open.empty())
	//{
	//	state = open.top();
	//	hvalue[state.statex][state.statey] = goaldistance - state.gvalue;
	//	open.pop();
	//}
	while (!close.empty())
	{
		state = close.top();
		hvalue[state.statex][state.statey] = goaldistance - state.gvalue;
		close.pop();
	}
	return 1;
}


