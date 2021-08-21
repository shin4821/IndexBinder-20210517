//Quiz.cpp
#include"Quiz.h"

Quiz::Quiz()
	:spelling(""), answer(""), ox(""), meaning(""), isImportant("") {
}

Quiz::~Quiz() {
}

Quiz::Quiz(string spelling, string answer, string ox, string meaning, string isImportant)
	:spelling(spelling), answer(answer), ox(ox), meaning(meaning), isImportant(isImportant) {
}

Quiz::Quiz(const Quiz& source)
	: spelling(source.spelling), answer(source.answer), ox(source.ox), meaning(source.meaning),
	isImportant(source.isImportant) {
}

bool Quiz::IsEqual(const Quiz& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) == 0 && this->answer.compare(other.answer) == 0 &&
		this->ox.compare(other.ox) == 0 && this->meaning.compare(other.meaning) == 0 &&
		this->isImportant.compare(other.isImportant) == 0) {
		ret = true;
	}

	return ret;
}

bool Quiz::IsNotEqual(const Quiz& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) != 0 || this->answer.compare(other.answer) != 0 ||
		this->ox.compare(other.ox) != 0 || this->meaning.compare(other.meaning) != 0 ||
		this->isImportant.compare(other.isImportant) != 0) {
		ret = true;
	}

	return ret;
}

bool Quiz::operator==(const Quiz& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) == 0 && this->answer.compare(other.answer) == 0 &&
		this->ox.compare(other.ox) == 0 && this->meaning.compare(other.meaning) == 0 &&
		this->isImportant.compare(other.isImportant) == 0) {
		ret = true;
	}

	return ret;
}

bool Quiz::operator!=(const Quiz& other) {
	bool ret = false;
	
	if (this->spelling.compare(other.spelling) != 0 || this->answer.compare(other.answer) != 0 ||
		this->ox.compare(other.ox) != 0 || this->meaning.compare(other.meaning) != 0 ||
		this->isImportant.compare(other.isImportant) != 0) {
		ret = true;
	}

	return ret;
}

Quiz& Quiz::operator=(const Quiz& source) {
	this->spelling = source.spelling;
	this->answer = source.answer;
	this->ox = source.ox;
	this->meaning = source.meaning;
	this->isImportant = source.isImportant;

	return *this;
}

void Quiz::PutImportantWord() {
	this->isImportant = "�߿�";
}

void Quiz::PutOutImportantWord() {
	this->isImportant = "";
}

bool Quiz::SpellingQuiz(string meaning) {
	bool ret;

	//1. �ǹ̸� �Է¹޴´�.
	//2. ������ ���信 ���´�.
	this->answer = meaning;
	//3. �ǹ̰� ������ ���� ���� ������ o�� ���´�.
	if (this->meaning.compare(this->answer) == 0) {
		this->ox = "o";
		ret = true;
	}
	//4. �ǹ̰� Ʋ���� x�� ���´�.
	else {
		this->ox = "x";
		ret = false;
	}

	return ret;
}

void Quiz::Reset() {
	this->answer = "";
	this->ox = "";
}

#if 0

#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
	Quiz quiz("apple", "", "", "���", "");
	cout << quiz.GetSpelling() << "-" << quiz.GetAnswer() << "-" << quiz.GetOx() << "-" << quiz.GetMeaning() 
		<< "-" <<quiz.GetIsImportant() << endl;

	quiz.PutImportantWord();
	cout << quiz.GetSpelling() << "-" << quiz.GetAnswer() << "-" << quiz.GetOx() << "-" << quiz.GetMeaning()
		<< "-" << quiz.GetIsImportant() << endl;

	return 0;
}

#endif











