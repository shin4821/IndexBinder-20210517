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
	this->isImportant = "중요";
}

void Quiz::PutOutImportantWord() {
	this->isImportant = "";
}

bool Quiz::SpellingQuiz(string meaning) {
	bool ret;

	//1. 의미를 입력받는다.
	//2. 퀴즈의 정답에 적는다.
	this->answer = meaning;
	//3. 의미가 맞으면 퀴즈 정답 유무에 o를 적는다.
	if (this->meaning.compare(this->answer) == 0) {
		this->ox = "o";
		ret = true;
	}
	//4. 의미가 틀리면 x를 적는다.
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
	Quiz quiz("apple", "", "", "사과", "");
	cout << quiz.GetSpelling() << "-" << quiz.GetAnswer() << "-" << quiz.GetOx() << "-" << quiz.GetMeaning() 
		<< "-" <<quiz.GetIsImportant() << endl;

	quiz.PutImportantWord();
	cout << quiz.GetSpelling() << "-" << quiz.GetAnswer() << "-" << quiz.GetOx() << "-" << quiz.GetMeaning()
		<< "-" << quiz.GetIsImportant() << endl;

	return 0;
}

#endif











