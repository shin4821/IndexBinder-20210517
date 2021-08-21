//Quiz.h
#ifndef _QUIZ_H
#define _QUIZ_H
#include<string>
using namespace std;

class Quiz {
public:
	Quiz();
	~Quiz();
	Quiz(string spelling, string answer, string ox, string meaning, string isImportant);
	Quiz(const Quiz& source);
	bool IsEqual(const Quiz& other);
	bool IsNotEqual(const Quiz& other);
	bool operator==(const Quiz& other);
	bool operator!=(const Quiz& other);
	Quiz& operator=(const Quiz& source);
	void PutImportantWord();
	void PutOutImportantWord();
	bool SpellingQuiz(string meaning);
	void Reset();
	string& GetSpelling() const;
	string& GetAnswer() const;
	string& GetOx() const;
	string& GetMeaning() const;
	string& GetIsImportant() const;

private:
	string spelling;
	string answer;
	string ox;
	string meaning;
	string isImportant;
};

inline string& Quiz::GetSpelling() const {
	return const_cast<string&>(this->spelling);
}

inline string& Quiz::GetAnswer() const {
	return const_cast<string&>(this->answer);
}

inline string& Quiz::GetMeaning() const {
	return const_cast<string&>(this->meaning);
}

inline string& Quiz::GetOx() const {
	return const_cast<string&>(this->ox);
}

inline string& Quiz::GetIsImportant() const {
	return const_cast<string&>(this->isImportant);
}

#endif//_QUIZ_H

