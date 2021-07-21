

#include <iostream>
#include <cstddef>
#include <queue>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <map>
#include <stack>

using namespace std;

class BackwardChaining
{
public:

	static const int varsize = 37, concsize = 30, clausesize = 180, var_inc = 6;
	string varlist[varsize], conclist[concsize], clausevarlist[clausesize], knbase[concsize];
	string str1, str2, heartDisease, compare;
	bool diseaseFound = false, isNO = false;

	
	//All the hash maps used for backward chaining
	map<int, string> rule_number;
	map<int, string> clause_number;
	map<string, string> varlist_instan;
	map<int, string>ruleno_concllist;
	stack<int> conclusion_stack;

	//Class constructor
	BackwardChaining();
	//Necessary functions used for backward chainings
	void knowledgebase();
	void Conclist();
	void assignClauseNumber();
	void varlistInstan();
	void buildString(int, int);
	string identifyDisease();
	bool Compare(string, string);
	int askValues(int);
};