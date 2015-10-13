//***************************************************************************
//  FILENAME:	 AllenAssn6.cpp
//  DESCRIPTION: Course Managemmt Program
//
//  DATE:        10/10/15
//  CLASS/TERM:  CS362_X40_Data Structures - CU_CS362 - XIN_X40_15F8W1
//  DESIGNER:	 Andrae Allen
//  FUNCTIONS:	 main - reads values, performs calculations, & displays results
//				 xxxxxxxxxxxxxxxxxx
//				 xxxxxxxxxxxxxxxxxx 
//				 xxxxxxxxxxxxxxxxxx
//				 xxxxxxxxxxxxxxxxxx
//				 xxxxxxxxxxxxxxxxxx
//				 xxxxxxxxxxxxxxxxxx
//				 xxxxxxxxxxxxxxxxxx
//				 xxxxxxxxxxxxxxxxxx
//***************************************************************************

#include <iostream> 
#include <fstream>
#include <cstdio> 
#include <iomanip>
#include <string>
#include <cstddef>

using namespace std;

struct residence
{
	string phoneNumber;
	float monthlyRent;
	bool rented;

	residence * next;
};



bool nodeIsEmpty(residence * head)
{
	if (head == NULL)
	{
		return true;
	}

	else
	{
		return false;
	}
}


const int IGNORE_AMOUNT = 100;

string showAddDeleteExit();
string convert2UpperCase(string stringInput);

int main()
{
	residence * topOfList = NULL;
	residence * tempResidence = NULL;
	residence *  residenceList = NULL;

	ask2LoadExistingData (residenceList);
	

	system("PAUSE");
	return 0;
}

//*************************************************************************
//  FUNCTION:	  showAddDeleteExit
//  DESCRIPTION:  Presents the user with the options of show, add, delete, or exit the program
//  INPUT:        Parameters:  User input from console
//
//  OUTPUT: 	  Return value: string response2Question - response to question
//*************************************************************************
string showAddDeleteExit()
{
	string response2Question;			// Response to question
	bool repeatQuestion;				// Repeat question
	do {

		cout << endl;
		cout << "Please choose an option by entering its corresponding letter" << endl;
		cout << "S = Show rentals to the Screen " << endl;
		cout << "A = Add rentals to the array " << endl;
		cout << "D = Delete a rental" << endl;
		cout << "X = Exit the program" << endl;
		cout << endl;
		cout << "Please enter response here: ";
		cin >> response2Question;
		cin.ignore(IGNORE_AMOUNT, '\n');

		response2Question = convert2UpperCase(response2Question);


		if ((response2Question != "S") && (response2Question != "A") && (response2Question != "D") && (response2Question != "X"))
		{
			cout << endl;
			cout << "ERROR! Unrecognized input, please try again." << endl;
			cout << endl;
			repeatQuestion = true;
		}

		else
		{
			repeatQuestion = false;
		}
	}

	// while repeat question equals true
	while (repeatQuestion == true);


	return response2Question;

}

string convert2UpperCase(string stringInput)
{
	int i = 0;  // variabel used for tracking index location in array
	char c;		// variable used to temporaliy store character from string

	string upperCasedString;		// A string where all the letters are uppercase  

	while (stringInput[i] != '\0')
	{
		// if character is a letter 
		if (isalpha(stringInput[i]))
		{
			c = stringInput[i];
			stringInput[i] = toupper(c);
			i++;
		}

		else
		{
			i++;
		}

	}

	upperCasedString = stringInput;

	return upperCasedString;

}

residence * ask2LoadExistingData(residence* residenceList)
{
	string promt1Response;
	string fileName2Load; 
	int numOfErrors;
	bool fileReadErorr;
	bool ReadInputFile; 

	//residence * next_ptr = NULL; 
	//residence * previous_ptr = NULL;

	residence * next_ptr = NULL;
	residence * previous_ptr = NULL;
	residence * tempResidence,
			  * lastResidence = NULL;

	do
	{
		numOfErrors = 0;
		cout << endl;
		cout << "Would you like to load existing data from a file (Y / N) ?  ";
		cin >> promt1Response;

		promt1Response = convert2UpperCase(promt1Response);


		if ((promt1Response != "Y") && (promt1Response != "N"))
		{
			cout << endl;
			cout << "ERROR! Unrecognized input, please try again." << endl;
			numOfErrors++;
		}

		else if (promt1Response == "Y")
		{
			
		
			do
			{
				cout << endl;
				cout << "Plese enter the name of the File you wish you load: ";
				cin.clear();
				getline(cin >> ws, fileName2Load);

				ifstream inputFile1; // input file stream variable

				//inputFile1.open(fileName2Load, ios::binary | ios::in);
				inputFile1.open(fileName2Load.c_str());

				if (!inputFile1)
				{
					fileReadErorr = true;
					inputFile1.clear();
					cout << endl;
					cerr << "Error! System could not open file named \"" << fileName2Load << "\"" << endl;
					cerr << "Please Try again." << endl;
					cerr << endl;

				}

				else
				{
					fileReadErorr = false;
					cout << "Exisiting file named " << fileName2Load << " has been loaded" << endl;
					//// link list stuff

					
					while (!inputFile1.eof)
					{
						if (residenceList == NULL)
						{
							lastResidence = tempResidence;
							residenceList = tempResidence;
						}

						else
						{
							lastNode->nextPat = tempNode;
							lastNode = tempNode;
						}
						tempResidence = new residence;

						inputFile1 >> tempResidence->phoneNumber;
						inputFile1 >> tempResidence->monthlyRent;
						inputFile1 >> tempResidence->rented;

						tempResidence->next = NULL;
						residenceList = tempResidence;
					}

					inputFile1.close(); 
				}



			} while (fileReadErorr == true);


		}


		else if (promt1Response == "N")
		{
			ReadInputFile = false;
			cout << "Okay, lets start fresh!" << endl;  
		}

	}

	// loop if error detected flag equals true 
	while (numOfErrors > 0);


	return residenceList;


}