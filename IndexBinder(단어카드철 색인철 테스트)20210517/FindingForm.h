//FindingForm.h
#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include<afxwin.h>
#include"resource.h"
typedef signed long int Long;

class WordCard;
class FindingForm :public CDialog {
public:
	enum{IDD=IDD_FINDINGFORM};
public:
	FindingForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
private:
	WordCard* (*indexes);
	Long count;
	Long current;
protected:
	afx_msg void OnSpellingButtonClicked();
	afx_msg void OnMeaningButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnSelectButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif//_FINDINGFORM_H