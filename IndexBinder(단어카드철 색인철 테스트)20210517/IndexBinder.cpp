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
	
	//1. indexCard�� �����.
	if (alphabet > 96 && alphabet < 123) { //�ҹ����̸� �빮�ڷ� ��ȯ
		alphabet = alphabet - 32;
	}
	Index indexCard(alphabet);

	//2. �ش� Index�� �ִ��� ������ Ȯ���Ѵ�.
	node = this->indexes.Search(indexCard, CompareAlphabet);

	//3. �ش� Index�� ������ ����ö�� �ȴ´�.
	if (node == 0) {
		node = this->indexes.Insert(indexCard, CompareAlphabet);
		this->length++;
	}
	//4. �ش� Index�� �ܾ�ī�带 �ȴ´�.
	key = &node->GetKey();
	key->PutIn(index);

	return key;
}

Index* IndexBinder::Find(string spelling) {
	char alphabet = spelling[0];
	BinaryTree<Index>::Node* node;
	Index* key = 0;

	//1. indexCard�� �����.
	if (alphabet > 96 && alphabet < 123) {//�ҹ��ڸ� �빮�ڷ� ��ȯ
		alphabet = alphabet - 32;
	}
	Index indexCard(alphabet);

	//2. �ش� ������ ã�´�.
	node = this->indexes.Search(indexCard, CompareAlphabet);

	//3. node�� null�� �ƴϸ�,
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

	//1. �ش� ����(Index)�� ã�´�.
	if (alphabet > 96 && alphabet < 123) {//�ҹ��ڸ� �빮�ڷ� ��ȯ
		alphabet = alphabet - 32;
	}
	Index indexCard(alphabet);
	node = this->indexes.Search(indexCard, CompareAlphabet);

	//2. �ش� Index���� ���� ī�尡 ���°���� ã�´�.
	key = &node->GetKey();
	index_ = key->Find(index);

	//3. �ش� ��°�� ���ο��� �̴´�.
	key->PutOut(index_);

	//4. ������ length�� 0���� ���ų� ������ �ش� ������ �̴´�.
	Long length = key->GetLength();
	if (length <= 0) {
		this->indexes.Delete(indexCard, CompareAlphabet);
		key = 0; //���� �̾����� nulló�� �Ѵ�.
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


	WordCard wordCard1("apple", "���", "���", "I like apple", "apple", "", "", "���", "");
	index_ = wordCardBinder.PutIn(wordCard1);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard2("arrange", "����", "�����ϴ�", "Have you arranged?", "arrange", "", "", "�����ϴ�", "");
	index_ = wordCardBinder.PutIn(wordCard2);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard3("alright", "�����", "�´�", "It's alright", "alright", "", "", "�´�", "");
	index_ = wordCardBinder.PutIn(wordCard3);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard4("brain", "�����", "�ȶ���", "You're brain.", "brain", "", "", "�ȶ���", "");
	index_ = wordCardBinder.PutIn(wordCard4);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard5("bee", "���", "�ܹ�", "There's a bee", "bee", "", "", "�ܹ�", "");
	index_ = wordCardBinder.PutIn(wordCard5);
	index = indexBinder.PutIn(index_);
	cout << index->GetAlphabet() << endl;

	WordCard wordCard6("balance", "����", "������ �����ϴ�", "Try to keep a balance", "balance", "", "", 
		"������ �����ϴ�", "");
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

	cout << "bee �̱�" << endl;

	index_ = wordCardBinder.FindSpelling("bee");
	wordCard = wordCardBinder.PutOut(index_); //�ܾ�ī��ö���� �̰�
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //����ö���� �̴´�.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}

	cout << "��ü ���� ��Ȳ" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;


	cout << "brain �̱�" << endl;

	index_ = wordCardBinder.FindSpelling("brain");
	wordCard = wordCardBinder.PutOut(index_); //�ܾ�ī��ö���� �̰�
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //����ö���� �̴´�.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}

	cout << "��ü ���� ��Ȳ" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;

	cout << "balance �̱�" << endl;

	index_ = wordCardBinder.FindSpelling("balance");
	wordCard = wordCardBinder.PutOut(index_); //�ܾ�ī��ö���� �̰�
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //����ö���� �̴´�.

	cout << "��ü ���� ��Ȳ" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;

	cout << "apple �̱�" << endl;

	index_ = wordCardBinder.FindSpelling("apple");
	wordCard = wordCardBinder.PutOut(index_); //�ܾ�ī��ö���� �̰�
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //����ö���� �̴´�.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}

	cout << "��ü ���� ��Ȳ" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;

	cout << "alright �̱�" << endl;

	index_ = wordCardBinder.FindSpelling("alright");
	wordCard = wordCardBinder.PutOut(index_); //�ܾ�ī��ö���� �̰�
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //����ö���� �̴´�.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}

	cout << "��ü ���� ��Ȳ" << endl;
	root = indexBinder.GetRoot();
	Print(root);
	cout << "-------------------------------" << endl;

	cout << "arrange �̱�" << endl;

	index_ = wordCardBinder.FindSpelling("arrange");
	wordCard = wordCardBinder.PutOut(index_); //�ܾ�ī��ö���� �̰�
	index = indexBinder.PutOut(wordCard.GetSpelling(), index_); //����ö���� �̴´�.

	i = 0;
	while (i < index->GetLength()) {
		index_ = index->GetAt(i);

		cout << index_->GetSpelling() << endl;
		i++;
	}
#endif

	cout << "��ü ���� ��Ȳ" << endl;
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

void Print(BinaryTree<Index>::Node* node) { //��ü ���� ��� �Լ�
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



