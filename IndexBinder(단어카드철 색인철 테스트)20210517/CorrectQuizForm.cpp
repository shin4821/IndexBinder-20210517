//CorrectQuizForm.cpp
#include"CorrectQuizForm.h"
#include"WordCardBinderForm.h"
#include"CorrectQuizBinder.h"
#include"WordCardBinder.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //트리컨트롤 스타일
#include<afxcmn.h> //트리뷰

BEGIN_MESSAGE_MAP(CorrectQuizForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_RESET,OnResetButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

CorrectQuizForm::CorrectQuizForm(CWnd* parent)
	:CDialog(CorrectQuizForm::IDD, parent) {
}

BOOL CorrectQuizForm::OnInitDialog() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//1. 윈도우가 생성될 때
	  //1.1. 단어카드철 윈도우를 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	  //1.2. 단어카드철 윈도우의 맞은퀴즈철의 적재개수가 있을 경우,
	  if (wordCardBinderForm->correctQuizBinder->GetLength() > 0) {
		  index = wordCardBinderForm->correctQuizBinder->First();

		  spelling = CString(index->GetSpelling().c_str());
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass = CString(index->GetWordClass().c_str());
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
		  meaning = CString(index->GetMeaning().c_str());
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
		  example = CString(index->GetExample().c_str());
		  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	  }
	  //1.3. 단어카드 없는 경우, 공백 처리한다.
	  else {
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
		  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");
	  }

	  return FALSE;
}
void CorrectQuizForm::OnFirstButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//2. 첫번째버튼 클릭했을 때
	  //2.1. 단어카드철 윈도우 찾는다.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//2.2. 단어카드철 윈도우의 맞은퀴즈철에서 첫번째단어카드 찾는다.
	index = wordCardBinderForm->correctQuizBinder->First();

	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(index->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}
void CorrectQuizForm::OnPreviousButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//3. 이전버튼 클릭했을 때
	  //3.1. 단어카드철 윈도우 찾는다.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//3.2. 단어카드철 윈도우의 맞은퀴즈철에서 이전단어카드 찾는다.
	index = wordCardBinderForm->correctQuizBinder->Previous();

	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(index->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}
void CorrectQuizForm::OnNextButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//4. 다음버튼 클릭했을 때
	  //4.1. 단어카드철 윈도우 찾는다.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//4.2. 단어카드철 윈도우의 맞은퀴즈철에서 다음 단어카드 찾는다.
	index = wordCardBinderForm->correctQuizBinder->Next();

	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(index->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}
void CorrectQuizForm::OnLastButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//5. 이전버튼 클릭했을 때
	  //5.1. 단어카드철 윈도우 찾는다.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");
	//5.2. 단어카드철 윈도우의 맞은퀴즈철에서 이전단어카드 찾는다.
	index = wordCardBinderForm->correctQuizBinder->Last();

	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(index->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
}
void CorrectQuizForm::OnResetButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	WordCard* current;
	WordCard* previous = NULL;
	WordCard wordCard;
	bool ret;
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
	Index* indexIndex=NULL;
	Long(*indexes) = NULL;
	Long count;
	Long wordCardIndex;
	Long i = 0;
	Long j = 0;
	TCHAR alphabets[2];
	WordCard* first;
	WordCard* restOne = NULL;
	WordCard* incorrectWord;
	CString wordClassText;

	//6. 리셋버튼 클릭했을 때
	  //6.1. 단어카드철 윈도우 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");

	  //6.2. 단어카드철 윈도우의 맞은 퀴즈철에서 리셋한다.
	  wordCardBinderForm->correctQuizBinder->Reset();

	  //6.3. 맞은 퀴즈철에서 단어카드 다 뽑아서 단어카드철에 꽂는다.
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
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle,FALSE);
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
	  // 맞은퀴즈개수 0으로 조절하기.


	  //6.4. 맞은퀴즈철 윈도우 공백 처리한다.
	  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
	  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
	  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
	  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");

	  //6.5. 단어카드철 윈도우에 첫번째 단어카드를 단어카드에 출력한다.
	  index = wordCardBinderForm->wordCardBinder->First();

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
	  indexIndex->FindSpellings(index, &indexes, &count);

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

	  if (indexes != NULL) {
		  delete[] indexes;
		  indexes = NULL;
	  }

	  spelling = CString(index->GetSpelling().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	  wordClass = CString(index->GetWordClass().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  meaning = CString(index->GetMeaning().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	  example = CString(index->GetExample().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

	  //6.6. 맞은카트철 윈도우 종료한다.
	  EndDialog(0);

}

void CorrectQuizForm::OnClose() {
	//7. 닫기 버튼을 클릭했을 때
	  //7.1. 맞은퀴즈철 윈도우를 닫는다.
	EndDialog(0);
}



















