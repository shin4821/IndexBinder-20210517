//WordCardBinder.cpp
#include"WordCardBinder.h"

WordCardBinder::WordCardBinder() {
	this->length = 0;
	this->current = 0;
}

WordCardBinder::~WordCardBinder() {
}

WordCardBinder::WordCardBinder(const WordCardBinder& source)
	:wordCards(source.wordCards) {
	this->length = source.length;
	this->current = &this->wordCards.GetCurrent()->GetObject();
}

WordCardBinder& WordCardBinder::operator=(const WordCardBinder& source) {
	this->wordCards = source.wordCards;
	this->length = source.length;
	this->current = &this->wordCards.GetCurrent()->GetObject();

	return *this;
}

WordCard* WordCardBinder::PutIn(WordCard wordCard) {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.AppendFromTail(wordCard);
	this->length++;
	this->current = &node->GetObject();

	return this->current;
}

void WordCardBinder::FindBySpelling(string spelling, WordCard** (*indexes), Long* count) {
	LinkedList<WordCard>::Node* (*nodes);

	this->wordCards.LinearSearchDuplicate(&spelling, &nodes, count, CompareSpellings);
	*indexes = new WordCard * [this->length];
	Long i = 0;
	while (i < *count) {
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}

	if (nodes != 0) {
		delete[] nodes;
	}
}

void WordCardBinder::FindByMeaning(string meaning, WordCard** (*indexes), Long* count) {
	LinkedList<WordCard>::Node* (*nodes);

	this->wordCards.LinearSearchDuplicate(&meaning, &nodes, count, CompareMeanings);
	*indexes = new WordCard * [this->length];
	Long i = 0;
	while (i < *count) {
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}

	if (nodes != 0) {
		delete[] nodes;
	}
}

WordCard* WordCardBinder::FindSpelling(string spelling) {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.LinearSearchUnique(&spelling, CompareSpellings);
	WordCard* index = 0;

	if (node != 0) {
		index = &node->GetObject();
	}

	return index;
}

WordCard* WordCardBinder::First() {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.First();
	this->current = &node->GetObject();

	return this->current;
}

WordCard* WordCardBinder::Previous() {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.Previous();
	this->current = &node->GetObject();

	return this->current;
}

WordCard* WordCardBinder::Next() {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.Next();
	this->current = &node->GetObject();

	return this->current;
}

WordCard* WordCardBinder::Last() {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.Last();
	this->current = &node->GetObject();

	return this->current;
}

WordCard* WordCardBinder::Move(WordCard* index) {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.LinearSearchUnique(index, CompareWordCards);
	this->current = &node->GetObject();

	return this->current;
}

WordCard WordCardBinder::PutOut(WordCard* index) {
	LinkedList<WordCard>::Node* node;
	WordCard wordCard;

	node = this->wordCards.LinearSearchUnique(index, CompareWordCards);
	wordCard = node->GetObject();

	this->wordCards.Delete(node);
	this->length--;
	
	if (this->wordCards.GetCurrent() != 0) {
		this->current = &this->wordCards.GetCurrent()->GetObject();
	}
	else {
		this->current = 0;
	}

	return wordCard;
}

WordCard WordCardBinder::GetAt(WordCard* index) {
	LinkedList<WordCard>::Node* node;

	node = this->wordCards.LinearSearchUnique(index, CompareWordCards);
	WordCard wordCard = node->GetObject();

	return wordCard;
}

WordCard* WordCardBinder::PutImportantWord(WordCard* index) {
	index->PutImportantWord();

	return index;
}

WordCard* WordCardBinder::PutOutImportantWord(WordCard* index) {
	index->PutOutImportantWord();

	return index;
}

void WordCardBinder::FindImportantWords(WordCard** (*indexes), Long* count) {
	LinkedList<WordCard>::Node* (*nodes);
	string key = "중요";

	this->wordCards.LinearSearchDuplicate(&key, &nodes, count, CompareImportantWords);
	(*indexes) = new WordCard * [this->length];
	Long i = 0;
	while (i < *count) {
		(*indexes)[i] = &nodes[i]->GetObject();
		i++;
	}

	if (nodes != 0) {
		delete[] nodes;
	}

}

bool WordCardBinder::SpellingQuiz(string meaning, WordCard* index) {
	bool ret;

	ret = index->SpellingQuiz(meaning);

	return ret;
}

WordCard* WordCardBinder::NextQuiz() {
	LinkedList<WordCard>::Node* current;
	LinkedList<WordCard>::Node* node;
	WordCard* nextQuiz = 0;

	current = this->wordCards.GetCurrent();
	node = this->wordCards.Next();
	if (current != node) {
		nextQuiz = &node->GetObject();
	}

	return nextQuiz;
}


int CompareSpellings(void* one, void* other) {
	WordCard* one_ = (WordCard*)one;
	string* other_ = (string*)other;
	int ret;

	ret = one_->GetSpelling().compare(*other_);

	return ret;
}

int CompareMeanings(void* one, void* other) {
	WordCard* one_ = (WordCard*)one;
	string* other_ = (string*)other;
	int ret;

	ret = one_->GetMeaning().compare(*other_);

	return ret;
}

int CompareWordCards(void* one, void* other) {
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

int CompareImportantWords(void* one, void* other) {
	WordCard* one_ = (WordCard*)one;
	string* other_ = (string*)other;
	int ret;

	ret = one_->GetIsImportant().compare(*other_);

	return ret;
}

#if 0

#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	WordCardBinder wordCardBinder;
	WordCard* index;
	WordCard* previous = 0;
	WordCard* (*indexes);
	Long count;
	Long i = 0;
	bool ret;

	WordCard wordCard1("list", "명사", "리스트", "A shopping list", "list", "", "", "리스트", "");
	index = wordCardBinder.PutIn(wordCard1);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" << 
		index->GetOx() << "-" <<index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	WordCard wordCard2("apple", "명사", "사과", "I like apple", "apple", "", "", "사과", "");
	index = wordCardBinder.PutIn(wordCard2);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	WordCard wordCard3("list", "동사", "항목을 작성하다", "We listed our favorite songs", "list", "", "",
		"항목을 작성하다", "");
	index = wordCardBinder.PutIn(wordCard3);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	WordCard wordCard4("good", "형용사", "좋은", "It's good", "good", "", "", "좋은", "");
	index = wordCardBinder.PutIn(wordCard4);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	WordCard wordCard5("good", "형용사", "좋은", "Is it good?", "good", "", "", "좋은", "");
	index = wordCardBinder.PutIn(wordCard5);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	wordCardBinder.FindBySpelling("list", &indexes, &count);
	while (i < count) {
		cout << indexes[i]->GetSpelling() << "-" << indexes[i]->GetWordClass() << "-" << indexes[i]->GetMeaning() << "-" <<
			indexes[i]->GetExample() << endl;
		i++;
	}
	
	if (indexes != 0) {
		delete[] indexes;
	}

	wordCardBinder.FindByMeaning("좋은", &indexes, &count);
	i = 0;
	while (i < count) {
		cout << indexes[i]->GetSpelling() << "-" << indexes[i]->GetWordClass() << "-" << indexes[i]->GetMeaning() << "-" <<
			indexes[i]->GetExample() << endl;
		i++;
	}

	if (indexes != 0) {
		delete[] indexes;
	}

	index = wordCardBinder.FindSpelling("apple");
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	index = wordCardBinder.Move(index);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	wordCardBinder.First();
	index = wordCardBinder.Next();
	WordCard wordCard;
	wordCard = wordCardBinder.PutOut(index);
	cout << wordCard.GetSpelling() << "-" << wordCard.GetWordClass() << "-" << wordCard.GetMeaning() << "-" <<
		wordCard.GetExample() << endl;

	index = wordCardBinder.Last();
	wordCard = wordCardBinder.GetAt(index);
	cout << wordCard.GetSpelling() << "-" << wordCard.GetWordClass() << "-" << wordCard.GetMeaning() << "-" <<
		wordCard.GetExample() << endl;

#if 0
	index = wordCardBinder.First();
	while (index != previous) {
		cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
			index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
			index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

		previous = index;
		index = wordCardBinder.Next();
	}
#endif

	index = wordCardBinder.First();
	wordCardBinder.PutImportantWord(index);
	index = wordCardBinder.Last();
	wordCardBinder.PutImportantWord(index);
	wordCardBinder.FindImportantWords(&indexes, &count);

	i = 0;
	while (i < count) {
		cout << indexes[i]->GetSpelling() << "-" << indexes[i]->GetWordClass() << "-" << indexes[i]->GetMeaning() << "-" <<
			indexes[i]->GetExample() << "-" << indexes[i]->GetIsImportant() << endl;
		i++;	
	}

	if (indexes != 0) {
		delete[] indexes;
	}

	index = wordCardBinder.First();
	wordCardBinder.PutOutImportantWord(index);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl;

	index = wordCardBinder.Last();
	wordCardBinder.PutOutImportantWord(index);
	cout << index->GetSpelling() << "-" << index->GetWordClass() << "-" << index->GetMeaning() << "-" <<
		index->GetExample() << "-" << index->GetQuizSpelling() << "-" << index->GetAnswer() << "-" <<
		index->GetOx() << "-" << index->GetQuizMeaning() << "-" << index->GetIsImportant() << endl<<endl;

	cout << "퀴즈1" << endl<<endl;
	index = wordCardBinder.First();
	cout << index->GetSpelling() << endl;
	ret = wordCardBinder.SpellingQuiz("리스트", index);
	if (ret == true) {
		cout << "맞습니다" << endl << endl;
	}
	else {
		cout << "틀렸습니다" << endl << endl;
	}

	cout << "퀴즈2" << endl << endl;
	index = wordCardBinder.NextQuiz();
	//문제가 있으면
	if (index != 0) {
		cout << index->GetSpelling() << endl;
		ret = wordCardBinder.SpellingQuiz("항목을 작성하다", index);
		if (ret == true) {
			cout << "맞습니다." << endl<<endl;
		}
		else {
			cout << "틀렸습니다." << endl<<endl;
		}

	}
	//문제가 없으면
	else {
		cout << "더 이상 문제가 없습니다." << endl << endl;
	}

	cout << "퀴즈3" << endl << endl;
	index = wordCardBinder.NextQuiz();
	//문제가 있으면
	if (index != 0) {
		cout << index->GetSpelling() << endl;
		ret = wordCardBinder.SpellingQuiz("좋은", index);
		if (ret == true) {
			cout << "맞습니다." << endl << endl;
		}
		else {
			cout << "틀렸습니다." << endl << endl;
		}

	}
	//문제가 없으면
	else {
		cout << "더 이상 문제가 없습니다." << endl << endl;
	}

	cout << "퀴즈4" << endl << endl;
	index = wordCardBinder.NextQuiz();
	//문제가 있으면
	if (index != 0) {
		cout << index->GetSpelling() << endl;
		ret = wordCardBinder.SpellingQuiz("좋은ㅁ", index);
		if (ret == true) {
			cout << "맞습니다." << endl << endl;
		}
		else {
			cout << "틀렸습니다." << endl << endl;
		}

	}
	//문제가 없으면
	else {
		cout << "더 이상 문제가 없습니다." << endl << endl;
	}

	cout << "퀴즈5" << endl << endl;
	index = wordCardBinder.NextQuiz();
	//문제가 있으면
	if (index != 0) {
		cout << index->GetSpelling() << endl;
		ret = wordCardBinder.SpellingQuiz("좋은ㅁ", index);
		if (ret == true) {
			cout << "맞습니다." << endl << endl;
		}
		else {
			cout << "틀렸습니다." << endl << endl;
		}

	}
	//문제가 없으면
	else {
		cout << "더 이상 문제가 없습니다." << endl << endl;
	}

	return 0;
}

#endif

