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

	//1. �����찡 ������ ��
	  //1.1. �ܾ�ī��ö ������ ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	  //1.2. �ܾ�ī��ö ������ �ܾ�ī��ö���� �߿�ܾ ã�´�.
	  wordCardBinderForm->wordCardBinder->FindImportantWords(&this->indexes, &this->count);
	  //1.3. �߿�ܾ �ִ� ���, �߿�ܾ��� ù��° �ܾ ����Ѵ�.
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
	  //1.4. �߿�ܾ� ���� ���, ���� ó���Ѵ�.
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

	//2. ù��° ��ư Ŭ������ ��
	  //2.1. �߿� �ܾ�ī�� �� ù��° �ܾ ã�´�.
	  this->current = 0;
	  //2.2. ù��° �ܾ�ī�带 ����Ѵ�.
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

	//3. ���� ��ư Ŭ������ ��
	  //3.1. �߿� �ܾ�ī�� �� ���� �ܾ ã�´�.
	this->current--;
	if (this->current < 0) {
		this->current = 0;
	}

	//3.2. ���� �ܾ�ī�带 ����Ѵ�.
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

	//4. ���� ��ư Ŭ������ ��
	  //4.1. �߿� �ܾ�ī�� �� ���� �ܾ ã�´�.
	this->current++;
	if (this->current >= this->count) {
		this->current = this->count - 1;
	}

	//4.2. ���� �ܾ�ī�带 ����Ѵ�.
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

	//5. ������ ��ư Ŭ������ ��
	  //5.1. �߿� �ܾ�ī�� �� ������ �ܾ ã�´�.
	this->current = this->count - 1;

	//5.2. ������ �ܾ�ī�带 ����Ѵ�.
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

	//6. �߿�ܾ� ��ҹ�ư Ŭ������ ��
	  //6.1. �ش� �ܾ�ī���� ��ġ�� �д´�.
	  //6.2. �ܾ�ī��ö ������ ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	  //6.3. �ܾ�ī��ö �������� �ܾ�ī��ö���� �߿�ܾ� ����Ѵ�.
	  wordCardBinderForm->wordCardBinder->PutOutImportantWord(this->indexes[this->current]);

	  //6.4. ���������쿡 �߿����� ����Ѵ�.
	  isImportant = CString(this->indexes[this->current]->GetIsImportant().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);

	  //db������ Modify�Ѵ�.
	  wordCardBinderForm->Modify(this->indexes[this->current]);


	  //6.4. �ܾ�ī��ö �������� �ܾ�ī��ö���� �߿�ܾ� �ٽ� ã�´�.
	  if (this->indexes != NULL) {
		  delete[] this->indexes;
	  }
	  wordCardBinderForm->wordCardBinder->FindImportantWords(&this->indexes, &this->count);
	  //6.5. �߿�ܾ �������, ����� ��ġ�� ���� �ܾ �����Ͽ� ����Ѵ�.
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
	  //6.6. �߿�ܾ� ���� ���, ���� ó���Ѵ�.
	  else {
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");
	  }
}



void ImportantWordsForm::OnClose() {
	//7. �ݱ��ư Ŭ������ ��
	if (this->indexes != NULL) {
		delete[] this->indexes;
		this->indexes = NULL;
	 }
	EndDialog(0);
}















