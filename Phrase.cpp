#include "stdafx.h"
#include "Phrase.h"

Phrase::Phrase(string& s) : str{ s } {}

Phrase::Phrase(const Phrase& other) {
	this->str = other.str;
	this->fitness = other.fitness;
}

Phrase& Phrase::operator =(const Phrase& other) {
	this->str = other.str;
	this->fitness = other.fitness;
	return *this;
}

void Phrase::CalculateFitness(string& realPhrase) {
	int length = this->str.length() < realPhrase.length() ? this->str.length() : realPhrase.length();
	for (int i = 0; i < length; i++) {
		if (this->str[i] == realPhrase[i]) {
			this->fitness += 5;
		}
		else {
			this->fitness -= 2;
		}
	}
	this->fitness -= abs((int)this->str.length()- (int)realPhrase.length() ) * 2;
}

Phrase Phrase::Crossover(Phrase& other) {
	string longer = this->str.length() > other.str.length() ? this->str : other.str;
	string shorter = this->str.length() < other.str.length() ? this->str : other.str;
	int lenChild = rand() % (longer.length() - shorter.length() + 1) + shorter.length();
	string child;
	int pos = 0;
	
	while (pos < shorter.length()) {
		if (rand() % 2){
			child += shorter[pos];
		}
		else child += longer[pos];
		pos++;
	}
	while (pos < lenChild) {
		child += longer[pos++];
	}

	return Phrase(child);
}

void Phrase::Mutate(float mutationRatio) {
	for (int i = 0; i < this->str.length(); i++) {
		if ( (float)(rand() % 10000) / 10000 < mutationRatio) {
			this->str[i] = rand() % ('z' - 'a') + 'a';
		}
	}
}
