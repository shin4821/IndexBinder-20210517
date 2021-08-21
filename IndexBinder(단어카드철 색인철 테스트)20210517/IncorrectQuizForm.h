//IncorrectQuizForm.h
#ifndef _INCORRECTQUIZFORM_H
#define _INCORRECTQUIZFORM_H
#include<afxwin.h>
#include"resource.h"

class IncorrectQuizForm :public CDialog {
public:
	enum{IDD=IDD_INCORRECTQUIZFORM};

public:
	IncorrectQuizForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();

protected:
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnResolveButtonClicked();
	afx_msg void OnPutImportantWordButtonClicked();
	afx_msg void OnPutOutImportantWordButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif//_INCORRECTQUIZFORM_H
