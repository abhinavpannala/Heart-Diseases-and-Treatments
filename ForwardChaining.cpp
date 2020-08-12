/*
 * Author: SriAakash MAndavilli
 */

 //This code demonstrates the working of the forward chaining technique

#include "Project1-S_M985-ForwardChaining.h"
using namespace std;

//Initialising the necessary functions of the class ForwardChaining 

ForwardChaining::ForwardChaining() {
	
	RuleNumber_FKnowBase();
	ClauseNumber_FClauseVarList();
	Varlist_Instantiation();
}


/* This function is used to input the forward chaining knowledge base from text file.
* Also, assigs rule number to the knowledge base using hash maps*/
void ForwardChaining::RuleNumber_FKnowBase()
{
	ifstream fin;
	fin.open("Knowledgebasef.txt");
	if (!fin) {
		cout << "Could not open the knowledge base file";
	}
	
	int rule = 10;
	for (int i = 0; i < rulesize; i++)
	{
		getline(fin, Know_Base[i], '\n');
		assign_rule_number.insert(pair<int, string>(rule, Know_Base[i]));
		rule = rule + 10;
	}
}

/*Input the clause variable list from the text file and assign 
* a clause numbers usign hash maps*/
void ForwardChaining::ClauseNumber_FClauseVarList()
{
	fstream Clausefile;

	// the file path is given where all the files are stored
	int Clause_no = 1;
	Clausefile.open("FW_Clausevarlist.txt");
	for (int i = 0; i < clausevarsize; i++)
	{
		Clausefile >> ClauseVarlist[i];
		assign_clause_number.insert(pair<int, string>(Clause_no, ClauseVarlist[i]));
		Clause_no++;
	}
	
}

//Used to initialise all the variables in the list to "NI"
void ForwardChaining::Varlist_Instantiation()
{
	var_list_Ins.insert(pair<string, string>("DISEASE", "NI"));
}

//Used to compare the strings irrespective of the type cases and spaces
//before and after the string
bool ForwardChaining::Compare(string s1, string s2)
{
	transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
	transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

	if (s1 == s2)
	{
		return true;
	}

	else
	{
		return false;
	}
}

/*Takes the diseases as input and moves them into a queue.
* Checks the knowledge base with the rule number of the last element in the queue.
* Returns the treatment when the disease matches the conditions in the knowledge base
*/
void ForwardChaining::therapy(string heartDisease)
{

	conc_var_queue.push("DISEASE");
	var_list_Ins["DISEASE"] = heartDisease;
	int Clause_no = 1, Rule_no;

	if (heartDisease != "")
	{
		while (!conc_var_queue.empty()) 
		{
			map<int, string>::iterator itr;
			for (itr = assign_clause_number.begin(); itr != assign_clause_number.end(); itr++)
			{
				if (itr->second != "e")
				{
					//Clause number to Rule number
					Rule_no = (((Clause_no / 3) + 1) * 10);
				}

			}

			//Compare disease with knowledge base
			int pos = assign_rule_number[Rule_no].find("=");
			int pos1 = assign_rule_number[Rule_no].find(" THEN");
			string compare = assign_rule_number[Rule_no].substr(pos + 1, pos1 - (pos + 1));

			if (Compare(compare, heartDisease))
			{
				int therapy = assign_rule_number[Rule_no].rfind("=");
				Result = assign_rule_number[Rule_no].substr(therapy, assign_rule_number[Rule_no].length());
				Result.erase(0, 1);
				cout << Result << endl;
				cout << "*****************************************************" << endl;
				break;
			}
			else
			{
				Clause_no = Clause_no + 2; \

			}

		} 

	} 

	else
		cout << "Disease not detected, could not prescribe you the treatment." << endl;

}

