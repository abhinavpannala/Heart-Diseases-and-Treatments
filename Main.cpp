/*
 * Author: SriAakash Mandavilli
 */

#include <iostream>
#include <string>
#include "Project1-S_M985-BackwardChaining.h"
#include "Project1-S_M985-ForwardChaining.h"

using namespace std;

int main()
{   
	cout << "*****************************************" << endl << endl;
	cout << "Expert System for Heart Disease Diagnose" << endl;
	cout << "*****************************************" << endl << endl;
	bool exitOption = false, listRepresentation = false;
	int choice;
	string response, heartDisease, listing;
	string list_print;

	/*Using an indefinite looping style which ends when the exit
	option is selected from the switch*/
	while (!exitOption)
	{
		cout << endl;
		cout << "Choose an option from the following:" << endl;
		cout << "1.Diagonse the disease" << endl;
		cout << "2.Enter the disease to know the treatment" << endl;
		cout << "3.exit" << endl;
		cin >> choice;
		BackwardChaining bw;
		ForwardChaining fw;
		switch (choice)
		{
		case 1:
		{
			cout << endl <<"***********************************************"<<endl;
			cout << "Please enter YES/NO for the following symptoms." << endl;
			cout << "***********************************************" << endl << endl;
			heartDisease = bw.identifyDisease();
			if (bw.diseaseFound == true) {
				cout << "********************************************************" << endl;
				cout << "Do you want to proceed to treatment for \"" << heartDisease << "\":" << endl;
				cout << "********************************************************" << endl;
				cin >> response;
				transform(response.begin(), response.end(), response.begin(), ::toupper);
				if (response == "YES")
				{
					transform(heartDisease.begin(), heartDisease.end(), heartDisease.begin(), ::toupper);
					cout <<endl<< "Treatment for \"" << heartDisease << "\" is" << endl;
					cout << "*****************************************************" << endl ;
					fw.therapy(heartDisease);
				}
				cout << "Exiting Intelligent Expert System" << endl;
				break;
			}
		}
		case 2:
		{
			cout << endl<<"Enter the disease to prescribe a therapy" << endl;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, heartDisease);
			transform(heartDisease.begin(), heartDisease.end(), heartDisease.begin(), ::toupper);
			cout << "Treatment for \"" << heartDisease << "\" is" << endl;
			fw.therapy(heartDisease);
			break;
		}
		
		case 3:
		{
			exitOption = true;
			cout << "The program has been terminated successfully";
			break;
		}
		default:
		{
			cout << "Please enter a valid choice";
			break;
		}
		}
	}
	return 0;
}
