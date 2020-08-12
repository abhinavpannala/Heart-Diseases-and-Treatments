
 
//Includes the demonstration of backward chaining 
#include "BackwardChaining.h"

using namespace std;


//Initialising the required functions using the class constructor
BackwardChaining::BackwardChaining() {
	knowledgebase();
	Conclist();
	assignClauseNumber();
	varlistInstan();
}

//Taking knowledge base to an array from text file and 
//assigning rules to the knowledge base using hash maps
void BackwardChaining::knowledgebase()
{
	int rule = 10;
	ifstream fin;
	fin.open("Knowledgebaseb.txt");
	//Knowledge base build only on the yes condition for minimalism
	if (!fin) {
		cout << "Could not open the knowledge base file";
	}
	for (int i = 0; i < concsize; i++) {
		getline(fin, knbase[i], '\n');
		rule_number.insert(pair<int, string>(rule, knbase[i]));
		rule = rule + 10;
	}
}

//Taking the types of heart diseases from the input file to an array
void BackwardChaining::Conclist()
{
	fstream  conlfile;
	conlfile.open("BC_Conclist.txt");
	for (int i = 0; i < concsize; i++)
	{
		conlfile >> conclist[i];
	}

	
}

//Taking clause variable list from the text file 
//and assigning clause numbers to them using hash maps
void BackwardChaining::assignClauseNumber()
{
	fstream clausefile;
	clausefile.open("BC_Clausevarlist.txt");
	int clauseno = 1;
	for (int i = 0; i < clausesize; i++)
	{
		clausefile >> clausevarlist[i];
		clause_number.insert(pair<int, string>(clauseno, clausevarlist[i]));
		clauseno++;
	}
}

//Taking the variable list from the files and initialising them ti "NI"
void BackwardChaining::varlistInstan()
{
	fstream varfile;

	varfile.open("BC_Varlist.txt");
	for (int i = 0; i < varsize; i++)
	{
		varfile >> varlist[i];
		varlist_instan.insert(pair<string, string>(varlist[i], "NI"));
	}
	
}

//Compares the strings.Here, the generated string with the knowledge base
bool BackwardChaining::Compare(string s1, string s2)
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

int BackwardChaining::askValues(int clause_no) {
	
	string userInputs; 
	for (int i = 1; i < var_inc; i++)
	{
		if (clause_number[clause_no] != "e")// Empty Values are stored as "e" in clause variable list.
		{
			map<string, string>::iterator itr;
			for (itr = varlist_instan.begin(); itr != varlist_instan.end(); itr++)
			{
				if (!(itr->first == clause_number[clause_no] && itr->second == "NO")) {
					if (itr->first == clause_number[clause_no] && itr->second == "NI")
						//If the variable in the list is considers as 'yes', then it is considered as a symptom
					{
						cout << "Are you suffering from " << clause_number[clause_no] << ":" << endl;
						cin >> userInputs;
						transform(userInputs.begin(), userInputs.end(), userInputs.begin(), ::toupper);
						if (userInputs == "YES") {
							varlist_instan[clause_number[clause_no]] = userInputs;
						}
						else if (userInputs == "NO") {
							varlist_instan[clause_number[clause_no]] = userInputs;
							isNO = true;
							return 0;
						}
						else
						{
							cout << "Please enter only yes/no" << endl;
							exit(1);
						}

					}
				}
				else
					return 0;

			}

		}

		clause_no++; //Checks for the next symptom on the next clause number
	}
	return 0;
}

//Construct the string based on the symptoms of the user
void BackwardChaining::buildString(int stack_rule, int k) {
	int clause_count = 0, var_count = 0;
	map<string, string>::iterator itr;
	for (int j = k; j < k + 6; j++)
	{
		for (itr = varlist_instan.begin(); itr != varlist_instan.end(); itr++)
		{
			if (clausevarlist[j - 1] == itr->first) {
				if (itr->second == "YES")
				{
					clause_count++;
					str1 = clausevarlist[j - 1];
					str2 = itr->second;
					compare = compare + str1 + "=" + str2 + " && ";
				}
			}
		}

	}
	for (itr = varlist_instan.begin(); itr != varlist_instan.end(); itr++)
	{
		if (itr->second != "NI" && itr->second == "YES")
		{
			var_count++;
		}
	}
	// Creating the string from user entered inputs.
	if (clause_count == var_count)
	{
		string user;
		user = "IF " + compare.substr(0, compare.length() - 3);
		int pos = rule_number[stack_rule].find("THEN");
		string know_base = rule_number[stack_rule].substr(0, pos);// String Compare function is called here
		diseaseFound = Compare(user, know_base);
	}
}

string BackwardChaining::identifyDisease()
{
	int index = 300, k = 1;

	for (int i = 0; i < concsize; i++)
	{
		conclusion_stack.push(index); 
		// Moving all the rules to the stack in ascending order, so that the top number has the highest index
		index = index - 10;
	}

	while (conclusion_stack.empty() != true)
	{
		int stack_rule = conclusion_stack.top(); //Operations are performed on the top element of the stack
		int clause_no = (((stack_rule / 10) - 1) * 6) + 1; //Rule number to Clause number
		int noValue;
		noValue = askValues(clause_no);
		if (isNO) {
			isNO = false;
		}
		else {
			buildString(stack_rule, k);
		}

		if (diseaseFound)
		{
			int pos = rule_number[stack_rule].rfind("=");
			heartDisease = rule_number[stack_rule].substr(pos + 1, rule_number[stack_rule].length());
			cout << endl<<"******************************************************************" << endl ;
			cout << "Considering the symptoms provided, you have been diagnosed with " << heartDisease << endl ;
			cout << "******************************************************************" << endl << endl;
			break;
		}
		else
		{
			// Popping the rule if the condition doesn't match.
			conclusion_stack.pop();
			compare.clear();


			if (k < 180) //skips 6 clause positions to move onto the next rule
			{
				k = k + 6;
			}

		}

	}
	// If none of the set of symptoms yield any disease
	if (heartDisease == "")
	{
		cout << "*************************************************************" << endl ;
		cout << "No rules matches with the symptoms selected" << endl;
		cout << "*************************************************************" << endl << endl;
	}

	return heartDisease;

}
