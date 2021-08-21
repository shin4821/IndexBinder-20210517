//CorrectQuizBinder.h
#ifndef _CORRECTQUIZBINDER_H
#define _CORRECTQUIZBINDER_H
#include"WordCard.h"
typedef signed long int Long;
#include"LinkedList.h"
#include<string>
using namespace std;

class CorrectQuizBinder {
public:
	CorrectQuizBinder();
	~CorrectQuizBinder();
	CorrectQuizBinder(const CorrectQuizBinder& source);
	CorrectQuizBinder& operator=(const CorrectQuizBinder& source);
	WordCard* PutIn(WordCard wordCard);
	WordCard* First();
	WordCard* Previous();
	WordCard* Next();
	WordCard* Last();
	WordCard PutOut(WordCard* index);
	void Reset();

	Long GetLength() const;
	WordCard* GetCurrent() const;

private:
	LinkedList<WordCard> wordCards;
	Long length;
	WordCard* current;
};

inline Long CorrectQuizBinder::GetLength() const {
	return this->length;
}
inline WordCard* CorrectQuizBinder::GetCurrent() const {
	return const_cast<WordCard*>(this->current);
}

int CompareCorrectQuizCard(void* one, void* other);

#endif//_CORRECTQUIZBINDER_H
