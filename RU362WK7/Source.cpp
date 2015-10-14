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






const int IGNORE_AMOUNT = 100;

string showAddDeleteExit();
string convert2UpperCase(string stringInput);
residence * ask2LoadExistingData(residence* residenceList);

int main()
{
	residence * topOfList = NULL;
	residence *newResidence = NULL;
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

	string phoneNumber;
	float monthlyRent;
	bool rented;

	residence	* newNode = NULL,
				* topOfList = NULL,
				* endOfList = NULL;

	ifstream inputFile1; // input file stream variable

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

		else if (promt1Response == "N")
		{
			ReadInputFile = false;
			cout << "Okay, lets start fresh!" << endl;
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

					do
					{
						inputFile1 >> phoneNumber >> monthlyRent >> rented;   // Read one line of data

						if (inputFile1)
						{                  // Was able to read data

							newNode = new (nothrow) residence;    // Allocate new node space

							if (newNode == NULL)
							{
								cout << "Heap error - could not allocate memory" << endl;
								system("pause");
							}

							else
							{                        // Memory allocated put data into new node
								newNode->phoneNumber = phoneNumber;
								newNode->monthlyRent = monthlyRent;
								newNode->rented = rented;
								newNode->next = NULL;

								// Insert new node into the list
								if (topOfList == NULL)			// If list is empty...
								{
									endOfList = newNode;          // point both pointers to new node 
									topOfList = newNode;
								}

								else
								{								// If list is not empty...
									endOfList->next = newNode;    // Point Next ptr in last to new node
									endOfList = newNode;          // and also point last to new node
								}

							}   // end else where newNode != NULL

						}   // end if (inFile)

					} while ((inputFile1) && (newNode != NULL));


				}//good 

			} while (fileReadErorr == true);

		}


	} while (numOfErrors > 0);

	/////////////
	residence *here = topOfList;
	while (here != NULL) {                // while not at end of list… 

                      // Increment count 

		cout << here->phoneNumber << endl;    // Print name in node pointed 
									   // to by here pointer 

		here = here->next;             // Move here pointer to point 
									   // to the next node in list 
	} // end while 



	return 0;
}