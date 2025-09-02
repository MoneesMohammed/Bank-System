#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
using namespace std;

class clsCurrency
{
private:
	enum enMode {EmptyMode =1 , UpdateMode = 2};
	enMode _Mode;
	string _Country, _CurrencyName, _CurrencyCode;
	float  _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
	{
		vector<string> vCurrencyData = clsString::Split(Line, Separator);
		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stod(vCurrencyData[3])) ;

	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
	{
		return Currency.GetCountry() + Separator + Currency.GetCurrencyCode() + Separator + Currency.GetCurrencyName() + Separator + to_string(Currency.GetRate());
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(EmptyMode, "", "", "",0);
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector <clsCurrency> _vCurrency;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				_vCurrency.push_back(Currency);


			}

			MyFile.close();
		}

		return  _vCurrency;
	}
	 
	static void _SaveCurrencyDataFromFile(vector <clsCurrency> vCurrency)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsCurrency Currency : vCurrency)
			{  

			  DataLine = _ConvertCurrencyObjectToLine(Currency);
			  MyFile << DataLine << endl;
			}

			MyFile.close();
		}

	}

	void _Update()
	{
		vector <clsCurrency> _vCurrency;
		_vCurrency = _LoadCurrencyDataFromFile();

		for (clsCurrency& Currency : _vCurrency)
		{
			if (Currency.GetCurrencyCode() == GetCurrencyCode())
			{
				Currency = *this;
				break;
			}
		}

		_SaveCurrencyDataFromFile(_vCurrency);

	}



public:

	clsCurrency(enMode Mode ,string Country, string CurrencyCode , string CurrencyName  , float Rate)
	{
		_Mode         = Mode;
		_Country      = Country;
		_CurrencyName = CurrencyName;
		_CurrencyCode = CurrencyCode;
		_Rate         = Rate;

	}


	bool IsEmpty() { return (_Mode == enMode::EmptyMode); }

	string GetCountry()      { return _Country; }
	string GetCurrencyName() { return _CurrencyName; }
	string GetCurrencyCode() { return _CurrencyCode; }
	float  GetRate()         { return _Rate; }
	
	
	void UpdateRate(float NewRate) 
	{ 
		_Rate  = NewRate;
		_Update();
	}
	

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency.GetCurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}

			}

			MyFile.close();
		}


		return _GetEmptyCurrencyObject();

	}
	
	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::LowerAllString(Country);
		vector<clsCurrency> vCurrency;
		string Line;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clsString::LowerAllString(Currency.GetCountry()) == Country)
				{
					MyFile.close();
					return Currency;
				}

				vCurrency.push_back(Currency);

			}

			MyFile.close();
		}


		return _GetEmptyCurrencyObject();

	}

	static bool IsCurrencyExistByCode(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());

	}

	static bool IsCurrencyExistByCountry(string CurrencyCountry)
	{
		clsCurrency Currency = clsCurrency::FindByCountry(CurrencyCountry);

		return (!Currency.IsEmpty());

	}

	static vector <clsCurrency> GetCurrenciesList()
	{

		return  _LoadCurrencyDataFromFile();


	}

	float ConvertToUSD(float Amount )
	{
		return Amount / GetRate();
	}

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);
		if (Currency2.GetCurrencyCode() == "USD") return AmountInUSD;

		return AmountInUSD * Currency2.GetRate();
	}

};

