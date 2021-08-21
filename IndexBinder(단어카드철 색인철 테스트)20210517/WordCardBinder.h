//WordCardBinder.h
#ifndef _WORDCARDBINDER_H
#define _WORDCARDBINDER_H
#include<string>
using namespace std;
#include"LinkedList.h"
#include"WordCard.h"
typedef signed long int Long;

class WordCardBinder {
public:
	WordCardBinder();
	~WordCardBinder();
	WordCardBinder(const WordCardBinder& source);
	WordCardBinder& operator=(const WordCardBinder& source);
	WordCard* PutIn(WordCard wordCard);
	void FindBySpelling(string spelling, WordCard** (*indexes), Long* count);
	void FindByMeaning(string spelling, WordCard** (*indexes), Long* count);
	WordCard* FindSpelling(string spelling);
	WordCard* First();
	WordCard* Next();
	WordCard* Previous();
	WordCard* Last();
	WordCard* Move(WordCard* index);
	WordCard PutOut(WordCard* index);
	WordCard GetAt(WordCard* index);
	WordCard* PutImportantWord(WordCard* index);
	WordCard* PutOutImportantWord(WordCard* index);
	void FindImportantWords(WordCard** (*indexes), Long* count);
	bool SpellingQuiz(string meaning, WordCard* index);
	WordCard* NextQuiz();

	Long GetLength() const;
	WordCard* GetCurrent() const;

private:
	LinkedList<WordCard> wordCards;
	Long length;
	WordCard* current;
};

inline Long WordCardBinder::GetLength() const {
	return this->length;
}
inline WordCard* WordCardBinder::GetCurrent() const {
	return const_cast<WordCard*>(this->current);
}

int CompareSpellings(void* one, void* other);
int CompareMeanings(void* one, void* other);
int CompareWordCards(void* one, void* other);
int CompareImportantWords(void* one, void* other);

#endif//_WORDCARDBINDER_H
