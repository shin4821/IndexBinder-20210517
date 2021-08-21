//IndexBinder.cpp
#include"IndexBinder.h"
#include"WordCardBinder.h"
#include"CorrectQuizBinder.h"

IndexBinder::IndexBinder() {
	this->length = 0;
}
IndexBinder::~IndexBinder() {
}

Index* IndexBinder::PutIn(WordCard* index) {
	BinaryTree<Index>::Node* node;
	Index* key;
	char alphabet = index->GetSpelling()[0];
	
	//1. indexCard를 만든다.
	if (alphabet > 96 && alphabet < 123) { //소문자이면 대문자로 변환
		alphabet = alphabet - 32;
	}
	Index indexCard(alphabet);

	//2. 해당 Index가 있는지 없는지 확인한다.
	node = this->indexes.Search(indexCard, CompareAlphabet);

	//3. 해당 Index가 없으면 색인철에 꽂는다.
	if (node == 0) {
		node = this->indexes.Insert(indexCard, CompareAlphabet);
		this->length++;
	}
	//4. 해당 Index에 단어카드를 꽂는다.
	key = &node->GetKey();
	key->PutIn(index);

	return key;
}

Index* IndexBinder::Find(string spelling) {
	char alphabet = spelling[0];
	BinaryTree<Index>::Node* node;
	Index* key = 0;

	//1. indexCard를 만든다.
	if (alphabet > 96 && alphabet < 123) {//소문자면 대문자로 변환
		alphabet = alphabet - 32;
	}
	Index indexCard(alphabet);

	//2. 해당 색인을 찾는다.
	node = this->indexes.Search(indexCard, CompareAlphabet);

	//3. node가 null이 아니면,
	if (node != 0) {
		key = &node->GetKey();
	}

	return key;
}

Index* IndexBinder::PutOut(string spelling, WordCard* index) {
	BinaryTree<Index>::Node* node;
	Index* key;
	Long index_;
	char alphabet = spelling[0];

	//1. 해당 색인(Index)을 찾는다.
	if (alphabet > 96 && alphabet < 123) {//소문자면 대문자로 변환
		alphabet = alphabet - 32;
	}
	Index indexCard(alphabet);
	node = this->indexes.Search(indexCard, CompareAlphabet);

	//2. 해당 Index에서 뽑은 카드가 몇번째인지 찾는다.
	key = &node->GetKey();
	index_ = key->Find(index);

	//3. 해당 번째를 색인에서 뽑는다.
	key->PutOut(index_);

	//4. 색인의 length가 0보다 같거나 작으면 해당 색인을 뽑는다.
	Long length = key->GetLength();
	if (length <= 0) {
		this->indexes.Delete(indexCard, CompareAlphabet);
		key = 0; //색인 뽑았으면 null처리 한다.
		this->length--;
	}

	return key;
}

BinaryTree<Index>::Node* IndexBinder::GetRoot() {

	return this->indexes.GetRoot();
}

void Node_Arrange(BinaryTree<Index>::Node* node) {
	if (node->GetLeft() != 0) {
		Node_Arrange(node->GetLeft());
	}

	node->GetKey().Arrange();

	if (node->GetRight() != 0) {
		Node_Arrange(node->GetRight());
	}
}

void IndexBinder::Arrange() {
	this->indexes.MakeBalance();
	Node_Arrange(this->indexes.GetRoot());
}

void IndexBinder::MakeList(Index* (*indexes), Long* count) {
	this->indexes.MakeKeys(indexes, count);
}


int CompareAlphabet(void* one, void* other) {
	Index* one_ = (Index*)one;
	Index* other_ = (Index*)other;
	int ret;

	if (one_->GetAlphabet() == other_->GetAlphabet()) {
		ret = 0;
	}
	else if(one_->GetAlphabet() > other_->GetAlphabet()) {
		ret = 1;
	}
	else if (one_->GetAlphabet() < other_->GetAlphabet()) {
		ret = -1;
	}
	return ret;
}


#include<iostream>
using namespace std;

void Print(BinaryTree<Index>::Node* node);
int main(int argc, char* argv[]) {
	IndexBinder indexBinder;
	WordCardBinder wordCardBinder;
	WordCard wordCard;
	Index* index;
	WordCard* index_;
	Long i;
	Long j;
	BinaryTree<Index>::Node* root;
	Index(*indexes);
	Long count;


	WordCard wordCard1("apple", "명사", "사과", "I like apple", "apple", "", "", "사과", "");
	index_ = wordCardBinder.PutIn(wordCard1);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard2("arrange", "동사", "정렬하다", "Have you arranged?", "arrange", "", "", "정렬하다", "");
	index_ = wordCardBinder.PutIn(wordCard2);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard3("alright", "형용사", "맞는", "It's alright", "alright", "", "", "맞는", "");
	index_ = wordCardBinder.PutIn(wordCard3);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard4("brain", "형용사", "똑똑한", "You're brain.", "brain", "", "", "똑똑한", "");
	index_ = wordCardBinder.PutIn(wordCard4);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard5("bee", "명사", "꿀벌", "There's a bee", "bee", "", "", "꿀벌", "");
	index_ = wordCardBinder.PutIn(wordCard5);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard6("balance", "동사", "균형을 유지하다", "Try to keep a balance", "balance", "", "", 
		"균형을 유지하다", "");
	index_ = wordCardBinder.PutIn(wordCard6);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	index = indexBinder.Find("arrange");
	cout << index->GetAlphabet() << endl;

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl<<endl;
		i++;
	}

#if 0

	cout << "bee 뽑기" << endl;

	index_ = wordCardBinder.FindSpelling("bee");
	wordCard = wordCardBinder.PutOut(index_); //단어카드철에서 뽑고
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //색인철에서 뽑는다.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}

	cout << "전체 색인 현황" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;


	cout << "brain 뽑기" << endl;

	index_ = wordCardBinder.FindSpelling("brain");
	wordCard = wordCardBinder.PutOut(index_); //단어카드철에서 뽑고
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //색인철에서 뽑는다.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}

	cout << "전체 색인 현황" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;

	cout << "balance 뽑기" << endl;

	index_ = wordCardBinder.FindSpelling("balance");
	wordCard = wordCardBinder.PutOut(index_); //단어카드철에서 뽑고
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //색인철에서 뽑는다.

	cout << "전체 색인 현황" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;

	cout << "apple 뽑기" << endl;

	index_ = wordCardBinder.FindSpelling("apple");
	wordCard = wordCardBinder.PutOut(index_); //단어카드철에서 뽑고
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //색인철에서 뽑는다.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}

	cout << "전체 색인 현황" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;

	cout << "alright 뽑기" << endl;

	index_ = wordCardBinder.FindSpelling("alright");
	wordCard = wordCardBinder.PutOut(index_); //단어카드철에서 뽑고
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //색인철에서 뽑는다.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}

	cout << "전체 색인 현황" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;

	cout << "arrange 뽑기" << endl;

	index_ = wordCardBinder.FindSpelling("arrange");
	wordCard = wordCardBinder.PutOut(index_); //단어카드철에서 뽑고
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //색인철에서 뽑는다.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}
#endif

	cout << "전체 색인 현황" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;

	cout << "Arrange" << endl;
	indexBinder.Arrange();
	root = indexBinder.GetRoot();
	Print(root);

	cout << "MakeList" << endl;
	indexBinder.MakeList(&indexes, &count);
	i = 0;
	while (i < count) {
		j = 0;
		while (j < indexes[i].GetLength()) {
			index_=indexes[i].GetAt(j);
			cout << index_->GetSpelling() << endl;
			j++;
		}

		i++;
	}


	return 0;
}

void Print(BinaryTree<Index>::Node* node) { //전체 색인 출력 함수
	if (node->GetLeft() != 0) {
		Print(node->GetLeft());
	}

	Long i = 0;
	Index* index = &node->GetKey();
	cout << index->GetAlphabet() << endl;

	while (i < index->GetLength()) {
		WordCard* index_ = index->GetAt(i);
		cout << index_->GetSpelling() << endl;
		i++;
	}


	if (node->GetRight() != 0) {
		Print(node->GetRight());
	}
}



