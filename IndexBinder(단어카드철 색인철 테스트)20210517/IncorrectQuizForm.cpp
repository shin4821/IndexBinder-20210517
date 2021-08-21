//IncorrectQuizForm.cpp
#include"IncorrectQuizForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"QuizForm.h"

BEGIN_MESSAGE_MAP(IncorrectQuizForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_RESOLVE,OnResolveButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PUTIMPORTANTWORD, OnPutImportantWordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PUTOUTIMPORTANTWORD, OnPutOutImportantWordButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

IncorrectQuizForm::IncorrectQuizForm(CWnd* parent)
	:CDialog(IncorrectQuizForm::IDD, parent) {
}

BOOL IncorrectQuizForm::OnInitDialog() {
	CDialog::OnInitDialog();

	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString meaning;
	CString answer;
	CString ox;

	//1. ������ ������ ��
      //1.1. �ܾ�ī��ö ������ ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	  //1.2. �ܾ�ī��ö �����쿡�� �� Ǭ ���� ã�´�.
	  index = wordCardBinderForm->wordCardBinder->GetCurrent();

	  //1.3. ��Ǭ ��� ���� ���, ��Ǭ ������ ù��° �ܾ ����Ѵ�.
	  if (index != NULL) {
		  index = wordCardBinderForm->wordCardBinder->First();

		  spelling = CString(index->GetSpelling().c_str());
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  meaning = CString(index->GetMeaning().c_str());
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
		  answer = CString(index->GetAnswer().c_str());
		  GetDlgItem(IDC_EDIT_ANSWER)->SetWindowText(answer);
		  ox = CString(index->GetOx().c_str());
		  GetDlgItem(IDC_EDIT_QUIZOX)->SetWindowText(ox);
	  }
	  //1.4. ��Ǭ ��� ���� ���, ���� ó���Ѵ�.
	  else {
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_ANSWER)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_QUIZOX)->SetWindowText("");
	  }

	  return FALSE;
}

void IncorrectQuizForm::OnFirstButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString meaning;
	CString answer;
	CString ox;
	CString isImportant;

	//2. ù��°��ư Ŭ������ ��
	  //2.1. �ܾ�ī��ö ������ ã�´�.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//2.2. �ܾ�ī��ö �����쿡�� ù��° �� Ǭ ���� ã�´�.
	index = wordCardBinderForm->wordCardBinder->First();

	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	answer = CString(index->GetAnswer().c_str());
	GetDlgItem(IDC_EDIT_ANSWER)->SetWindowText(answer);
	ox = CString(index->GetOx().c_str());
	GetDlgItem(IDC_EDIT_QUIZOX)->SetWindowText(ox);
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}

void IncorrectQuizForm::OnPreviousButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString meaning;
	CString answer;
	CString ox;
	CString isImportant;

	//3. ������ư Ŭ������ ��
	  //3.1. �ܾ�ī��ö ������ ã�´�.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//3.2. �ܾ�ī��ö �����쿡�� ���� �� Ǭ ���� ã�´�.
	index = wordCardBinderForm->wordCardBinder->Previous();

	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	answer = CString(index->GetAnswer().c_str());
	GetDlgItem(IDC_EDIT_ANSWER)->SetWindowText(answer);
	ox = CString(index->GetOx().c_str());
	GetDlgItem(IDC_EDIT_QUIZOX)->SetWindowText(ox);
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}

void IncorrectQuizForm::OnNextButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString meaning;
	CString answer;
	CString ox;
	CString isImportant;

	//4. ������ư Ŭ������ ��
	  //4.1. �ܾ�ī��ö ������ ã�´�.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//4.2. �ܾ�ī��ö �����쿡�� ���� �� Ǭ ���� ã�´�.
	index = wordCardBinderForm->wordCardBinder->Next();

	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	answer = CString(index->GetAnswer().c_str());
	GetDlgItem(IDC_EDIT_ANSWER)->SetWindowText(answer);
	ox = CString(index->GetOx().c_str());
	GetDlgItem(IDC_EDIT_QUIZOX)->SetWindowText(ox);
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}

void IncorrectQuizForm::OnLastButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString meaning;
	CString answer;
	CString ox;
	CString isImportant;

	//5. ��������ư Ŭ������ ��
	  //5.1. �ܾ�ī��ö ������ ã�´�.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//5.2. �ܾ�ī��ö �����쿡�� ������ �� Ǭ ���� ã�´�.
	index = wordCardBinderForm->wordCardBinder->Last();

	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	answer = CString(index->GetAnswer().c_str());
	GetDlgItem(IDC_EDIT_ANSWER)->SetWindowText(answer);
	ox = CString(index->GetOx().c_str());
	GetDlgItem(IDC_EDIT_QUIZOX)->SetWindowText(ox);
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}

void IncorrectQuizForm::OnResolveButtonClicked() {
	//6. �ٽ�Ǯ�� ��ư�� Ŭ������ ��
      //6.2 Ʋ�� �������� �����츦 �����Ѵ�.
	  EndDialog(0);

	  //6.1 ���� �����츦 ����Ѵ�.
	  QuizForm quizForm;
	  quizForm.DoModal();	  
}

void IncorrectQuizForm::OnPutImportantWordButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString isImportant;
	
	//7.�߿�ܾ� �߰� ��ư�� Ŭ������ ��
      //7.1 �ܾ��� �����츦 ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
      //7.2 ���� �ܾ�ī���� ��ġ�� �д´�.
	  index = wordCardBinderForm->wordCardBinder->GetCurrent();
      //7.3 �ܾ��� �������� �ܾ��忡�� �߿�ܾ� �߰��Ѵ�
	  index = wordCardBinderForm->wordCardBinder->PutImportantWord(index);

	  //db������ �����Ѵ�.
	  wordCardBinderForm->Modify(index);

      //7.4 ����Ȯ�� �������� �ܾ�ī�忡 '�߿�'�� ����Ѵ�.
	  isImportant = CString(index->GetIsImportant().c_str());
	  GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);

	  //7.5. ���������쿡 �߿����� ����Ѵ�.
	  isImportant = CString(index->GetIsImportant().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}

void IncorrectQuizForm::OnPutOutImportantWordButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString isImportant;

	//8.�߿�ܾ� ��� ��ư�� Ŭ������ ��
	  //8.1 �ܾ��� �����츦 ã�´�.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//8.2 ���� �ܾ�ī���� ��ġ�� �д´�.
	index = wordCardBinderForm->wordCardBinder->GetCurrent();
	//8.3 �ܾ��� �������� �ܾ��忡�� �߿�ܾ� ����Ѵ�
	index = wordCardBinderForm->wordCardBinder->PutOutImportantWord(index);

	//db������ �����Ѵ�.
	wordCardBinderForm->Modify(index);

	//8.4 ����Ȯ�� �������� �ܾ�ī�忡 '�߿�'�� �����.
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);

	//8.5. ���������쿡 �߿����� ����Ѵ�.
	isImportant = CString(index->GetIsImportant().c_str());
	wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}

void IncorrectQuizForm::OnClose() {
	//9. �ݱ��ư Ŭ������ ��
	  //9.1. Ʋ������ �����츦 �ݴ´�.
	EndDialog(0);
}
