// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// IndigioGamertiseView.cpp : implementation of the CIndigioGamertiseView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IndigioGamertise.h"
#endif

#include "IndigioGamertiseDoc.h"
#include "IndigioGamertiseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIndigioGamertiseView

IMPLEMENT_DYNCREATE(CIndigioGamertiseView, CView)

BEGIN_MESSAGE_MAP(CIndigioGamertiseView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIndigioGamertiseView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CIndigioGamertiseView construction/destruction

CIndigioGamertiseView::CIndigioGamertiseView()
{
	// TODO: add construction code here

}

CIndigioGamertiseView::~CIndigioGamertiseView()
{
}

BOOL CIndigioGamertiseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIndigioGamertiseView drawing

void CIndigioGamertiseView::OnDraw(CDC* /*pDC*/)
{
	CIndigioGamertiseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CIndigioGamertiseView printing


void CIndigioGamertiseView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIndigioGamertiseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIndigioGamertiseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIndigioGamertiseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CIndigioGamertiseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIndigioGamertiseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIndigioGamertiseView diagnostics

#ifdef _DEBUG
void CIndigioGamertiseView::AssertValid() const
{
	CView::AssertValid();
}

void CIndigioGamertiseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIndigioGamertiseDoc* CIndigioGamertiseView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIndigioGamertiseDoc)));
	return (CIndigioGamertiseDoc*)m_pDocument;
}
#endif //_DEBUG


// CIndigioGamertiseView message handlers
