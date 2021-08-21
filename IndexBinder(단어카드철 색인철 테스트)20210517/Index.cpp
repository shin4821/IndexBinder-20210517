//Index.cpp
#include"Index.h"
#include"WordCardBinder.h"
#include"CorrectQuizBinder.h"

Index::Index(Long capacity)
	:alphabet(' '){
	this->capacity = capacity;
	this->length = 0;
}

Index::~Index() {
}

Index::Index(char alphabet, Long capacity)
	:alphabet(alphabet) {
	this->capacity = capacity;
	this->length = 0;
}


Long Index::PutIn(WordCard* key) {
	Long index;

	if (this->capacity > this->length) {
		index = this->wordCards.Store(this->length, key);
	}
	else if (this->capacity <= this->length) {
		index = this->wordCards.AppendForRear(key);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Index::Find(WordCard* key) {
	Long index = 0;

	index = this->wordCards.LinearSearchUnique(key, CompareWordCard);

	return index;
}

void Index::FindSpellings(WordCard* key, Long* (*indexes), Long* count) {

	this->wordCards.LinearSearchDuplicate(key, indexes, count, CompareSameSpelling);
}

Long Index::PutOut(Long index) {
	Long index_;

	index_ = this->wordCards.Delete(index);

	this->capacity--;
	this->length--;

	return index_;
}

void Index::Arrange() {
	this->wordCards.SelectionSort(CompareSpelling);
}

WordCard* Index::GetAt(Long index) {
	return this->wordCards.GetAt(index);
}


int CompareWordCard(void* one, void* other) {
	WordCard** one_ = (WordCard**)one;
	WordCard* other_ = (WordCard*)other;
	int ret;

	if (*one_ == other_) {
		ret = 0;
	}
	else{
		ret = -1;
	}

	return ret;
}

int CompareSpelling(void* one, void* other) {
	WordCard** one_ = (WordCard**)one;
	WordCard** other_ = (WordCard**)other;
	int ret;

	if ((*one_)->GetSpelling().compare((*other_)->GetSpelling()) == 0) {
		ret = 0;
	}
	else if ((*one_)->GetSpelling().compare((*other_)->GetSpelling()) > 0) {
		ret = 1;
	}
	else if ((*one_)->GetSpelling().compare((*other_)->GetSpelling()) < 0) {
		ret = -1;
	}

	return ret;
}

int CompareSameSpelling(void* one, void* other) {
	WordCard** one_ = (WordCard**)one;
	WordCard* other_ = (WordCard*)other;
	int ret;

	if ((*one_)->GetSpelling().compare(other_->GetSpelling()) == 0) {
		ret = 0;
	}
	else {
		ret = -1;
	}

	return ret;
}


#if 0

#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	Index index;
	WordCard* index_;
	Long(*indexes);
	Long count;
	Long i;
	WordCardBinder wordCardBinder;

	WordCard wordCard1("apple","���","���","I like apple","apple","","","���","");
	index_ = wordCardBinder.PutIn(wordCard1);
#if 0
	cout << wordCard1.GetSpelling() << endl;
#endif
	i = index.PutIn(index_);
	cout << i << endl;

	WordCard wordCard2("arrange", "����", "�����ϴ�", "Have you arranged?", "arrange", "", "", "�����ϴ�", "");
	index_ = wordCardBinder.PutIn(wordCard2);
	i = index.PutIn(index_);
	cout << i << endl;

	WordCard wordCard3("alright", "�����", "�´�", "It's alright", "alright", "", "", "�´�", "");
	index_ = wordCardBinder.PutIn(wordCard3);
	i = index.PutIn(index_);
	cout << i << endl;

	index_ = wordCardBinder.First();
	index_ = wordCardBinder.Next();
	i = index.Find(index_);
	cout << i << endl;

#if 0
	wordCardBinder.PutOut(index_);
	i = index.Find(index_);
	cout <<"���� ��ġ"<<":"<< i << endl;

	index.PutOut(i);

	i = 0;
	while (i < index.GetLength()) {
		index_ = index.GetAt(i);
		cout << index_->GetSpelling() << endl;
		i++;
	}
#endif

	index.Arrange();
	i = 0;
	while (i < index.GetLength()) {
		index_ = index.GetAt(i);
		cout << index_->GetSpelling() << endl;
		i++;
	}


	Index index1('b');
	cout << index1.GetAlphabet() << endl;


	return 0;
}

#endif
