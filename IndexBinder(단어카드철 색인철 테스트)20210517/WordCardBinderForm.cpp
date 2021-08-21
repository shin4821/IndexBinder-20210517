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

#include<CommCtrl.h> //트리컨트롤 스타일
#include<afxcmn.h> //트리뷰
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

	//1. 오늘 날짜를 6자리로 구해놓는다.
	time(&timer);
	today = localtime(&timer);
	year.Format("%4d", today->tm_year + 1900); //2021
	year_ = year.Right(2); //21
	todayDate.Format("%s%02d%02d", year_, today->tm_mon + 1, today->tm_mday); //210506

	//2. 기본 코드 만들어놓는다.
	quizCode.Format("Q%s001", todayDate); //Q210506001

	//3. quizCode를 내림차순하여 첫번째 코드를 구한다.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);

	//4. 데이터가 있으면 첫번째 코드를 구한다.
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, quizCode_);
		//코드가 오늘날짜 코드인지 확인한다.
		todayDate_ = quizCode_.Mid(1, 6); //210504

		//4.1. 그 코드가 오늘 날짜인 경우,
		if (todayDate == todayDate_) {
			//4.1.1. 맨뒤 세자리 숫자부분을 분리한다.
			number = quizCode_.Right(3); //004
			//4.1.2. 숫자부분을 정수로바꾼다.
			number_ = _ttoi(number);
			//4.1.3. 1씩 더해준다.
			number_++;
			//4.1.4. 오늘 날짜와 정수부분을 합친다.(정식 코드를 만든다.)
			quizCode.Format("Q%s%03d", todayDate, number_);
		}
	}
	//5. 코드를 출력한다.
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

	//1. 오늘날짜를 6자리로 구해놓는다.
	time(&timer);
	today = localtime(&timer);
	year.Format("%4d", today->tm_year + 1900); //2021
	year_ = year.Right(2); //21
	todayDate.Format("%s%02d%02d", year_, today->tm_mon + 1, today->tm_mday); //210506

	//2. 기본코드 만들어놓는다. 
	code.Format("W%s001", todayDate); //W210506001

	//3. code를 내림차순하여 첫번째 코드를 구한다.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	
	//4. 파일이 있으면
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code_);
		//4.1. 코드가 오늘 날짜 코드인지 확인한다.
		todayDate_ = code_.Mid(1, 6);
		//4.2. 오늘 날짜 코드인 경우,
		if (todayDate == todayDate_) {
			//4.2.1. 맨 뒤 세자리 숫자부분을 분리한다.
			number = code_.Right(3);
			//4.2.2. 숫자부분을 정수로 바꾼다.
			number_ = _ttoi(number);
			//4.2.3. 1씩 더해준다.
			number_++;
			//4.2.4. 오늘날짜와 정수부분을 합한다.
			code.Format("W%s%03d", todayDate, number_);
		}
	}
	//5.코드를 출력한다.
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

	//1. sql, sql1 날린다.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs1.Open(AFX_DB_USE_DEFAULT_TYPE, sql1);
	
	//2. 전체 데이터 지운다.

	db.ExecuteSQL("DELETE FROM Quiz");
	db.ExecuteSQL("DELETE FROM Word");


	//3. 단어카드철의 처음부터 끝까지 반복한다.
	it = this->wordCardBinder->First();
	while (!rs.IsEOF() && it != previous) {
		//3.1. code, quizCode 구한다.
		rs.GetFieldValue((short)0, code);
		rs.GetFieldValue((short)1, quizCode);
		example = it->GetExample().c_str();
		example.Replace("'", "\\'");

		//3.3. 단어 Insert한다.
		sql.Format("INSERT INTO Word(code, spelling, wordClass, meaning, example) VALUES('%s','%s','%s',"
			"'%s','%s');", (LPCTSTR)code, it->GetSpelling().c_str(), it->GetWordClass().c_str(),
			it->GetMeaning().c_str(), (LPCTSTR)example);
		db.ExecuteSQL(sql);


		//3.2. 퀴즈 Insert한다.
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

	//4. 맞은퀴즈철의 처음부터 끝까지 반복한다.
	previous = NULL;
	it = this->correctQuizBinder->First();
	while (!rs1.IsEOF() && it != previous) {
		//4.1. code, quizCode 구한다.
		rs1.GetFieldValue((short)0, code);
		rs1.GetFieldValue((short)1, quizCode);
		example = it->GetExample().c_str();
		example.Replace("'", "\\'");

		//4.3. 단어 Insert한다.
		sql1.Format("INSERT INTO Word(code, spelling, wordClass, meaning, example) VALUES('%s','%s','%s',"
			"'%s','%s');", (LPCTSTR)code, it->GetSpelling().c_str(),
			it->GetWordClass().c_str(), it->GetMeaning().c_str(), (LPCTSTR)example);
		db.ExecuteSQL(sql1);


		//4.2. 퀴즈 Insert한다.
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

	//1. sql, sql1 날린다.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs1.Open(AFX_DB_USE_DEFAULT_TYPE, sql1);

	//2. rs의 끝이 아닌동안 반복한다.
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, spelling);
		rs.GetFieldValue((short)1, wordClass);
		rs.GetFieldValue((short)2, meaning);
		rs.GetFieldValue((short)3, example);
		rs.GetFieldValue((short)4, answer);
		rs.GetFieldValue((short)5, ox);
		rs.GetFieldValue((short)6, isImportant);

		//2.1. 단어카드철에 꽂는다.
		WordCard wordCard((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
			(LPCTSTR)spelling, (LPCTSTR)answer, (LPCTSTR)ox, (LPCTSTR)meaning, (LPCTSTR)isImportant);
		this->wordCardBinder->PutIn(wordCard);
		
		rs.MoveNext();
	}
	rs.Close();

	//3. rs1의 끝이 아닌동안 반복한다.
	while (!rs1.IsEOF()) {
		rs1.GetFieldValue((short)0, spelling);
		rs1.GetFieldValue((short)1, wordClass);
		rs1.GetFieldValue((short)2, meaning);
		rs1.GetFieldValue((short)3, example);
		rs1.GetFieldValue((short)4, answer);
		rs1.GetFieldValue((short)5, ox);
		rs1.GetFieldValue((short)6, isImportant);

		//3.1. 맞은퀴즈철에 꽂는다.
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

	//1. code, quizCode 구한다.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	code = GetCode();
	quizCode = GetQuizCode();
	example = index->GetExample().c_str();
	example.Replace("'", "\\'");

	//3. 단어 Insert 한다.
	sql.Format("INSERT INTO Word(code, spelling, wordClass, meaning, example) VALUES('%s','%s','%s',"
		"'%s','%s');", (LPCTSTR)code, index->GetSpelling().c_str(),
		index->GetWordClass().c_str(), index->GetMeaning().c_str(), (LPCTSTR)example);
	db.ExecuteSQL(sql);


	//2. 퀴즈 Insert 한다.
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

	//1. 해당 index의 code를 찾는다.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs.GetFieldValue((short)0, code);

	//3. 해당 code를 퀴즈에서 지운다.
	sql.Format("DELETE FROM Quiz WHERE code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);

	//2. 해당 code를 단어에서 지운다.
	sql.Format("DELETE FROM Word WHERE code='%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);

	//4. 끝낸다.
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

	//1.code 찾는다.
	db.OpenEx("DSN=WordCardBinder;UID=Sydney;PWD=4821");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	rs.GetFieldValue((short)0, code);

	//2. 해당 코드를 업데이트한다.
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

	//1. 윈도우가 생성될 때
	  //1.1. 단어카드철 만든다.
	  this->wordCardBinder = new WordCardBinder;
	  //1.2. 맞은퀴즈철 만든다.
	  this->correctQuizBinder = new CorrectQuizBinder;
	  //1.3. 색인철 만든다.
	  this->indexBinder = new IndexBinder;

	  //1.4. 트리뷰에 알파벳 카테고리 핸들을 만든다.
	  parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem("알파벳", TVI_ROOT, TVI_LAST);
	  

	  //1.5. 맞은퀴즈철, 단어카드철에 적재한다.
	  Load();


	  //1.6. 단어카드철 단어카드가 1개 이상일 경우,
	  wLength = this->wordCardBinder->GetLength();
	  if (wLength > 0) {
		  index = this->wordCardBinder->First();
		  //1.6.1 단어카드철의 끝이 아닌동안 반복한다.
		  while (index != previous) {
			  //1.6.1.1. 색인철에 끼운다.
			  this->indexBinder->PutIn(index);

			  previous = index;
			  index = this->wordCardBinder->Next();
		  }
	  }

	  //1.7. 맞은퀴즈철 단어가 1개 이상일 경우,

	  cLength = this->correctQuizBinder->GetLength();
	  if (cLength > 0) {
		  previous = NULL;
		  index = this->correctQuizBinder->First();
		  //1.7.1. 맞은퀴즈철의 끝이 아닌동안 반복한다.
		  while (index != previous) {
			  //1.7.1.1. 색인철에 끼운다.
			  this->indexBinder->PutIn(index);

			  previous = index;
			  index = this->correctQuizBinder->Next();
		  }
	  }

	  //트리뷰 초기화
	  GetDlgItem(IDC_TREE_INDEXES)->ModifyStyle(TVS_CHECKBOXES, 0);
	  GetDlgItem(IDC_TREE_INDEXES)->ModifyStyle(0, TVS_CHECKBOXES);


	
	  //1.8. 색인철에 색인이 1개 이상일 경우,
	  if (wLength > 0 || cLength > 0) { //트리뷰 핸들 추가 시작
		  //1.8.1. 색인리스트를 만든다.
		  this->indexBinder->MakeList(&indexes, &count);

		  //1.8.2. 색인리스트 개수만큼 반복한다.
		  while (i < count) {
			  //1.8.2.1. 알파벳 카테고리 핸들 하위에 알파벳 핸들 추가한다.
			  alphabets[0] = indexes[i].GetAlphabet();
			  alphabets[1] = '\0';
			  alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->InsertItem(alphabets, parent, TVI_LAST);


			  //1.8.2.2. 해당 알파벳 색인의 length만큼 반복한다.
			  indexLength = indexes[i].GetLength();
			  j = 0;
			  while (j < indexLength) {

				  //1.8.2.2.1. 해당 색인에 동일단어 있는지 확인한다.
				  index = indexes[i].GetAt(j);

				  indexes[i].FindSpellings(index, &sameIndexes, &sameCount);
				  //--------------------------------------------------------------------------------------------
				  //1.8.2.2.2. 동일단어가 있으면,
				  if (sameCount > 1) {
					  //1. 단어핸들 찾는다.
					  spelling = CString(index->GetSpelling().c_str());
					  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
						  ->GetNextItem(alphabetHandle, TVGN_CHILD);
					  word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
					  while (wordHandle != NULL && spelling != word) {
						  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
							  ->GetNextItem(wordHandle, TVGN_NEXT);
						  word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
					  }

					  //2. 단어핸들 없으면 추가한다.
					  if (wordHandle == NULL) {
						  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
							  ->InsertItem(spelling, alphabetHandle, TVI_LAST);
					  }

					  //3. 단어핸들 하위에 품사핸들 추가하고, 맞은 퀴즈면 체크한다.
					  wordClass = CString(index->GetWordClass().c_str());

					  wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
						  ->InsertItem(wordClass, wordHandle, TVI_LAST);

					  ox = CString(index->GetOx().c_str());
					  if (ox == "o") {
						  ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle, TRUE);
					  }
         		  }

				  //1.8.2.2.3. 동일단어 없으면,
				  else {
					  //1. 알파벳 핸들 하위에 단어핸들 추가하고, 맞은 퀴즈면 체크한다.					  
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


	 //1.9. 단어카드철의 단어카드가 1개 이상인 경우,
	if (wLength > 0) {
			  //1.9.1. 단어카드철에서 첫번째 단어를 현재 단어로 옮긴다.
			  index = this->wordCardBinder->First();


			  //1.9.2. 트리뷰 상 현재 단어의 알파벳 핸들 찾는다.
			  spelling = CString(index->GetSpelling().c_str());
			  indexIndex = this->indexBinder->Find((LPCTSTR)spelling);

			  alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
			  alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

			  while (alphabet != spelling[0] - 32) {
				  alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle,
					  TVGN_NEXT);
				  alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
			  }
			  //1.9.3. 트리뷰 상 알파벳 핸들 펼친다.
			  ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

			  //1.9.4. 트리뷰 상 현재 단어의 단어핸들 찾는다.
			  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
			  word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  while (spelling != word) {
				  wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
				  word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
			  }
			  //1.9.5. 해당 단어가 색인에 동일단어 있는지 확인한다.
			  indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
			  indexIndex->FindSpellings(index, &sameIndexes, &sameCount);

			  //1.9.6. 동일 단어가 있으면,
			  if (sameCount > 1) {
				  //1. 단어핸들의 몇 번째 품사인지 확인한다.
				  wordCardIndex = indexIndex->Find(index);
				  i = 0;
				  while (sameIndexes[i] != wordCardIndex) {
					  i++;
				  }
				  //2. 품사핸들 찾는다.
				  wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
				  j = 0;
				  while (j < i) {
					  wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))
						  ->GetNextItem(wordClassHandle, TVGN_NEXT);
					  j++;
				  }
				  //3. 단어핸들 펼쳐준다.
				  ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
				  //4. 해당 품사핸들을 선택된 상태로 처리한다.
				  ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
			  }
			  //1.9.7. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
			  else {
				  selectCheck = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);

			  }

			  if (sameIndexes != NULL) {
				  delete[] sameIndexes;
				  sameIndexes = NULL;
			  }

			  //1.4.2. 단어카드에 현재 단어카드 출력한다.
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
	//2. 꽂기 버튼 클릭했을 때
	  //2.1. 꽂기윈도우 출력한다.
      PuttingForm puttingForm;
	  puttingForm.DoModal();
}
void WordCardBinderForm::OnFindButtonClicked() {
	//3. 찾기 버튼 클릭했을 때
	  //3.1. 찾기윈도우 출력한다.
	FindingForm findingForm;
	findingForm.DoModal();
}
void WordCardBinderForm::OnPutOutButtonClicked() {
	//4. 뽑기 버튼 클릭했을 때
	  //4.1. 뽑기윈도우 출력한다.
	PuttingOutForm puttingOutForm;
	puttingOutForm.DoModal();
}
void WordCardBinderForm::OnQuizButtonClicked() {
	//5. 퀴즈 버튼 클릭했을 때
	  //5.1. 퀴즈윈도우 출력한다.
	QuizForm quizForm;
	quizForm.DoModal();
}
void WordCardBinderForm::OnCorrectQuizButtonClicked() {
	//6. 암기단어(맞은퀴즈철)버튼 클릭했을 때
	  //6.1. 암기단어 윈도우 출력한다.
	CorrectQuizForm correctQuizForm;
	correctQuizForm.DoModal();
}
void WordCardBinderForm::OnImportantWordsButtonClicked() {
	//7. 중요단어 버튼 클릭했을 때
	  //7.1. 중요단어 윈도우 출력한다.
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



	//8. 첫번째 버튼 클릭했을 때
	 //8.1. 첫번째 단어카드를 현재 카드로 옮긴다.
     index = this->wordCardBinder->First();

	 //8.2. 트리뷰 상 현재 단어의 알파벳핸들 찾는다.
	 spelling = CString(index->GetSpelling().c_str());

	 parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	 alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	 alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	 
	 while (alphabet != spelling[0] - 32) {
		 alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		 alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	 }

	 //8.3. 트리뷰 상 알파벳 핸들 펼친다.
	 ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	 //8.4. 트리뷰 상 현재 단어의 단어핸들 찾는다.
	 wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	 word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	 while (spelling != word) {
		 wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		 word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	 }

	 //8.5. 해당 단어가 색인에 동일단어 있는지 확인한다.
	 indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
	 indexIndex->FindSpellings(index, &indexes, &count);

	 //8.6. 동일단어 있으면,
	 if (count > 1) { //품사핸들을 찾아준다.

		 //8.6.2. 품사핸들 찾는다.
		 wordClass = CString(index->GetWordClass().c_str());
		 wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		 wordClassText= ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		 while (wordClassText != wordClass) {
			 wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			 wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		 }

		 //8.6.3. 단어핸들 펼쳐준다.
		 ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		 //8.6.4. 해당 품사핸들을 선택된 상태로 처리한다.
		 ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

	 }
	 //8.7. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
	 else {
		 ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
	 }

	 if (indexes != NULL) {
		 delete[] indexes;
		 indexes = NULL;
	 }

	 //8.2. 첫번째 단어카드의 철자,품사,의미,예시를 출력한다.
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


	//9. 이전 버튼 클릭했을 때
	 //9.1. 이전 단어카드를 현재 카드로 옮긴다.
	index = this->wordCardBinder->Previous();

	//9.2. 트리뷰 상 현재 단어의 알파벳핸들 찾는다.
	spelling = CString(index->GetSpelling().c_str());
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

	while (alphabet != spelling[0] - 32) {
		alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	}

	//9.3. 트리뷰 상 알파벳 핸들 펼친다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	//9.4. 트리뷰 상 현재 단어의 단어핸들 찾는다.
	wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	while (spelling != word) {
		wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	}

	//9.5. 해당 단어가 색인에 동일단어 있는지 확인한다.
	indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
	indexIndex->FindSpellings(index, &indexes, &count);

	//9.6. 동일단어 있으면,
	if (count > 1) {
		//9.6.1. 단어핸들의 몇번째 품사인지 확인한다.
		 //8.6.2. 품사핸들 찾는다.
		wordClass = CString(index->GetWordClass().c_str());
		wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		while (wordClassText != wordClass) {
			wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		}
		//9.6.3. 단어핸들 펼쳐준다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		//9.6.4. 해당 품사핸들을 선택된 상태로 처리한다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);


	}
	//9.7. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
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

	//9.2. 이전 단어카드의 철자,품사,의미,예시를 출력한다.
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

	//10. 다음 버튼 클릭했을 때
	 //10.1. 다음 단어카드를 현재 카드로 옮긴다.
	index = this->wordCardBinder->Next();

	//10.2. 트리뷰 상 현재 단어의 알파벳핸들 찾는다.
	spelling = CString(index->GetSpelling().c_str());
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

	while (alphabet != spelling[0] - 32) {
		alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	}

	//10.3. 트리뷰 상 알파벳 핸들 펼친다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	//10.4. 트리뷰 상 현재 단어의 단어핸들 찾는다.
	wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	while (spelling != word) {
		wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	}

	//10.5. 해당 단어가 색인에 동일단어 있는지 확인한다.
	indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
	indexIndex->FindSpellings(index, &indexes, &count);

	//10.6. 동일단어 있으면,
	if (count > 1) {
		//10.6.1. 단어핸들의 몇번째 품사인지 확인한다.
		//8.6.2. 품사핸들 찾는다.
		wordClass = CString(index->GetWordClass().c_str());
		wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		while (wordClassText != wordClass) {
			wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		}


		//10.6.3. 단어핸들 펼쳐준다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		//10.6.4. 해당 품사핸들을 선택된 상태로 처리한다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);


#if 0

		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordClassHandle, TRUE);
#endif

	}
	//10.7. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
	else {
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
#if 0
		//확인란을 사용 하려면 트리 컨트롤을 채우기 전에 TVS_CHECKBOXES을 설정 합니다.
		GetDlgItem(IDC_TREE_INDEXES)->ModifyStyle(0, TVS_CHECKBOXES);
		GetDlgItem(IDC_TREE_INDEXES)->ModifyStyle(TVS_CHECKBOXES, 0);

		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(wordHandle, TRUE);
#endif
	}

	if (indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}

	//10.2. 다음 단어카드의 철자,품사,의미,예시를 출력한다.
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

	//11. 마지막 버튼 클릭했을 때
	 //11.1. 마지막 단어카드를 현재 카드로 옮긴다.
	index = this->wordCardBinder->Last();

	//11.2. 트리뷰 상 현재 단어의 알파벳핸들 찾는다.
	spelling = CString(index->GetSpelling().c_str());
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
	alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

	while (alphabet != spelling[0] - 32) {
		alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
		alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
	}

	//11.3. 트리뷰 상 알파벳 핸들 펼친다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

	//11.4. 트리뷰 상 현재 단어의 단어핸들 찾는다.
	wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
	word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	while (spelling != word) {
		wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
		word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
	}

	//11.5. 해당 단어가 색인에 동일단어 있는지 확인한다.
	indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
	indexIndex->FindSpellings(index, &indexes, &count);

	//11.6. 동일단어 있으면,
	if (count > 1) {
		//11.6.1. 단어핸들의 몇번째 품사인지 확인한다.
		 //8.6.2. 품사핸들 찾는다.
		wordClass = CString(index->GetWordClass().c_str());
		wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
		wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

		while (wordClassText != wordClass) {
			wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
			wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
		}

		//11.6.3. 단어핸들 펼쳐준다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
		//11.6.4. 해당 품사핸들을 선택된 상태로 처리한다.
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);
	}
	//11.7. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
	else {
		((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordHandle);
	}

	if (indexes != NULL) {
		delete[] indexes;
		indexes = NULL;
	}

	//11.2. 마지막 단어카드의 철자,품사,의미,예시를 출력한다.
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

	//12. 중요단어추가버튼 클릭했을 때
	  //12.1. 현재 단어카드의 위치를 읽는다.
	  index = this->wordCardBinder->GetCurrent();
	  //12.2. 단어카드철에서 중요단어로 추가한다.
	  index = this->wordCardBinder->PutImportantWord(index);

	  //db에서 Modify한다.
	  Modify(index);


	  //12.3. 윈도우에 중요유무 출력한다.
	  isImportant = CString(index->GetIsImportant().c_str());
	  GetDlgItem(IDC_EDIT_ISIMPORTANT)->SetWindowText(isImportant);
}
void WordCardBinderForm::OnPutOutImportantWordButtonClicked() {
	WordCard* index;
	CString isImportant;

	//13. 중요단어취소버튼 클릭했을 때
	  //13.1. 현재 단어카드의 위치를 읽는다.
	index = this->wordCardBinder->GetCurrent();
	//13.2. 단어카드철에서 중요단어를 취소한다.
	index = this->wordCardBinder->PutOutImportantWord(index);

	//db에서 Modify한다.
	Modify(index);


	//13.3. 윈도우에 중요유무 출력한다.
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



	//1. 알파벳 카테고리 핸들을 구해놓는다.
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
	//2. 선택된 항목의 핸들을 구한다.
	current = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_CARET);
	//3. 선택된 항목의 부모를 읽는다.
	currentParent= ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(current, TVGN_PARENT);

	//4. 선택된 항목의 자식을 읽는다.
	currentChild= ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(current, TVGN_CHILD);
	//5. 선택된 항목의 조부모를 읽는다.
	currentGParent= ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(currentParent, TVGN_PARENT);

	// 선택된 항목의 체크박스 상태를 읽는다.
	ret = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetCheck(current);

	//6. currentParent가 parent가 아니고, currentChild가 null일 경우,
	if (currentParent != parent && currentChild == NULL && ret==FALSE) {

		//6.1. currentGParent가 parent가 아닐경우,(품사핸들일 경우)
		if (currentGParent != parent) {

			//6.1.1. currentParent의 text를 구한다.(apple)
			cpText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(currentParent);
			cText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(current);

			//6.1.3. current의 색인을 구한다.
			indexIndex = this->indexBinder->Find((LPCTSTR)cpText);

			//6.1.4. 해당 색인에서 current의 단어카드 찾는다.
			j = 0;
			index = indexIndex->GetAt(j);
			spelling = CString(index->GetSpelling().c_str());
			wordClass = CString(index->GetWordClass().c_str());

			while (spelling != cpText || wordClass != cText) { //하나라도 같지 않으면, 
				j++;

				index = indexIndex->GetAt(j);
				spelling = CString(index->GetSpelling().c_str());
				wordClass = CString(index->GetWordClass().c_str());
			}

			index = indexIndex->GetAt(j);

			//6.1.5. 해당 단어를 현재로 옮긴다.
			index = this->wordCardBinder->Move(index);

			//6.1.5. 해당 단어카드를 출력한다.
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
		//6.2. currentGParent가 parent일 경우,(단어핸들일 경우)
		else {
			//6.2.1. current의 text를 구한다.
			cText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(current);
			//6.2.2. current의 색인을 찾는다.
			indexIndex = this->indexBinder->Find((LPCTSTR)cText);

			//6.2.3. current가 색인의 몇 번째 있는지 구한다.
			i = 0;
			index = indexIndex->GetAt(i);
			spelling = CString(index->GetSpelling().c_str());
			while (spelling != cText) {
				i++;
				index = indexIndex->GetAt(i);
				spelling = CString(index->GetSpelling().c_str());
			}

			//6.2.4. 해당 단어카드를 현재 위치로 이동시킨다.
			index = indexIndex->GetAt(i);

			//6.1.5. 해당 단어를 현재로 옮긴다.
			index = this->wordCardBinder->Move(index);


			//6.1.5. 해당 단어카드를 출력한다.
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

	//1. 해당 핸들의 체크박스 상태를 구한다.
	((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(current);
	ret = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetCheck(current);


	//2. 해당 핸들의 단어카드를 구한다.
	  //2.1. 알파벳 카테고리 핸들을 구해놓는다.
	parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);

	//2.2. 선택된 항목의 부모를 읽는다.
	currentParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(current, TVGN_PARENT);

	//2.3. 선택된 항목의 자식을 읽는다.
	currentChild = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(current, TVGN_CHILD);

	//2.4. 선택된 항목의 조부모를 읽는다.
	currentGParent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(currentParent, TVGN_PARENT);

	//6. [선택한 핸들의 단어카드를 구한다.]currentParent가 parent가 아니고, currentChild가 null일 경우,
	if (currentParent != parent && currentChild == NULL) {

		//6.1. currentGParent가 parent가 아닐경우,(품사핸들일 경우)
		if (currentGParent != parent) {

			//6.1.1. currentParent의 text를 구한다.(apple)
			cpText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(currentParent);
			cText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(current);

			//6.1.3. current의 색인을 구한다.
			indexIndex = this->indexBinder->Find((LPCTSTR)cpText);

			//6.1.4. 해당 색인에서 current의 단어카드 찾는다.
			j = 0;
			index = indexIndex->GetAt(j);
			spelling = CString(index->GetSpelling().c_str());
			wordClass = CString(index->GetWordClass().c_str());

			while (spelling != cpText || wordClass != cText) { //하나라도 같지 않으면, 
				j++;

				index = indexIndex->GetAt(j);
				spelling = CString(index->GetSpelling().c_str());
				wordClass = CString(index->GetWordClass().c_str());
			}

			index = indexIndex->GetAt(j);

		}
		//6.2. currentGParent가 parent일 경우,(단어핸들일 경우)
		else if(currentGParent==parent){
			//6.2.1. current의 text를 구한다.
			cText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(current);
			//6.2.2. current의 색인을 찾는다.
			indexIndex = this->indexBinder->Find((LPCTSTR)cText);

			//6.2.3. current가 색인의 몇 번째 있는지 구한다.
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

		//3. "체크" 된 항목을 언체크하는 경우,[맞는퀴즈철 -> 단어카드철]
		if (ret == FALSE) {
			//맞은퀴즈철에서 뽑는다.
			temp = index;
			wordCard = this->correctQuizBinder->PutOut(index);
			spelling = CString(wordCard.GetSpelling().c_str());

			// 색인철에서 뽑는다.
			indexIndex = this->indexBinder->PutOut((LPCTSTR)spelling, temp);


			//db에서 delete한다.
			Delete(wordCard);

			//꽂은후 처리(PuttingForm)--------------------------------------------------------------------------------------

			//단어카드철에 꽂는다.
			//answer, ox 모두 초기화
			spelling = CString(wordCard.GetSpelling().c_str());
			wordClass = CString(wordCard.GetWordClass().c_str());
			meaning = CString(wordCard.GetMeaning().c_str());
			example = CString(wordCard.GetExample().c_str());
			isImportant = CString(wordCard.GetIsImportant().c_str());

			WordCard wordCard1((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
				(LPCTSTR)spelling, "", "", (LPCTSTR)meaning, (LPCTSTR)isImportant);

			index = this->wordCardBinder->PutIn(wordCard1);

			// 색인철에 꽂는다.
			indexIndex = this->indexBinder->PutIn(index);
			spelling = CString(index->GetSpelling().c_str());

			//db에 Insert한다.
			Insert(index);



			//해당 단어핸들을 선택으로 설정한다.
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(current, FALSE);


			//3.8. 꽂은 단어카드를  단어카드철 단어카드에 출력한다.
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

		else { //"언체크" 된 항목을 체크하는 경우,[단어카드철 -> 맞는퀴즈철]
			//------------------------------------------------------------------------------
			//뽑기전 처리(PuttingOutForm)
			//2.6.1. 단어카드철에서 뽑는다.
			temp = index;
			wordCard = this->wordCardBinder->PutOut(index);
			spelling = CString(wordCard.GetSpelling().c_str());

			//db에서 delete한다.
			Delete(wordCard);

			// 색인철에서 뽑는다.
			indexIndex = this->indexBinder->PutOut((LPCTSTR)spelling, temp);

			//꽂는 처리(PuttingForm)------------------------------------------------------------------------

			//2.6.2. 맞은퀴즈철에 꽂는다.
			//answer, ox 맞은걸로 설정,
			spelling = CString(wordCard.GetSpelling().c_str());
			wordClass = CString(wordCard.GetWordClass().c_str());
			meaning = CString(wordCard.GetMeaning().c_str());
			example = CString(wordCard.GetExample().c_str());
			isImportant = CString(wordCard.GetIsImportant().c_str());
			ox = "o";

			WordCard wordCard1((LPCTSTR)spelling, (LPCTSTR)wordClass, (LPCTSTR)meaning, (LPCTSTR)example,
				(LPCTSTR)spelling, (LPCTSTR)spelling, (LPCTSTR)ox, (LPCTSTR)meaning, (LPCTSTR)isImportant);

			index = this->correctQuizBinder->PutIn(wordCard1);


			//db에 Insert한다.
			Insert(index);


			// 색인철에 꽂는다.
			indexIndex = this->indexBinder->PutIn(index);
			spelling = CString(index->GetSpelling().c_str());


			//해당 단어핸들을 선택으로 설정한다.
			((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SetCheck(current, TRUE);

			//-------------------------------------------------------------------------------


			//2.6.3. 단어카드철 윈도우에 현재 단어카드가 있는지 확인한다.
			index = this->wordCardBinder->GetCurrent();
			//2.6.4. 현재 카드가 있으면 단어카드철 윈도우의 단어카드철에 출력한다.
			if (index != NULL) {

				//해당 항목의 핸들을 찾아 체크한다.
				//-------------------------------------------------------
					 //8.2. 트리뷰 상 현재 단어의 알파벳핸들 찾는다.
				spelling = CString(index->GetSpelling().c_str());

				parent = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(NULL, TVGN_ROOT);
				alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(parent, TVGN_CHILD);
				alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);

				while (alphabet != spelling[0] - 32) {
					alphabetHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_NEXT);
					alphabet = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(alphabetHandle);
				}

				//8.3. 트리뷰 상 알파벳 핸들 펼친다.
				((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(alphabetHandle, TVE_EXPAND);

				//8.4. 트리뷰 상 현재 단어의 단어핸들 찾는다.
				wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(alphabetHandle, TVGN_CHILD);
				word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				while (spelling != word) {
					wordHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_NEXT);
					word = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordHandle);
				}

				//8.5. 해당 단어가 색인에 동일단어 있는지 확인한다.
				indexIndex = this->indexBinder->Find((LPCTSTR)spelling);
				indexIndex->FindSpellings(index, &indexes, &count);

				//8.6. 동일단어 있으면,
				if (count > 1) { //품사핸들을 찾아준다.

					//8.6.2. 품사핸들 찾는다.
					wordClass = CString(index->GetWordClass().c_str());
					wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordHandle, TVGN_CHILD);
					wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);

					while (wordClassText != wordClass) {
						wordClassHandle = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetNextItem(wordClassHandle, TVGN_NEXT);
						wordClassText = ((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->GetItemText(wordClassHandle);
					}

					//8.6.3. 단어핸들 펼쳐준다.
					((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->Expand(wordHandle, TVE_EXPAND);
					//8.6.4. 해당 품사핸들을 선택된 상태로 처리한다.
					((CTreeCtrl*)GetDlgItem(IDC_TREE_INDEXES))->SelectItem(wordClassHandle);

				}
				//8.7. 해당 색인에 동일단어 없으면, 단어핸들을 선택된 상태로 처리한다.
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
			//2.6.5. 현재 카드가 없으면 공백 처리한다.
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
	//14.2. 닫기버튼 클릭했을 때
	  //14.0 저장한다.
	    Save();

	  //14.1. 단어카드철 없앤다.
	  if (this->wordCardBinder != NULL) {

		  delete this->wordCardBinder;
		  this->wordCardBinder = NULL;
	  }
	  //14.2. 맞은퀴즈철 없앤다.
	  if (this->correctQuizBinder != NULL) {

		  delete this->correctQuizBinder;
		  this->correctQuizBinder = NULL;
	  }
	  EndDialog(0);
}
