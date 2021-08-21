//CorrectQuizBinder.cpp
#include"CorrectQuizBinder.h"

CorrectQuizBinder::CorrectQuizBinder() {
	this->length = 0;
	this->current = 0;
}

CorrectQuizBinder::~CorrectQuizBinder() {
}

CorrectQuizBinder::CorrectQuizBinder(const CorrectQuizBinder& source)
	:wordCards(source.wordCards) {
	this->length = source.length;
	this->current = &this->wordCards.GetCurrent()->GetObject();
}

CorrectQuizBinder& CorrectQuizBinder::operator=(const CorrectQuizBinder& source) {
	this->wordCards = source.wordCards;
	this->length = source.length;
	this->current = &this->wordCards.GetCurrent()->GetObject();

	return *this;
}

WordCard* CorrectQuizBinder::PutIn(WordCard wordCard) {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.AppendFromTail(wordCard);
	this->length++;
	this->current = &node->GetObject();

	return this->current;
}

WordCard CorrectQuizBinder::PutOut(WordCard* index) {
	LinkedList<WordCard>::Node* node;
	WordCard wordCard;

	node = this->wordCards.LinearSearchUnique(index, CompareCorrectQuizCard);
	wordCard = node->GetObject();

	this->wordCards.Delete(node);
	this->length--;
	node = this->wordCards.GetCurrent();
	if (node != 0) {
		this->current = &node->GetObject();
	}
	else {
		this->current = 0;
	}

	return wordCard;
}




WordCard* CorrectQuizBinder::First() {
	LinkedList<WordCard>::Node* node;
	
	node = this->wordCards.First();
	this->current = &node->GetObject();

	return this->current;
}

WordCard* CorrectQuizBinder::Previous() {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.Previous();
	this->current = &node->GetObject();

	return this->current;
}

WordCard* CorrectQuizBinder::Next() {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.Next();
	this->current = &node->GetObject();

	return this->current;
}


WordCard* CorrectQuizBinder::Last() {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.Last();
	this->current = &node->GetObject();

	return this->current;
}

void CorrectQuizBinder::Reset() {
	LinkedList<WordCard>::Node* node;
	WordCard* index;
	LinkedList<WordCard>::Node* previous = 0;

	node = this->wordCards.First();
	while (node != previous) {
		index = &node->GetObject();
		index->Reset();
		previous = node;
		node = this->wordCards.Next();	
	}
}



int CompareCorrectQuizCard(void* one, void* other) {
	WordCard* one_ = (WordCard*)one;
	WordCard* other_ = (WordCard*)other;
	int ret;

	if (one_ == other_) {
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
	CorrectQuizBinder correctQuizBinder1;
	WordCard* index;
	WordCard* previous = 0;


	WordCard wordCard1("apple", "명사", "사과", "I like apple", "apple", "바나나", "x", "사과", "");
	index = correctQuizBinder1.PutIn(wordCard1);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	WordCard wordCard2("banana", "명사", "바나나", "Do you like banana?", "banana", "딸기", "x", "바나나", "");
	index = correctQuizBinder1.PutIn(wordCard2);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	CorrectQuizBinder correctQuizBinder(correctQuizBinder1);
	index = correctQuizBinder.First();
	while (index != previous) {
		cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
			index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
			index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

		previous = index;
		index = correctQuizBinder.Next();
	}

	WordCard wordCard3("good", "형용사", "좋은", "Is it good?", "good", "좋은", "o", "좋은", "");
	index = correctQuizBinder1.PutIn(wordCard3);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;
	
	cout << "치환연산자" << endl << endl;
	correctQuizBinder = correctQuizBinder1;
	index = correctQuizBinder.First();
	while (index != previous) {
		cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
			index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
			index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

		previous = index;
		index = correctQuizBinder.Next();
	}

	index = correctQuizBinder.First();
	WordCard wordCard = correctQuizBinder.PutOut(index);
	cout << wordCard.GetSpelling() << "-" << wordCard.GetWordClass() << "-" << wordCard.GetMeaning() << "-" <<
		wordCard.GetExample() << endl;

	cout << "뽑고나서" << endl << endl;

	index = correctQuizBinder.First();
	while (index != previous) {
		cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
			index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
			index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

		previous = index;
		index = correctQuizBinder.Next();
	}

	correctQuizBinder.Reset();
	index = correctQuizBinder.First();
	while (index != previous) {
		cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
			index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
			index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

		previous = index;
		index = correctQuizBinder.Next();
	}


	return 0;
}

#endif















