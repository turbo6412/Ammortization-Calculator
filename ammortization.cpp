// Anthony Vuong 
// HOMEWORK #3
// CWID : 888291937
// #30
// PROFESSOR MICHAEL FALKOW
// CPSC 120 



#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <locale>
#include <fstream>

using namespace std;

// Function Prototypes
void displayMenu();
int getChoice(int min, int max);
void investCalc();
void fixedMortgageCalc();
void carLoanCalc();
void verifyTable();					// HW 3 FUNCTION

// Constant variable given gonna use in formulas
const double e = 2.718281828459045;

/*****	 main	*****/
int main()
{
	string equals; // title decoration
	int choice; // for switch
	equals.assign(95, '='); // allows us to have 95 equal signs across same for the next line
	cout << equals << endl << endl;
	cout << "Anthony's Awesome Financial Calculators" << endl; // I ADDED THIS AFTER I SCREENSHOTED EVERYTHING
	cout << equals << endl << endl;
	do
	{
		displayMenu();					// this is gonna call down there to display the options to select

		choice = getChoice(1, 5);		// // this accounts for cin down there and also assigns a limit down there so you can only pick 1-4
		switch (choice)
		{
		case 1: investCalc();			// Calls for Investment Calculator
			break;
		case 2: fixedMortgageCalc();		// Calls for Fixed-Rate Mortgage Loan Calculator
			break;
		case 3: carLoanCalc();			// Calls for Car Loan Calculator
			break;
		case 4: verifyTable();		// Verification for amortization table in file
			break;
		case 5: cout << "Now exiting the program. Have a nice day Falkow!" << endl;		// Exit
			break;
		default: cout << "Error, please select one of the options from 1 to 4." << endl;
			break;
		}

	} while (choice != 5);


	system("Pause");
	return 0;
}

/*****		displayMenu		*****/
void displayMenu() // actual code when called to display menu
{
	cout << "Please select one of the three calculators or select option 4 to exit." << endl << endl;
	cout << "1. Investment Calculator" << endl
		<< "2. Fixed-Rate Mortgage Loan Calculator" << endl
		<< "3. Car Loan Calculator" << endl
		<< "4. Verify Amortization Table" << endl
		<< "5. Exit the Program" << endl << endl;
}

/*****		getChoice		*****/
int getChoice(int min, int max)
{
	int input;

	// Get and validate the input.
	cin >> input;
	while (input < min || input > max)
	{
		cout << "Invalid input. Enter an integer between 1 and 3 to select a calculator or choose 4 to exit the program: ";
		cin >> input;
	}
	return input; // takes us back to switch statement
}

/*****		investCalc		*****/
void investCalc()
{ 
	string f_name, mid_name, l_name, fullName, // Using these variables for the user's full name. The fullName is gonna be used for getline and as the filename for out.open
		 t, f; // using two cin answers, one for the table and one for the file
	double princip, annual_rate, total_invest,		// Variables for principle, annual rate, and total investment.
		new_invest, amt_earn,				// Variables for the table of growth.
		total_earn, initial_princip;
	int invest_time, year;						// Variables for investment time period and years.
	cout.imbue(locale("")); // does the commas

	cout << "Please enter your full name: ";
	cin >> f_name >> mid_name >> l_name;

	cout << "Please enter the amount you wish to invest or save: ";
	cin >> initial_princip;

	cout << "Please enter the average annual rate of return that you expect to recieve as a decimal: ";
	cin >> annual_rate;

	cout << "Please enter the time period, in years, that you expect to have the amount invested or saved for: ";
	cin >> invest_time;

	total_invest = initial_princip * pow(e, annual_rate * invest_time); // the pert formula defined into totalinvest
	cout << endl << "The total value of your investment of $" << initial_princip << " will be worth $" << fixed << setprecision(2) << total_invest
		<< " in " << invest_time << " years." << endl << endl;

	cout << "Would you like to see a table of growth of your investment? (y/n): ";
	cin >> t;
	if (t == "Y" || t == "y") // allows user to use both y and Y for producing table, if no goes back to main
	{ 
		total_earn = 0.0; // to start it out
		princip = initial_princip; // need this for new investment formula
		cout << setw(6) << right << "Year" << setw(24) << right << "Starting Investment"
			 << setw(25) << right << "New Investment Value" << setw(18) << right << "Amount Earned" << setw(19) << right << "Total Earnings" << endl;
	
		for (year = 1; year <= invest_time; year++) // used a for loop because we want the years to keep showing up until the investment time is up(whatever user put)
		{
			new_invest = initial_princip * pow(e, annual_rate * year);
			amt_earn = new_invest - princip; // subtract the difference of what your new investment is to orginal money to see how much you earned
			total_earn = total_earn + amt_earn;
			cout << setw(5) << fixed << setprecision(2) << right << year << setw(19) << fixed << setprecision(2) << right << princip 
				 << setw(25) << fixed << setprecision(2) << right << new_invest << setw(21) << fixed << setprecision(2) << right << amt_earn 
				 << setw(19) << fixed << setprecision(2) << right << total_earn << endl;
			princip = new_invest;
		}

		cout << endl << "Would you like to save this table to a text file? (y/n): "; // entering n would take us back to the top and end the program
		cin >> f;
		if (f == "Y" || f == "y") // allows user to use both y and Y for producing file, goes back to main if no
		{
			fullName = f_name + l_name + ".txt"; // need to do this before the out.open so that the file name(fullName) reads just first and last name no middle. ".txt" is in quotes so it turns the file in .txt file if you didn't put it in quotes it will treat it as a variable and won't recognize it since you never defined it
			ofstream out; // formulas for converting into files
			out.open(fullName.c_str());

			total_earn = 0.0;
			princip = initial_princip; // using out not cout because outputting to a file, but copying only the table data over 
			out << setw(6) << right << "Year" << setw(24) << right << "Starting Investment"
			 << setw(25) << right << "New Investment Value" << setw(18) << right << "Amount Earned" << setw(19) << right << "Total Earnings" << endl;
			for (year = 1; year <= invest_time; year++) // makes sure the year keeps going until it reaches the amount of time you want to invest
			{
				new_invest = initial_princip * pow(e, annual_rate * year);
				amt_earn = new_invest - princip; 
				total_earn = total_earn + amt_earn;
				out << setw(5) << fixed << setprecision(2) << right << year << setw(19) << fixed << setprecision(2) << right << princip 
				 << setw(25) << fixed << setprecision(2) << right << new_invest << setw(21) << fixed << setprecision(2) << right << amt_earn 
				 << setw(19) << fixed << setprecision(2) << right << total_earn << endl;
				princip = new_invest;
			}

			out.close(); // ends the file outputting 
			cout << endl << "You have successfully saved the table into a text file." << endl << endl;

		}

	}
	
	cout << "Press the Enter key to continue.";			// clear the screen neatly for a restart
	cin.get();
	cin.get();

	system("cls");
}

/*****		fixedMortgageCalc		*****/
void fixedMortgageCalc()
{
	string f_name2, m_name2, l_name2, fullName2,		// Variables for the user's full name for this calculator.
		u, m, q;										// Variables for user's choices.
	double morg_loan, morg_interest_rate,							// Variables for the mortgage loan amount and annual interest rate.
		r, n, month_pay,								// Variables for the monthly payment calculation.
		loan_bala, int_amt,							// Variables for amortization table.
		int_paid, princ_amt,
		princ_paid, new_bala, mort_pay,
		mort_int;
	int mort_yrs, pay_num, t;							// Variables for mortgage loan term in years, payment row number, and payment row number holder.
	cout.imbue(locale(""));

	cout << "Please enter your full name: ";
	cin >> f_name2 >> m_name2 >> l_name2;

	cout << "Please enter how much your mortgage loan will be: ";
	cin >> morg_loan;

	cout << "Please enter the annual interest rate of the mortgage loan as a decimal: ";
	cin >> morg_interest_rate;

	cout << "Please enter the term of the mortgage loan in years: ";
	cin >> mort_yrs;

	r = morg_interest_rate / 12;
	n = mort_yrs * 12;
	month_pay = morg_loan * ((r * pow((1 + r), n)) / (pow((1 + r), n) - 1));

	cout << endl << "Your monthly payment amount will be $" << fixed << setprecision(2) << month_pay << "." << endl << endl;

	cout << "Would you like to see an amortization table of this mortgage loan? (y/n): ";
	cin >> u;
	if (u == "y" || u == "Y")
	{
		new_bala = 0.0;
		int_paid = 0.0;
		princ_paid = 0.0;
		loan_bala = morg_loan;
		t = 1;
		do
		{
			cout << setw(9) << "Payment #" << setw(15) << "Loan Balance" << setw(19) << "Mortgage Payment" << setw(20) << "Mortgage Interest"
				<< setw(16) << "Interest Paid" << setw(19) << "Principle Amount" << setw(17) << "Principle Paid" << setw(19) << "New Loan Balance" << endl;
			for (pay_num = t; pay_num <= (t + 29); pay_num++)
			{
				if (pay_num <= n)
				{
					mort_pay = month_pay;
					mort_int = loan_bala * r;
					princ_amt = mort_pay - mort_int;
					new_bala = loan_bala - princ_amt;
					int_paid += mort_int;
					princ_paid += princ_amt;

					cout << setw(5) << fixed << setprecision(2) << right << pay_num << setw(18) << fixed << setprecision(2) << loan_bala
						<< setw(16) << fixed << setprecision(2) << mort_pay << setw(20) << fixed << setprecision(2) << mort_int
						<< setw(19) << fixed << setprecision(2) << int_paid << setw(17) << fixed << setprecision(2) << princ_amt
						<< setw(18) << fixed << setprecision(2) << princ_paid << setw(18) << fixed << setprecision(2) << new_bala << endl;

					loan_bala = new_bala;
				}
			}
			cout << "Would you like to continue with the amortization table calculations? (y/n): ";
			cin >> q;
			if (q == "y" || q == "Y")
			{
				t = pay_num;
			}

		} while (q == "y" || q == "Y");

		cout << endl << "Would you like to save this table to a text file? (y/n): ";
		cin >> m;
		if (m == "y" || m == "Y")
		{
			fullName2 = f_name2 + l_name2 + ".txt";
			ofstream out;
			out.open(fullName2.c_str());

			new_bala = 0.0;
			int_paid = 0.0;
			princ_paid = 0.0;
			loan_bala = morg_loan;
			out << setw(9) << "Payment #" << setw(15) << "Loan Balance" << setw(19) << "Mortgage Payment" << setw(20) << "Mortgage Interest"
				<< setw(16) << "Interest Paid" << setw(19) << "Principle Amount" << setw(17) << "Principle Paid" << setw(19) << "New Loan Balance" << endl;
			for (pay_num = 1; pay_num <= n; pay_num++)
			{
				int_amt = loan_bala * r;
				princ_amt = month_pay - int_amt;
				new_bala = loan_bala - princ_amt;
				int_paid += int_amt;
				princ_paid += princ_amt;

				out << setw(5) << fixed << setprecision(2) << right << pay_num << setw(18) << fixed << setprecision(2) << loan_bala
					<< setw(16) << fixed << setprecision(2) << mort_pay << setw(20) << fixed << setprecision(2) << int_amt
					<< setw(19) << fixed << setprecision(2) << int_paid << setw(17) << fixed << setprecision(2) << princ_amt
					<< setw(18) << fixed << setprecision(2) << princ_paid << setw(18) << fixed << setprecision(2) << new_bala << endl;

				loan_bala = new_bala;
			}

			out.close();
			cout << endl << "The table has been saved to a text file." << endl << endl;
		}

	}

	cout << "Press the Enter key to continue.";
	cin.get();
	cin.get();

	system("cls");
}

/*****		carLoanCalc		*****/
void carLoanCalc()
{
	string f_name3, m_name3, l_name3, fullName3,		// Variables for the user's full name for this calculator.
		f, b, z;										// Variables for the user's choices.
	double a_loan, a_int_rate,							// Variables for the auto loan and auto loan annual interest rate.
		r2, n2, month_pay2,							// Variables for monthly payment calcuation.
		new_bal2, int_paid2,							// Variables for armortization table.
		princ_paid2, loan_bal2,
		auto_pay, auto_int,
		princ_amt2;
	int auto_yrs, k, pay_num2;							// Variables for auto loan term in years, payment row number holder, and payment row number.
	cout.imbue(locale(""));

	cout << "Please enter your full name: ";
	cin >> f_name3 >> m_name3 >> l_name3;

	cout << "Please enter how much your auto loan will be: ";
	cin >> a_loan;

	cout << "Please enter the annual interest rate of the auto loan as a decimal: ";
	cin >> a_int_rate;

	cout << "Please enter the term of the auto loan in years: ";
	cin >> auto_yrs;

	r2 = a_int_rate / 12;
	n2 = auto_yrs * 12;
	month_pay2 = a_loan * ((r2 * pow((1 + r2), n2)) / (pow((1 + r2), n2) - 1));

	cout << endl << "Your monthly payment amount will be $" << fixed << setprecision(2) << month_pay2 << "." << endl << endl;

	cout << "Would you like to see an amortization table of this mortgage loan? (y/n): ";
	cin >> f;
	if (f == "y" || f == "Y")
	{
		new_bal2 = 0.0;
		int_paid2 = 0.0;
		princ_paid2 = 0.0;
		loan_bal2 = a_loan;
		k = 1;
		do
		{
			cout << setw(9) << "Payment #" << setw(15) << "Loan Balance" << setw(15) << "Auto Payment" << setw(16) << "Auto Interest"
				<< setw(16) << "Interest Paid" << setw(19) << "Principle Amount" << setw(17) << "Principle Paid" << setw(19) << "New Loan Balance" << endl;
			for (pay_num2 = k; pay_num2 <= (k + 29); pay_num2++)
			{
				if (pay_num2 <= n2)
				{
					auto_pay = month_pay2;
					auto_int = loan_bal2 * r2;
					princ_amt2 = auto_pay - auto_int;
					new_bal2 = loan_bal2 - princ_amt2;
					int_paid2 += auto_int;
					princ_paid2 += princ_amt2;

					cout << setw(5) << fixed << setprecision(2) << right << pay_num2 << setw(18) << fixed << setprecision(2) << loan_bal2
						<< setw(13) << fixed << setprecision(2) << auto_pay << setw(16) << fixed << setprecision(2) << auto_int
						<< setw(17) << fixed << setprecision(2) << int_paid2 << setw(17) << fixed << setprecision(2) << princ_amt2
						<< setw(18) << fixed << setprecision(2) << princ_paid2 << setw(18) << fixed << setprecision(2) << new_bal2 << endl;

					loan_bal2 = new_bal2;
				}

			}
			cout << "Would you like to continue with the amortization table calculations? (y/n): ";
			cin >> b;
			if (b == "y" || b == "Y")
			{
				k = pay_num2;
			}

		} while (b == "y" || b == "Y");

		cout << endl << "Would you like to save this table to a text file? (y/n): ";
		cin >> z;
		if (z == "y" || z == "Y")
		{
			fullName3 = f_name3 + l_name3 + ".txt";
			ofstream out;
			out.open(fullName3.c_str());

			new_bal2 = 0.0;
			int_paid2 = 0.0;
			princ_paid2 = 0.0;
			loan_bal2 = a_loan;
			out << setw(9) << "Payment #" << setw(15) << "Loan Balance" << setw(15) << "Auto Payment" << setw(16) << "Auto Interest"
				<< setw(16) << "Interest Paid" << setw(19) << "Principle Amount" << setw(17) << "Principle Paid" << setw(19) << "New Loan Balance" << endl;
			for (pay_num2 = 1; pay_num2 <= n2; pay_num2++)
			{
				auto_int = loan_bal2 * r2;
				princ_amt2 = month_pay2 - auto_int;
				new_bal2 = loan_bal2 - princ_amt2;
				int_paid2 += auto_int;
				princ_paid2 += princ_amt2;

				out << setw(5) << fixed << setprecision(2) << right << pay_num2 << setw(18) << fixed << setprecision(2) << loan_bal2
					<< setw(13) << fixed << setprecision(2) << auto_pay << setw(16) << fixed << setprecision(2) << auto_int
					<< setw(17) << fixed << setprecision(2) << int_paid2 << setw(17) << fixed << setprecision(2) << princ_amt2
					<< setw(18) << fixed << setprecision(2) << princ_paid2 << setw(18) << fixed << setprecision(2) << new_bal2 << endl;

				loan_bal2 = new_bal2;
			}

			out.close();
			cout << endl << "The table has been saved to a text file." << endl << endl;
		}

	}

	cout << "Press the Enter key to continue.";
	cin.get();
	cin.get();

	system("cls");
}

/*****		verifyTable	   *****/
void verifyTable()
{
	int year, rows;									// using 15 or 30 years we will use rows for (year * 12) + 1 
	double interest_total, princ_total;				// how we are going to get the sum of the two single columns by using these two accumulators
	ifstream dataIn;								// the name of our file carrier
	string readHeading[1][17], file_name;				// Use STRING for this array to read in headings and file is for the file name.
	double firstTable[361][8];		// this array is a place holder for the size of file, so for 30 years its 361 months (header + rows) and 8 columns, dont need 181 for 15, cause we made a formula for that limit later
	
	cout << "Which would you like to verify, 15 or 30 year amortization schedule?: ";  
		cin >> year;
	if (year == 30 || year == 15)						// we only want user to type in 30 or 15 years
	{
		rows = (year * 12) + 1;						// using 15 or 30 years with (year * 12) + 1 to calculate the exact number of rows SIZE not INDEX
		cout << "Please enter your filename you would like to validate. (put .txt afterwards): ";
		cin >> file_name;									// we want user to type their filename with .txt for the next function to work
	}
	else
	{
		cout << "Now exiting the program";
		return;													// will bring us back to switch statement (its in void)
	}
	dataIn.open(file_name);											// using our file variable from up there, whatever the user typed up there, will be put into function to open it
	if (dataIn.fail())											// if the file does not exist(not inside our folder) we wil display this message
	{
		cout << endl << "Error! Please enter the correct FILE NAME!" << endl;
	}
	else
	{
		interest_total = 0.0;										// Set interest and principal equal to zero, so they become accumulators for the sum 
		princ_total = 0.0;										// ex: 0 + table[i][4], just takes the sum of certain number of rows and a specific column
		for (int r = 0; r < 17; r++)							// Just trying to read in the header by itself, 17 b/c count the words that are spaced away
		{
			dataIn >> readHeading[0][r];							// Use dataIn to put all file table data into the matrix so that it loops all of it
		}									// Whole point is to just take the heading section of the file and put it into one array so the other array can't read headers(headers dropped) and get confused with calculations
		for (int i = 1; i < rows; i++)							// used nested for loop to record the rows after the header, since we did that previously, would be error if we said go header again
		{
			for (int x = 0; x < 8; x++)				// The next two fors are nested for loop that we will include it with dataIn to put the table data into the table array as it loops to record it into table array
				dataIn >> firstTable[i][x];				// so now table array has all the values in the file after the header 
		}
		for (int i = 1; i < rows; i++)				// using this for loop to take a section of the table array recordings and manipulate to add a certain rows and column(just one column like interest paid)
		{
			interest_total = interest_total + firstTable[i][3];				// using accumulators as we explained up there so 0 + each time the array loops for these two
			princ_total = princ_total + firstTable[i][5];					
		}
		cout << "Difference for the interest paid: $" << fixed << setprecision(2) << interest_total - firstTable[rows-1][4] << endl;		// subtract rows - 1 cause its the size, due to the second array recording past header, size is now 360, making 360 last row
		cout << "Difference for the principle paid: $" << fixed << setprecision(2) << princ_total - firstTable[rows-1][6] << endl;
	}	// else bracket
	dataIn.close();

	cout << endl << "Press the Enter key to continue.";		// neat restart to go back to switch statements after calculations
		cin.get();
		cin.get();

		system("cls"); // we want to clear the screen for a neat restart for user
} // last function bracket

