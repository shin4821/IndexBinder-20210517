//QuizForm.h
#ifndef _QUIZFORM_H
#define _QUIZFORM_H
#include<afxwin.h>
#include"resource.h"
class WordCard;
class QuizForm :public CDialog {
public:
	enum{IDD=IDD_QUIZFORM};
public:
	QuizForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
protected:
	afx_msg void OnNextButtonClicked();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
private:
	WordCard* nextQuiz;
};

#endif//_QUIZFORM_H
