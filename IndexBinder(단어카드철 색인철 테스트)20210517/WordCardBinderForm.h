//WordCardBinderForm.h
#ifndef _WORDCARDBINDERFORM_H
#define _WORDCARDBINDERFORM_H
#include<afxwin.h>
#include"resource.h"
typedef signed long int Long;

class WordCard;
class WordCardBinder;
class IndexBinder;
class CorrectQuizBinder;

class WordCardBinderForm :public CDialog {
public:
	enum{IDD=IDD_WORDCARDBINDERFORM};
public:
	WordCardBinderForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
public:
	WordCardBinder* wordCardBinder;
	CorrectQuizBinder* correctQuizBinder;
	IndexBinder* indexBinder;

public:
	void Load();
	void Save();
	void Insert(WordCard* index);
	void Delete(WordCard wordCard);
	void Modify(WordCard* index);
	CString GetCode();
	CString GetQuizCode();

protected:
	afx_msg void OnClose();
	afx_msg void OnPutButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnPutOutButtonClicked();
	afx_msg void OnQuizButtonClicked();
	afx_msg void OnCorrectQuizButtonClicked();
	afx_msg void OnImportantWordsButtonClicked();
	afx_msg void OnFirstButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnLastButtonClicked();
	afx_msg void OnPutImportantWordButtonClicked();
	afx_msg void OnPutOutImportantWordButtonClicked();
	afx_msg void OnTreeViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnTreeViewCheckBoxClicked(NMHDR* pNotifyStruct, LRESULT* result);

	afx_msg LRESULT OnTreeChangeCheck(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

#endif//_WORDCARDBINDERFORM_H
