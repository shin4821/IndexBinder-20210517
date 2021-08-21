//FindingForm.cpp
#include"FindingForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //Ʈ����Ʈ�� ��Ÿ��
#include<afxcmn.h> //Ʈ����

BEGIN_MESSAGE_MAP(FindingForm,CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SPELLING, OnSpellingButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_MEANING, OnMeaningButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnSelectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

FindingForm::FindingForm(CWnd* parent)
	:CDialog(FindingForm::IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
	this->current = 0;
}

BOOL FindingForm::OnInitDialog() {
	CDialog::OnInitDialog();

	//1. �����찡 ������ ��
	  //1.1. ö�� ���� �ڽ��� üũ�Ѵ�.
	((CButton*)GetDlgItem(IDC_BUTTON_SPELLING))->SetCheck(BST_CHECKED);

	return FALSE;
}

void FindingForm::OnSpellingButtonClicked() {
	//1. ö�ڹ�ư Ŭ������ ��
	  //1.1. �ǹ̸� �����.
	GetDlgItem(IDC_EDIT_CONDITIONMEANING)->SetWindowText("");
}

void FindingForm::OnMeaningButtonClicked() {
	//2. �ǹ̹�ư Ŭ������ ��
	  //2.1. ö�ڸ� �����.
	GetDlgItem(IDC_EDIT_CONDITIONSPELLING)->SetWindowText("");
}

void FindingForm::OnFindButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	int retSpelling;
	int retMeaning;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//3. ã���ư Ŭ������ ��
	  //3.1. ö�ڹ�ư �д´�.
	  retSpelling = ((CButton*)GetDlgItem(IDC_BUTTON_SPELLING))->GetCheck();
	  
	  //3.2. ö�� �д´�.
	  GetDlgItem(IDC_EDIT_CONDITIONSPELLING)->GetWindowText(spelling);

	  //3.3. �ǹ̹�ư �д´�.
	  retMeaning = ((CButton*)GetDlgItem(IDC_BUTTON_MEANING))->GetCheck();

	  //3.4. �ǹ� �д´�.
	  GetDlgItem(IDC_EDIT_CONDITIONMEANING)->GetWindowText(meaning);

	  //3.5. �ܾ�ī��ö ������ ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");

	  //3.6. �ܾ�ī��ö �������� �ܾ�ī��ö�� ���ǿ� ���� ã�´�.
	  if (this->indexes != NULL) {
		  delete[] this->indexes;
	  }
	  if (retSpelling == BST_CHECKED) {
		  wordCardBinderForm->wordCardBinder->FindBySpelling((LPCTSTR)spelling, &this->indexes, &this->count);
	  }
	  else if (retMeaning == BST_CHECKED) {
		  wordCardBinderForm->wordCardBinder->FindByMeaning((LPCTSTR)meaning, &this->indexes, &this->count);
	  }
	  //3.7. �ܾ�ī�尡 �ִ� ���, ã�� �ܾ�ī�� �� ù��° �ܾ�ī�带 ����Ѵ�.
	  if (this->count > 0) {
		  this->current = 0;

		  spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
		  meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
		  example = CString(this->indexes[this->current]->GetExample().c_str());
		  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	  }
	  //3.8. �ܾ�ī�尡 ���� ���, ���� ó���Ѵ�.
	  else {
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");
	  }
}

void FindingForm::OnSelectButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	WordCard* index;
	Long(*sameIndexes);
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	CString alphabet;
	CString word;
	Index* indexIndex;
	CString wordClassText;
	CString isImportant;

	//4. ���ù�ư Ŭ������ ��
	  //4.1. ���� �ܾ�ī���� ��ġ�� �д´�.
	  //4.2. �ܾ�ī��ö ������ ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");

	  //4.3. ���� �ܾ�ī�带 �ܾ�ī��ö�������� �ܾ�ī��ö���� ���� ��ġ�� �ű��.
	  index = wordCardBinderForm->wordCardBinder->Move(this->indexes[this->current]);

	  //11.2. Ʈ���� �� ���� �ܾ��� ���ĺ��ڵ� ã�´�.
	  spelling = CString(index->GetSpelling().c_str());
	  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

	  while (alphabet != spelling[0] - 32) {
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  }

	  //11.3. Ʈ���� �� ���ĺ� �ڵ� ��ģ��.
	  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	  //11.4. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
	  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	  while (spelling != word) {
		  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	  }

	  //11.5. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
	  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);
	  indexIndex->FindSpellings(index, &sameIndexes, &count);

	  //11.6. ���ϴܾ� ������,
	  if (count > 1) {
		  //11.6.1. �ܾ��ڵ��� ���° ǰ������ Ȯ���Ѵ�.
		   //8.6.2. ǰ���ڵ� ã�´�.
		  wordClass = CString(index->GetWordClass().c_str());
		  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		  while (wordClassText != wordClass) {
			  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		  }

		  //11.6.3. �ܾ��ڵ� �����ش�.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		  //11.6.4. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
	  }
	  //11.7. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
	  else {
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
	  }

	  if (sameIndexes != NULL) {
		  delete[] sameIndexes;
		  sameIndexes = NULL;
	  }

	  //4.4. ���� �ܾ�ī�带 �ܾ�ī��ö �����쿡 ����Ѵ�.
	  spelling = CString(index->GetSpelling().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	  wordClass = CString(index->GetWordClass().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  meaning = CString(index->GetWordClass().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	  example = CString(index->GetExample().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	  isImportant = CString(index->GetIsImportant().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);

	  //4.5. ã�������� �����Ѵ�.
	  if (this->indexes != NULL) {
		  delete[] this->indexes;
		  this->indexes = NULL;
	  }
	  EndDialog(0);
}

void FindingForm::OnFirstButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//5. ù��° ��ư�� Ŭ������ ��
	  //5.1 ù��° �ܾ ����Ѵ�.
	  this->current = 0;

	  spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
	  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	  wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
	  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
	  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	  example = CString(this->indexes[this->current]->GetExample().c_str());
	  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}

void FindingForm::OnPreviousButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//6. ���� ��ư�� Ŭ������ ��
	  //6.1 ���� �ܾ ����Ѵ�.
	this->current--;
	if (this->current < 0) {
		this->current = 0;
	}

	spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

}

void FindingForm::OnNextButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//7. ���� ��ư�� Ŭ������ ��
	  //7.1 ���� �ܾ ����Ѵ�.
	this->current++;
	if (this->current >= this->count) {
		this->current = this->count - 1;
	}

	spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

}

void FindingForm::OnLastButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//8. ������ ��ư�� Ŭ������ ��
	  //8.1 ������ �ܾ ����Ѵ�.
	this->current = this->count - 1;

	spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}


void FindingForm::OnClose() {
	if (this->indexes != NULL) {
		delete[] this->indexes;
		this->indexes = NULL;
	}
	EndDialog(0);
}















