//IndexBInder.h
#ifndef _INDEXBINDER_H
#define _INDEXBINDER_H
#include"BinaryTree.h"
#include"Index.h"
#include<string>
using namespace std;
typedef signed long int Long;

class WordCard;
class IndexBinder {
public:
	IndexBinder();
	~IndexBinder();
	Index* PutIn(WordCard* index);
	Index* Find(string spelling);
	Index* PutOut(string spelling, WordCard* index);
	void Arrange();
	void MakeList(Index* (*indexes), Long* count);
	Long GetLength() const;
	BinaryTree<Index>::Node* GetRoot(); // 전체 출력할 때

private:
	BinaryTree<Index> indexes;
	Long length;
};

inline Long IndexBinder::GetLength() const {
	return this->length;
}

int CompareAlphabet(void* one, void* other);
void Node_Arrange(BinaryTree<Index>::Node* node);


#endif//_INDEXBINDER_H

