//Index.h
#ifndef _INDEX_H
#define _INDEX_H
#include"Array.h"
typedef signed long int Long;
#include<string>
using namespace std;

class WordCard;
class Index {
public:
	Index(Long capacity = 256);
	~Index();
	Index(char alphabet, Long capacity=256);
	Long PutIn(WordCard* key);
	Long Find(WordCard* key);
	void FindSpellings(WordCard* key, Long* (*indexes), Long* count);
	Long PutOut(Long index);
	void Arrange();
	WordCard* GetAt(Long index);
	char& GetAlphabet() const;
	Long GetCapacity() const;
	Long GetLength() const;

private:
	char alphabet;
	Array<WordCard*> wordCards;
	Long capacity;
	Long length;
};
inline char& Index::GetAlphabet() const {
	return const_cast<char&>(this->alphabet);
}

inline Long Index::GetCapacity() const {
	return this->capacity;
}

inline Long Index::GetLength() const {
	return this->length;
}

int CompareWordCard(void* one, void* other);
int CompareSpelling(void* one, void* other);
int CompareSameSpelling(void* one, void* other);

#endif//_INDEX_H

