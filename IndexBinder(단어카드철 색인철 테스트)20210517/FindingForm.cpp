//FindingForm.cpp
#include"FindingForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //트리컨트롤 스타일
#include<afxcmn.h> //트리뷰

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

	//1. 윈도우가 생성될 때
	  //1.1. 철자 라디오 박스에 체크한다.
	((CButton*)GetDlgItem(IDC_BUTTON_SPELLING))->SetCheck(BST_CHECKED);

	return FALSE;
}

void FindingForm::OnSpellingButtonClicked() {
	//1. 철자버튼 클릭했을 때
	  //1.1. 의미를 지운다.
	GetDlgItem(IDC_EDIT_CONDITIONMEANING)->SetWindowText("");
}

void FindingForm::OnMeaningButtonClicked() {
	//2. 의미버튼 클릭했을 때
	  //2.1. 철자를 지운다.
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

	//3. 찾기버튼 클릭했을 때
	  //3.1. 철자버튼 읽는다.
	  retSpelling = ((CButton*)GetDlgItem(IDC_BUTTON_SPELLING))->GetCheck();
	  
	  //3.2. 철자 읽는다.
	  GetDlgItem(IDC_EDIT_CONDITIONSPELLING)->GetWindowText(spelling);

	  //3.3. 의미버튼 읽는다.
	  retMeaning = ((CButton*)GetDlgItem(IDC_BUTTON_MEANING))->GetCheck();

	  //3.4. 의미 읽는다.
	  GetDlgItem(IDC_EDIT_CONDITIONMEANING)->GetWindowText(meaning);

	  //3.5. 단어카드철 윈도우 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");

	  //3.6. 단어카드철 윈도우의 단어카드철에 조건에 따라 찾는다.
	  if (this->indexes != NULL) {
		  delete[] this->indexes;
	  }
	  if (retSpelling == BST_CHECKED) {
		  wordCardBinderForm->wordCardBinder->FindBySpelling((LPCTSTR)spelling, &this->indexes, &this->count);
	  }
	  else if (retMeaning == BST_CHECKED) {
		  wordCardBinderForm->wordCardBinder->FindByMeaning((LPCTSTR)meaning, &this->indexes, &this->count);
	  }
	  //3.7. 단어카드가 있는 경우, 찾은 단어카드 중 첫번째 단어카드를 출력한다.
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
	  //3.8. 단어카드가 없는 경우, 공백 처리한다.
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

	//4. 선택버튼 클릭했을 때
	  //4.1. 현재 단어카드의 위치를 읽는다.
	  //4.2. 단어카드철 윈도우 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");

	  //4.3. 현재 단어카드를 단어카드철윈도우의 단어카드철에서 현재 위치로 옮긴다.
	  index = wordCardBinderForm->wordCardBinder->Move(this->indexes[this->current]);

	  //11.2. 트리뷰 상 현재 단어의 알파벳핸들 찾는다.
	  spelling = CString(index->GetSpelling().c_str());
	  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

	  while (alphabet != spelling[0] - 32) {
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  }

	  //11.3. 트리뷰 상 알파벳 핸들 펼친다.
	  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	  //11.4. 트리뷰 상 현재 단어의 단어핸들 찾는다.
	  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	  while (spelling != word) {
		  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	  }

	  //11.5. 해당 단어가 색인에 동일단어 있는지 확인한다.
	  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);
	  indexIndex->FindSpellings(index, &sameIndexes, &count);

	  //11.6. 동일단어 있으면,
	  if (count > 1) {
		  //11.6.1. 단어핸들의 몇번째 품사인지 확인한다.
		   //8.6.2. 품사핸들 찾는다.
		  wordClass = CString(index->GetWordClass().c_str());
		  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		  while (wordClassText != wordClass) {
			  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		  }

		  //11.6.3. 단어핸들 펼쳐준다.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		  //11.6.4. 해당 품사핸들을 선택된 상태로 처리한다.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
	  }
	  //11.7. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
	  else {
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
	  }

	  if (sameIndexes != NULL) {
		  delete[] sameIndexes;
		  sameIndexes = NULL;
	  }

	  //4.4. 현재 단어카드를 단어카드철 윈도우에 출력한다.
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

	  //4.5. 찾기윈도우 종료한다.
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

	//5. 첫번째 버튼을 클릭했을 때
	  //5.1 첫번째 단어를 출력한다.
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

	//6. 이전 버튼을 클릭했을 때
	  //6.1 이전 단어를 출력한다.
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

	//7. 다음 버튼을 클릭했을 때
	  //7.1 다음 단어를 출력한다.
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

	//8. 마지막 버튼을 클릭했을 때
	  //8.1 마지막 단어를 출력한다.
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















