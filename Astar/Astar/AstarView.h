// homework AI 1View.h : CAstarView ��Ľӿ�
//

#pragma once



class CAstarView : public CView
{
protected: // �������л�����
	CAstarView();
	DECLARE_DYNCREATE(CAstarView)

	// ����
public:
	CAstarDoc* GetDocument() const;

	// ����
public:

	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CAstarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // homework AI 1View.cpp �еĵ��԰汾
inline CAstarDoc* CAstarView::GetDocument() const
{
	return reinterpret_cast<CAstarDoc*>(m_pDocument);
}
#endif

