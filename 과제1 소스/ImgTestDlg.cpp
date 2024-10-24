
// ImgTestDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ImgTest.h"
#include "ImgTestDlg.h"
#include "afxdialogex.h"

#include <cstdlib>
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImgTestDlg dialog



CImgTestDlg::CImgTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMGTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImgTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_SX, m_sliderSX);
	DDX_Control(pDX, IDC_SLIDER_SY, m_sliderSY);
	DDX_Control(pDX, IDC_STEXT_SPOS, m_staticStartPosition);
	DDX_Control(pDX, IDC_STEXT_SX, m_staticSX);
	DDX_Control(pDX, IDC_STEXT_SY, m_staticSY);
	DDX_Control(pDX, IDC_SLIDER_EX, m_sliderEX);
	DDX_Control(pDX, IDC_SLIDER_EY, m_sliderEY);
	DDX_Control(pDX, IDC_STEXT_EX, m_staticEX);
	DDX_Control(pDX, IDC_STEXT_EY, m_staticEY);
	DDX_Control(pDX, IDC_STEXT_EPOS, m_staticEndPosition);
}

BEGIN_MESSAGE_MAP(CImgTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CImgTestDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CImgTestDlg::OnBnClickedBtnAction)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CImgTestDlg::OnBnClickedBtnOpen)
END_MESSAGE_MAP()


// CImgTestDlg message handlers

BOOL CImgTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	gnWidth = 640;
	gnHeight = 480;
	gnStartX = 0;
	gnStartY = 0;
	gnEndX = 640;
	gnEndY = 480;

	m_sliderSX.SetRange(gnStartX, gnEndX);
	m_sliderSX.SetPos(gnStartX);
	m_sliderSX.SetTicFreq(10);
	m_sliderSX.SetLineSize(1);

	m_sliderSY.SetRange(gnStartY, gnEndY);
	m_sliderSY.SetPos(gnStartY);
	m_sliderSY.SetTicFreq(10);
	m_sliderSY.SetLineSize(1);

	m_sliderEX.SetRange(gnStartX, gnEndX);
	m_sliderEX.SetPos(gnEndX);
	m_sliderEX.SetTicFreq(10);
	m_sliderEX.SetLineSize(1);

	m_sliderEY.SetRange(gnStartY, gnEndY);
	m_sliderEY.SetPos(gnEndY);
	m_sliderEY.SetTicFreq(10);
	m_sliderEY.SetLineSize(1);

	CFont font;
	font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	m_staticStartPosition.SetFont(&font);
	m_staticEndPosition.SetFont(&font);

	m_staticSX.SetFont(&font);
	m_staticSY.SetFont(&font);
	m_staticEX.SetFont(&font);
	m_staticEY.SetFont(&font);

	CString str;
	str.Format(_T("Start X: %d"), m_sliderSX.GetPos());
	m_staticSX.SetWindowTextW(str);

	str.Format(_T("Start Y: %d"), m_sliderSY.GetPos());
	m_staticSY.SetWindowTextW(str);

	str.Format(_T("Start X: %d"), m_sliderEX.GetPos());
	m_staticEX.SetWindowTextW(str);

	str.Format(_T("Start Y: %d"), m_sliderEY.GetPos());
	m_staticEY.SetWindowTextW(str);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImgTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImgTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}


	InitDraw();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImgTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImgTestDlg::InitDraw()
{
	int nWidth = gnWidth;
	int nHeight = gnHeight;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
		{
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_image.SetColorTable(0, 256, rgb);
		}
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}


void CImgTestDlg::OnBnClickedBtnDraw()
{
	static int snX, snY, snRadius;
	int nGray = 80;
	//int nRadius = rand() % 10;
	int nRadius = rand() % 50;

	//nRadius = nRadius == 1 ? 2 : nRadius;

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	DrawCircle(fm, snX, snY, snRadius, 0xff);

	snX = gnStartX;
	snY = gnStartY;
	snRadius = nRadius;

	DrawCircle(fm, snX, snY, nRadius, nGray);

	UpdateDisplay();
}


void CImgTestDlg::OnBnClickedBtnAction()
{
	CString strImageName = _T("images\\circle_0.bmp");

	CreateDirectoryRecursively(strImageName);

	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 0xff, gnWidth * gnHeight);

	int nDistanceX = gnEndX - gnStartX;
	int nDistanceY = gnEndY - gnStartY;

	double nStepX = nDistanceX / (double)10;
	double nStepY = nDistanceY / (double)10;

	int nPosX[10];
	int nPosY[10];
	int nRadius[10];

	for (int i = 0; i < 10; i++)
	{
		nPosX[i] = gnStartX + nStepX * i;
		nPosY[i] = gnStartY + nStepY * i;
		nRadius[i] = rand() % 50;
	}

	DrawCircle(fm, nPosX[0], nPosY[0], nRadius[0], 80);
	UpdateDisplay();
	m_image.Save(strImageName);

	for (int i = 1; i < 10; i++)
	{
		Sleep(10);
		DrawCircle(fm, nPosX[i-1], nPosY[i-1], nRadius[i-1], 0xff);

		DrawCircle(fm, nPosX[i], nPosY[i], nRadius[i], 80);

		strImageName.Format(_T("images\\circle_%d.bmp"), i);
		m_image.Save(strImageName);

		UpdateDisplay();
	}	
}


void CImgTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if(pScrollBar == (CScrollBar*)&m_sliderSX)
	{
		int value = m_sliderSX.GetPos();
		CString str;
		str.Format(_T("Start X: %d"), value);
		m_staticSX.SetWindowTextW(str);
		gnStartX = value;
	}
	else if (pScrollBar == (CScrollBar*)&m_sliderEX)
	{
		int value = m_sliderEX.GetPos();
		CString str;
		str.Format(_T("End X: %d"), value);
		m_staticEX.SetWindowTextW(str);
		gnEndX = value;
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CImgTestDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if(pScrollBar == (CScrollBar*)&m_sliderSY)
	{
		int value = m_sliderSY.GetPos();
		CString str;
		str.Format(_T("Start Y: %d"), value);
		m_staticSY.SetWindowTextW(str);
		gnStartY = value;
	}
	else if (pScrollBar == (CScrollBar*)&m_sliderEY)
	{
		int value = m_sliderEY.GetPos();
		CString str;
		str.Format(_T("End Y: %d"), value);
		m_staticEY.SetWindowTextW(str);
		gnEndY = value;
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CImgTestDlg::DrawCircle(unsigned char* fm, int nX, int nY, int nRadius, int nGray)
{
	int nCenterX = nX + nRadius;
	int nCenterY = nY + nRadius;
	int nPitch = m_image.GetPitch();


	for (int i = nX; i < nX + nRadius * 2; i++)
	{
		for (int j = nY; j < nY + nRadius * 2; j++)
		{
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
			{
				fm[i + j * nPitch] = nGray;
			}
		}
	}
}


bool CImgTestDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) bRet = true;

	return bRet;
}


void CImgTestDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}


void CImgTestDlg::OnBnClickedBtnOpen()
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);

	LPCTSTR szFilter = _T("Bmp files (*.bmp)|*.bmp|All files (*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter, NULL);

	// 실행 파일의 디렉토리 경로 추출
	CString strPath(szPath);
	int nPos = strPath.ReverseFind('\\');
	if (nPos != -1)
		strPath = strPath.Left(nPos);

	dlg.m_ofn.lpstrInitialDir = strPath;

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();

		//cout << filePath << endl;

		if (m_image != NULL)
		{
			m_image.Destroy();
		}

		m_image.Load(filePath);

		UpdateDisplay();
	
		FindCenter();
	}
}

void CImgTestDlg::CreateDirectoryRecursively(const CString& path)
{
	int pos = 0;
	CString subPath;

	while ((pos = path.Find('\\', pos + 1)) != -1)
	{
		subPath = path.Left(pos);
		if (GetFileAttributes(subPath) == INVALID_FILE_ATTRIBUTES)
		{
			CreateDirectory(subPath, NULL);
		}
	}
}



void CImgTestDlg::FindCenter()
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nTargetGrayLevel = 100;

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int nSumX = 0, nSumY = 0, nSumCount = 0;

	for (int i = 0; i < nWidth; i++)
	{
		for (int j = 0; j < nHeight; j++)
		{
			if (fm[i + j* nPitch] < nTargetGrayLevel)
			{
				nSumX += i;
				nSumY += j;
				nSumCount += 1;
			}
		}
	}

	int nCenterPosX = nSumX / nSumCount;
	int nCenterPosY = nSumY / nSumCount;

	cout << "Center X: " << nCenterPosX << " Center Y: " << nCenterPosY << endl;

	DrawCerterMark(nCenterPosX, nCenterPosY);
}


void CImgTestDlg::DrawCerterMark(int nPosX, int nPosY)
{
	int nLineOffset = 5;

	// DC 얻기
	CDC* pDC = CDC::FromHandle(m_image.GetDC());

	// 펜 생성 및 선택
	CPen pen(PS_SOLID, 2, RGB(255, 255, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);

	// X자 그리기
	pDC->MoveTo(nPosX - nLineOffset, nPosY - nLineOffset);
	pDC->LineTo(nPosX + nLineOffset, nPosY + nLineOffset);
	pDC->MoveTo(nPosX + nLineOffset, nPosY - nLineOffset);
	pDC->LineTo(nPosX - nLineOffset, nPosY + nLineOffset);


	pDC->SetTextColor(RGB(255, 0, 0)); // 빨간색 텍스트
	pDC->SetBkMode(TRANSPARENT); // 투명 배경

	CString strText;
	strText.Format(_T("x: %d, y: %d"), nPosX, nPosY);

	int nPosTextX = 0, nPosTextY = 0;
	int nOffset = 80;

	if (nPosX < (gnWidth / 2))
	{
		if (nPosY < (gnHeight / 2))
		{
			nPosTextX = nPosX + nOffset;
			nPosTextY = nPosY + nOffset;
		}
		else
		{
			nPosTextX = nPosX + nOffset;
			nPosTextY = nPosY - nOffset;
		}
	}
	else
	{
		if (nPosY < (gnHeight / 2))
		{
			nPosTextX = nPosX - nOffset;
			nPosTextY = nPosY + nOffset;
		}
		else
		{
			nPosTextX = nPosX - nOffset;
			nPosTextY = nPosY - nOffset;
		}
	}

	pDC->TextOut(nPosTextX, nPosTextY, strText);

	pDC->SelectObject(pOldPen);
	m_image.ReleaseDC();

	UpdateDisplay();
}
