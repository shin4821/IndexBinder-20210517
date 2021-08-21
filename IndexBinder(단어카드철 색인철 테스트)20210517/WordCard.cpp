//WordCard.cpp
#include"WordCard.h"
WordCard::WordCard() {
}

WordCard::~WordCard() {
}

WordCard::WordCard(string spelling, string wordClass, string meaning, string example, string quizSpelling,
	string answer, string ox, string quizMeaning, string isImportant)
	:word(spelling, wordClass, meaning, example), quiz(quizSpelling, answer, ox, quizMeaning, isImportant) {
}

WordCard::WordCard(const WordCard& source)
	: word(source.word), quiz(source.quiz) {
}

WordCard& WordCard::operator=(const WordCard& source) {
	this->word = source.word;
	this->quiz = source.quiz;

	return *this;
}

bool WordCard::IsEqual(const WordCard& other) {
	bool ret = false;

	if (this->word.IsEqual(other.word) == true && this->quiz.IsEqual(other.quiz) == true) {
		ret = true;
	}
	return ret;
}

bool WordCard::IsNotEqual(const WordCard& other) {
	bool ret = false;

	if (this->word.IsNotEqual(other.word) == true || this->quiz.IsNotEqual(other.quiz) == true) {
		ret = true;
	}

	return ret;
}

bool WordCard::operator==(const WordCard& other) {
	bool ret = false;

	if (this->word == other.word && this->quiz == other.quiz) {
		ret = true;
	}
	return ret;
}

bool WordCard::operator!=(const WordCard& other) {
	bool ret = false;

	if (this->word != other.word || this->quiz != other.quiz) {
		ret = true;
	}

	return ret;
}

void WordCard::PutImportantWord() {
	this->quiz.PutImportantWord();
}

void WordCard::PutOutImportantWord() {
	this->quiz.PutOutImportantWord();
}

bool WordCard::SpellingQuiz(string meaning) {
	bool ret;

	ret = this->quiz.SpellingQuiz(meaning);

	return ret;
}

void WordCard::Reset() {
	this->quiz.Reset();
}

