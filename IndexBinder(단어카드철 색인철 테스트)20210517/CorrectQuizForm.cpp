//CorrectQuizForm.cpp
#include"CorrectQuizForm.h"
#include"WordCardBinderForm.h"
#include"CorrectQuizBinder.h"
#include"WordCardBinder.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //Ʈ����Ʈ�� ��Ÿ��
#include<afxcmn.h> //Ʈ����

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

	//1. �����찡 ������ ��
	  //1.1. �ܾ�ī��ö �����츦 ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	  //1.2. �ܾ�ī��ö �������� ��������ö�� ���簳���� ���� ���,
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
	  //1.3. �ܾ�ī�� ���� ���, ���� ó���Ѵ�.
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

	//2. ù��°��ư Ŭ������ ��
	  //2.1. �ܾ�ī��ö ������ ã�´�.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//2.2. �ܾ�ī��ö �������� ��������ö���� ù��°�ܾ�ī�� ã�´�.
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

	//3. ������ư Ŭ������ ��
	  //3.1. �ܾ�ī��ö ������ ã�´�.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//3.2. �ܾ�ī��ö �������� ��������ö���� �����ܾ�ī�� ã�´�.
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

	//4. ������ư Ŭ������ ��
	  //4.1. �ܾ�ī��ö ������ ã�´�.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//4.2. �ܾ�ī��ö �������� ��������ö���� ���� �ܾ�ī�� ã�´�.
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

	//5. ������ư Ŭ������ ��
	  //5.1. �ܾ�ī��ö ������ ã�´�.
	wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	//5.2. �ܾ�ī��ö �������� ��������ö���� �����ܾ�ī�� ã�´�.
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

	//6. ���¹�ư Ŭ������ ��
	  //6.1. �ܾ�ī��ö ������ ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");

	  //6.2. �ܾ�ī��ö �������� ���� ����ö���� �����Ѵ�.
	  wordCardBinderForm->correctQuizBinder->Reset();

	  //6.3. ���� ����ö���� �ܾ�ī�� �� �̾Ƽ� �ܾ�ī��ö�� �ȴ´�.
	  index = wordCardBinderForm->correctQuizBinder->First();

	  while (index != previous) {
		  //�̱��� �̸� �� ���� ī�� ���س���-----------------------------------------------------------------------------------------------------
		  current = wordCardBinderForm->correctQuizBinder->Next();
		  previous = index;
		  //--------------------------------------------------------------------------------------------------------------------------------------
		  //�̱��� ó��(PuttingOutForm)
  
		  //��������ö���� �̴´�.
		  temp = index;
		  wordCard = wordCardBinderForm->correctQuizBinder->PutOut(index);
		  spelling = CString(wordCard.GetSpelling().c_str());

		  // ����ö���� �̴´�.
		  indexIndex = wordCardBinderForm->indexBinder->PutOut((LPCTSTR)spelling, temp);

		  //db���� delete�Ѵ�.
		  wordCardBinderForm->Delete(wordCard);

		  //������ ó��(PuttingForm)----------------------------------------------------------------------------------------------------------------

          //�ܾ�ī��ö�� �ȴ´�.
		  index = wordCardBinderForm->wordCardBinder->PutIn(wordCard);

		  // ����ö�� �ȴ´�.
		  indexIndex = wordCardBinderForm->indexBinder->PutIn(index);
		  spelling = CString(index->GetSpelling().c_str());

		  //db�� Insert�Ѵ�.
		  wordCardBinderForm->Insert(index);

		  //3.5. Ʈ���� �� ���� �ܾ��� alphabet �ڵ� ã�´�.
		  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);

		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(parent, TVGN_CHILD);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

		  while (alphabetHandle != NULL && alphabet != spelling[0] - 32) {
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(alphabetHandle, TVGN_NEXT);
			  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  }

		  //3.6.3.1. �ܾ��ڵ� ã�´�.
		  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(alphabetHandle, TVGN_CHILD);
		  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  while (word != spelling) {
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(wordHandle, TVGN_NEXT);
			  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  }

	
			  //3.6.2. ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
			  indexIndex->FindSpellings(index, &indexes, &count);

			  //3.6.3. ���ϴܾ� ������,
			  if (count > 1) {


				  //8.6.2. ǰ���ڵ� ã�´�.
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

				  //2. �ش� ǰ���ڵ��� ��üũ ���·� ó���Ѵ�.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle,FALSE);
			  }

			  //3.6.4. ���ϴܾ ������,
			  else {
				  //3.6.4.2. �ش� �ܾ��ڵ��� ��üũ ���·� ó���Ѵ�.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, FALSE);

			  }

			  if (indexes != NULL) {
				  delete[] indexes;
				  indexes = NULL;
		      }
		  


		  //�����---------------------------------------------------------------------------------------------------------------------------------
		  index = current;
		  //---------------------------------------------------------------------------------------------------------------------------------------
	  }
	  // ��������� 0���� �����ϱ�.


	  //6.4. ��������ö ������ ���� ó���Ѵ�.
	  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
	  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
	  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
	  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");

	  //6.5. �ܾ�ī��ö �����쿡 ù��° �ܾ�ī�带 �ܾ�ī�忡 ����Ѵ�.
	  index = wordCardBinderForm->wordCardBinder->First();

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
	  indexIndex->FindSpellings(index, &indexes, &count);

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

	  //6.6. ����īƮö ������ �����Ѵ�.
	  EndDialog(0);

}

void CorrectQuizForm::OnClose() {
	//7. �ݱ� ��ư�� Ŭ������ ��
	  //7.1. ��������ö �����츦 �ݴ´�.
	EndDialog(0);
}



















