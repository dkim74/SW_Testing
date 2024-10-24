
// ImgTestDlg.h : header file
//

#pragma once


// CImgTestDlg dialog
class CImgTestDlg : public CDialogEx
{
// Construction
public:
	CImgTestDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMGTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CImage m_image;
	int gnWidth;
	int gnHeight;
private:
	void InitDraw();
	void CreateDirectoryRecursively(const CString& path);
public:
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	CSliderCtrl m_sliderSX;
	CSliderCtrl m_sliderSY;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CStatic m_staticStartPosition;
	CStatic m_staticSX;
	CStatic m_staticSY;
	CSliderCtrl m_sliderEX;
	CSliderCtrl m_sliderEY;
	CStatic m_staticEX;
	CStatic m_staticEY;
	CStatic m_staticEndPosition;
	int gnStartX;
	int gnStartY;
	int gnEndX;
	int gnEndY;
	void DrawCircle(unsigned char* fm, int nX, int nY, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void UpdateDisplay();
	afx_msg void OnBnClickedBtnOpen();
	void FindCenter();
	void DrawCerterMark(int nPosX, int nPosY);
};
