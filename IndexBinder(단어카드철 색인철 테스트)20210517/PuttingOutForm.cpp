//PuttingOutForm.cpp
#include"PuttingOutForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //트리컨트롤 스타일
#include<afxcmn.h> //트리뷰

BEGIN_MESSAGE_MAP(PuttingOutForm,CDialog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

PuttingOutForm::PuttingOutForm(CWnd* parent)
	:CDialog(PuttingOutForm::IDD, parent) {
}

BOOL PuttingOutForm::OnInitDialog() {
	CDialog::OnInitDialog();

	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	WordCard wordCard;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString ox;
	Index* indexIndex;
	Long(*indexes);
	Long count;
	Long wordCardIndex;
	Long i = 0;
	Long j = 0;
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	WordCard* temp;
	CString alphabet;
	TCHAR alphabets[2];
	CString word;
	CString wordClassText;

	//1. 뽑기윈도우 생성될 때

	  //1.1. 단어카드철윈도우를 찾는다.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");

	  //1.2. 단어카드철 윈도우의 현재 단어카드 위치 읽는다.
	  index = wordCardBinderForm->wordCardBinder->GetCurrent();

	  //1.3. 현재 단어카드의 색인을 찾는다.
	  spelling = CString(index->GetSpelling().c_str());
	  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);

	  //1.4. 해당 색인에서 현재 단어와 동일단어 있는지 확인.
	  indexIndex->FindSpellings(index, &indexes, &count);

	  //1.5. 동일단어가 3개 이상인 경우, 몇번째 품사인지 확인.
	  if (count > 2) {
		  wordCardIndex = indexIndex->Find(index);
		  while (wordCardIndex != indexes[i]) {
			  i++; //i번째 품사
		  }
	  }

	  //1.6. 단어카드철에서 현재 단어카드 뽑는다.
	  temp = index;
	  wordCard = wordCardBinderForm->wordCardBinder->PutOut(index);

	  //db에서 delete한다.
	  wordCardBinderForm->Delete(wordCard);

	  //1.7. 뽑은 단어카드를 뽑기윈도우 단어카드에 출력한다.
	  spelling = CString(wordCard.GetSpelling().c_str());
	  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	  wordClass = CString(wordCard.GetWordClass().c_str());
	  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  meaning = CString(wordCard.GetMeaning().c_str());
	  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	  example = CString(wordCard.GetExample().c_str());
	  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

	  //1.8. 트리뷰 상 알파벳 핸들 찾는다.
	  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
		  ->GetNextItem(parent, TVGN_CHILD);
	  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  while (alphabet != spelling[0] - 32) {
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(alphabetHandle, TVGN_NEXT);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  }

	  //1.9. 트리뷰 상 단어핸들 찾는다.
	  wordHandle= ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
		  ->GetNextItem(alphabetHandle, TVGN_CHILD);
	  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	  while (word != spelling) {
		  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(wordHandle, TVGN_NEXT);
		  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	  }

	  //2.0. 동일단어가 3개 이상이었던 경우,
	  if (count > 2) {
		  //2.0.1. 단어핸들 하위 품사핸들 찾는다.
		  wordClassHandle= ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(wordHandle, TVGN_CHILD);
		  while (j < i) {
			  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(wordClassHandle, TVGN_NEXT);
			  j++;
		  }

		  //2.0.2. 해당 품사핸들 없앤다.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->DeleteItem(wordClassHandle);
	  }

	  //2.1. 동일단어가 2개인 경우,
	  else if (count > 1 && count < 3) {
		  //2.1.0. 현재 남은(동일단어) 카드의 ox 알아낸다.
		  if (i <= 0) { // 남은 카드위치: 1
			  index = indexIndex->GetAt(indexes[1]);
		  }
		  else if (i >= 1) { //남은 카드위치: 0
			  index = indexIndex->GetAt(indexes[0]);
		  }
		  //2.1.1. 품사핸들 2개 모두 없앤다.
		  i = 0;
		  while (i < count) {
			  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(wordHandle, TVGN_CHILD);
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->DeleteItem(wordClassHandle);

			  i++;
		  }
		  ox = CString(index->GetOx().c_str());
		  if (ox == "o") {// 단어핸들에 체크한다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle);
		  }
	  }

	  //2.2. 동일단어가 없을 경우,
	  else if (count < 2) {
		  //2.2.1. 단어핸들 없앤다.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->DeleteItem(wordHandle);
	  }

	  if (indexes != NULL) {
		  delete[] indexes;
		  indexes = NULL;
	  }

	  //2.3. 단어카드철 윈도우의 색인철에서 해당 단어를 뽑는다.
	  indexIndex = wordCardBinderForm->indexBinder->PutOut((LPCTSTR)spelling, temp);

	  //2.4. 색인철에 해당 알파벳 색인 없는 경우, 트리뷰 상 해당 알파벳색인 없앤다.
	  if (indexIndex == NULL) {
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->DeleteItem(alphabetHandle);
	  }

	  //2.5. 단어카드철 윈도우의 단어카드철에서 현재 단어카드의 위치를 읽는다.
	  index = wordCardBinderForm->wordCardBinder->GetCurrent();

	  //2.6. 단어가 있는 경우,
	  if (index != NULL) {
		  //2.6.1. 트리뷰 상 현재 단어의 알파벳 핸들을 찾는다.
		  spelling = CString(index->GetSpelling().c_str());
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(parent, TVGN_CHILD);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  while (alphabet != spelling[0] - 32) {
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(alphabetHandle, TVGN_NEXT);
			  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  }

		  //2.6.2. 트리뷰 상 알파벳 핸들 펼친다.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

		  //2.6.3. 트리뷰 상 현재 단어의 단어핸들 찾는다.
		  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(alphabetHandle, TVGN_CHILD);
		  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  while (spelling != word) {
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(wordHandle, TVGN_NEXT);
			  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  }

		  //2.6.4. 해당 단어가 색인에 동일단어 있는지 확인한다.
		  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);
		  indexIndex->FindSpellings(index, &indexes, &count);

		  //2.6.5. 동일단어가 있으면,
		  if (count > 1) {
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
		  //2.6.6. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
		  else {
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
		  }

		  //2.6.7. 단어카드철 윈도우의 단어카드에 현재 단어를 출력한다.
		  spelling = CString(index->GetSpelling().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass = CString(index->GetWordClass().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
		  meaning = CString(index->GetMeaning().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
		  example = CString(index->GetExample().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

		  //2.6.8. indexes 할당해제한다.
		  if (indexes != NULL) {
			  delete[] indexes;
			  indexes = NULL;
		  }

	  }

	  //2.7. 단어카드가 없으면 단어카드철 윈도우의 단어카드를 공백 처리한다.
	  else {
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");
	  }

	  return FALSE;
}

void PuttingOutForm::OnClose() {
	WordCardBinderForm* wordCardBinderForm;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString ox;
	int ret;
	BOOL ret_;
	Index* indexIndex;
	CString alphabet;
	CString word;
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	TCHAR alphabets[2];
	Long(*indexes)=NULL;
	Long count;
	WordCard* first;

	//2. 닫기버튼 클릭했을 때
	  //2.1. 메세지박스 띄운다.
	  ret = MessageBox("꽂으시겠습니까?", "알림창", MB_YESNOCANCEL);

	  //2.2. '예'버튼 클릭했을 때
	  if (ret == IDYES) {
		  //2.2.1. 단어카드 읽는다.
		  GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);
		  GetDlgItem(IDC_EDIT_WORDCLASS)->GetWindowText(wordClass);
		  GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);
		  GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);

		  //2.2.2. 단어카드철 윈도우 찾는다.
		  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "단어카드철");

		  //2.2.3. 단어카드철 윈도우의 단어카드철에 꽂는다.
		  WordCard wordCard((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
			  (LPCTSTR)spelling, (LPCTSTR)"", (LPCTSTR)"", (LPCTSTR)meaning, (LPCTSTR)"");
		  index = wordCardBinderForm->wordCardBinder->PutIn(wordCard);

		  //db에서 Insert한다.
		  wordCardBinderForm->Insert(index);

		  //2.2.4. 단어카드철 윈도우의 색인철에 해당 단어카드 꽂는다.
		  indexIndex = wordCardBinderForm->indexBinder->PutIn(index);
		  spelling = CString(index->GetSpelling().c_str());

		  //2.2.5. 알파벳 카테고리 핸들을 펼쳐준다.
		  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(parent, TVE_EXPAND);

		  //2.2.6. 트리뷰 상 현재 단어의 알파벳 핸들 찾는다.
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(parent, TVGN_CHILD);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  while (alphabetHandle != NULL && alphabet != spelling[0] - 32) {
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(alphabetHandle, TVGN_NEXT);
			  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  }

		  //2.2.7. 알파벳 핸들이 있는 경우,
		  if (alphabetHandle != NULL) {
			  //1. 알파벳 핸들 펼친다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

			  //2. 색인에 동일단어 있는지 확인한다.
			  indexIndex->FindSpellings(index, &indexes, &count);

			  //3. 동일단어가 있으면,
			  if (count > 1) {
				  //3.1. 단어핸들 찾는다.
				  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->GetNextItem(alphabetHandle, TVGN_CHILD);
				  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				  while (word != spelling) {
					  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->GetNextItem(wordHandle, TVGN_NEXT);
					  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				  }
				  //3.2. 동일단어가 2개이면,
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
						  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
							  ->SetCheck(wordClassHandle, TRUE);
					  }

					  //4. 두번째 단어의 품사 역시 단어핸들 하위에 추가한다.
					  wordClass = CString(index->GetWordClass().c_str());
					  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->InsertItem(wordClass, wordHandle, TVI_LAST);

					  //5. 해당 품사핸들을 선택된 상태로 처리한다.
					  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

				  }
				  //3.3. 동일단어가 3개이면
				  else if (count > 2) {
					  //1. 단어핸들 하위에 품사핸들 추가한다.
					  wordClass = CString(index->GetWordClass().c_str());
					  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->InsertItem(wordClass, wordHandle, TVI_LAST);

					  //2. 해당 품사핸들을 선택된 상태로 처리한다.
					  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

				  }
			  }
			  //4. 동일단어가 없으면,
			  else {
				  //4.1. 알파벳 핸들 하위에 단어핸들 추가한다.
				  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->InsertItem(spelling, alphabetHandle, TVI_LAST);
				  //4.2. 해당 단어핸들을 선택된 상태로 처리한다.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);

			  }

			  if (indexes != NULL) {
				  delete[] indexes;
				  indexes = NULL;
			  }
		  }

		  //2.2.8. 알파벳핸들 없을 경우,
		  else {
			  //1. 알파벳 카테고리 핸들 하위에 알파벳 핸들 추가한다.
			  alphabets[0] = spelling[0] - 32;
			  alphabets[1] = '\0';
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->InsertItem(alphabets, parent, TVI_SORT);
			  //2. 알파벳 핸들 하위에 단어핸들 추가한다.
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->InsertItem(spelling, alphabetHandle, TVI_SORT);
			  //3. 알파벳 핸들 펼친다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);
			  //4. 해당 단어핸들을 선택된 상태로 처리한다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);

			  //현재 단어카드를 체크상태로 바꾼다.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, FALSE);
		  }



		  //2.2.9. 단어카드철 윈도우의 단어카드에 현재 단어카드를 출력한다.
		  spelling = CString(index->GetSpelling().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass = CString(index->GetWordClass().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
		  meaning = CString(index->GetMeaning().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
		  example = CString(index->GetExample().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

		  //2.2.5. 뽑기윈도우 종료한다.
		  EndDialog(0);
	  }
	  //2.3. '아니오'버튼 클릭했을 때
	  else if (ret == IDNO) {
		  //2.3.1. 뽑기윈도우 종료한다.
		  EndDialog(0);
	  }
}

