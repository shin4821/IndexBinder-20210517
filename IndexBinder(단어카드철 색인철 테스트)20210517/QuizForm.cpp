//QuizForm.cpp
#include"QuizForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"CorrectQuizBinder.h"
#include"IncorrectQuizForm.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //트리컨트롤 스타일
#include<afxcmn.h> //트리뷰

BEGIN_MESSAGE_MAP(QuizForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NEXT,OnNextButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

QuizForm::QuizForm(CWnd* parent)
	:CDialog(QuizForm::IDD, parent) {
	this->nextQuiz = NULL;
}

BOOL QuizForm::OnInitDialog() {
	CDialog::OnInitDialog();

	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	WordCard* current;
	WordCard* previous = NULL;
	CString spelling;
	WordCard wordCard;
	int ret;
	CString wordClass;
	CString meaning;
	CString example;

	WordCard* temp;
	WordCard* newIndex = NULL;
	CString ox;
	int ret_;
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	CString alphabet;
	CString word;
	Index* indexIndex = NULL;
	Long(*indexes) = NULL;
	Long count;
	Long wordCardIndex;
	Long i = 0;
	Long j = 0;
	TCHAR alphabets[2];
	WordCard* first;
	WordCard* restOne = NULL;
	WordCard* incorrectWord;
	Long testLength;
	CString wordClassText;



	//1. 윈도우가 생성될 때
	 //1.1. 단어카드철 윈도우를 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");

	  //1.2. 단어카드철에서 질문을 찾는다.
	  this->nextQuiz = wordCardBinderForm->wordCardBinder->First();
	  testLength = wordCardBinderForm->wordCardBinder->GetLength();

	  //1.3. 질문이 있으면 퀴즈 철자를 출력한다.
	  if (testLength>0 &&  this->nextQuiz != NULL) {
		  spelling = CString(this->nextQuiz->GetSpelling().c_str());
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass= CString(this->nextQuiz->GetWordClass().c_str());
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  }
	  //1.4. 질문이 없으면,
	  else {
		  //1.4.1. 메세지를 출력한다.
		  ret = MessageBox("더 이상 문제가 없습니다. 리셋하시겠습니까?", "알림창", MB_YESNOCANCEL);

		  //1.4.2. '예'버튼 클릭했을 때
		  if (ret == IDYES) {
			  //1.4.2.1. 단어카드철 윈도우의 맞은퀴즈철에서 리셋한다.
			  wordCardBinderForm->correctQuizBinder->Reset();
			  //1.4.2.2. 맞은퀴즈철의 처음부터 끝까지 반복한다.
			  index = wordCardBinderForm->correctQuizBinder->First();
			  while (index != previous) {
				  //뽑기전 미리 그 다음 카드 구해놓기-----------------------------------------------------------------------------------------------------
				  current = wordCardBinderForm->correctQuizBinder->Next();
				  previous = index;
				  //--------------------------------------------------------------------------------------------------------------------------------------
		  //뽑기전 처리(PuttingOutForm)

		  //맞은퀴즈철에서 뽑는다.
				  temp = index;
				  wordCard = wordCardBinderForm->correctQuizBinder->PutOut(index);
				  spelling = CString(wordCard.GetSpelling().c_str());

				  // 색인철에서 뽑는다.
				  indexIndex = wordCardBinderForm->indexBinder->PutOut((LPCTSTR)spelling, temp);

				  //db에서 delete한다.
				  wordCardBinderForm->Delete(wordCard);

				  //꽂은후 처리(PuttingForm)----------------------------------------------------------------------------------------------------------------

				  //단어카드철에 꽂는다.
				  index = wordCardBinderForm->wordCardBinder->PutIn(wordCard);

				  // 색인철에 꽂는다.
				  indexIndex = wordCardBinderForm->indexBinder->PutIn(index);
				  spelling = CString(index->GetSpelling().c_str());

				  //db에 Insert한다.
				  wordCardBinderForm->Insert(index);

				  //3.5. 트리뷰 상 현재 단어의 alphabet 핸들 찾는다.
				  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);

				  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->GetNextItem(parent, TVGN_CHILD);
				  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

				  while (alphabetHandle != NULL && alphabet != spelling[0] - 32) {
					  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->GetNextItem(alphabetHandle, TVGN_NEXT);
					  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
				  }

				  //3.6.3.1. 단어핸들 찾는다.
				  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->GetNextItem(alphabetHandle, TVGN_CHILD);
				  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				  while (word != spelling) {
					  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->GetNextItem(wordHandle, TVGN_NEXT);
					  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				  }


				  //3.6.2. 색인에 동일단어 있는지 확인한다.
				  indexIndex->FindSpellings(index, &indexes, &count);

				  //3.6.3. 동일단어 있으면,
				  if (count > 1) {


					  //8.6.2. 품사핸들 찾는다.
					  wordClass = CString(index->GetWordClass().c_str());
					  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->GetNextItem(wordHandle, TVGN_CHILD);
					  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->GetItemText(wordClassHandle);

					  while (wordClassText != wordClass) {
						  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
							  ->GetNextItem(wordClassHandle, TVGN_NEXT);
						  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
							  ->GetItemText(wordClassHandle);
					  }

					  //2. 해당 품사핸들을 언체크 상태로 처리한다.
					  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle, FALSE);
				  }

				  //3.6.4. 동일단어가 없으면,
				  else {
					  //3.6.4.2. 해당 단어핸들을 언체크 상태로 처리한다.
					  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, FALSE);

				  }

				  if (indexes != NULL) {
					  delete[] indexes;
					  indexes = NULL;
				  }

				  //변경식---------------------------------------------------------------------------------------------------------------------------------
				  index = current;
				  //---------------------------------------------------------------------------------------------------------------------------------------
			  }

			  //6.5. 단어카드철 윈도우에 첫번째 단어카드를 단어카드에 출력한다.
			  index = wordCardBinderForm->wordCardBinder->First();

			  spelling = CString(index->GetSpelling().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			  wordClass = CString(index->GetWordClass().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
			  meaning = CString(index->GetMeaning().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
			  example = CString(index->GetExample().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
			  //단어카드철 윈도우의 맞은퀴즈철 적재개수를 0개로 조절한다.
	
			  //1.4.2.3. 단어카드철 윈도우의 단어카드철에서 질문을 찾는다.
			  this->nextQuiz = wordCardBinderForm->wordCardBinder->First();

			  //1.4.2.4. 퀴즈철자를 출력한다.
			  spelling = CString(this->nextQuiz->GetSpelling().c_str());
			  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			  wordClass = CString(this->nextQuiz->GetWordClass().c_str());
			  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
		  }
		  //1.4.3. '아니오'버튼 클릭했을 때
		  else if (ret == IDNO) {
			  //1.4.3.1. 퀴즈윈도우 종료한다.
			  EndDialog(0);
		  }
	  }
	  return FALSE;
}

void QuizForm::OnNextButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	CString meaning;
	bool ret;
	WordCard wordCard;
	WordCard* index;
	WordCard* temp;
	WordCard* newIndex=NULL;
	CString spelling;
	CString wordClass;
	CString example;
	CString ox;
	int ret_;
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	CString alphabet;
	CString word;
	Index* indexIndex;
	Long(*indexes) = NULL;
	Long count;
	Long wordCardIndex;
	Long i = 0;
	Long j=0;
	TCHAR alphabets[2];
	WordCard* first;
	WordCard* restOne = NULL;
	WordCard* incorrectWord;
	CString wordClassText;
	CString isImportant;


	//2. 다음 버튼 클릭했을 때
	  //2.1. 단어카드철 윈도우 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	  //2.2. 퀴즈윈도우에서 현재 퀴즈의 위치를 읽는다.
	  index = this->nextQuiz;
	  //2.3. 의미를 읽는다.
	  GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);
	  //2.4. 문제를 푼다.
	  ret = wordCardBinderForm->wordCardBinder->SpellingQuiz((LPCTSTR)meaning, index);
	  //db에서도 문제를 푼다(수정한다.)
	  wordCardBinderForm->Modify(index);
	  

	  //2.5. 다음 문제를 미리 구해놓는다.
	  this->nextQuiz = wordCardBinderForm->wordCardBinder->NextQuiz();
	  
	  //2.6. 퀴즈가 맞았을 경우,
	  if (ret == true) {
		  //------------------------------------------------------------------------------
		  //뽑기전 처리(PuttingOutForm)
			//2.6.1. 단어카드철에서 뽑는다.
		  temp = index;
		  wordCard = wordCardBinderForm->wordCardBinder->PutOut(index);
		  spelling = CString(wordCard.GetSpelling().c_str());

		  // 색인철에서 뽑는다.
		  indexIndex = wordCardBinderForm->indexBinder->PutOut((LPCTSTR)spelling, temp);

		  //db에서 delete한다.
		  wordCardBinderForm->Delete(wordCard);



		  //꽂는 처리(PuttingForm)------------------------------------------------------------------------

		  //2.6.2. 맞은퀴즈철에 꽂는다.
		  index = wordCardBinderForm->correctQuizBinder->PutIn(wordCard);

		  // 색인철에 꽂는다.
		  indexIndex = wordCardBinderForm->indexBinder->PutIn(index);
		  spelling = CString(index->GetSpelling().c_str());

		  //db에 Insert한다.
		  wordCardBinderForm->Insert(index);


		  //단어핸들 또는 품사핸들을 찾는다.
		  //-------------------------------------------------------------------------------------------------------
			 //8.2. 트리뷰 상 현재 단어의 알파벳핸들 찾는다.
		  spelling = CString(index->GetSpelling().c_str());

		  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

		  while (alphabet != spelling[0] - 32) {
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
			  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  }

		  //8.6.3. 알파벳핸들 펼쳐준다.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

		  //8.4. 트리뷰 상 현재 단어의 단어핸들 찾는다.
		  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
		  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  while (spelling != word) {
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
			  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  }

		  //8.5. 해당 단어가 색인에 동일단어 있는지 확인한다.
		  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);
		  indexIndex->FindSpellings(index, &indexes, &count);

		  //8.6. 동일단어 있으면,
		  if (count > 1) { //품사핸들을 찾아준다.

			  //8.6.2. 품사핸들 찾는다.
			  wordClass = CString(index->GetWordClass().c_str());
			  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
			  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

			  while (wordClassText != wordClass) {
				  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->GetNextItem(wordClassHandle, TVGN_NEXT);
				  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
			  }
			  //8.6.3. 단어핸들 펼쳐준다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);


			  //해당 품사핸들을 체크로 설정한다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle, TRUE);

		  }
		  //8.7. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
		  else {
			  //해당 단어핸들을 체크로 설정한다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
		  }

		  if (indexes != NULL) {
			  delete[] indexes;
			  indexes = NULL;
		  }

		  //-------------------------------------------------------------------------------


		  //2.6.3. 단어카드철 윈도우에 현재 단어카드가 있는지 확인한다.
		  index = wordCardBinderForm->wordCardBinder->GetCurrent();
		  //2.6.4. 현재 카드가 있으면 단어카드철 윈도우의 단어카드철에 출력한다.
		  if (index != NULL) {

			  //현재 카드의 색인을 찾아 선택 처리한다.
			  //-------------------------------------------------------
			  //8.2. 트리뷰 상 현재 단어의 알파벳핸들 찾는다.
			  spelling = CString(index->GetSpelling().c_str());

			  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
			  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

			  while (alphabet != spelling[0] - 32) {
				  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
				  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
			  }

			  //8.3. 트리뷰 상 알파벳 핸들 펼친다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

			  //8.4. 트리뷰 상 현재 단어의 단어핸들 찾는다.
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
			  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  while (spelling != word) {
				  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
				  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  }

			  //8.5. 해당 단어가 색인에 동일단어 있는지 확인한다.
			  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);
			  indexIndex->FindSpellings(index, &indexes, &count);

			  //8.6. 동일단어 있으면,
			  if (count > 1) { //품사핸들을 찾아준다.

				  //8.6.2. 품사핸들 찾는다.
				  wordClass = CString(index->GetWordClass().c_str());
				  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
				  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

				  while (wordClassText != wordClass) {
					  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
					  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
				  }

				  //8.6.3. 단어핸들 펼쳐준다.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
				  //8.6.4. 해당 품사핸들을 선택된 상태로 처리한다.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

			  }
			  //8.7. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
			  else {
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
			  }

			  if (indexes != NULL) {
				  delete[] indexes;
				  indexes = NULL;
			  }

			  //-------------------------------------------------------

			  spelling = CString(index->GetSpelling().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			  wordClass = CString(index->GetWordClass().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
			  meaning = CString(index->GetMeaning().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
			  example = CString(index->GetExample().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
			  isImportant = CString(index->GetIsImportant().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
		  }
		  //2.6.5. 현재 카드가 없으면 공백 처리한다.
		  else {
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText("");
		  }


	  }

	  //2.7. 다음질문이 있으면,
	  if (this->nextQuiz != NULL) {
		  //2.7.1. 퀴즈철자를 출력한다.
		  spelling = CString(this->nextQuiz->GetSpelling().c_str());
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass = CString(this->nextQuiz->GetWordClass().c_str());
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);

		  //2.7.2. 의미를 공백처리한다.
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
	  }
	  //2.8. 다음질문이 없으면,
	  else {
		  //2.8.1. 메세지박스 출력한다.
		  ret_ = MessageBox("마지막 문제입니다. 결과를 확인해보시겠습니까?", "알림창", MB_YESNOCANCEL);
		  //2.8.2. '예'버튼 클릭했을 때
		  if (ret_ == IDYES) {
			  //2.8.2.2. 퀴즈윈도우 종료한다.
			  EndDialog(0);

			  //2.8.2.1. 오답윈도우를 출력한다.
			  IncorrectQuizForm incorrectQuizForm;
			  incorrectQuizForm.DoModal();


		  }
		  //2.8.3. '아니오'버튼 클릭했을 때
		  else if (ret_ == IDNO) {
			  //2.8.3.1. 퀴즈윈도우 종료한다.
			  EndDialog(0);
		  }
	  }

}


void QuizForm::OnClose() {
	int ret;

	//3. 닫기버튼 클릭했을때
	  //3.1. 메세지박스 출력한다.
	  ret = MessageBox("결과를 확인해보시겠습니까?", "알림창", MB_YESNOCANCEL);
	  //3.2. '예'버튼 클릭했을 때
	  if (ret == IDYES) {
		  //3.2.2. 퀴즈윈도우 종료한다.
		  EndDialog(0);

		  //3.2.1. 오답윈도우 출력한다.
		  IncorrectQuizForm incorrectQuizForm;
		  incorrectQuizForm.DoModal();
	  }

	  //3.3. '아니오'버튼 클릭했을 때
	  else if (ret == IDNO) {
		  //3.3.1. 퀴즈윈도우 종료한다.
		  EndDialog(0);
	  }
}















