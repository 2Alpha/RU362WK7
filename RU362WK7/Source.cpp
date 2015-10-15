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
const float  MAX_RENT = 999999;		// Max rental price - this was not specified

string showAddDelModExit();
string convert2UpperCase(string stringInput);
void ask2LoadExistingData(residence *& topOfList, residence *& endOfList);

void showRentals(string MainMenuChoice, residence *& topOfList, residence *& endOfList);
void AddRentals2Array(string MainMenuChoice, residence *& topOfList, residence *& endOfList);
void deleteARental(string MainMenuChoice, residence *& topOfList, residence *& endOfList);
void modifyRental(string MainMenuChoice, residence *& topOfList, residence *& endOfList);

void displayAptPhoneNumbers(residence *& topOfList);

string GetPhoneNumber();
float GetMonthlyRent();
bool GetRentalStatus();

int main()
{
	residence * topOfList = NULL;
	residence * endOfList = NULL;

	string MainMenuChoice;

	ask2LoadExistingData(topOfList,endOfList);

	do
	{
		MainMenuChoice = showAddDelModExit();

		showRentals (MainMenuChoice, topOfList, endOfList);
		AddRentals2Array (MainMenuChoice, topOfList, endOfList);
		deleteARental (MainMenuChoice, topOfList, endOfList);
		modifyRental(MainMenuChoice, topOfList, endOfList);
	}
	while (MainMenuChoice != "X");

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
string showAddDelModExit()
{
	string response2Question;			// Response to question
	bool repeatQuestion;				// Repeat question
	do {

		cout << endl;
		cout << "Please choose an option by entering its corresponding letter" << endl;
		cout << "S = Show all rentals to the Screen " << endl;
		cout << "A = Add rentals to the array " << endl;
		cout << "D = Delete a rental" << endl;
		cout << "M = Modify Monthly Rent" << endl;
		cout << "X = Exit the program" << endl;
		cout << endl;
		cout << "Please enter response here: ";
		cin >> response2Question;
		cin.ignore(IGNORE_AMOUNT, '\n');

		response2Question = convert2UpperCase(response2Question);


		if ((response2Question != "S") && (response2Question != "A") && (response2Question != "D") && (response2Question != "M") 
			&& (response2Question != "X"))
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

void ask2LoadExistingData(residence *& topOfList, residence *& endOfList)
{
	string promt1Response;
	string fileName2Load;
	int numOfErrors;
	bool fileReadErorr;
	bool ReadInputFile;

	string phoneNumber;
	float monthlyRent;
	bool rented;

	residence	* newNode = NULL;

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


}

void showRentals(string MainMenuChoice, residence *& topOfList, residence *& endOfList)
{
	if (MainMenuChoice == "S")
	{ 
		cout << fixed << showpoint << setprecision(2);
		cout << "Phone Nmmber" << setw(15) << " Monthly Rent" << setw(15)  << "Status      " << endl;
		cout << "------------" << setw(15) << "-------------" << setw(15)  << "------------" << endl;

		residence *here = topOfList;
		while (here != NULL) // while not at end of list… 
		{                
	
			cout << here->phoneNumber << setw(15);    // Print phone number in node pointed 
			cout << here->monthlyRent << setw(15);    // Print monthly in node pointed 

			if (here->rented == 1)
			{
				cout << left;
				cout << "   rented" << endl;
				cout << right;
			}

			else
			{
				cout << left;
				cout << "   available" << endl;
				cout << right;
			}


			here = here->next;             // Move here pointer to point 
			// to the next node in list 
		} // end while 

	}

}

void AddRentals2Array(string MainMenuChoice, residence *& topOfList, residence *& endOfList)
{
	if (MainMenuChoice == "A")
	{
		residence * newNode = NULL;
		
		cout << "You selected Add Rental to array" << endl;
		cout << "There are 3 steps to complete this entry, see below for instructions " << endl;
		cout << "Step 1. Enter a vaild phone number in the format of \"###-###-####\" " << endl;
		cout << "Step 2. Enter the monthly rent. Must greater than 0 and less than " << MAX_RENT << endl;
		cout << "Step 3. Enter the Rental Status as Y = yes, N = No" << endl;
		cout << endl;
		
		string validPhoneNumber = GetPhoneNumber();
		float monthlyRent = GetMonthlyRent();
		bool rentalStatus = GetRentalStatus();
		

		newNode = new (nothrow)residence;    // Allocate new node space

		if (newNode == NULL)
		{
			cout << "Heap error - could not allocate memory" << endl;
			system("pause");
		}

		else
		{                        // Memory allocated put data into new node
			newNode->phoneNumber = validPhoneNumber;
			newNode->monthlyRent = monthlyRent;
			newNode->rented = rentalStatus;
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



		cout << "Entry successfully added!" << endl << endl;
		

	}
}

//*************************************************************************
//  FUNCTION:	  GetPhoneNumber
//  DESCRIPTION:  Stores the entered phone number specifically in the format ###-###-####
//
//  INPUT:        Parameters:  None
//
//  OUTPUT: 	  Return value: string phoneNumber - Phone Number 
//*************************************************************************
string GetPhoneNumber()
{
	string phoneNumber;					// Phone Number 
	int length;                         // Length of user input

	int errorCounter;					// Error Counter

	do
	{
		int i = 0;
		errorCounter = 0;
		cout << endl;
		cout << "Step 1. Enter the phone number : ";
		getline(cin, phoneNumber);

		length = phoneNumber.length();

		if (length < 12)
		{
			cout << "The phone number you entered is too short" << endl;
			cout << "Please follow the format \"###-###-####\" Try again." << endl;
			errorCounter++;
		}

		else if (length > 12)
		{
			cout << "The phone number you entered is too long" << endl;
			cout << "Please follow the format \"###-###-####\" Try again." << endl;
			errorCounter++;
		}

		else if (length = 12)
		{

			for (int index = 0; index < 3; index++)         // Used Loops for error checking 
			{
				if (!(isdigit(phoneNumber[index])))
				{

					errorCounter++;
					//cout << "not a number " << endl; 
				}

			}


			for (int index = 3; index < 4; index++)         // Used Loops for error checking 
			{
				if (phoneNumber[index] != '-')
				{
					errorCounter++;
					//cout << "dash not where it should be " << endl;
				}

			}

			for (int index = 4; index < 7; index++)         // Used Loops for error checking 
			{
				if (!(isdigit(phoneNumber[index])))
				{
					errorCounter++;
					//cout << "not a number " << endl;
				}

			}

			for (int index = 7; index < 8; index++)         // Used Loops for error checking 
			{
				if (phoneNumber[index] != '-')
				{
					errorCounter++;
					//cout << "dash not where it should be " << endl;
				}

			}

			for (int index = 8; index < 12; index++)         // Used Loops for error checking 
			{
				if (!(isdigit(phoneNumber[index])))
				{
					errorCounter++;
					//cout << "not a number " << endl;
				}

			}

		} /// end else if

		if ((length == 12) && (errorCounter > 0))
		{
			cout << endl;
			cout << "Error! You Enterd 12 characters, however not in the correct format." << endl;
			cout << "Please follow the format \"###-###-####\" Try again." << endl;
		}
	}


	while (errorCounter > 0); // loop if error counter is greater than zero (0) 

	return phoneNumber;

}

//*************************************************************************
//  FUNCTION:	  GetMonthlyRent
//  DESCRIPTION:  Stores the entered amount for monthly rent
//
//  INPUT:        Parameters:  None
//
//  OUTPUT: 	  Return value: float monthlyRent - Monthly Rent 
//*************************************************************************
float GetMonthlyRent()
{
	int errorCounter;								// Error Counter 
	float monthlyRent;								// Monthly Rent

	do
	{
		int i = 0;
		errorCounter = 0;
		cout << endl;
		cout << "Step 2. Enter the Monthly Rent : ";
		cin >> monthlyRent;

		if ((cin.fail()) || (monthlyRent > MAX_RENT))

		{
			cin.clear();
			cin.ignore(999, '\n');
			errorCounter++;
			cout << "Error! you did not enter a number between 0 and " << MAX_RENT << " Try again." << endl;
		}

	}

	// while error counter is greater than zero 
	while (errorCounter > 0);

	return monthlyRent;

}

//*************************************************************************
//  FUNCTION:	  GetRentalStatus
//  DESCRIPTION:  Stores the entered amoount for rental status (available or rented)
//
//  INPUT:        Parameters:  None
//
//  OUTPUT: 	  Return value: bool  rentalStatusInBool - Rental Status in boolean 
//*************************************************************************
bool GetRentalStatus()
{
	bool repeatQuestion;				// Repeat Question 
	bool rentalStatusInBool;			// Rental Status in boolean 
	string rentalStatusResponse;

	do
	{

		cout << endl;
		cout << "Step 3. Is the apartment currently rented? Y = yes, N = No" << endl;
		cout << "Please enter your choice here : ";
		cin >> rentalStatusResponse;

		rentalStatusResponse = convert2UpperCase(rentalStatusResponse);

		if ((rentalStatusResponse != "Y") && (rentalStatusResponse != "N"))
		{
			cout << endl;
			cout << "ERROR! Unrecognized input, please try again." << endl;
			cout << endl;
			repeatQuestion = true;
		}


		else if (rentalStatusResponse == "Y")
		{
			repeatQuestion = false;
			rentalStatusInBool = true;
		}



		else if (rentalStatusResponse == "N")
		{
			repeatQuestion = false;
			rentalStatusInBool = false;
		}
	}


	// while repeat question equals true
	while (repeatQuestion == true);

	return rentalStatusInBool;
}

void deleteARental(string MainMenuChoice, residence *& topOfList, residence *& endOfList)
{
	if (MainMenuChoice == "D")
	{
		string item2Delete;
		residence *here;		// Node being checked
		residence *prev;		// Node prior to node being checked
		bool success = false;

		if (topOfList == NULL)
		{
			cout << "Error! The list is empty." << endl; 
			cout << "Therefore Renatals cannot be removed." << endl; 
		}
		
		else
		{
			displayAptPhoneNumbers(topOfList);

			do
			{
				item2Delete = GetPhoneNumber();

				                        

				if (topOfList->phoneNumber == item2Delete)		// If delName found in first node,
				{        
					here = topOfList;
					topOfList = topOfList->next;		      //  Delete top item
					delete here;
					success = true;
					cout << "Success! Apartment with phone number " << item2Delete << " has been deleted" << endl;
				}

				else // Not top item, so search..
				{                                   

					prev = topOfList;                      // Initialize prev and here to 
					here = topOfList->next;                // first 2 nodes in list

														 // Look for delName (while not end of list and name doesn't match)
					while ((here != NULL) && (here->phoneNumber != item2Delete))
					{
						prev = here;               // move prev down one
						here = here->next;         // move here down one
					}

					if (here != NULL) {               // If found, delete item from list
						prev->next = here->next;
						delete here;
						success = true;
						cout << "Success! Apartment with phone number " << item2Delete << " has been deleted" << endl; 
					}
					else
					{// Otherwise, give error message
						cout << "Error! Phone number " << item2Delete << " was not found within the list." << endl;
						cout << "Please Try again" << endl;
					}



				}	// End else (not top Item)

			} while (success == false);


			return;


		}
	}

}
void displayAptPhoneNumbers(residence *& topOfList)
{
	cout << fixed << showpoint << setprecision(2);
	cout << "Apartment Phone Numbers on file" << endl;
	cout << "------------" << endl; 

	residence *here = topOfList;
	while (here != NULL) // while not at end of list… 
	{

		cout << here->phoneNumber << endl;     // Print phone number in node pointed  

		here = here->next;             // Move here pointer to point 
									   // to the next node in list 
	} // end while 

	cout << endl; 
}

void modifyRental(string MainMenuChoice, residence *& topOfList, residence *& endOfList)
{
	if (MainMenuChoice == "M")
	{
		ifstream modsFile; // input file stream variable
		modsFile.open("MODS.txt");

		string phoneNumber;
		char plusOrMinus;
		float byHowMuch;

		if (!modsFile)
		{
			cout << "ERROR! could not open file named MODS.txt" << endl; 
			cout << "Therefore no chnages were made to the list of rentals" << endl; 
		}

		else
		{
			do
			{
				modsFile >> phoneNumber >> plusOrMinus >> byHowMuch;

				cout << fixed << showpoint << setprecision(2);
				cout << "------------" << endl; 
				cout << "Phone  : " << phoneNumber << endl; 
				cout << "+ or - : " << plusOrMinus << endl;
				cout << "bhm    : " << byHowMuch << endl;
			}

			while (modsFile);

		}



	}


	 
}