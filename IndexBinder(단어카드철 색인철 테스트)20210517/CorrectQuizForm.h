//CorrectQuizForm.h
#ifndef _CORRECTQUIZFORM_H
#define _CORRECTQUIZFORM_H
#include<afxwin.h>
#include"resource.h"

class CorrectQuizForm :public CDialog {
public:
	enum{IDD=IDD_CORRECTQUIZFORM};
public:
	CorrectQuizForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnResetButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif//_CORRECTQUIZFORM_H
