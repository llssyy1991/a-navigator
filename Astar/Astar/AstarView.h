// homework AI 1View.h : CAstarView 类的接口
//

#pragma once



class CAstarView : public CView
{
protected: // 仅从序列化创建
	CAstarView();
	DECLARE_DYNCREATE(CAstarView)

	// 特性
public:
	CAstarDoc* GetDocument() const;

	// 操作
public:

	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
	virtual ~CAstarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetStart();
	afx_msg void OnSetGoal();
	afx_msg void Onstart();
	afx_msg void Onstartbackward();
	afx_msg void OnstartAdaptive();
	afx_msg void Onclearpath();
	afx_msg void mazemaking();
	afx_msg void onshow();
private:
	CRect start;
public:
	//	CButton *p_buttonsetstart;
	virtual void OnInitialUpdate();
	//void onshow();
	void showpoint(int, int);
	CButton* p_buttonsetstart;
	CButton* p_buttonsetgoal;
	CButton* p_startfinding;
	CButton* p_startbackwardfinding;
	CButton* p_startadaptive;
	CButton* clearpath;
	CButton* mazemake;
	CButton* showmaze;
};

#ifndef _DEBUG  // homework AI 1View.cpp 中的调试版本
inline CAstarDoc* CAstarView::GetDocument() const
{
	return reinterpret_cast<CAstarDoc*>(m_pDocument);
}
#endif

