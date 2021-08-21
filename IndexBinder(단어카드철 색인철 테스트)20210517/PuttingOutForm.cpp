//PuttingOutForm.cpp
#include"PuttingOutForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //Ʈ����Ʈ�� ��Ÿ��
#include<afxcmn.h> //Ʈ����

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

	//1. �̱������� ������ ��

	  //1.1. �ܾ�ī��ö�����츦 ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");

	  //1.2. �ܾ�ī��ö �������� ���� �ܾ�ī�� ��ġ �д´�.
	  index = wordCardBinderForm->wordCardBinder->GetCurrent();

	  //1.3. ���� �ܾ�ī���� ������ ã�´�.
	  spelling = CString(index->GetSpelling().c_str());
	  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);

	  //1.4. �ش� ���ο��� ���� �ܾ�� ���ϴܾ� �ִ��� Ȯ��.
	  indexIndex->FindSpellings(index, &indexes, &count);

	  //1.5. ���ϴܾ 3�� �̻��� ���, ���° ǰ������ Ȯ��.
	  if (count > 2) {
		  wordCardIndex = indexIndex->Find(index);
		  while (wordCardIndex != indexes[i]) {
			  i++; //i��° ǰ��
		  }
	  }

	  //1.6. �ܾ�ī��ö���� ���� �ܾ�ī�� �̴´�.
	  temp = index;
	  wordCard = wordCardBinderForm->wordCardBinder->PutOut(index);

	  //db���� delete�Ѵ�.
	  wordCardBinderForm->Delete(wordCard);

	  //1.7. ���� �ܾ�ī�带 �̱������� �ܾ�ī�忡 ����Ѵ�.
	  spelling = CString(wordCard.GetSpelling().c_str());
	  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	  wordClass = CString(wordCard.GetWordClass().c_str());
	  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  meaning = CString(wordCard.GetMeaning().c_str());
	  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	  example = CString(wordCard.GetExample().c_str());
	  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

	  //1.8. Ʈ���� �� ���ĺ� �ڵ� ã�´�.
	  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
		  ->GetNextItem(parent, TVGN_CHILD);
	  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  while (alphabet != spelling[0] - 32) {
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(alphabetHandle, TVGN_NEXT);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  }

	  //1.9. Ʈ���� �� �ܾ��ڵ� ã�´�.
	  wordHandle= ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
		  ->GetNextItem(alphabetHandle, TVGN_CHILD);
	  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	  while (word != spelling) {
		  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(wordHandle, TVGN_NEXT);
		  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	  }

	  //2.0. ���ϴܾ 3�� �̻��̾��� ���,
	  if (count > 2) {
		  //2.0.1. �ܾ��ڵ� ���� ǰ���ڵ� ã�´�.
		  wordClassHandle= ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(wordHandle, TVGN_CHILD);
		  while (j < i) {
			  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(wordClassHandle, TVGN_NEXT);
			  j++;
		  }

		  //2.0.2. �ش� ǰ���ڵ� ���ش�.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->DeleteItem(wordClassHandle);
	  }

	  //2.1. ���ϴܾ 2���� ���,
	  else if (count > 1 && count < 3) {
		  //2.1.0. ���� ����(���ϴܾ�) ī���� ox �˾Ƴ���.
		  if (i <= 0) { // ���� ī����ġ: 1
			  index = indexIndex->GetAt(indexes[1]);
		  }
		  else if (i >= 1) { //���� ī����ġ: 0
			  index = indexIndex->GetAt(indexes[0]);
		  }
		  //2.1.1. ǰ���ڵ� 2�� ��� ���ش�.
		  i = 0;
		  while (i < count) {
			  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(wordHandle, TVGN_CHILD);
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->DeleteItem(wordClassHandle);

			  i++;
		  }
		  ox = CString(index->GetOx().c_str());
		  if (ox == "o") {// �ܾ��ڵ鿡 üũ�Ѵ�.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle);
		  }
	  }

	  //2.2. ���ϴܾ ���� ���,
	  else if (count < 2) {
		  //2.2.1. �ܾ��ڵ� ���ش�.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->DeleteItem(wordHandle);
	  }

	  if (indexes != NULL) {
		  delete[] indexes;
		  indexes = NULL;
	  }

	  //2.3. �ܾ�ī��ö �������� ����ö���� �ش� �ܾ �̴´�.
	  indexIndex = wordCardBinderForm->indexBinder->PutOut((LPCTSTR)spelling, temp);

	  //2.4. ����ö�� �ش� ���ĺ� ���� ���� ���, Ʈ���� �� �ش� ���ĺ����� ���ش�.
	  if (indexIndex == NULL) {
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->DeleteItem(alphabetHandle);
	  }

	  //2.5. �ܾ�ī��ö �������� �ܾ�ī��ö���� ���� �ܾ�ī���� ��ġ�� �д´�.
	  index = wordCardBinderForm->wordCardBinder->GetCurrent();

	  //2.6. �ܾ �ִ� ���,
	  if (index != NULL) {
		  //2.6.1. Ʈ���� �� ���� �ܾ��� ���ĺ� �ڵ��� ã�´�.
		  spelling = CString(index->GetSpelling().c_str());
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(parent, TVGN_CHILD);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  while (alphabet != spelling[0] - 32) {
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(alphabetHandle, TVGN_NEXT);
			  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  }

		  //2.6.2. Ʈ���� �� ���ĺ� �ڵ� ��ģ��.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

		  //2.6.3. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
		  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(alphabetHandle, TVGN_CHILD);
		  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  while (spelling != word) {
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(wordHandle, TVGN_NEXT);
			  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
		  }

		  //2.6.4. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
		  indexIndex = wordCardBinderForm->indexBinder->Find((LPCTSTR)spelling);
		  indexIndex->FindSpellings(index, &indexes, &count);

		  //2.6.5. ���ϴܾ ������,
		  if (count > 1) {
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
		  //2.6.6. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
		  else {
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
		  }

		  //2.6.7. �ܾ�ī��ö �������� �ܾ�ī�忡 ���� �ܾ ����Ѵ�.
		  spelling = CString(index->GetSpelling().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass = CString(index->GetWordClass().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
		  meaning = CString(index->GetMeaning().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
		  example = CString(index->GetExample().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

		  //2.6.8. indexes �Ҵ������Ѵ�.
		  if (indexes != NULL) {
			  delete[] indexes;
			  indexes = NULL;
		  }

	  }

	  //2.7. �ܾ�ī�尡 ������ �ܾ�ī��ö �������� �ܾ�ī�带 ���� ó���Ѵ�.
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

	//2. �ݱ��ư Ŭ������ ��
	  //2.1. �޼����ڽ� ����.
	  ret = MessageBox("�����ðڽ��ϱ�?", "�˸�â", MB_YESNOCANCEL);

	  //2.2. '��'��ư Ŭ������ ��
	  if (ret == IDYES) {
		  //2.2.1. �ܾ�ī�� �д´�.
		  GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);
		  GetDlgItem(IDC_EDIT_WORDCLASS)->GetWindowText(wordClass);
		  GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);
		  GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);

		  //2.2.2. �ܾ�ī��ö ������ ã�´�.
		  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");

		  //2.2.3. �ܾ�ī��ö �������� �ܾ�ī��ö�� �ȴ´�.
		  WordCard wordCard((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
			  (LPCTSTR)spelling, (LPCTSTR)"", (LPCTSTR)"", (LPCTSTR)meaning, (LPCTSTR)"");
		  index = wordCardBinderForm->wordCardBinder->PutIn(wordCard);

		  //db���� Insert�Ѵ�.
		  wordCardBinderForm->Insert(index);

		  //2.2.4. �ܾ�ī��ö �������� ����ö�� �ش� �ܾ�ī�� �ȴ´�.
		  indexIndex = wordCardBinderForm->indexBinder->PutIn(index);
		  spelling = CString(index->GetSpelling().c_str());

		  //2.2.5. ���ĺ� ī�װ� �ڵ��� �����ش�.
		  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(parent, TVE_EXPAND);

		  //2.2.6. Ʈ���� �� ���� �ܾ��� ���ĺ� �ڵ� ã�´�.
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(parent, TVGN_CHILD);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  while (alphabetHandle != NULL && alphabet != spelling[0] - 32) {
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(alphabetHandle, TVGN_NEXT);
			  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
		  }

		  //2.2.7. ���ĺ� �ڵ��� �ִ� ���,
		  if (alphabetHandle != NULL) {
			  //1. ���ĺ� �ڵ� ��ģ��.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

			  //2. ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
			  indexIndex->FindSpellings(index, &indexes, &count);

			  //3. ���ϴܾ ������,
			  if (count > 1) {
				  //3.1. �ܾ��ڵ� ã�´�.
				  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->GetNextItem(alphabetHandle, TVGN_CHILD);
				  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				  while (word != spelling) {
					  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->GetNextItem(wordHandle, TVGN_NEXT);
					  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				  }
				  //3.2. ���ϴܾ 2���̸�,
				  if (count > 1 && count < 3) {
					  //1. �ش� �ܾ��ڵ��� üũ�Ǿ� �ִٸ�, uncheck ���ش�.
	                  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, FALSE);
				

					  //2. �ܾ��ڵ� ������ �̹� �����ִ� ù��° �ܾ��� ǰ�� �߰��Ѵ�.
					  first = indexIndex->GetAt(indexes[0]);
					  wordClass = CString(first->GetWordClass().c_str());
					  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->InsertItem(wordClass, wordHandle, TVI_LAST);

					  //3. üũ �Ǿ��־����� üũ���ش�.
					  ox = CString(first->GetOx().c_str());
					  if (ox == "o") {
						  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
							  ->SetCheck(wordClassHandle, TRUE);
					  }

					  //4. �ι�° �ܾ��� ǰ�� ���� �ܾ��ڵ� ������ �߰��Ѵ�.
					  wordClass = CString(index->GetWordClass().c_str());
					  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->InsertItem(wordClass, wordHandle, TVI_LAST);

					  //5. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
					  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

				  }
				  //3.3. ���ϴܾ 3���̸�
				  else if (count > 2) {
					  //1. �ܾ��ڵ� ������ ǰ���ڵ� �߰��Ѵ�.
					  wordClass = CString(index->GetWordClass().c_str());
					  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
						  ->InsertItem(wordClass, wordHandle, TVI_LAST);

					  //2. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
					  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

				  }
			  }
			  //4. ���ϴܾ ������,
			  else {
				  //4.1. ���ĺ� �ڵ� ������ �ܾ��ڵ� �߰��Ѵ�.
				  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->InsertItem(spelling, alphabetHandle, TVI_LAST);
				  //4.2. �ش� �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);

			  }

			  if (indexes != NULL) {
				  delete[] indexes;
				  indexes = NULL;
			  }
		  }

		  //2.2.8. ���ĺ��ڵ� ���� ���,
		  else {
			  //1. ���ĺ� ī�װ� �ڵ� ������ ���ĺ� �ڵ� �߰��Ѵ�.
			  alphabets[0] = spelling[0] - 32;
			  alphabets[1] = '\0';
			  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->InsertItem(alphabets, parent, TVI_SORT);
			  //2. ���ĺ� �ڵ� ������ �ܾ��ڵ� �߰��Ѵ�.
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->InsertItem(spelling, alphabetHandle, TVI_SORT);
			  //3. ���ĺ� �ڵ� ��ģ��.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);
			  //4. �ش� �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);

			  //���� �ܾ�ī�带 üũ���·� �ٲ۴�.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, FALSE);
		  }



		  //2.2.9. �ܾ�ī��ö �������� �ܾ�ī�忡 ���� �ܾ�ī�带 ����Ѵ�.
		  spelling = CString(index->GetSpelling().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
		  wordClass = CString(index->GetWordClass().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
		  meaning = CString(index->GetMeaning().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
		  example = CString(index->GetExample().c_str());
		  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

		  //2.2.5. �̱������� �����Ѵ�.
		  EndDialog(0);
	  }
	  //2.3. '�ƴϿ�'��ư Ŭ������ ��
	  else if (ret == IDNO) {
		  //2.3.1. �̱������� �����Ѵ�.
		  EndDialog(0);
	  }
}

