//ImportantWordsForm.cpp
#include"ImportantWordsForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"

BEGIN_MESSAGE_MAP(ImportantWordsForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PUTOUTIMPORTANTWORD,OnPutOutImportantWordButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

ImportantWordsForm::ImportantWordsForm(CWnd* parent)
	:CDialog(ImportantWordsForm::IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
	this->current = 0;
}

BOOL ImportantWordsForm::OnInitDialog() {
	WordCardBinderForm* wordCardBinderForm;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//1. 윈도우가 생성될 때
	  //1.1. 단어카드철 윈도우 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	  //1.2. 단어카드철 윈도우 단어카드철에서 중요단어를 찾는다.
	  wordCardBinderForm->wordCardBinder->FindImportantWords(&this->indexes, &this->count);
	  //1.3. 중요단어가 있는 경우, 중요단어의 첫번째 단어를 출력한다.
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
	  //1.4. 중요단어 없을 경우, 공백 처리한다.
	  else {
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");
	  }

	  return FALSE;
}

void ImportantWordsForm::OnFirstButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//2. 첫번째 버튼 클릭했을 때
	  //2.1. 중요 단어카드 중 첫번째 단어를 찾는다.
	  this->current = 0;
	  //2.2. 첫번째 단어카드를 출력한다.
	  spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
	  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	  wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
	  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
	  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	  example = CString(this->indexes[this->current]->GetExample().c_str());
	  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}


void ImportantWordsForm::OnPreviousButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//3. 이전 버튼 클릭했을 때
	  //3.1. 중요 단어카드 중 이전 단어를 찾는다.
	this->current--;
	if (this->current < 0) {
		this->current = 0;
	}

	//3.2. 이전 단어카드를 출력한다.
	spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}

void ImportantWordsForm::OnNextButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//4. 다음 버튼 클릭했을 때
	  //4.1. 중요 단어카드 중 다음 단어를 찾는다.
	this->current++;
	if (this->current >= this->count) {
		this->current = this->count - 1;
	}

	//4.2. 다음 단어카드를 출력한다.
	spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}

void ImportantWordsForm::OnLastButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//5. 마지막 버튼 클릭했을 때
	  //5.1. 중요 단어카드 중 마지막 단어를 찾는다.
	this->current = this->count - 1;

	//5.2. 마지막 단어카드를 출력한다.
	spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(this->indexes[this->current]->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}

void ImportantWordsForm::OnPutOutImportantWordButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString isImportant;

	//6. 중요단어 취소버튼 클릭했을 때
	  //6.1. 해당 단어카드의 위치를 읽는다.
	  //6.2. 단어카드철 윈도우 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	  //6.3. 단어카드철 윈도우의 단어카드철에서 중요단어 취소한다.
	  wordCardBinderForm->wordCardBinder->PutOutImportantWord(this->indexes[this->current]);

	  //6.4. 메인윈도우에 중요유무 출력한다.
	  isImportant = CString(this->indexes[this->current]->GetIsImportant().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);

	  //db에서도 Modify한다.
	  wordCardBinderForm->Modify(this->indexes[this->current]);


	  //6.4. 단어카드철 윈도우의 단어카드철에서 중요단어 다시 찾는다.
	  if (this->indexes != NULL) {
		  delete[] this->indexes;
	  }
	  wordCardBinderForm->wordCardBinder->FindImportantWords(&this->indexes, &this->count);
	  //6.5. 중요단어가 있을경우, 취소한 위치에 따라 단어를 선택하여 출력한다.
	  if (this->count > 0) {
		  if (this->current < this->count) {
			  spelling = CString(this->indexes[this->current]->GetSpelling().c_str());
			  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			  wordClass = CString(this->indexes[this->current]->GetWordClass().c_str());
			  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
			  meaning = CString(this->indexes[this->current]->GetMeaning().c_str());
			  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
			  example = CString(this->indexes[this->current]->GetExample().c_str());
			  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
		  }
		  else if (this->current >= this->count) {
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
	  }
	  //6.6. 중요단어 없을 경우, 공백 처리한다.
	  else {
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");
	  }
}



void ImportantWordsForm::OnClose() {
	//7. 닫기버튼 클릭했을 때
	if (this->indexes != NULL) {
		delete[] this->indexes;
		this->indexes = NULL;
	 }
	EndDialog(0);
}















