//***************************************************************************
//  FILENAME:	 AllenAssn6.cpp
//  DESCRIPTION: Course Managemmt Program
//
//  DATE:        10/10/15
//  CLASS/TERM:  CS362_X40_Data Structures - CU_CS362 - XIN_X40_15F8W1
//  DESIGNER:	 Andrae Allen
//  FUNCTIONS:	 main - Reads values, performs calculations, & displays results
//				 showAddDelModExit - Shows menu options of show, add, delete, modify, or exit
//				 convert2UpperCase -Converts all chars in a string to upper case 
//				 ask2LoadExistingData - Asks user if they would like to load existing data 
//				 showRentals - Displays a list of all rental data on file
//				 AddRentals2Array - Adds an entry to the linked list of Rental units  
//				 deleteARental - Deletes an entry from the linked list of Rental units 
//				 modifyRental - Imports and executs file containing rental unit modification data 
//				 exitProgram - Allows user to save data and or exit program 
//				 displayAptPhoneNumbers - Displays a list of all rental phone numbers on file
//				 GetPhoneNumber - Gets phone number via user input
//				 GetMonthlyRent - Gets rent via user input
//				 GetMonthlyRent - Gets rental status via user input
//				 does_file_exist - Checks to see if file specified exists with home directory 
//				 checkFile_Ext - Varifies output file has .txt extention
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


const int IGNORE_AMOUNT = 999;
const int PHONE_CHAR_LENGTH = 12;
const int PHONE_CHAR_SECTION_1 = 3; 
const int PHONE_CHAR_SECTION_2 = 4;
const int PHONE_CHAR_SECTION_3 = 7;
const int PHONE_CHAR_SECTION_4 = 8;
const int PHONE_CHAR_SECTION_5 = 12;

const int TXT_DOT_LOCATION = 4; 
const int TXT_T1_LOCATION = 3; 
const int TXT_X_LOCATION = 2;
const int TXT_T2_LOCATION = 1;

const float  MAX_RENT = 999999;		// Max rental price - this was not specified

string showAddDelModExit();
string convert2UpperCase(string stringInput);
void ask2LoadExistingData(residence *& topOfList, residence *& endOfList);

void showRentals(string MainMenuChoice, residence *& topOfList, residence *& endOfList);
void AddRentals2Array(string MainMenuChoice, residence *& topOfList, residence *& endOfList);
void deleteARental(string MainMenuChoice, residence *& topOfList);
void modifyRental(string MainMenuChoice, residence *& topOfList, residence *& endOfList);
void exitProgram(string MainMenuChoice, residence *& topOfList);

void displayAptPhoneNumbers(residence *& topOfList);

string GetPhoneNumber();
float GetMonthlyRent();
bool GetRentalStatus();
bool checkFileExt(string fileName2check);
bool does_file_exist(string fileName);

//**************************************************************************
//  FUNCTION:       main
//  DESCRIPTION:    Create and manipulate a linked list containing rental data 
//  OUTPUT:	
//  Return Value:	0 for success
//  CALLS TO:	    ask2LoadExistingData, showAddDelModExit, showRentals, AddRentals2Array
//					deleteARental, modifyRental, exitProgram
//**************************************************************************
int main()
{
	residence * topOfList = NULL;			// initializing first node in linked list
	residence * endOfList = NULL;			// initializing last node in linked list

	string MainMenuChoice;					// Main menu choice

	ask2LoadExistingData(topOfList,endOfList);

	do
	{
		MainMenuChoice = showAddDelModExit();

		showRentals (MainMenuChoice, topOfList, endOfList);
		AddRentals2Array (MainMenuChoice, topOfList, endOfList);
		deleteARental (MainMenuChoice, topOfList);
		modifyRental(MainMenuChoice, topOfList, endOfList);
		exitProgram(MainMenuChoice, topOfList);
	}
	while (MainMenuChoice != "X");			// While user input not equal "X" 

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

//**************************************************************************
//  FUNCTION:       convert2UpperCase
//  DESCRIPTION:    converts  string to upper case
//  INPUT			Parameters - stringInput - string input
//  OUTPUT:			upperCasedString - upper cased string
//**************************************************************************
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

//**************************************************************************
//  FUNCTION:       ask2LoadExistingData
//  DESCRIPTION:    Asks user if they would like to load existing data 
//  INPUT			Parameters - topOfList - Top of linked List
//							   - endOfList - End of linked list
//
//  OUTPUT:			Imports existing data into linked list 
//**************************************************************************
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

					
				}

			} while (fileReadErorr == true);

			inputFile1.close();
		}


	} while (numOfErrors > 0);


}

//**************************************************************************
//  FUNCTION:       showRentals 
//  DESCRIPTION:    Displays a list of all rental data on file 
//  INPUT			Parameters - MainMenuChoice - Main Menu Choice
//							   - topOfList - Top of linked List
//							   - endOfList - End of linked list
//
//  Return:			None
//**************************************************************************
void showRentals(string MainMenuChoice, residence *& topOfList, residence *& endOfList)
{
	if (MainMenuChoice == "S")
	{ 
		int widthValue = 15; 
		int precisionAmount = 2;

		cout << fixed << showpoint << setprecision(precisionAmount);
		cout << "Phone Nmmber" << setw(widthValue) << " Monthly Rent" << setw(widthValue) << "Status      " << endl;
		cout << "------------" << setw(widthValue) << "-------------" << setw(widthValue) << "------------" << endl;

		residence *here = topOfList;
		while (here != NULL) // while not at end of list… 
		{                
	
			cout << here->phoneNumber << setw(widthValue);    // Print phone number in node pointed 
			cout << here->monthlyRent << setw(widthValue);    // Print monthly in node pointed 

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

//**************************************************************************
//  FUNCTION:       AddRentals2Array
//  DESCRIPTION:    Adds an entry to the linked list of Rental units
//  INPUT			Parameters - MainMenuChoice - Main Menu Choice
//							   - topOfList - Top of linked List
//							   - endOfList - End of linked list
//
//  Return:			None
//**************************************************************************
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

		if (length < PHONE_CHAR_LENGTH)
		{
			cout << "The phone number you entered is too short" << endl;
			cout << "Please follow the format \"###-###-####\" Try again." << endl;
			errorCounter++;
		}

		else if (length > PHONE_CHAR_LENGTH)
		{
			cout << "The phone number you entered is too long" << endl;
			cout << "Please follow the format \"###-###-####\" Try again." << endl;
			errorCounter++;
		}

		else if (length = PHONE_CHAR_LENGTH)
		{

			for (int index = 0; index < PHONE_CHAR_SECTION_1; index++)         // Used Loops for error checking 
			{
				if (!(isdigit(phoneNumber[index])))
				{

					errorCounter++;
					//cout << "not a number " << endl; 
				}

			}


			for (int index = PHONE_CHAR_SECTION_1; index < PHONE_CHAR_SECTION_2; index++)         // Used Loops for error checking 
			{
				if (phoneNumber[index] != '-')
				{
					errorCounter++;
					//cout << "dash not where it should be " << endl;
				}

			}

			for (int index = PHONE_CHAR_SECTION_2; index < PHONE_CHAR_SECTION_3; index++)         // Used Loops for error checking 
			{
				if (!(isdigit(phoneNumber[index])))
				{
					errorCounter++;
					//cout << "not a number " << endl;
				}

			}

			for (int index = PHONE_CHAR_SECTION_3; index < PHONE_CHAR_SECTION_4; index++)         // Used Loops for error checking 
			{
				if (phoneNumber[index] != '-')
				{
					errorCounter++;
					//cout << "dash not where it should be " << endl;
				}

			}

			for (int index = PHONE_CHAR_SECTION_4; index < PHONE_CHAR_SECTION_5; index++)         // Used Loops for error checking 
			{
				if (!(isdigit(phoneNumber[index])))
				{
					errorCounter++;
					//cout << "not a number " << endl;
				}

			}

		} /// end else if

		if ((length == PHONE_CHAR_LENGTH) && (errorCounter > 0))
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
			cin.ignore(IGNORE_AMOUNT, '\n');
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

//**************************************************************************
//  FUNCTION:       deleteARental
//  DESCRIPTION:    Deletes an entry from the linked list of Rental units 
//  INPUT			Parameters - MainMenuChoice - Main Menu Choice
//							   - topOfList - Top of linked List						
//  Return:			None
//**************************************************************************
void deleteARental(string MainMenuChoice, residence *& topOfList)
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

//*************************************************************************
//  FUNCTION:	  displayAptPhoneNumbers
//  DESCRIPTION:  Displays a list of all rental phone numbers on file
//  INPUT:        Parameters:  - topOfList - Top of linked List	
//
//  Return:		  None
//*************************************************************************
void displayAptPhoneNumbers(residence *& topOfList)
{
	int precisionAmount = 2;
	
	cout << fixed << showpoint << setprecision(precisionAmount);
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
		int  ModCounter = 0;
		int widthValue = 20;
		int precisionAmount = 2;

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

				cout << fixed << showpoint << setprecision(precisionAmount);

				//cout << "Phone  : " << phoneNumber << endl;	// debug line
				//cout << "+ or - : " << plusOrMinus << endl;	// debug line
				//cout << "bhm    : " << byHowMuch << endl;		// debug line

				residence *here = topOfList;      // pointer, initialized to top node 

				while (here != NULL)
				{
					
					if (here->phoneNumber == phoneNumber)
					{

						if (plusOrMinus == '+')
						{
							if (here->monthlyRent + byHowMuch >= MAX_RENT)
							{
								cout << here->phoneNumber << setw(widthValue) << "Error! rent would be >= " << MAX_RENT << endl;
							}

							else
							{
								here->monthlyRent = (here->monthlyRent + byHowMuch);
								cout << here->phoneNumber << setw(widthValue) << here->monthlyRent << endl;
								ModCounter++;
							}
						}

						if (plusOrMinus == '-')
						{
							if (here->monthlyRent - byHowMuch <= 0)
							{
								cout << here->phoneNumber << setw(widthValue) << "Error! rent would be <= 0" << endl;
							}

							else
							{
								here->monthlyRent = (here->monthlyRent - byHowMuch);
								cout << here->phoneNumber << setw(widthValue) << here->monthlyRent << endl;
								ModCounter++;
							}
						}
					}

						here = here->next;     // If not, move to next node in list 

				}

			} while (modsFile);

			if (ModCounter > 0)
			{
				cout << "Total Modifictaions made = " << ModCounter << endl;
			}

			else
			{
				cout << "The file MODS.txt does indeed exist." << endl;
				cout << "However it does not contain any usable information" << endl;
				cout << "Toal chnages made = " << ModCounter << " Womp Womp." << endl;
			}

			modsFile.close();
		}
	}	 
}

//**************************************************************************
//  FUNCTION:       exitProgram
//  DESCRIPTION:    Allows user to save data and or exit program 
//  INPUT			Parameters - MainMenuChoice - Main Menu Choice
//							   - topOfList - Top of linked List
//							   - endOfList - End of linked list
//
//  Return:			None
//**************************************************************************
void exitProgram(string MainMenuChoice, residence *& topOfList)
{
	if (MainMenuChoice == "X")
	{
		ofstream data2Save;

		string saveDataResponse;
		string overWriteDataResponse;
		string outputFileName;
		int errorCounter; 

		do
		{

			cout << "Wait! Before you go,would you like to save any modification you may have made" << endl;
			cout << "Enter your choice as Y = yes, N = No : ";
			cin >> saveDataResponse;
			saveDataResponse = convert2UpperCase(saveDataResponse);

			if ((saveDataResponse != "Y") && (saveDataResponse != "N"))
				
			{
				cout << endl;
				cout << "ERROR! Unrecognized input, please try again." << endl;
				cout << endl;
			}

		} while ((saveDataResponse != "Y") && (saveDataResponse != "N"));


		if (saveDataResponse == "Y")
		{

			do
			{
				cout << endl;
				cout << "Plese enter a file name for the data you wish to save" << endl;
				cout << "Lets make things simple...and remember to end file name with .txt" << endl;
				cout << "Enter File Name Here :";
				cin.clear();
				getline(cin >> ws, outputFileName);

				outputFileName = convert2UpperCase(outputFileName);
				

			} while (checkFileExt(outputFileName) != true);

			if (does_file_exist(outputFileName) == true)
			{
				do
				{
					errorCounter = 0;
					cout << "Warning your are about to overwrite existing file named  " << outputFileName << endl;
					cout << "Are you 100% sure this is what you want to do" << endl;
					cout << "Enter your choice as Y = yes, N = No : ";
					cin >> overWriteDataResponse;
					overWriteDataResponse = convert2UpperCase(overWriteDataResponse);

					if ((overWriteDataResponse != "Y") && (overWriteDataResponse != "N"))

					{
						cout << endl;
						cout << "ERROR! Unrecognized input, please try again." << endl;
						errorCounter++;
						cout << endl;
					}

				} while (errorCounter > 0);

				if (overWriteDataResponse == "Y")
				{
					cout << endl;
					cout << "Warning, File will be overwritten. ";

					data2Save.open(outputFileName.c_str());     // open file for writing

					residence *here = topOfList;      // pointer, initialized to top node 

					while (here != NULL)
					{
						data2Save << here->phoneNumber << " " << here->monthlyRent << " " << here->rented << endl;
						here = here->next;
					}

					cout << "Data successfully Exported to file named " << outputFileName << endl;
					cout << "Thank you, come again!" << endl;
					data2Save.close();     // close output file
					
				}

				else if (overWriteDataResponse == "N")
				{
					cout << endl;
					cout << "Okay Enter a different file name here: ";
					cin.clear();
					getline(cin >> ws, outputFileName);
					outputFileName = convert2UpperCase(outputFileName);

					data2Save.open(outputFileName.c_str());     // open file for writing
					
					residence *here = topOfList;      // pointer, initialized to top node 

					while (here != NULL)
					{
						data2Save << here->phoneNumber << " " << here->monthlyRent << " " << here->rented << endl;
						here = here->next;
					}

					cout << "Data successfully Exported to file named " << outputFileName << endl;
					cout << "Thank you, come again!" << endl; 
					data2Save.close();     // close output file
				}

			}

		}
	}

}

//**************************************************************************
//  FUNCTION:       checkFileExt
//  DESCRIPTION:    Varifies output file has .txt extention
//  INPUT			Parameters - fileName2check - File Name to check
//
//  Return:			bool - isFileExtGood - is file good 
//*************************************************************************
bool checkFileExt(string fileName2check)
{

	int length = fileName2check.length();			// length of file name
	bool isFileExtGood;

	if ((fileName2check[length - TXT_DOT_LOCATION] == '.') && (fileName2check[length - TXT_T1_LOCATION] == 'T') &&
		(fileName2check[length - TXT_X_LOCATION] == 'X') && (fileName2check[length - TXT_T2_LOCATION] == 'T'))
	{
		isFileExtGood = true; 

	}

	else
	{
		isFileExtGood = false;
		cout << endl; 
		cout << "Error! File name extention does not end with .txt" << endl; 
		cout << "Please Try again." << endl; 

	}

	return isFileExtGood;
}

//**************************************************************************
//  FUNCTION:       does_file_exist
//  DESCRIPTION:    Checks to see if file specified exists with home directory 
//  INPUT			Parameters - fileName - File Name
//
//  Return:			bool - isFileReadable - is file readable 
//*************************************************************************
bool does_file_exist(string fileName)
{

	bool isFileReadable;
	ifstream infile(fileName);

	if (infile)
	{
		isFileReadable = true;
	}

	else
	{
		isFileReadable = false; 
	}

	return isFileReadable; 
}

