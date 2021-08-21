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

	//1. 윈도우 생성될 때
      //1.1. 단어카드철 윈도우 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	  //1.2. 단어카드철 윈도우에서 못 푼 퀴즈 찾는다.
	  index = wordCardBinderForm->wordCardBinder->GetCurrent();

	  //1.3. 못푼 퀴즈가 있을 경우, 못푼 퀴즈의 첫번째 단어를 출력한다.
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
	  //1.4. 못푼 퀴즈가 없을 경우, 공백 처리한다.
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

	//2. 첫번째버튼 클릭했을 때
	  //2.1. 단어카드철 윈도우 찾는다.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//2.2. 단어카드철 윈도우에서 첫번째 못 푼 퀴즈 찾는다.
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

	//3. 이전버튼 클릭했을 때
	  //3.1. 단어카드철 윈도우 찾는다.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//3.2. 단어카드철 윈도우에서 이전 못 푼 퀴즈 찾는다.
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

	//4. 다음버튼 클릭했을 때
	  //4.1. 단어카드철 윈도우 찾는다.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//4.2. 단어카드철 윈도우에서 다음 못 푼 퀴즈 찾는다.
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

	//5. 마지막버튼 클릭했을 때
	  //5.1. 단어카드철 윈도우 찾는다.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//5.2. 단어카드철 윈도우에서 마지막 못 푼 퀴즈 찾는다.
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
	//6. 다시풀기 버튼을 클릭했을 때
      //6.2 틀린 문제보기 윈도우를 종료한다.
	  EndDialog(0);

	  //6.1 퀴즈 윈도우를 출력한다.
	  QuizForm quizForm;
	  quizForm.DoModal();	  
}

void IncorrectQuizForm::OnPutImportantWordButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString isImportant;
	
	//7.중요단어 추가 버튼을 클릭했을 때
      //7.1 단어장 윈도우를 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
      //7.2 현재 단어카드의 위치를 읽는다.
	  index = wordCardBinderForm->wordCardBinder->GetCurrent();
      //7.3 단어장 윈도우의 단어장에서 중요단어 추가한다
	  index = wordCardBinderForm->wordCardBinder->PutImportantWord(index);

	  //db에서도 수정한다.
	  wordCardBinderForm->Modify(index);

      //7.4 오답확인 윈도우의 단어카드에 '중요'를 출력한다.
	  isImportant = CString(index->GetIsImportant().c_str());
	  GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);

	  //7.5. 메인윈도우에 중요유무 출력한다.
	  isImportant = CString(index->GetIsImportant().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}

void IncorrectQuizForm::OnPutOutImportantWordButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString isImportant;

	//8.중요단어 취소 버튼을 클릭했을 때
	  //8.1 단어장 윈도우를 찾는다.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//8.2 현재 단어카드의 위치를 읽는다.
	index = wordCardBinderForm->wordCardBinder->GetCurrent();
	//8.3 단어장 윈도우의 단어장에서 중요단어 취소한다
	index = wordCardBinderForm->wordCardBinder->PutOutImportantWord(index);

	//db에서도 수정한다.
	wordCardBinderForm->Modify(index);

	//8.4 오답확인 윈도우의 단어카드에 '중요'를 지운다.
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);

	//8.5. 메인윈도우에 중요유무 출력한다.
	isImportant = CString(index->GetIsImportant().c_str());
	wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}

void IncorrectQuizForm::OnClose() {
	//9. 닫기버튼 클릭했을 때
	  //9.1. 틀린퀴즈 윈도우를 닫는다.
	EndDialog(0);
}
