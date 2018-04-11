#pragma once
#ifndef PHRASE_H
#define PHRASE_H
#include <string>
using namespace std;

struct Phrase {
	string str;
	int fitness = 0;

	Phrase(){}
	Phrase(string& s);
	Phrase(const Phrase& other);
	Phrase& operator =(const Phrase& other);
	void CalculateFitness(string& realPhrase);
	Phrase Crossover(Phrase& other);
	void Mutate(float mutationRatio);
};

#endif // !1

