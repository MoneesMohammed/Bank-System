#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
    static void _PrintCurrency(clsCurrency Currency,string Title)
    {
        cout << "\n"<<Title<<"\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.GetCountry();
        cout << "\nCode       : " << Currency.GetCurrencyCode();
        cout << "\nName       : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) = : " << Currency.GetRate();

        cout << "\n_____________________________\n";

    }

    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;
        Amount = clsInputValidate::ReadFloatNumber();
        return  Amount;
    }

    static clsCurrency _GetCurrency(string MessageText)
    {
        string CurrencyCode = "";
        cout << MessageText;
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
        {
            cout << "Currency Code is not Found, Choose Another One : ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        return clsCurrency::FindByCode(CurrencyCode);
    }

    static void  _PrintCalculationResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {
        _PrintCurrency(Currency1, "Convert From:");
        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << "\n" << Amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInUSD << " USD\n";

        if (Currency2.GetCurrencyCode() == "USD")
        {
            return;
        }

        cout << "\n\nConverting from USD to:\n";
        _PrintCurrency(Currency2, "To:");
        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);
        cout << "\n" << Amount << " " << Currency1.GetCurrencyCode() << " = " << AmountInCurrency2 << " " << Currency2.GetCurrencyCode();
    }


public:

	static void ShowCurrencyCalculatorScreen()
	{
        char Continue = 'y';
        while(Continue == 'y' || Continue == 'Y')
        { 
           system("cls");
           _DrawScreenHeader("\tCurrency Calculator Screen");
         
           clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code : ");
           clsCurrency CurrencyTo   = _GetCurrency("\nPlease Enter Currency2 Code : ");
         
           
           float Amount = _ReadAmount();
         
           _PrintCalculationResults(Amount, CurrencyFrom, CurrencyTo);
         
           cout << "\n\nDo you want to perform another calculation? y/n ?";
           cin >> Continue;

        }
        

	}


};

