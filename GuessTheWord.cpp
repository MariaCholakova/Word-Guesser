﻿// GuessTheWord.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Phrase.h"
#include <vector>
#include <stdlib.h>     
#include <time.h>  
#include <iostream>   //TO DO: not include iostream
#include <fstream>

using namespace std;

const int G = 5000;
const int N = 100;
const float mutationRate = 0.05;

vector<Phrase> InitPopulation(string& phrase) {
	srand(time(NULL));
	vector <Phrase> vPh;
	for (int n = 0; n < N; n++) {
		int length = rand() % 19 + 1;
		string s;
		for (int i = 0; i < length; i++) {
			char c = rand() % ('z' - 'a') + 'a';
			s += c;
		}
		Phrase p(s);
		p.CalculateFitness(phrase);
		vPh.push_back(p);
	}
	return vPh;
}

vector<int> BuildMatingPool(vector<Phrase>& generation) {
	vector<int> indicesPool;
	int sz = generation.size();
	int sumFitness = 0;
	for (int i = 0; i < sz; i++) {
		//fitness is in the range [-2*19 ; 5*19 ]
		//but we don't want negative sum, so add 38
		sumFitness += generation[i].fitness + 38;   
	}
	for (int i = 0; i < sz; i++) {
		//number of occurrences of a phrase is based on its fitnes - 
		//the more fitness, the more occurrences in the mating pool
		int occurrences = round((float) (generation[i].fitness + 38) * 100/ sumFitness); 
		for (int j = 0; j < occurrences; j++) {
			indicesPool.push_back(i);
		}
	}
	return indicesPool;
}

void FindPhrase(vector<Phrase>& firstGeneration, string& realPhrase, ofstream& outfile) {
	vector<Phrase> currGeneration = firstGeneration;
	int genCnt = 1;
	while (genCnt < G) {
		vector<Phrase> newGeneration;
		outfile << "\t\tGeneration " << genCnt << endl;
		vector<int> indicesPool = BuildMatingPool(currGeneration);
		for (int i = 0; i < N; i++) {
			int parA = rand() % indicesPool.size();
			int parB = rand() % indicesPool.size();
			Phrase child = currGeneration[indicesPool[parA]].
				            Crossover(currGeneration[indicesPool[parB]]);
			child.Mutate(mutationRate);
			if (child.str == realPhrase ) {
				cout<<"The phrase " <<child.str<<" is found!\n";
				cout << "Generation: " << genCnt << endl;
				return;
			}
			else {
				outfile << child.str << endl;
				child.CalculateFitness(realPhrase);
				newGeneration.push_back(child);	
			}
		}
		currGeneration = newGeneration;
		genCnt++;
	}
}


int main()
{
	srand(time(NULL));
	string phrase("generous");
	vector<Phrase> firstGen = InitPopulation(phrase);
	ofstream outfile;
	outfile.open("out.txt");
	FindPhrase(firstGen, phrase, outfile);
	
    return 0;
}

