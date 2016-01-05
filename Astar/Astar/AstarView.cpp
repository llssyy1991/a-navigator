// AstarView.cpp : CAstarView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Astar.h"
#endif
#include "pathfinder.h"
#include "AstarDoc.h"
#include "AstarView.h"
#include <string>

#ifndef stdlib
#define stdlib
#include <stdlib.h>
#endif

#include <stack>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef iostreams
#define iostreams
#include <iostream>
#endif

#ifndef visitcheck
#define unvisited 0
#define visited 1
#endif

#define _CRT_SECURE_NO_WARNINGS
#define _AFX_SECURE_NO_WARNINGS
#define _ATL_SECURE_NO_WARNINGS

int setstart;
int steps = 0;
pathfinder hero;
CPoint pointselected;
CPoint startpoint(1500, 1500);
CPoint goalpoint(1500, 1500);
CBrush brushW(RGB(255, 255, 255));
int map[101][101];
int visit[101][101];
stack<CPoint> pointinput;

int getrandneigh(int, int);
CPoint getpointleft();

// CAstarView

IMPLEMENT_DYNCREATE(CAstarView, CView)

BEGIN_MESSAGE_MAP(CAstarView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_buttonsetstart, OnSetStart)
	ON_BN_CLICKED(IDC_buttonsetgoal, OnSetGoal)
	ON_BN_CLICKED(IDC_start, Onstart)
	ON_BN_CLICKED(IDC_startbackward, Onstartbackward)
	ON_BN_CLICKED(IDC_startadaptive, OnstartAdaptive)
	ON_BN_CLICKED(IDC_clearpath, Onclearpath)
	ON_BN_CLICKED(IDC_mazemaking, mazemaking)
	ON_BN_CLICKED(IDC_showmazes, onshow)
END_MESSAGE_MAP()

// CAstarView 构造/析构

CAstarView::CAstarView()
{


	// TODO:  在此处添加构造代码
	//CButton *p_buttonsetstart = new CButton();
	//CButton *p_buttonsetgoal = new CButton();
	//p_buttonsetstart->Create(_T("set it as start"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1100, 100, 1200, 200), this, 101);
	//p_buttonsetgoal->Create(_T("set it as goal"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1100, 300, 1200, 400), this, 102);


}

CAstarView::~CAstarView()
{
}

BOOL CAstarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CAstarView 绘制

void CAstarView::OnDraw(CDC* /*pDC*/)
{
	CAstarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	CClientDC dc(this);
	int i;
	for (i = 0; i < 101; i++)
	{
		dc.MoveTo(i * 10, 0);
		dc.LineTo(i * 10, 1010);
	}
	for (i = 0; i < 101; i++)
	{
		dc.MoveTo(0, i * 10);
		dc.LineTo(1010, i * 10);
	}


}


// CAstarView 打印

BOOL CAstarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CAstarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CAstarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CAstarView 诊断

#ifdef _DEBUG
void CAstarView::AssertValid() const
{
	CView::AssertValid();
}

void CAstarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAstarDoc* CAstarView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAstarDoc)));
	return (CAstarDoc*)m_pDocument;
}
#endif //_DEBUG


// CAstarView 消息处理程序


void CAstarView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CBrush brush(RGB(255, 0, 0));

	CClientDC dc(this);

	CView::OnLButtonDown(nFlags, point);
	if (point.x < 1010 && point.y < 1010)
	{
		pointselected = point;
		int x1 = point.x - point.x % 10 + 1, y1 = point.y - point.y % 10 + 1, x2 = point.x - point.x % 10 + 10 - 1, y2 = point.y - point.y % 10 + 10 - 1;
		CPoint upleft(x1, y1), downright(x2, y2);
		dc.FillRect(start, &brushW);
		start = CRect(upleft, downright);
		dc.FillRect(start, &brush);

	}
	//CButton *p_buttonsetstart = new CButton();
	//CButton *p_buttonsetgoal = new CButton();
	//p_buttonsetstart->Create(_T("set it as start"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1100, 100, 1200, 200), this, 101);
	//p_buttonsetgoal->Create(_T("set it as goal"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1100, 300, 1200, 400), this, 102);

}


void CAstarView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	p_buttonsetstart = new CButton();
	p_buttonsetgoal = new CButton();
	p_startfinding = new CButton();
	p_startbackwardfinding = new CButton();
	p_startadaptive = new CButton();
	clearpath = new CButton();
	mazemake = new CButton();
	showmaze = new CButton();
	// TODO:  在此添加专用代码和/或调用基类
	p_buttonsetstart->Create(_T("set it as start"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1100, 100, 1200, 200), this, 101);
	//p_buttonsetgoal->Create(_T("set it as goal"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1100, 300, 1200, 400), this, 102);
	//p_startfinding->Create(_T("start"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1100, 500, 1200, 600), this, 103);
	//p_startbackwardfinding->Create(_T("startbackward"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1300, 500, 1400, 600), this, 104);
	//p_startadaptive->Create(_T("startadaptive"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1300, 300, 1400, 400), this, 105);
	//clearpath->Create(_T("clearpath"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1300, 100, 1400, 200), this, 106);
	//mazemake->Create(_T("maze"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1200, 100, 1300, 200), this, 107);
	//showmaze->Create(_T("showblock"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1200, 300, 1300, 400), this, 108);
}

void CAstarView::OnSetStart()
{

	int x1 = startpoint.x - startpoint.x % 10 + 1, y1 = startpoint.y - startpoint.y % 10 + 1, x2 = startpoint.x - startpoint.x % 10 + 10 - 1, y2 = startpoint.y - startpoint.y % 10 + 10 - 1;

	CClientDC dc(this);
	dc.FillRect(new CRect(x1, y1, x2, y2), &brushW);
	CBrush brushG(RGB(0, 255, 0));
	dc.FillRect(start, &brushG);
	startpoint = pointselected;
	start = new CRect(1500, 1500, 1500, 1500);
#ifndef setgoal
#define setgoal
	p_buttonsetgoal->Create(_T("set it as goal"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1100, 300, 1200, 400), this, 102);
#endif
}

void CAstarView::OnSetGoal()
{
	int x1 = goalpoint.x - goalpoint.x % 10 + 1, y1 = goalpoint.y - goalpoint.y % 10 + 1, x2 = goalpoint.x - goalpoint.x % 10 + 10 - 1, y2 = goalpoint.y - goalpoint.y % 10 + 10 - 1;

	CClientDC dc(this);
	dc.FillRect(new CRect(x1, y1, x2, y2), &brushW);
	CBrush brushG(RGB(0, 0, 255));
	dc.FillRect(start, &brushG);
	goalpoint = pointselected;
	start = new CRect(1500, 1500, 1500, 1500);
#ifndef mazeandother
#define mazeandother
	mazemake->Create(_T("maze"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1200, 100, 1300, 200), this, 107);
	showmaze->Create(_T("showblock"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1200, 300, 1300, 400), this, 108);
#endif
}

void CAstarView::Onstart()
{

	CClientDC dc(this);
	//int steps=0;
	//maze making
	//mazemaking();
	//set goal and start for player
	map[startpoint.x / 10][startpoint.y / 10] = unblocked;
	map[goalpoint.x / 10][goalpoint.y / 10] = unblocked;
	hero.x = startpoint.x / 10;
	hero.y = startpoint.y / 10;
	hero.goalx = goalpoint.x / 10;
	hero.goaly = goalpoint.y / 10;
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			hero.memory[i][j] = unblocked;
		}
	}
	//onshow();

	//start searching 
	hero.getsurrounding();
	int check = hero.findpath();
	if (check == 0)
	{
		MessageBox(_T("can not find a way"));
		return;
	}
	hero.path.pop();
	findingstate nextstep = hero.path.top();
	while ((nextstep.statex != hero.goalx) || (nextstep.statey != hero.goaly))
	{

		if (hero.memory[nextstep.statex][nextstep.statey] != blocked)
		{
			hero.x = nextstep.statex;
			hero.y = nextstep.statey;
			showpoint(hero.x, hero.y);
			hero.getsurrounding();
			hero.path.pop();
			nextstep = hero.path.top();
			//steps++;
		}


		if (hero.memory[nextstep.statex][nextstep.statey] == blocked)
		{
			CBrush brush1(RGB(232, 22, 247));
			dc.FillRect(new CRect(nextstep.statex * 10, nextstep.statey * 10, nextstep.statex * 10 + 9, nextstep.statey * 10 + 9), &brush1);
			while (!hero.path.empty())
			{
				hero.path.pop();
			}
			check = hero.findpath();

			if (check == 0)
			{
				MessageBox(_T("wrong"));
				return;
				//cout << "can't find a way" << endl;

			};
			if (check != 0)
			{
				hero.path.pop();
				nextstep = hero.path.top();
			}
		};
		//string results = std::to_string(steps);


	}
	char results[10];
	sprintf(results, "%d", steps);
	//const char result[10]=results;
	wchar_t result[10];
	mbstowcs(result, results, strlen(results) + 1);

	MessageBox(result);
	return;
}


int getrandneigh(int x, int y)
{
	stack<CPoint> nearby;
	if (x < 101 && visit[x + 1][y] != visited)
	{
		nearby.push(*new CPoint(x + 1, y));
	}
	if (x>0 && visit[x - 1][y] != visited)
	{
		nearby.push(*new CPoint(x - 1, y));
	}
	if (y < 101 && visit[x][y + 1] != visited)
	{
		nearby.push(*new CPoint(x, y + 1));
	}
	if (y>0 && visit[x][y - 1] != visited)
	{
		nearby.push(*new CPoint(x, y - 1));
	}
	if (nearby.size() == 0)
	{
		return 0;
	}
	int nearrand = rand() % nearby.size();
	int poptime = 0;
	while (poptime < nearrand)
	{
		nearby.pop();
		poptime++;
	}
	CPoint randpoint = nearby.top();
	pointinput.push(randpoint);

	visit[randpoint.x][randpoint.y] = visited;
	int randnum = rand() % 100;
	if (randnum < 30)
	{
		map[randpoint.x][randpoint.y] = blocked;
	}
	if (randnum >= 30)
	{
		map[randpoint.x][randpoint.y] = unblocked;
	}
	return 1;
}


void CAstarView::onshow()
{
	CBrush brush1(RGB(232, 22, 247));
	CClientDC dc(this);
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			if (map[i][j] == blocked)
			{
				dc.FillRect(new CRect(i * 10, j * 10, i * 10 + 9, j * 10 + 9), &brush1);
			}
		}
	}
}


CPoint getpointleft()
{
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			if (visit[i][j] == unvisited)
			{
				return *new CPoint(i, j);
			}
		}
	}
}


void CAstarView::showpoint(int i, int j)
{
	CBrush brush1(RGB(255, 0, 0));
	CClientDC dc(this);
	dc.FillRect(new CRect(i * 10, j * 10, i * 10 + 9, j * 10 + 9), &brush1);
}

void CAstarView::mazemaking()
{
	int checkvisit = 0;

	int mazestartx = rand() % 101;
	int mazestatrty = rand() % 101;
	map[mazestartx][mazestatrty] = unblocked;
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			visit[i][j] = unvisited;
		}
	}

	pointinput.push(*new CPoint(mazestartx, mazestatrty));
	while (pointinput.size() != 0)
	{

		CPoint pointexpand = pointinput.top();
		int checktopop = getrandneigh(pointexpand.x, pointexpand.y);
		if (checktopop == 0)
		{
			pointinput.pop();
			checkvisit++;
		}
	}


	while (checkvisit < 101 * 101)
	{
		CPoint pointleft;
		pointleft = getpointleft();
		pointinput.push(pointleft);
		while (pointinput.size() != 0)
		{

			CPoint pointexpand = pointinput.top();
			int checktopop = getrandneigh(pointexpand.x, pointexpand.y);
			if (checktopop == 0)
			{
				pointinput.pop();
				checkvisit++;
			}
		}


	}
	map[startpoint.x / 10][startpoint.y / 10] = unblocked;
	map[goalpoint.x / 10][goalpoint.y / 10] = unblocked;
	FILE *fp;
	fp = fopen("C:\\Users\\lsy\\Documents\\Visual Studio 2013\\Projects\\Project3\\Project3\\maze13.txt", "a");
	fprintf(fp, "%d   %d\n", startpoint.x / 10, startpoint.y / 10);
	fprintf(fp, "%d   %d\n", goalpoint.x / 10, goalpoint.y / 10);
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			fprintf(fp, "%d ", map[i][j]);
		}
		fprintf(fp, "\n");
	}
#ifndef pathfinding
#define pathfinding
	p_startfinding->Create(_T("start"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1100, 500, 1200, 600), this, 103);
	p_startbackwardfinding->Create(_T("startbackward"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1300, 500, 1400, 600), this, 104);
	p_startadaptive->Create(_T("startadaptive"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1300, 300, 1400, 400), this, 105);
	clearpath->Create(_T("clearpath"), WS_VISIBLE | BS_PUSHBUTTON, CRect(1300, 100, 1400, 200), this, 106);
#endif

}


void CAstarView::Onstartbackward()
{
	CClientDC dc(this);
	//maze making
	//mazemaking();
	//set goal and start for player
	map[startpoint.x / 10][startpoint.y / 10] = unblocked;
	map[goalpoint.x / 10][goalpoint.y / 10] = unblocked;
	hero.x = startpoint.x / 10;
	hero.y = startpoint.y / 10;
	hero.goalx = goalpoint.x / 10;
	hero.goaly = goalpoint.y / 10;
	hero.clearmemory();
	onshow();
	hero.clearpath();


	//start searching 
	hero.getsurrounding();
	int check = hero.findpathbackward();
	if (check == 0)
	{
		MessageBox(_T("can not find a way"));
		return;
	}
	hero.path.pop();
	findingstate nextstep = hero.path.top();
	while ((nextstep.statex != hero.goalx) || (nextstep.statey != hero.goaly))
	{

		if (hero.memory[nextstep.statex][nextstep.statey] != blocked)
		{
			hero.x = nextstep.statex;
			hero.y = nextstep.statey;
			showpoint(hero.x, hero.y);
			hero.getsurrounding();
			hero.path.pop();
			nextstep = hero.path.top();
		}


		if (hero.memory[nextstep.statex][nextstep.statey] == blocked)
		{
			hero.clearpath();
			check = hero.findpathbackward();

			if (check == 0)
			{
				MessageBox(_T("wrong"));
				return;
				//cout << "can't find a way" << endl;

			};
			if (check != 0)
			{
				hero.path.pop();
				nextstep = hero.path.top();
			}
		};


	}
	char results[10];
	sprintf(results, "%d", steps);
	//const char result[10]=results;
	wchar_t result[10];
	mbstowcs(result, results, strlen(results) + 1);

	MessageBox(result);
	return;

}

void CAstarView::OnstartAdaptive()
{
	CClientDC dc(this);
	//maze making
	//mazemaking();
	//set goal and start for player
	map[startpoint.x / 10][startpoint.y / 10] = unblocked;
	map[goalpoint.x / 10][goalpoint.y / 10] = unblocked;
	hero.x = startpoint.x / 10;
	hero.y = startpoint.y / 10;
	hero.goalx = goalpoint.x / 10;
	hero.goaly = goalpoint.y / 10;
	hero.clearmemory();
	onshow();
	hero.clearpath();


	//start searching 
	hero.getsurrounding();
	int check = hero.adaptivefindpath();
	if (check == 0)
	{
		MessageBox(_T("can not find a way"));
		return;
	}
	hero.path.pop();
	findingstate nextstep = hero.path.top();
	while ((nextstep.statex != hero.goalx) || (nextstep.statey != hero.goaly))
	{

		if (hero.memory[nextstep.statex][nextstep.statey] != blocked)
		{
			hero.x = nextstep.statex;
			hero.y = nextstep.statey;
			showpoint(hero.x, hero.y);
			hero.getsurrounding();
			hero.path.pop();
			nextstep = hero.path.top();
		}


		if (hero.memory[nextstep.statex][nextstep.statey] == blocked)
		{
			hero.clearpath();
			check = hero.adaptivefindpath();

			if (check == 0)
			{
				MessageBox(_T("wrong"));
				return;
				//cout << "can't find a way" << endl;

			};
			if (check != 0)
			{
				hero.path.pop();
				nextstep = hero.path.top();
			}
		};


	}
	char results[10];
	sprintf(results, "%d", steps);
	//const char result[10]=results;
	wchar_t result[10];
	mbstowcs(result, results, strlen(results) + 1);

	MessageBox(result);
	return;

}


void CAstarView::Onclearpath()
{
	CBrush brush1(RGB(232, 22, 247));
	CBrush brush2(RGB(255, 255, 255));
	CBrush brush3(RGB(0, 255, 0));
	CBrush brush4(RGB(0, 0, 255));
	CClientDC dc(this);
	hero.clearmemory();
	hero.clearpath();
	steps = 0;
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			dc.FillRect(new CRect(i * 10, j * 10, i * 10 + 9, j * 10 + 9), &brush2);
		}
	}
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			if (map[i][j] == blocked)
			{
				dc.FillRect(new CRect(i * 10, j * 10, i * 10 + 9, j * 10 + 9), &brush1);
			}
		}
	}
	int startx = startpoint.x / 10;
	int starty = startpoint.y / 10;
	int goalx = goalpoint.x / 10;
	int goaly = goalpoint.y / 10;
	dc.FillRect(new CRect(startx * 10, starty * 10, startx * 10 + 9, starty * 10 + 9), &brush3);
	dc.FillRect(new CRect(goalx * 10, goaly * 10, goalx * 10 + 9, goaly * 10 + 9), &brush4);

}