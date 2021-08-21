//PuttingForm.cpp
#include"PuttingForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //트리컨트롤 스타일
#include<afxcmn.h> //트리뷰

BEGIN_MESSAGE_MAP(PuttingForm,CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_SPELLING, OnSpellingKillFocus)
	ON_BN_CLICKED(IDC_BUTTON_PUT, OnPutButtonClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

PuttingForm::PuttingForm(CWnd* parent)
	:CDialog(PuttingForm::IDD, parent) {
}

BOOL PuttingForm::OnInitDialog() {
	CDialog::OnInitDialog();
	TCHAR wordClasses[][8] = { "명사","동사","형용사","부사","대명사","접속사","전치사","감탄사" };
	Long i;

	//1. 꽂기윈도우 생성될 때
	  //1.1. 콤보박스 목록에 품사를 추가한다.
	for (i = 0; i < sizeof(wordClasses) / sizeof(wordClasses[0]); i++) {
		((CComboBox*)GetDlgItem(IDC_EDIT_WORDCLASS))->AddString((LPCTSTR)wordClasses[i]);
	}

	return FALSE;
}

void PuttingForm::OnSpellingKillFocus() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;

	//2. 철자에서 포커스를 잃을 때
	  //2.1. 철자를 읽는다.
	  GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);

	  //2.2. 단어카드철 윈도우를 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");

	  //2.3. 단어카드철윈도우의 단어카드철에 해당 철자와 동일한 철자가 있을 경우 출력한다.
	  index = wordCardBinderForm->wordCardBinder->FindSpelling((LPCTSTR)spelling);
	  if (index != NULL) {
		  wordClass = CString(index->GetWordClass().c_str());
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
		  meaning = CString(index->GetMeaning().c_str());
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
		  example = CString(index->GetExample().c_str());
		  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	  }
}

void PuttingForm::OnPutButtonClicked() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString ox;
	Index* indexIndex;
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	CString alphabet;
	TCHAR alphabets[2];
	Long(*indexes) = NULL;
	Long count;
	CString word;
	WordCard* first;
	BOOL ret;

	//3. 꽂기버튼 클릭했을 때
	  //3.1. 단어카드 읽는다.
	  GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);
	  GetDlgItem(IDC_EDIT_WORDCLASS)->GetWindowText(wordClass);
	  GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);
	  GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);

	  //3.2. 단어카드철 윈도우 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");

	  //3.3. 단어카드철 윈도우의 단어카드철에 꽂는다.
	  WordCard wordCard((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
		  (LPCTSTR)spelling, (LPCTSTR)"", (LPCTSTR)"", (LPCTSTR)meaning, (LPCTSTR)"");

	  index = wordCardBinderForm->wordCardBinder->PutIn(wordCard);

	  //db에 Insert한다.
	  wordCardBinderForm->Insert(index);

	  //3.4. 색인철에 해당 단어카드 꽂는다.
	  indexIndex = wordCardBinderForm->indexBinder->PutIn(index);
	  spelling = CString(index->GetSpelling().c_str());

	  //알파벳 카테고리 핸들을 펼쳐준다.
	  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(parent, TVE_EXPAND);

	  //3.5. 트리뷰 상 현재 단어의 alphabet 핸들 찾는다.
	  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
		  ->GetNextItem(parent, TVGN_CHILD);
	  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  while (alphabetHandle != NULL && alphabet != spelling[0] - 32) {
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(alphabetHandle, TVGN_NEXT);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  }
	  //3.6. 알파벳 핸들이 있는 경우,
	  if (alphabetHandle != NULL) {
		  //3.6.1. 알파벳 핸들 펼친다.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);
		  
		  //3.6.2. 색인에 동일단어 있는지 확인한다.
		  indexIndex->FindSpellings(index, &indexes, &count);

		  //3.6.3. 동일단어 있으면,
		  if (count > 1) {
			  //3.6.3.1. 단어핸들 찾는다.
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(alphabetHandle, TVGN_CHILD);
			  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  while (word != spelling) {
				  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->GetNextItem(wordHandle, TVGN_NEXT);
				  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  }

			  //단어핸들 펼쳐준다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);

			  //3.6.3.2. 동일단어가 2개이면,
			  if (count > 1 && count < 3) {

				  //1. 해당 단어핸들이 체크되어 있다면, uncheck 해준다.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, FALSE);

				  //2. 단어핸들 하위에 이미 꽂혀있던 첫번째 단어의 품사 추가한다.
				  first = indexIndex->GetAt(indexes[0]);
				  wordClass = CString(first->GetWordClass().c_str());
				  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->InsertItem(wordClass, wordHandle, TVI_LAST);

				  //3. 체크 되어있었으면 체크해준다.
				  ox = CString(first->GetOx().c_str());
				  if (ox == "o") {
					  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES)) ->SetCheck(wordClassHandle, TRUE);
				  }


				  //4. 두번째 단어의 품사 역시 단어핸들 하위에 추가한다.
				  wordClass = CString(index->GetWordClass().c_str());
				  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->InsertItem(wordClass, wordHandle, TVI_LAST);

				  //5. 해당 품사핸들을 선택된 상태로 처리한다.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
			  }
			  //3.6.3.3. 동일단어가 3개 이상이면,
			  else if (count > 2) {
				  //1. 단어핸들 하위에 품사핸들 추가한다.
				  wordClass = CString(index->GetWordClass().c_str());
				  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->InsertItem(wordClass, wordHandle, TVI_LAST);

				  //2. 해당 품사핸들을 선택된 상태로 처리한다.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
			  }
		  }

		  //3.6.4. 동일단어가 없으면,
		  else {
			  //3.6.4.1. 알파벳 핸들 하위에 단어핸들 추가한다.
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->InsertItem(spelling, alphabetHandle, TVI_LAST);
			  //3.6.4.2. 해당 단어핸들을 선택된 상태로 처리한다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
		  }
	  }

	  if (indexes != NULL) {
		  delete[] indexes;
		  indexes = NULL;
	  }
	 
	  //3.7. 알파벳 핸들 없는 경우,
	  else {
		  //3.7.1. 알파벳 카테고리 핸들 하위에 알파벳 핸들 추가한다.
		  alphabets[0] = spelling[0]-32;
		  alphabets[1] = '\0';
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->InsertItem(alphabets, parent, TVI_SORT);

		  //3.7.2. 알파벳 핸들 하위에 단어핸들 추가한다.
		  wordHandle= ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->InsertItem(spelling, alphabetHandle, TVI_SORT);
		 
#if 0
		  if (spelling == "apple") {
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
		  }
#endif



		  //3.7.3. 알파벳 핸들 펼친다.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);
		  //3.7.4. 해당 단어핸들을 선택된 상태로 처리한다.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
	  }

	  //3.4. 꽂은 단어카드를 단어카드철 윈도우에 출력한다.
	  spelling = CString(index->GetSpelling().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	  wordClass = CString(index->GetWordClass().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  meaning = CString(index->GetMeaning().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	  example = CString(index->GetExample().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

	  //3.5. 꽂기윈도우 종료한다.
	  EndDialog(0);
}

void PuttingForm::OnClose() {
	//4. 닫기버튼 클릭했을 때
	  //4.1. 꽂기윈도우 종료한다.
	EndDialog(0);

}














