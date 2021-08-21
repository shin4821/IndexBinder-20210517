//PuttingForm.cpp
#include"PuttingForm.h"
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"IndexBinder.h"
#include<CommCtrl.h> //Ʈ����Ʈ�� ��Ÿ��
#include<afxcmn.h> //Ʈ����

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
	TCHAR wordClasses[][8] = { "���","����","�����","�λ�","����","���ӻ�","��ġ��","��ź��" };
	Long i;

	//1. �ȱ������� ������ ��
	  //1.1. �޺��ڽ� ��Ͽ� ǰ�縦 �߰��Ѵ�.
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

	//2. ö�ڿ��� ��Ŀ���� ���� ��
	  //2.1. ö�ڸ� �д´�.
	  GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);

	  //2.2. �ܾ�ī��ö �����츦 ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");

	  //2.3. �ܾ�ī��ö�������� �ܾ�ī��ö�� �ش� ö�ڿ� ������ ö�ڰ� ���� ��� ����Ѵ�.
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

	//3. �ȱ��ư Ŭ������ ��
	  //3.1. �ܾ�ī�� �д´�.
	  GetDlgItem(IDC_EDIT_SPELLING)->GetWindowText(spelling);
	  GetDlgItem(IDC_EDIT_WORDCLASS)->GetWindowText(wordClass);
	  GetDlgItem(IDC_EDIT_MEANING)->GetWindowText(meaning);
	  GetDlgItem(IDC_EDIT_EXAMPLE)->GetWindowText(example);

	  //3.2. �ܾ�ī��ö ������ ã�´�.
	  wordCardBinderForm = (WordCardBinderForm*)CWnd::FindWindow("#32770", "�ܾ�ī��ö");

	  //3.3. �ܾ�ī��ö �������� �ܾ�ī��ö�� �ȴ´�.
	  WordCard wordCard((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
		  (LPCTSTR)spelling, (LPCTSTR)"", (LPCTSTR)"", (LPCTSTR)meaning, (LPCTSTR)"");

	  index = wordCardBinderForm->wordCardBinder->PutIn(wordCard);

	  //db�� Insert�Ѵ�.
	  wordCardBinderForm->Insert(index);

	  //3.4. ����ö�� �ش� �ܾ�ī�� �ȴ´�.
	  indexIndex = wordCardBinderForm->indexBinder->PutIn(index);
	  spelling = CString(index->GetSpelling().c_str());

	  //���ĺ� ī�װ� �ڵ��� �����ش�.
	  parent = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(parent, TVE_EXPAND);

	  //3.5. Ʈ���� �� ���� �ܾ��� alphabet �ڵ� ã�´�.
	  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
		  ->GetNextItem(parent, TVGN_CHILD);
	  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  while (alphabetHandle != NULL && alphabet != spelling[0] - 32) {
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->GetNextItem(alphabetHandle, TVGN_NEXT);
		  alphabet = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	  }
	  //3.6. ���ĺ� �ڵ��� �ִ� ���,
	  if (alphabetHandle != NULL) {
		  //3.6.1. ���ĺ� �ڵ� ��ģ��.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);
		  
		  //3.6.2. ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
		  indexIndex->FindSpellings(index, &indexes, &count);

		  //3.6.3. ���ϴܾ� ������,
		  if (count > 1) {
			  //3.6.3.1. �ܾ��ڵ� ã�´�.
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->GetNextItem(alphabetHandle, TVGN_CHILD);
			  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  while (word != spelling) {
				  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->GetNextItem(wordHandle, TVGN_NEXT);
				  word = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  }

			  //�ܾ��ڵ� �����ش�.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);

			  //3.6.3.2. ���ϴܾ 2���̸�,
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
					  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES)) ->SetCheck(wordClassHandle, TRUE);
				  }


				  //4. �ι�° �ܾ��� ǰ�� ���� �ܾ��ڵ� ������ �߰��Ѵ�.
				  wordClass = CString(index->GetWordClass().c_str());
				  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->InsertItem(wordClass, wordHandle, TVI_LAST);

				  //5. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
			  }
			  //3.6.3.3. ���ϴܾ 3�� �̻��̸�,
			  else if (count > 2) {
				  //1. �ܾ��ڵ� ������ ǰ���ڵ� �߰��Ѵ�.
				  wordClass = CString(index->GetWordClass().c_str());
				  wordClassHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
					  ->InsertItem(wordClass, wordHandle, TVI_LAST);

				  //2. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
				  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
			  }
		  }

		  //3.6.4. ���ϴܾ ������,
		  else {
			  //3.6.4.1. ���ĺ� �ڵ� ������ �ܾ��ڵ� �߰��Ѵ�.
			  wordHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
				  ->InsertItem(spelling, alphabetHandle, TVI_LAST);
			  //3.6.4.2. �ش� �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
		  }
	  }

	  if (indexes != NULL) {
		  delete[] indexes;
		  indexes = NULL;
	  }
	 
	  //3.7. ���ĺ� �ڵ� ���� ���,
	  else {
		  //3.7.1. ���ĺ� ī�װ� �ڵ� ������ ���ĺ� �ڵ� �߰��Ѵ�.
		  alphabets[0] = spelling[0]-32;
		  alphabets[1] = '\0';
		  alphabetHandle = ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->InsertItem(alphabets, parent, TVI_SORT);

		  //3.7.2. ���ĺ� �ڵ� ������ �ܾ��ڵ� �߰��Ѵ�.
		  wordHandle= ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))
			  ->InsertItem(spelling, alphabetHandle, TVI_SORT);
		 
#if 0
		  if (spelling == "apple") {
			  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
		  }
#endif



		  //3.7.3. ���ĺ� �ڵ� ��ģ��.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);
		  //3.7.4. �ش� �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
		  ((CTreeCtrl*)wordCardBinderForm->GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
	  }

	  //3.4. ���� �ܾ�ī�带 �ܾ�ī��ö �����쿡 ����Ѵ�.
	  spelling = CString(index->GetSpelling().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	  wordClass = CString(index->GetWordClass().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	  meaning = CString(index->GetMeaning().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	  example = CString(index->GetExample().c_str());
	  wordCardBinderForm->GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);

	  //3.5. �ȱ������� �����Ѵ�.
	  EndDialog(0);
}

void PuttingForm::OnClose() {
	//4. �ݱ��ư Ŭ������ ��
	  //4.1. �ȱ������� �����Ѵ�.
	EndDialog(0);

}














