/*
 * Author: SriAakash Mandavilli
 */

#include <iostream>
#include <cstddef>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <stack>
#include <map>
#include <queue>

using namespace std;


class ForwardChaining
{
public:

	static const int varsize = 1, rulesize = 30, clausevarsize = 90, var_inc = 10;
	string ClauseVarlist[clausevarsize], Know_Base[rulesize];
	string Result;

	
	//All the hash maps used
	map<int, string> assign_rule_number;
	map<int, string> assign_clause_number;
	map<string, string> var_list_Ins;
	queue <string> conc_var_queue;

	//Constructor to initialise the essential functions of the class
	ForwardChaining();
	
	//All the remaining functions
	void RuleNumber_FKnowBase();
	void ClauseNumber_FClauseVarList();
	void Varlist_Instantiation();
	bool Compare(string str1, string str2);
	void therapy(string str);
};
