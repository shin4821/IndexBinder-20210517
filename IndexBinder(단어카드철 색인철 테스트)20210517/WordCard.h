//WordCard.h
#ifndef _WORDCARD_H
#define _WORDCARD_H
#include<string>
using namespace std;
#include"Word.h"
#include"Quiz.h"

class WordCard {
public:
	WordCard();
	~WordCard();
	WordCard(string spelling, string wordClass, string meaning, string example, string quizSpelling,
		string answer, string ox, string quizMeaning, string isImportant);
	WordCard(const WordCard& source);
	WordCard& operator=(const WordCard& source);
	bool IsEqual(const WordCard& other);
	bool IsNotEqual(const WordCard& other);
	bool operator==(const WordCard& other);
	bool operator!=(const WordCard& other);
	void PutImportantWord();
	void PutOutImportantWord();
	bool SpellingQuiz(string meaning);
	void Reset();

	string& GetSpelling() const;
	string& GetWordClass() const;
	string& GetMeaning() const;
	string& GetExample() const;
	string& GetQuizSpelling() const;
	string& GetAnswer() const;
	string& GetOx() const;
	string& GetQuizMeaning() const;
	string& GetIsImportant() const;

private:
	Word word;
	Quiz quiz;
};

inline string& WordCard::GetSpelling() const {
	return const_cast<string&>(this->word.GetSpelling());
}
inline string& WordCard::GetWordClass() const {
	return const_cast<string&>(this->word.GetWordClass());
}
inline string& WordCard::GetMeaning() const {
	return const_cast<string&>(this->word.GetMeaning());
}
inline string& WordCard::GetExample() const {
	return const_cast<string&>(this->word.GetExample());
}
inline string& WordCard::GetQuizSpelling() const {
	return const_cast<string&>(this->quiz.GetSpelling());
}
inline string& WordCard::GetAnswer() const {
	return const_cast<string&>(this->quiz.GetAnswer());
}
inline string& WordCard::GetOx() const {
	return const_cast<string&>(this->quiz.GetOx());
}
inline string& WordCard::GetQuizMeaning() const {
	return const_cast<string&>(this->quiz.GetMeaning());
}
inline string& WordCard::GetIsImportant() const {
	return const_cast<string&>(this->quiz.GetIsImportant());
}

#endif//_WORDCARD_H
