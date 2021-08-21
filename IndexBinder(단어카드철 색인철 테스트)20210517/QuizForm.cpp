//QuizForm.cpp
#include"QuizForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"CorrectQuizBinder.h"
#include"IncorrectQuizForm.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //Ʈ����Ʈ�� ��Ÿ��
#include<afxcmn.h> //Ʈ����

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



	//1. �����찡 ������ ��
	 //1.1. �ܾ�ī��ö �����츦 ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");

	  //1.2. �ܾ�ī��ö���� ������ ã�´�.
	  this->nextQuiz = wordCardBinderForm->wordCardBinder->First();
	  testLength = wordCardBinderForm->wordCardBinder->GetLength();

	  //1.3. ������ ������ ���� ö�ڸ� ����Ѵ�.
	  if (testLength>0 &&  this->nextQuiz != NULL) {
		  spelling = CString(this->nextQuiz->GetSpelling().c_str());
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass= CString(this->nextQuiz->GetWordClass().c_str());
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  }
	  //1.4. ������ ������,
	  else {
		  //1.4.1. �޼����� ����Ѵ�.
		  ret = MessageBox("�� �̻� ������ �����ϴ�. �����Ͻðڽ��ϱ�?", "�˸�â", MB_YESNOCANCEL);

		  //1.4.2. '��'��ư Ŭ������ ��
		  if (ret == IDYES) {
			  //1.4.2.1. �ܾ�ī��ö �������� ��������ö���� �����Ѵ�.
			  wordCardBinderForm->correctQuizBinder->Reset();
			  //1.4.2.2. ��������ö�� ó������ ������ �ݺ��Ѵ�.
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
					  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle, FALSE);
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

			  //6.5. �ܾ�ī��ö �����쿡 ù��° �ܾ�ī�带 �ܾ�ī�忡 ����Ѵ�.
			  index = wordCardBinderForm->wordCardBinder->First();

			  spelling = CString(index->GetSpelling().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			  wordClass = CString(index->GetWordClass().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
			  meaning = CString(index->GetMeaning().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
			  example = CString(index->GetExample().c_str());
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
			  //�ܾ�ī��ö �������� ��������ö ���簳���� 0���� �����Ѵ�.
	
			  //1.4.2.3. �ܾ�ī��ö �������� �ܾ�ī��ö���� ������ ã�´�.
			  this->nextQuiz = wordCardBinderForm->wordCardBinder->First();

			  //1.4.2.4. ����ö�ڸ� ����Ѵ�.
			  spelling = CString(this->nextQuiz->GetSpelling().c_str());
			  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			  wordClass = CString(this->nextQuiz->GetWordClass().c_str());
			  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
		  }
		  //1.4.3. '�ƴϿ�'��ư Ŭ������ ��
		  else if (ret == IDNO) {
			  //1.4.3.1. ���������� �����Ѵ�.
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


	//2. ���� ��ư Ŭ������ ��
	  //2.1. �ܾ�ī��ö ������ ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");
	  //2.2. ���������쿡�� ���� ������ ��ġ�� �д´�.
	  index = this->nextQuiz;
	  //2.3. �ǹ̸� �д´�.
	  GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);
	  //2.4. ������ Ǭ��.
	  ret = wordCardBinderForm->wordCardBinder->SpellingQuiz((LPCTSTR)meaning, index);
	  //db������ ������ Ǭ��(�����Ѵ�.)
	  wordCardBinderForm->Modify(index);
	  

	  //2.5. ���� ������ �̸� ���س��´�.
	  this->nextQuiz = wordCardBinderForm->wordCardBinder->NextQuiz();
	  
	  //2.6. ��� �¾��� ���,
	  if (ret == true) {
		  //------------------------------------------------------------------------------
		  //�̱��� ó��(PuttingOutForm)
			//2.6.1. �ܾ�ī��ö���� �̴´�.
		  temp = index;
		  wordCard = wordCardBinderForm->wordCardBinder->PutOut(index);
		  spelling = CString(wordCard.GetSpelling().c_str());

		  // ����ö���� �̴´�.
		  indexIndex = wordCardBinderForm->indexBinder->PutOut((LPCTSTR)spelling, temp);

		  //db���� delete�Ѵ�.
		  wordCardBinderForm->Delete(wordCard);



		  //�ȴ� ó��(PuttingForm)------------------------------------------------------------------------

		  //2.6.2. ��������ö�� �ȴ´�.
		  index = wordCardBinderForm->correctQuizBinder->PutIn(wordCard);

		  // ����ö�� �ȴ´�.
		  indexIndex = wordCardBinderForm->indexBinder->PutIn(index);
		  spelling = CString(index->GetSpelling().c_str());

		  //db�� Insert�Ѵ�.
		  wordCardBinderForm->Insert(index);


		  //�ܾ��ڵ� �Ǵ� ǰ���ڵ��� ã�´�.
		  //-------------------------------------------------------------------------------------------------------
			 //8.2. Ʈ���� �� ���� �ܾ��� ���ĺ��ڵ� ã�´�.
		  spelling = CString(index->GetSpelling().c_str());

		  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

		  while (alphabet != spelling[0] - 32) {
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
			  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  }

		  //8.6.3. ���ĺ��ڵ� �����ش�.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

		  //8.4. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
		  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
		  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  while (spelling != word) {
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
			  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  }

		  //8.5. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
		  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);
		  indexIndex->FindSpellings(index, &indexes, &count);

		  //8.6. ���ϴܾ� ������,
		  if (count > 1) { //ǰ���ڵ��� ã���ش�.

			  //8.6.2. ǰ���ڵ� ã�´�.
			  wordClass = CString(index->GetWordClass().c_str());
			  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
			  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

			  while (wordClassText != wordClass) {
				  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->GetNextItem(wordClassHandle, TVGN_NEXT);
				  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
			  }
			  //8.6.3. �ܾ��ڵ� �����ش�.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);


			  //�ش� ǰ���ڵ��� üũ�� �����Ѵ�.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle, TRUE);

		  }
		  //8.7. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
		  else {
			  //�ش� �ܾ��ڵ��� üũ�� �����Ѵ�.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
		  }

		  if (indexes != NULL) {
			  delete[] indexes;
			  indexes = NULL;
		  }

		  //-------------------------------------------------------------------------------


		  //2.6.3. �ܾ�ī��ö �����쿡 ���� �ܾ�ī�尡 �ִ��� Ȯ���Ѵ�.
		  index = wordCardBinderForm->wordCardBinder->GetCurrent();
		  //2.6.4. ���� ī�尡 ������ �ܾ�ī��ö �������� �ܾ�ī��ö�� ����Ѵ�.
		  if (index != NULL) {

			  //���� ī���� ������ ã�� ���� ó���Ѵ�.
			  //-------------------------------------------------------
			  //8.2. Ʈ���� �� ���� �ܾ��� ���ĺ��ڵ� ã�´�.
			  spelling = CString(index->GetSpelling().c_str());

			  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
			  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

			  while (alphabet != spelling[0] - 32) {
				  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
				  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
			  }

			  //8.3. Ʈ���� �� ���ĺ� �ڵ� ��ģ��.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

			  //8.4. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
			  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  while (spelling != word) {
				  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
				  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  }

			  //8.5. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
			  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);
			  indexIndex->FindSpellings(index, &indexes, &count);

			  //8.6. ���ϴܾ� ������,
			  if (count > 1) { //ǰ���ڵ��� ã���ش�.

				  //8.6.2. ǰ���ڵ� ã�´�.
				  wordClass = CString(index->GetWordClass().c_str());
				  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
				  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

				  while (wordClassText != wordClass) {
					  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
					  wordClassText = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
				  }

				  //8.6.3. �ܾ��ڵ� �����ش�.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
				  //8.6.4. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

			  }
			  //8.7. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
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
		  //2.6.5. ���� ī�尡 ������ ���� ó���Ѵ�.
		  else {
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");
			  wordCardBinderForm->GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText("");
		  }


	  }

	  //2.7. ���������� ������,
	  if (this->nextQuiz != NULL) {
		  //2.7.1. ����ö�ڸ� ����Ѵ�.
		  spelling = CString(this->nextQuiz->GetSpelling().c_str());
		  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass = CString(this->nextQuiz->GetWordClass().c_str());
		  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);

		  //2.7.2. �ǹ̸� ����ó���Ѵ�.
		  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
	  }
	  //2.8. ���������� ������,
	  else {
		  //2.8.1. �޼����ڽ� ����Ѵ�.
		  ret_ = MessageBox("������ �����Դϴ�. ����� Ȯ���غ��ðڽ��ϱ�?", "�˸�â", MB_YESNOCANCEL);
		  //2.8.2. '��'��ư Ŭ������ ��
		  if (ret_ == IDYES) {
			  //2.8.2.2. ���������� �����Ѵ�.
			  EndDialog(0);

			  //2.8.2.1. ���������츦 ����Ѵ�.
			  IncorrectQuizForm incorrectQuizForm;
			  incorrectQuizForm.DoModal();


		  }
		  //2.8.3. '�ƴϿ�'��ư Ŭ������ ��
		  else if (ret_ == IDNO) {
			  //2.8.3.1. ���������� �����Ѵ�.
			  EndDialog(0);
		  }
	  }

}


void QuizForm::OnClose() {
	int ret;

	//3. �ݱ��ư Ŭ��������
	  //3.1. �޼����ڽ� ����Ѵ�.
	  ret = MessageBox("����� Ȯ���غ��ðڽ��ϱ�?", "�˸�â", MB_YESNOCANCEL);
	  //3.2. '��'��ư Ŭ������ ��
	  if (ret == IDYES) {
		  //3.2.2. ���������� �����Ѵ�.
		  EndDialog(0);

		  //3.2.1. ���������� ����Ѵ�.
		  IncorrectQuizForm incorrectQuizForm;
		  incorrectQuizForm.DoModal();
	  }

	  //3.3. '�ƴϿ�'��ư Ŭ������ ��
	  else if (ret == IDNO) {
		  //3.3.1. ���������� �����Ѵ�.
		  EndDialog(0);
	  }
}















