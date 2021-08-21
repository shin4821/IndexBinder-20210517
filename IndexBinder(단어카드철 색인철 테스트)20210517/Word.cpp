//Word.cpp
#include"Word.h"

Word::Word()
	:spelling(""), wordClass(""), meaning(""), example("") {
}

Word::~Word() {
}

Word::Word(const Word& source)
	:spelling(source.spelling), wordClass(source.wordClass), meaning(source.meaning), example(source.example) {
}

Word::Word(string spelling, string wordClass, string meaning, string example)
	: spelling(spelling), wordClass(wordClass), meaning(meaning), example(example) {
}

Word& Word::operator=(const Word& source) {
	this->spelling = source.spelling;
	this->wordClass = source.wordClass;
	this->meaning = source.meaning;
	this->example = source.example;

	return *this;
}

bool Word::IsEqual(const Word& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) == 0 && this->wordClass.compare(other.wordClass) == 0 &&
		this->meaning.compare(other.meaning) == 0 && this->example.compare(other.example) == 0) {
		ret = true;
	}

	return ret;
}

bool Word::IsNotEqual(const Word& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) != 0 || this->wordClass.compare(other.wordClass) != 0 ||
		this->meaning.compare(other.meaning) != 0 || this->example.compare(other.example) != 0) {
		ret = true;
	}

	return ret;
}

bool Word::operator==(const Word& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) == 0 && this->wordClass.compare(other.wordClass) == 0 &&
		this->meaning.compare(other.meaning) == 0 && this->example.compare(other.example) == 0) {
		ret = true;
	}

	return ret;
}

bool Word::operator!=(const Word& other) {
	bool ret = false;

	if (this->spelling.compare(other.spelling) != 0 || this->wordClass.compare(other.wordClass) != 0 ||
		this->meaning.compare(other.meaning) != 0 || this->example.compare(other.example) != 0) {
		ret = true;
	}

	return ret;
}

