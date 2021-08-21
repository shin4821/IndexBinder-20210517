//ImportantWordsForm.h
#ifndef _IMPORTANTWORDSFORM_H
#define _IMPORTANTWORDSFORM_H
#include<afxwin.h>
#include"resource.h"
typedef signed long int Long;

class WordCard;
class ImportantWordsForm :public CDialog {
public:
	enum{IDD=IDD_IMPORTANTWORDSFORM};
public:
	ImportantWordsForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnPutOutImportantWordButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
protected:
	WordCard* (*indexes);
	Long count;
	Long current;
};

#endif//_IMPORTANTWORDSFORM_H

