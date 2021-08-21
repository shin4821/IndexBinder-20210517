//WordCardBinderForm.cpp
#include"WordCardBinderForm.h"
#include"WordCardBinder.h"
#include"CorrectQuizBinder.h"
#include"PuttingForm.h"
#include"FindingForm.h"
#include"PuttingOutForm.h"
#include"QuizForm.h"
#include"IncorrectQuizForm.h"
#include"CorrectQuizForm.h"
#include"ImportantWordsForm.h"
#include"IndexBinder.h"

#include<CommCtrl.h> //Ʈ����Ʈ�� ��Ÿ��
#include<afxcmn.h> //Ʈ����
#include<afxdb.h>
#include<ctime>
#include<cstdio>

#define WM_USER_TREE_CHANGE_CHECK (WM_USER + 100)

#pragma warning(disable:4996)



BEGIN_MESSAGE_MAP(WordCardBinderForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PUT, OnPutButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PUTOUT, OnPutOutButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_QUIZ, OnQuizButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECTQUIZ, OnCorrectQuizButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_IMPORTANTWORDS, OnImportantWordsButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnFirstButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnLastButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PUTIMPORTANTWORD, OnPutImportantWordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_PUTOUTIMPORTANTWORD, OnPutOutImportantWordButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_INDEXES, OnTreeViewItemDoubleClicked)
	ON_NOTIFY(NM_CLICK, IDC_TREE_INDEXES, OnTreeViewCheckBoxClicked)

	ON_MESSAGE(WM_USER_TREE_CHANGE_CHECK, OnTreeChangeCheck)

	ON_WM_CLOSE()
END_MESSAGE_MAP()






WordCardBinderForm::WordCardBinderForm(CWnd* parent)
	:CDialog(WordCardBinderForm::IDD, parent) {
	this->wordCardBinder = NULL;
	this->correctQuizBinder = NULL;
	this->indexBinder = NULL;
}
CString WordCardBinderForm::GetQuizCode() {
	CString sql = "SELECT quizCode FROM Quiz ORDER BY quizCode DESC;";
	CDatabase db;
	CRecordset rs(&db);
	time_t timer;
	struct tm* today;
	CString todayDate;
	CString todayDate_;
	CString year;
	CString year_;
	CString number;
	int number_;
	CString quizCode;
	CString quizCode_;

	//1. ���� ��¥�� 6�ڸ��� ���س��´�.
	time(&timer);
	today = localtime(&timer);
	year.Format("%4d", today->tm_year + 1900); //2021
	year_ = year.Right(2); //21
	todayDate.Format("%s%02d%02d", year_, today->tm_mon + 1, today->tm_mday); //210506

	//2. �⺻ �ڵ� �������´�.
	quizCode.Format("Q%s001", todayDate); //Q210506001

	//3. quizCode�� ���������Ͽ� ù��° �ڵ带 ���Ѵ�.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	//4. �����Ͱ� ������ ù��° �ڵ带 ���Ѵ�.
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, quizCode_);
		//�ڵ尡 ���ó�¥ �ڵ����� Ȯ���Ѵ�.
		todayDate_ = quizCode_.Mid(1, 6); //210504

		//4.1. �� �ڵ尡 ���� ��¥�� ���,
		if (todayDate == todayDate_) {
			//4.1.1. �ǵ� ���ڸ� ���ںκ��� �и��Ѵ�.
			number = quizCode_.Right(3); //004
			//4.1.2. ���ںκ��� �����ιٲ۴�.
			number_ = _ttoi(number);
			//4.1.3. 1�� �����ش�.
			number_++;
			//4.1.4. ���� ��¥�� �����κ��� ��ģ��.(���� �ڵ带 �����.)
			quizCode.Format("Q%s%03d", todayDate, number_);
		}
	}
	//5. �ڵ带 ����Ѵ�.
	rs.Close();
	db.Close();
	
	return quizCode;
}
CString WordCardBinderForm::GetCode() {
	CString sql = "SELECT code FROM Word ORDER BY code DESC;";
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	CString code_;
	time_t timer;
	struct tm* today;
	CString todayDate;
	CString todayDate_;
	CString year;
	CString year_;
	CString number;
	int number_;

	//1. ���ó�¥�� 6�ڸ��� ���س��´�.
	time(&timer);
	today = localtime(&timer);
	year.Format("%4d", today->tm_year + 1900); //2021
	year_ = year.Right(2); //21
	todayDate.Format("%s%02d%02d", year_, today->tm_mon + 1, today->tm_mday); //210506

	//2. �⺻�ڵ� �������´�. 
	code.Format("W%s001", todayDate); //W210506001

	//3. code�� ���������Ͽ� ù��° �ڵ带 ���Ѵ�.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	
	//4. ������ ������
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code_);
		//4.1. �ڵ尡 ���� ��¥ �ڵ����� Ȯ���Ѵ�.
		todayDate_ = code_.Mid(1, 6);
		//4.2. ���� ��¥ �ڵ��� ���,
		if (todayDate == todayDate_) {
			//4.2.1. �� �� ���ڸ� ���ںκ��� �и��Ѵ�.
			number = code_.Right(3);
			//4.2.2. ���ںκ��� ������ �ٲ۴�.
			number_ = _ttoi(number);
			//4.2.3. 1�� �����ش�.
			number_++;
			//4.2.4. ���ó�¥�� �����κ��� ���Ѵ�.
			code.Format("W%s%03d", todayDate, number_);
		}
	}
	//5.�ڵ带 ����Ѵ�.
	rs.Close();
	db.Close();

	return code;
}
void WordCardBinderForm::Save() {
	CString sql = "SELECT Word.code, Quiz.quizCode FROM Word INNER JOIN Quiz ON Word.code = Quiz.code"
		" WHERE Quiz.ox ='x' OR Quiz.ox='';";
	CDatabase db;
	CRecordset rs(&db);
	CString sql1="SELECT Word.code, Quiz.quizCode FROM Word INNER JOIN Quiz ON Word.code = Quiz.code"
		" WHERE Quiz.ox ='o';";
	CRecordset rs1(&db);
	CString code;
	CString quizCode;
	WordCard* it;
	WordCard* previous = NULL;
	CString example;

	//1. sql, sql1 ������.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs1.Open(AFX_DB_USE_DEFAULT_TYPE, sql1);
	
	//2. ��ü ������ �����.

	db.ExecuteSQL("DELETE FROM Quiz");
	db.ExecuteSQL("DELETE FROM Word");


	//3. �ܾ�ī��ö�� ó������ ������ �ݺ��Ѵ�.
	it = this->wordCardBinder->First();
	while (!rs.IsEOF() && it != previous) {
		//3.1. code, quizCode ���Ѵ�.
		rs.GetFieldValue((short)0, code);
		rs.GetFieldValue((short)1, quizCode);
		example = it->GetExample().c_str();
		example.Replace("'", "\\'");

		//3.3. �ܾ� Insert�Ѵ�.
		sql.Format("INSERT INTO Word(code, spelling, wordClass, meaning, example) VALUES('%s','%s','%s',"
			"'%s','%s');", (LPCTSTR)code, it->GetSpelling().c_str(), it->GetWordClass().c_str(),
			it->GetMeaning().c_str(), (LPCTSTR)example);
		db.ExecuteSQL(sql);


		//3.2. ���� Insert�Ѵ�.
		sql.Format("INSERT INTO Quiz(code, quizCode, answer, ox, isImportant) VALUES('%s','%s','%s','%s','%s');",
			(LPCTSTR)code, (LPCTSTR)quizCode, it->GetAnswer().c_str(), it->GetOx().c_str(), 
			it->GetIsImportant().c_str()
		);
		db.ExecuteSQL(sql);



		rs.MoveNext();
		previous = it;
		it = this->wordCardBinder->Next();
	}
	rs.Close();

	//4. ��������ö�� ó������ ������ �ݺ��Ѵ�.
	previous = NULL;
	it = this->correctQuizBinder->First();
	while (!rs1.IsEOF() && it != previous) {
		//4.1. code, quizCode ���Ѵ�.
		rs1.GetFieldValue((short)0, code);
		rs1.GetFieldValue((short)1, quizCode);
		example = it->GetExample().c_str();
		example.Replace("'", "\\'");

		//4.3. �ܾ� Insert�Ѵ�.
		sql1.Format("INSERT INTO Word(code, spelling, wordClass, meaning, example) VALUES('%s','%s','%s',"
			"'%s','%s');", (LPCTSTR)code, it->GetSpelling().c_str(),
			it->GetWordClass().c_str(), it->GetMeaning().c_str(), (LPCTSTR)example);
		db.ExecuteSQL(sql1);


		//4.2. ���� Insert�Ѵ�.
		sql1.Format("INSERT INTO Quiz(code, quizCode, answer, ox, isImportant) VALUES('%s', '%s','%s','%s','%s');",
			(LPCTSTR)code, (LPCTSTR)quizCode, it->GetAnswer().c_str(), it->GetOx().c_str(), 
			it->GetIsImportant().c_str());
		db.ExecuteSQL(sql1);


		rs1.MoveNext();
		previous = it;
		it = this->correctQuizBinder->Next();
	}
	rs1.Close();

	db.Close();
}
void WordCardBinderForm::Load() {
	CString sql = "SELECT Word.spelling, Word.wordClass, Word.meaning, Word.example, Quiz.answer, Quiz.ox, "
		"Quiz.isImportant FROM Quiz INNER JOIN Word ON Quiz.code = Word.code WHERE Quiz.ox='x' OR "
		"Quiz.ox='';";
	CDatabase db;
	CRecordset rs(&db);
	CString sql1 = "SELECT Word.spelling, Word.wordClass, Word.meaning, Word.example, Quiz.answer, Quiz.ox, "
		"Quiz.isImportant FROM Quiz INNER JOIN Word ON Quiz.code=Word.code WHERE Quiz.ox='o';";
	CRecordset rs1(&db);
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString answer;
	CString ox;
	CString isImportant;

	//1. sql, sql1 ������.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs1.Open(AFX_DB_USE_DEFAULT_TYPE, sql1);

	//2. rs�� ���� �ƴѵ��� �ݺ��Ѵ�.
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, spelling);
		rs.GetFieldValue((short)1, wordClass);
		rs.GetFieldValue((short)2, meaning);
		rs.GetFieldValue((short)3, example);
		rs.GetFieldValue((short)4, answer);
		rs.GetFieldValue((short)5, ox);
		rs.GetFieldValue((short)6, isImportant);

		//2.1. �ܾ�ī��ö�� �ȴ´�.
		WordCard wordCard((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
			(LPCTSTR)spelling, (LPCTSTR)answer, (LPCTSTR)ox, (LPCTSTR)meaning, (LPCTSTR)isImportant);
		this->wordCardBinder->PutIn(wordCard);
		
		rs.MoveNext();
	}
	rs.Close();

	//3. rs1�� ���� �ƴѵ��� �ݺ��Ѵ�.
	while (!rs1.IsEOF()) {
		rs1.GetFieldValue((short)0, spelling);
		rs1.GetFieldValue((short)1, wordClass);
		rs1.GetFieldValue((short)2, meaning);
		rs1.GetFieldValue((short)3, example);
		rs1.GetFieldValue((short)4, answer);
		rs1.GetFieldValue((short)5, ox);
		rs1.GetFieldValue((short)6, isImportant);

		//3.1. ��������ö�� �ȴ´�.
		WordCard wordCard((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
			(LPCTSTR)spelling, (LPCTSTR)answer, (LPCTSTR)ox, (LPCTSTR)meaning, (LPCTSTR)isImportant);
		this->correctQuizBinder->PutIn(wordCard);

		rs1.MoveNext();
	}
	rs1.Close();
	db.Close();
}
void WordCardBinderForm::Insert(WordCard* index) {
	CString sql;
	CDatabase db;
	CString code;
	CString quizCode;
	CString example;

	//1. code, quizCode ���Ѵ�.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	code = GetCode();
	quizCode = GetQuizCode();
	example = index->GetExample().c_str();
	example.Replace("'", "\\'");

	//3. �ܾ� Insert �Ѵ�.
	sql.Format("INSERT INTO Word(code, spelling, wordClass, meaning, example) VALUES('%s','%s','%s',"
		"'%s','%s');", (LPCTSTR)code, index->GetSpelling().c_str(),
		index->GetWordClass().c_str(), index->GetMeaning().c_str(), (LPCTSTR)example);
	db.ExecuteSQL(sql);


	//2. ���� Insert �Ѵ�.
	sql.Format("INSERT INTO Quiz(code, quizCode, answer, ox, isImportant) VALUES('%s','%s','%s','%s','%s');", 
		(LPCTSTR)code, (LPCTSTR)quizCode, index->GetAnswer().c_str(), index->GetOx().c_str(), 
		index->GetIsImportant().c_str());
	db.ExecuteSQL(sql);



	db.Close();
}
void WordCardBinderForm::Delete(WordCard wordCard) {
	CString sql;
	CString example = wordCard.GetExample().c_str();
	example.Replace("'", "\\'");
	sql.Format("SELECT code FROM Word WHERE spelling='%s' AND wordClass='%s' AND meaning='%s' AND "
		"example='%s';", wordCard.GetSpelling().c_str(), wordCard.GetWordClass().c_str(),
		wordCard.GetMeaning().c_str(), (LPCTSTR)example);
	CDatabase db;
	CRecordset rs(&db);
	CString code;

	//1. �ش� index�� code�� ã�´�.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs.GetFieldValue((short)0, code);

	//3. �ش� code�� ����� �����.
	sql.Format("DELETE FROM Quiz WHERE code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);

	//2. �ش� code�� �ܾ�� �����.
	sql.Format("DELETE FROM Word WHERE code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);

	//4. ������.
	rs.Close();
	db.Close();
}
void WordCardBinderForm::Modify(WordCard* index) {
	CString sql;
	CString example = index->GetExample().c_str();
	example.Replace("'", "\\'");

	sql.Format("SELECT code FROM Word WHERE spelling='%s' AND wordClass='%s' AND meaning='%s' AND "
		"example='%s';", index->GetSpelling().c_str(), index->GetWordClass().c_str(),
		index->GetMeaning().c_str(), (LPCTSTR)example);

	CDatabase db;
	CRecordset rs(&db);
	CString code;

	//1.code ã�´�.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs.GetFieldValue((short)0, code);

	//2. �ش� �ڵ带 ������Ʈ�Ѵ�.
	sql.Format("UPDATE Quiz SET answer='%s', ox='%s', isImportant='%s' WHERE code='%s';",
		index->GetAnswer().c_str(), index->GetOx().c_str(), index->GetIsImportant().c_str(), (LPCTSTR)code);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();
}

BOOL WordCardBinderForm::OnInitDialog() {
	CDialog::OnInitDialog();

	Long count;
	WordCard* index;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString isImportant;
	CString ox;
	CString alphabet;
	HTREEITEM parent;
	HTREEITEM wordHandle;
	HTREEITEM alphabetHandle;
	HTREEITEM wordClassHandle;
	Long wLength;
	Long cLength;
	Long iLength;
	WordCard* previous = NULL;
	Index(*indexes);
	TCHAR textAlphabets[2];
	TCHAR alphabets[2];
	CString word;
	Long i = 0;
	Long j;
	Long k;
	Long indexLength;
	Long(*sameIndexes) = NULL;
	Long sameCount;
	Long wordCardIndex;
	Index* indexIndex;
	BOOL setCheck;
	BOOL selectCheck;
	BOOL ret;
	WordCard* first;

	//1. �����찡 ������ ��
	  //1.1. �ܾ�ī��ö �����.
	  this->wordCardBinder = new WordCardBinder;
	  //1.2. ��������ö �����.
	  this->correctQuizBinder = new CorrectQuizBinder;
	  //1.3. ����ö �����.
	  this->indexBinder = new IndexBinder;

	  //1.4. Ʈ���信 ���ĺ� ī�װ� �ڵ��� �����.
	  parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem("���ĺ�", TVI_ROOT, TVI_LAST);
	  

	  //1.5. ��������ö, �ܾ�ī��ö�� �����Ѵ�.
	  Load();


	  //1.6. �ܾ�ī��ö �ܾ�ī�尡 1�� �̻��� ���,
	  wLength = this->wordCardBinder->GetLength();
	  if (wLength > 0) {
		  index = this->wordCardBinder->First();
		  //1.6.1 �ܾ�ī��ö�� ���� �ƴѵ��� �ݺ��Ѵ�.
		  while (index != previous) {
			  //1.6.1.1. ����ö�� �����.
			  this->indexBinder->PutIn(index);

			  previous = index;
			  index = this->wordCardBinder->Next();
		  }
	  }

	  //1.7. ��������ö �ܾ 1�� �̻��� ���,

	  cLength = this->correctQuizBinder->GetLength();
	  if (cLength > 0) {
		  previous = NULL;
		  index = this->correctQuizBinder->First();
		  //1.7.1. ��������ö�� ���� �ƴѵ��� �ݺ��Ѵ�.
		  while (index != previous) {
			  //1.7.1.1. ����ö�� �����.
			  this->indexBinder->PutIn(index);

			  previous = index;
			  index = this->correctQuizBinder->Next();
		  }
	  }

	  //Ʈ���� �ʱ�ȭ
	  GetDlgItem(IDC_TREE_INDEXES)->ModifyStyle(TVS_CHECKBOXES, 0);
	  GetDlgItem(IDC_TREE_INDEXES)->ModifyStyle(0, TVS_CHECKBOXES);


	
	  //1.8. ����ö�� ������ 1�� �̻��� ���,
	  if (wLength > 0 || cLength > 0) { //Ʈ���� �ڵ� �߰� ����
		  //1.8.1. ���θ���Ʈ�� �����.
		  this->indexBinder->MakeList(&indexes, &count);

		  //1.8.2. ���θ���Ʈ ������ŭ �ݺ��Ѵ�.
		  while (i < count) {
			  //1.8.2.1. ���ĺ� ī�װ� �ڵ� ������ ���ĺ� �ڵ� �߰��Ѵ�.
			  alphabets[0] = indexes[i].GetAlphabet();
			  alphabets[1] = '\0';
			  alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem(alphabets, parent, TVI_LAST);


			  //1.8.2.2. �ش� ���ĺ� ������ length��ŭ �ݺ��Ѵ�.
			  indexLength = indexes[i].GetLength();
			  j = 0;
			  while (j < indexLength) {

				  //1.8.2.2.1. �ش� ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
				  index = indexes[i].GetAt(j);

				  indexes[i].FindSpellings(index, &sameIndexes, &sameCount);
				  //--------------------------------------------------------------------------------------------
				  //1.8.2.2.2. ���ϴܾ ������,
				  if (sameCount > 1) {
					  //1. �ܾ��ڵ� ã�´�.
					  spelling = CString(index->GetSpelling().c_str());
					  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
						  ->GetNextItem(alphabetHandle, TVGN_CHILD);
					  word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
					  while (wordHandle != NULL && spelling != word) {
						  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
							  ->GetNextItem(wordHandle, TVGN_NEXT);
						  word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
					  }

					  //2. �ܾ��ڵ� ������ �߰��Ѵ�.
					  if (wordHandle == NULL) {
						  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
							  ->InsertItem(spelling, alphabetHandle, TVI_LAST);
					  }

					  //3. �ܾ��ڵ� ������ ǰ���ڵ� �߰��ϰ�, ���� ����� üũ�Ѵ�.
					  wordClass = CString(index->GetWordClass().c_str());

					  wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
						  ->InsertItem(wordClass, wordHandle, TVI_LAST);

					  ox = CString(index->GetOx().c_str());
					  if (ox == "o") {
						  ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle, TRUE);
					  }
         		  }

				  //1.8.2.2.3. ���ϴܾ� ������,
				  else {
					  //1. ���ĺ� �ڵ� ������ �ܾ��ڵ� �߰��ϰ�, ���� ����� üũ�Ѵ�.					  
					  spelling = CString(index->GetSpelling().c_str());

					  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
						  ->InsertItem(spelling, alphabetHandle, TVI_LAST);

					  ox = CString(index->GetOx().c_str());
					  if (ox == "o") {
						  ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
					  }


				  }
				  //--------------------------------------------------------------------------------------------------
				  if (sameIndexes != NULL) {
					  delete[] sameIndexes;
					  sameIndexes = NULL;
				  }

			     j++;
			  }

			i++;
		  }

		  if (indexes != NULL) {
			  delete[] indexes;
			  indexes = NULL;
		  }

	  }


	 //1.9. �ܾ�ī��ö�� �ܾ�ī�尡 1�� �̻��� ���,
	if (wLength > 0) {
			  //1.9.1. �ܾ�ī��ö���� ù��° �ܾ ���� �ܾ�� �ű��.
			  index = this->wordCardBinder->First();


			  //1.9.2. Ʈ���� �� ���� �ܾ��� ���ĺ� �ڵ� ã�´�.
			  spelling = CString(index->GetSpelling().c_str());
			  indexIndex = this->indexBinder->Find((LPCTSTR)spelling);

			  alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
			  alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

			  while (alphabet != spelling[0] - 32) {
				  alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle,
					  TVGN_NEXT);
				  alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
			  }
			  //1.9.3. Ʈ���� �� ���ĺ� �ڵ� ��ģ��.
			  ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

			  //1.9.4. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
			  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
			  word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  while (spelling != word) {
				  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
				  word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  }
			  //1.9.5. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
			  indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
			  indexIndex->FindSpellings(index, &sameIndexes, &sameCount);

			  //1.9.6. ���� �ܾ ������,
			  if (sameCount > 1) {
				  //1. �ܾ��ڵ��� �� ��° ǰ������ Ȯ���Ѵ�.
				  wordCardIndex = indexIndex->Find(index);
				  i = 0;
				  while (sameIndexes[i] != wordCardIndex) {
					  i++;
				  }
				  //2. ǰ���ڵ� ã�´�.
				  wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
				  j = 0;
				  while (j < i) {
					  wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
						  ->GetNextItem(wordClassHandle, TVGN_NEXT);
					  j++;
				  }
				  //3. �ܾ��ڵ� �����ش�.
				  ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
				  //4. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
				  ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
			  }
			  //1.9.7. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
			  else {
				  selectCheck = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);

			  }

			  if (sameIndexes != NULL) {
				  delete[] sameIndexes;
				  sameIndexes = NULL;
			  }

			  //1.4.2. �ܾ�ī�忡 ���� �ܾ�ī�� ����Ѵ�.
			  spelling = CString(index->GetSpelling().c_str());
			  GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			  wordClass = CString(index->GetWordClass().c_str());
			  GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
			  meaning = CString(index->GetMeaning().c_str());
			  GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
			  example = CString(index->GetExample().c_str());
			  GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
			  isImportant = CString(index->GetIsImportant().c_str());
			  GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
    }


	 return FALSE;
 
}
void WordCardBinderForm::OnPutButtonClicked() {
	//2. �ȱ� ��ư Ŭ������ ��
	  //2.1. �ȱ������� ����Ѵ�.
      PuttingForm puttingForm;
	  puttingForm.DoModal();
}
void WordCardBinderForm::OnFindButtonClicked() {
	//3. ã�� ��ư Ŭ������ ��
	  //3.1. ã�������� ����Ѵ�.
	FindingForm findingForm;
	findingForm.DoModal();
}
void WordCardBinderForm::OnPutOutButtonClicked() {
	//4. �̱� ��ư Ŭ������ ��
	  //4.1. �̱������� ����Ѵ�.
	PuttingOutForm puttingOutForm;
	puttingOutForm.DoModal();
}
void WordCardBinderForm::OnQuizButtonClicked() {
	//5. ���� ��ư Ŭ������ ��
	  //5.1. ���������� ����Ѵ�.
	QuizForm quizForm;
	quizForm.DoModal();
}
void WordCardBinderForm::OnCorrectQuizButtonClicked() {
	//6. �ϱ�ܾ�(��������ö)��ư Ŭ������ ��
	  //6.1. �ϱ�ܾ� ������ ����Ѵ�.
	CorrectQuizForm correctQuizForm;
	correctQuizForm.DoModal();
}
void WordCardBinderForm::OnImportantWordsButtonClicked() {
	//7. �߿�ܾ� ��ư Ŭ������ ��
	  //7.1. �߿�ܾ� ������ ����Ѵ�.
	ImportantWordsForm importantWordsForm;
	importantWordsForm.DoModal();
}
void WordCardBinderForm::OnFirstButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString isImportant;
	WordCard* index;
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	CString alphabet;
	CString word;
	CString wordClassText;
	Index* indexIndex;
	Long(*indexes);
	Long count;
	Long wordCardIndex;
	Long i = 0;
	Long j;



	//8. ù��° ��ư Ŭ������ ��
	 //8.1. ù��° �ܾ�ī�带 ���� ī��� �ű��.
     index = this->wordCardBinder->First();

	 //8.2. Ʈ���� �� ���� �ܾ��� ���ĺ��ڵ� ã�´�.
	 spelling = CString(index->GetSpelling().c_str());

	 parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	 alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	 alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	 
	 while (alphabet != spelling[0] - 32) {
		 alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		 alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	 }

	 //8.3. Ʈ���� �� ���ĺ� �ڵ� ��ģ��.
	 ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	 //8.4. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
	 wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	 word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	 while (spelling != word) {
		 wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		 word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	 }

	 //8.5. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
	 indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
	 indexIndex->FindSpellings(index, &indexes, &count);

	 //8.6. ���ϴܾ� ������,
	 if (count > 1) { //ǰ���ڵ��� ã���ش�.

		 //8.6.2. ǰ���ڵ� ã�´�.
		 wordClass = CString(index->GetWordClass().c_str());
		 wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		 wordClassText= ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		 while (wordClassText != wordClass) {
			 wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			 wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		 }

		 //8.6.3. �ܾ��ڵ� �����ش�.
		 ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		 //8.6.4. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
		 ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

	 }
	 //8.7. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
	 else {
		 ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
	 }

	 if (indexes != NULL) {
		 delete[] indexes;
		 indexes = NULL;
	 }

	 //8.2. ù��° �ܾ�ī���� ö��,ǰ��,�ǹ�,���ø� ����Ѵ�.
	 spelling = CString(index->GetSpelling().c_str());
	 GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	 wordClass = CString(index->GetWordClass().c_str());
	 GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	 meaning = CString(index->GetMeaning().c_str());
	 GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	 example = CString(index->GetExample().c_str());
	 GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	 isImportant = CString(index->GetIsImportant().c_str());
	 GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}
void WordCardBinderForm::OnPreviousButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString isImportant;
	WordCard* index;
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	CString alphabet;
	CString word;
	Index* indexIndex;
	Long(*indexes);
	Long count;
	Long wordCardIndex;
	Long i = 0;
	Long j;
	CString wordClassText;


	//9. ���� ��ư Ŭ������ ��
	 //9.1. ���� �ܾ�ī�带 ���� ī��� �ű��.
	index = this->wordCardBinder->Previous();

	//9.2. Ʈ���� �� ���� �ܾ��� ���ĺ��ڵ� ã�´�.
	spelling = CString(index->GetSpelling().c_str());
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

	while (alphabet != spelling[0] - 32) {
		alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	}

	//9.3. Ʈ���� �� ���ĺ� �ڵ� ��ģ��.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	//9.4. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
	wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	while (spelling != word) {
		wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	}

	//9.5. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
	indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
	indexIndex->FindSpellings(index, &indexes, &count);

	//9.6. ���ϴܾ� ������,
	if (count > 1) {
		//9.6.1. �ܾ��ڵ��� ���° ǰ������ Ȯ���Ѵ�.
		 //8.6.2. ǰ���ڵ� ã�´�.
		wordClass = CString(index->GetWordClass().c_str());
		wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		while (wordClassText != wordClass) {
			wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		}
		//9.6.3. �ܾ��ڵ� �����ش�.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		//9.6.4. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);


	}
	//9.7. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
	else {
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
#if 0

		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
#endif

	}

	if (indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}

	//9.2. ���� �ܾ�ī���� ö��,ǰ��,�ǹ�,���ø� ����Ѵ�.
	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(index->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}
void WordCardBinderForm::OnNextButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString isImportant;
	WordCard* index;
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	CString alphabet;
	CString word;
	Index* indexIndex;
	Long(*indexes);
	Long count;
	Long wordCardIndex;
	Long i = 0;
	Long j;
	CString wordClassText;

	//10. ���� ��ư Ŭ������ ��
	 //10.1. ���� �ܾ�ī�带 ���� ī��� �ű��.
	index = this->wordCardBinder->Next();

	//10.2. Ʈ���� �� ���� �ܾ��� ���ĺ��ڵ� ã�´�.
	spelling = CString(index->GetSpelling().c_str());
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

	while (alphabet != spelling[0] - 32) {
		alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	}

	//10.3. Ʈ���� �� ���ĺ� �ڵ� ��ģ��.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	//10.4. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
	wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	while (spelling != word) {
		wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	}

	//10.5. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
	indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
	indexIndex->FindSpellings(index, &indexes, &count);

	//10.6. ���ϴܾ� ������,
	if (count > 1) {
		//10.6.1. �ܾ��ڵ��� ���° ǰ������ Ȯ���Ѵ�.
		//8.6.2. ǰ���ڵ� ã�´�.
		wordClass = CString(index->GetWordClass().c_str());
		wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		while (wordClassText != wordClass) {
			wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		}


		//10.6.3. �ܾ��ڵ� �����ش�.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		//10.6.4. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);


#if 0

		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle, TRUE);
#endif

	}
	//10.7. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
	else {
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
#if 0
		//Ȯ�ζ��� ��� �Ϸ��� Ʈ�� ��Ʈ���� ä��� ���� TVS_CHECKBOXES�� ���� �մϴ�.
		GetDlgItem(IDC_TREE_INDEXES)->ModifyStyle(0, TVS_CHECKBOXES);
		GetDlgItem(IDC_TREE_INDEXES)->ModifyStyle(TVS_CHECKBOXES, 0);

		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
#endif
	}

	if (indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}

	//10.2. ���� �ܾ�ī���� ö��,ǰ��,�ǹ�,���ø� ����Ѵ�.
	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(index->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}
void WordCardBinderForm::OnLastButtonClicked() {
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString isImportant;
	WordCard* index;
	HTREEITEM parent;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	CString alphabet;
	CString word;
	Index* indexIndex;
	Long(*indexes);
	Long count;
	Long wordCardIndex;
	Long i = 0;
	Long j;
	CString wordClassText;

	//11. ������ ��ư Ŭ������ ��
	 //11.1. ������ �ܾ�ī�带 ���� ī��� �ű��.
	index = this->wordCardBinder->Last();

	//11.2. Ʈ���� �� ���� �ܾ��� ���ĺ��ڵ� ã�´�.
	spelling = CString(index->GetSpelling().c_str());
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

	while (alphabet != spelling[0] - 32) {
		alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	}

	//11.3. Ʈ���� �� ���ĺ� �ڵ� ��ģ��.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	//11.4. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
	wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	while (spelling != word) {
		wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	}

	//11.5. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
	indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
	indexIndex->FindSpellings(index, &indexes, &count);

	//11.6. ���ϴܾ� ������,
	if (count > 1) {
		//11.6.1. �ܾ��ڵ��� ���° ǰ������ Ȯ���Ѵ�.
		 //8.6.2. ǰ���ڵ� ã�´�.
		wordClass = CString(index->GetWordClass().c_str());
		wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		while (wordClassText != wordClass) {
			wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		}

		//11.6.3. �ܾ��ڵ� �����ش�.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		//11.6.4. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
	}
	//11.7. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
	else {
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
	}

	if (indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}

	//11.2. ������ �ܾ�ī���� ö��,ǰ��,�ǹ�,���ø� ����Ѵ�.
	spelling = CString(index->GetSpelling().c_str());
	GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
	wordClass = CString(index->GetWordClass().c_str());
	GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
	meaning = CString(index->GetMeaning().c_str());
	GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
	example = CString(index->GetExample().c_str());
	GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}
void WordCardBinderForm::OnPutImportantWordButtonClicked() {
	WordCard* index;
	CString isImportant;

	//12. �߿�ܾ��߰���ư Ŭ������ ��
	  //12.1. ���� �ܾ�ī���� ��ġ�� �д´�.
	  index = this->wordCardBinder->GetCurrent();
	  //12.2. �ܾ�ī��ö���� �߿�ܾ�� �߰��Ѵ�.
	  index = this->wordCardBinder->PutImportantWord(index);

	  //db���� Modify�Ѵ�.
	  Modify(index);


	  //12.3. �����쿡 �߿����� ����Ѵ�.
	  isImportant = CString(index->GetIsImportant().c_str());
	  GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}
void WordCardBinderForm::OnPutOutImportantWordButtonClicked() {
	WordCard* index;
	CString isImportant;

	//13. �߿�ܾ���ҹ�ư Ŭ������ ��
	  //13.1. ���� �ܾ�ī���� ��ġ�� �д´�.
	index = this->wordCardBinder->GetCurrent();
	//13.2. �ܾ�ī��ö���� �߿�ܾ ����Ѵ�.
	index = this->wordCardBinder->PutOutImportantWord(index);

	//db���� Modify�Ѵ�.
	Modify(index);


	//13.3. �����쿡 �߿����� ����Ѵ�.
	isImportant = CString(index->GetIsImportant().c_str());
	GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}
void WordCardBinderForm::OnTreeViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result) {
	HTREEITEM parent;
	HTREEITEM current;
	HTREEITEM currentParent;
	HTREEITEM currentChild;
	HTREEITEM currentGParent;
	HTREEITEM cpChild;
	CString cpText;
	CString cText;
	CString ox;
	WordCard* index=NULL;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString isImportant;
	Long i = 1;
	Long j = 0;
	Long k = 0;
	Index* indexIndex;
	Long(*indexes) = NULL;
	Long count;
	BOOL ret;



	//1. ���ĺ� ī�װ� �ڵ��� ���س��´�.
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	//2. ���õ� �׸��� �ڵ��� ���Ѵ�.
	current = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_CARET);
	//3. ���õ� �׸��� �θ� �д´�.
	currentParent= ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(current, TVGN_PARENT);

	//4. ���õ� �׸��� �ڽ��� �д´�.
	currentChild= ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(current, TVGN_CHILD);
	//5. ���õ� �׸��� ���θ� �д´�.
	currentGParent= ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(currentParent, TVGN_PARENT);

	// ���õ� �׸��� üũ�ڽ� ���¸� �д´�.
	ret = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetCheck(current);

	//6. currentParent�� parent�� �ƴϰ�, currentChild�� null�� ���,
	if (currentParent != parent && currentChild == NULL && ret==FALSE) {

		//6.1. currentGParent�� parent�� �ƴҰ��,(ǰ���ڵ��� ���)
		if (currentGParent != parent) {

			//6.1.1. currentParent�� text�� ���Ѵ�.(apple)
			cpText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(currentParent);
			cText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(current);

			//6.1.3. current�� ������ ���Ѵ�.
			indexIndex = this->indexBinder->Find((LPCTSTR)cpText);

			//6.1.4. �ش� ���ο��� current�� �ܾ�ī�� ã�´�.
			j = 0;
			index = indexIndex->GetAt(j);
			spelling = CString(index->GetSpelling().c_str());
			wordClass = CString(index->GetWordClass().c_str());

			while (spelling != cpText || wordClass != cText) { //�ϳ��� ���� ������, 
				j++;

				index = indexIndex->GetAt(j);
				spelling = CString(index->GetSpelling().c_str());
				wordClass = CString(index->GetWordClass().c_str());
			}

			index = indexIndex->GetAt(j);

			//6.1.5. �ش� �ܾ ����� �ű��.
			index = this->wordCardBinder->Move(index);

			//6.1.5. �ش� �ܾ�ī�带 ����Ѵ�.
			spelling = CString(index->GetSpelling().c_str());
			GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			wordClass = CString(index->GetWordClass().c_str());
			GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
			meaning = CString(index->GetMeaning().c_str());
			GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
			example = CString(index->GetExample().c_str());
			GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
			isImportant = CString(index->GetIsImportant().c_str());
			GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);

		}
		//6.2. currentGParent�� parent�� ���,(�ܾ��ڵ��� ���)
		else {
			//6.2.1. current�� text�� ���Ѵ�.
			cText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(current);
			//6.2.2. current�� ������ ã�´�.
			indexIndex = this->indexBinder->Find((LPCTSTR)cText);

			//6.2.3. current�� ������ �� ��° �ִ��� ���Ѵ�.
			i = 0;
			index = indexIndex->GetAt(i);
			spelling = CString(index->GetSpelling().c_str());
			while (spelling != cText) {
				i++;
				index = indexIndex->GetAt(i);
				spelling = CString(index->GetSpelling().c_str());
			}

			//6.2.4. �ش� �ܾ�ī�带 ���� ��ġ�� �̵���Ų��.
			index = indexIndex->GetAt(i);

			//6.1.5. �ش� �ܾ ����� �ű��.
			index = this->wordCardBinder->Move(index);


			//6.1.5. �ش� �ܾ�ī�带 ����Ѵ�.
			spelling = CString(index->GetSpelling().c_str());
			GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			wordClass = CString(index->GetWordClass().c_str());
			GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
			meaning = CString(index->GetMeaning().c_str());
			GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
			example = CString(index->GetExample().c_str());
			GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
			isImportant = CString(index->GetIsImportant().c_str());
			GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);


			
		}
	}
}
void WordCardBinderForm::OnTreeViewCheckBoxClicked(NMHDR* pNotifyStruct, LRESULT* result){

	///////////////////////////////////////////////////////////////////////////////////////////
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNotifyStruct;
	///////////////////////////////////////////////////////////////////////////////////////////

	// get the mouse position relative to the treectrl
	CPoint ptMouse;
	UINT uFlags;
	GetCursorPos(&ptMouse);
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->ScreenToClient(&ptMouse); //Mouse coords

    // determine if this location is on a treectrl item
	HTREEITEM current = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->HitTest(ptMouse, &uFlags);

	// action depends on whether the click was on the checkbox or the label
	if ((current != NULL) && (TVHT_ONITEMSTATEICON & uFlags)!=0){
		
		PostMessage(WM_USER_TREE_CHANGE_CHECK, (WPARAM)pNotifyStruct->hwndFrom, (LPARAM)current);
    }

	*result = 0;

}
LRESULT WordCardBinderForm::OnTreeChangeCheck(WPARAM wParam, LPARAM lParam) {
	HTREEITEM current = (HTREEITEM)lParam;
	BOOL ret;
	HTREEITEM parent;
	HTREEITEM currentParent;
	HTREEITEM currentChild;
	HTREEITEM currentGParent;
	HTREEITEM cpChild;
	HTREEITEM currentCurrent;
	CString cpText;
	CString cText;
	WordCard* index = NULL;
	WordCard* temp = NULL;
	CString spelling;
	CString wordClass;
	CString meaning;
	CString example;
	CString isImportant;
	Long i = 1;
	Long j = 0;
	Long k = 0;
	Index* indexIndex;
	WordCard wordCard;
	WordCard* newIndex = NULL;
	CString ox;
	int ret_;
	HTREEITEM alphabetHandle;
	HTREEITEM wordHandle;
	HTREEITEM wordClassHandle;
	CString alphabet;
	CString word;
	Long(*indexes) = NULL;
	Long count;
	Long wordCardIndex;
	TCHAR alphabets[2];
	WordCard* first;
	WordCard* restOne = NULL;
	WordCard* incorrectWord;
	CString wordClassText;

	//1. �ش� �ڵ��� üũ�ڽ� ���¸� ���Ѵ�.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(current);
	ret = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetCheck(current);


	//2. �ش� �ڵ��� �ܾ�ī�带 ���Ѵ�.
	  //2.1. ���ĺ� ī�װ� �ڵ��� ���س��´�.
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);

	//2.2. ���õ� �׸��� �θ� �д´�.
	currentParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(current, TVGN_PARENT);

	//2.3. ���õ� �׸��� �ڽ��� �д´�.
	currentChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(current, TVGN_CHILD);

	//2.4. ���õ� �׸��� ���θ� �д´�.
	currentGParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(currentParent, TVGN_PARENT);

	//6. [������ �ڵ��� �ܾ�ī�带 ���Ѵ�.]currentParent�� parent�� �ƴϰ�, currentChild�� null�� ���,
	if (currentParent != parent && currentChild == NULL) {

		//6.1. currentGParent�� parent�� �ƴҰ��,(ǰ���ڵ��� ���)
		if (currentGParent != parent) {

			//6.1.1. currentParent�� text�� ���Ѵ�.(apple)
			cpText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(currentParent);
			cText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(current);

			//6.1.3. current�� ������ ���Ѵ�.
			indexIndex = this->indexBinder->Find((LPCTSTR)cpText);

			//6.1.4. �ش� ���ο��� current�� �ܾ�ī�� ã�´�.
			j = 0;
			index = indexIndex->GetAt(j);
			spelling = CString(index->GetSpelling().c_str());
			wordClass = CString(index->GetWordClass().c_str());

			while (spelling != cpText || wordClass != cText) { //�ϳ��� ���� ������, 
				j++;

				index = indexIndex->GetAt(j);
				spelling = CString(index->GetSpelling().c_str());
				wordClass = CString(index->GetWordClass().c_str());
			}

			index = indexIndex->GetAt(j);

		}
		//6.2. currentGParent�� parent�� ���,(�ܾ��ڵ��� ���)
		else if(currentGParent==parent){
			//6.2.1. current�� text�� ���Ѵ�.
			cText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(current);
			//6.2.2. current�� ������ ã�´�.
			indexIndex = this->indexBinder->Find((LPCTSTR)cText);

			//6.2.3. current�� ������ �� ��° �ִ��� ���Ѵ�.
			i = 0;
			index = indexIndex->GetAt(i);
			spelling = CString(index->GetSpelling().c_str());
			while (spelling != cText) {
				i++;
				index = indexIndex->GetAt(i);
				spelling = CString(index->GetSpelling().c_str());
			}
		}
	}


	if (currentParent != parent && currentChild == NULL) {

		//3. "üũ" �� �׸��� ��üũ�ϴ� ���,[�´�����ö -> �ܾ�ī��ö]
		if (ret == FALSE) {
			//��������ö���� �̴´�.
			temp = index;
			wordCard = this->correctQuizBinder->PutOut(index);
			spelling = CString(wordCard.GetSpelling().c_str());

			// ����ö���� �̴´�.
			indexIndex = this->indexBinder->PutOut((LPCTSTR)spelling, temp);


			//db���� delete�Ѵ�.
			Delete(wordCard);

			//������ ó��(PuttingForm)--------------------------------------------------------------------------------------

			//�ܾ�ī��ö�� �ȴ´�.
			//answer, ox ��� �ʱ�ȭ
			spelling = CString(wordCard.GetSpelling().c_str());
			wordClass = CString(wordCard.GetWordClass().c_str());
			meaning = CString(wordCard.GetMeaning().c_str());
			example = CString(wordCard.GetExample().c_str());
			isImportant = CString(wordCard.GetIsImportant().c_str());

			WordCard wordCard1((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
				(LPCTSTR)spelling, "", "", (LPCTSTR)meaning, (LPCTSTR)isImportant);

			index = this->wordCardBinder->PutIn(wordCard1);

			// ����ö�� �ȴ´�.
			indexIndex = this->indexBinder->PutIn(index);
			spelling = CString(index->GetSpelling().c_str());

			//db�� Insert�Ѵ�.
			Insert(index);



			//�ش� �ܾ��ڵ��� �������� �����Ѵ�.
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(current, FALSE);


			//3.8. ���� �ܾ�ī�带  �ܾ�ī��ö �ܾ�ī�忡 ����Ѵ�.
			spelling = CString(index->GetSpelling().c_str());
			GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
			wordClass = CString(index->GetWordClass().c_str());
			GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
			meaning = CString(index->GetMeaning().c_str());
			GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
			example = CString(index->GetExample().c_str());
			GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
			isImportant = CString(index->GetIsImportant().c_str());
			GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);

			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(current, FALSE);


		}

		else { //"��üũ" �� �׸��� üũ�ϴ� ���,[�ܾ�ī��ö -> �´�����ö]
			//------------------------------------------------------------------------------
			//�̱��� ó��(PuttingOutForm)
			//2.6.1. �ܾ�ī��ö���� �̴´�.
			temp = index;
			wordCard = this->wordCardBinder->PutOut(index);
			spelling = CString(wordCard.GetSpelling().c_str());

			//db���� delete�Ѵ�.
			Delete(wordCard);

			// ����ö���� �̴´�.
			indexIndex = this->indexBinder->PutOut((LPCTSTR)spelling, temp);

			//�ȴ� ó��(PuttingForm)------------------------------------------------------------------------

			//2.6.2. ��������ö�� �ȴ´�.
			//answer, ox �����ɷ� ����,
			spelling = CString(wordCard.GetSpelling().c_str());
			wordClass = CString(wordCard.GetWordClass().c_str());
			meaning = CString(wordCard.GetMeaning().c_str());
			example = CString(wordCard.GetExample().c_str());
			isImportant = CString(wordCard.GetIsImportant().c_str());
			ox = "o";

			WordCard wordCard1((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
				(LPCTSTR)spelling, (LPCTSTR)spelling, (LPCTSTR)ox, (LPCTSTR)meaning, (LPCTSTR)isImportant);

			index = this->correctQuizBinder->PutIn(wordCard1);


			//db�� Insert�Ѵ�.
			Insert(index);


			// ����ö�� �ȴ´�.
			indexIndex = this->indexBinder->PutIn(index);
			spelling = CString(index->GetSpelling().c_str());


			//�ش� �ܾ��ڵ��� �������� �����Ѵ�.
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(current, TRUE);

			//-------------------------------------------------------------------------------


			//2.6.3. �ܾ�ī��ö �����쿡 ���� �ܾ�ī�尡 �ִ��� Ȯ���Ѵ�.
			index = this->wordCardBinder->GetCurrent();
			//2.6.4. ���� ī�尡 ������ �ܾ�ī��ö �������� �ܾ�ī��ö�� ����Ѵ�.
			if (index != NULL) {

				//�ش� �׸��� �ڵ��� ã�� üũ�Ѵ�.
				//-------------------------------------------------------
					 //8.2. Ʈ���� �� ���� �ܾ��� ���ĺ��ڵ� ã�´�.
				spelling = CString(index->GetSpelling().c_str());

				parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
				alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
				alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

				while (alphabet != spelling[0] - 32) {
					alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
					alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
				}

				//8.3. Ʈ���� �� ���ĺ� �ڵ� ��ģ��.
				((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

				//8.4. Ʈ���� �� ���� �ܾ��� �ܾ��ڵ� ã�´�.
				wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
				word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				while (spelling != word) {
					wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
					word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				}

				//8.5. �ش� �ܾ ���ο� ���ϴܾ� �ִ��� Ȯ���Ѵ�.
				indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
				indexIndex->FindSpellings(index, &indexes, &count);

				//8.6. ���ϴܾ� ������,
				if (count > 1) { //ǰ���ڵ��� ã���ش�.

					//8.6.2. ǰ���ڵ� ã�´�.
					wordClass = CString(index->GetWordClass().c_str());
					wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
					wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

					while (wordClassText != wordClass) {
						wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
						wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
					}

					//8.6.3. �ܾ��ڵ� �����ش�.
					((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
					//8.6.4. �ش� ǰ���ڵ��� ���õ� ���·� ó���Ѵ�.
					((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

				}
				//8.7. �ش� ���ο� ���ϴܾ� ������, �ܾ��ڵ��� ���õ� ���·� ó���Ѵ�.
				else {
					((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
				}

				if (indexes != NULL) {
					delete[] indexes;
					indexes = NULL;
				}

				//-------------------------------------------------------


				spelling = CString(index->GetSpelling().c_str());
				GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText(spelling);
				wordClass = CString(index->GetWordClass().c_str());
				GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText(wordClass);
				meaning = CString(index->GetMeaning().c_str());
				GetDlgItem(IDC_EDIT_MEANING)->SetWindowText(meaning);
				example = CString(index->GetExample().c_str());
				GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText(example);
				isImportant = CString(index->GetIsImportant().c_str());
				GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
			}
			//2.6.5. ���� ī�尡 ������ ���� ó���Ѵ�.
			else {
				GetDlgItem(IDC_EDIT_SPELLING)->SetWindowText("");
				GetDlgItem(IDC_EDIT_WORDCLASS)->SetWindowText("");
				GetDlgItem(IDC_EDIT_MEANING)->SetWindowText("");
				GetDlgItem(IDC_EDIT_EXAMPLE)->SetWindowText("");
			}

		}
	}


	return 0;
}
void WordCardBinderForm::OnClose() {
	//14.2. �ݱ��ư Ŭ������ ��
	  //14.0 �����Ѵ�.
	    Save();

	  //14.1. �ܾ�ī��ö ���ش�.
	  if (this->wordCardBinder != NULL) {

		  delete this->wordCardBinder;
		  this->wordCardBinder = NULL;
	  }
	  //14.2. ��������ö ���ش�.
	  if (this->correctQuizBinder != NULL) {

		  delete this->correctQuizBinder;
		  this->correctQuizBinder = NULL;
	  }
	  EndDialog(0);
}
