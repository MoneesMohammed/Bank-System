#pragma once
#include <iostream>
#include <String>
#include "clsDate.h"
#include "clsUtil.h"
#include "clsString.h"
using namespace std;

class clsInputValidate
{
private:
	

public:

	static bool IsNumberBetween(short Number, short From, short To)// هل الرقم يقع ما بين
	{

		return (From <= Number && To >= Number);

	}

	static bool IsNumberBetween(int Number ,int From,int To)  
	{
	
		return (From <= Number && To >= Number);

	}

	static bool IsNumberBetween(float Number, float From, float To)
	{

		return (From <= Number && To >= Number);

	}


	static bool IsNumberBetween(double Number, double From, double To)
	{
		
		return (From <= Number && To >= Number);

	}


	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if (clsDate::IsDate1BeforeDate2(To ,From )) clsUtil::Swap(From, To);

		return (clsDate::IsDate1BeforeDate2(From, Date) || clsDate::IsDate1EqualDate2(Date, From)) && (clsDate::IsDate1BeforeDate2(Date,To ) || clsDate::IsDate1EqualDate2(Date, To));
		
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		short Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}


	static int ReadIntNumber(string ErrorMessage = "Invalid Number , Enter Again\n")
	{
		int Number = 0;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << ErrorMessage << "\n";
			cin >> Number;
		}
		
		return Number;
	}

	static double ReadFloatNumber(string ErrorMessage = "Invalid Number , Enter Again\n")
	{
		float Number = 0;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << ErrorMessage << "\n";
			cin >> Number;
		}

		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number , Enter Again\n")
	{
		double Number = 0;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');

			cout << ErrorMessage << "\n";
			cin >> Number;
		}

		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadShortNumber();
		}
		return Number;
	}


	static int ReadIntNumberBetween(int From , int To, string ErrorMessage ="Numbre is not wihtin range , Enter Again ?")
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << "\n";
			Number = ReadIntNumber();
			
		}

		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Numbre is not wihtin range , Enter Again ?")
	{
		double Number = ReadDblNumber();
		
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage << "\n";
			Number = ReadDblNumber();
		}
		
		return Number;
	}


	static bool IsValidDate(clsDate Date)
	{

		return clsDate::IsValidDate(Date);

	}

	static string ReadString()
	{
		string S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);

		return S1;

	}

	static char ReadChar()
	{
		char chr = 'n';
		cin >> chr;

		return chr;

	}
	

};

