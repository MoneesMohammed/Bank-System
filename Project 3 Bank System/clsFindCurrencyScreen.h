#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen
{

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.GetCountry();
        cout << "\nCode       : " << Currency.GetCurrencyCode();
        cout << "\nName       : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) = : " << Currency.GetRate();

        cout << "\n_____________________________\n";

    }

    enum enFindCurrencyOptions { ByCode = 1, ByCountry = 2 };

    static short _ReadFindCurrencyOption()
    {
        cout << "Find By: [1] Code or [2] Country ? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 2 , "Enter a Number , [1] Code or [2] Country ? ");
        return Choice;
    }

    static void _FindCurrencyByCode()
    {
        string Code = "";
        cout << "\nPlease Enter Currency Code : ";
        Code = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExistByCode(Code))
        {
            cout << "Currency Code is not Found, Choose Another One : ";
            Code = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(Code);

        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was Not Found :-(\n";
        }

        
    }
  
    static void _FindCurrencyByCountry()
    {
        string Country = "";
        cout << "\nPlease Enter Currency Country : ";
        Country = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExistByCountry(Country))
        {
            cout << "Currency Country is not Found, Choose Another One : ";
            Country = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCountry(Country);

        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was Not Found :-(\n";
        }

        
    }


public:

    static void ShowFindCurrencyScreen()
    {
         
       _DrawScreenHeader("\tFind Currency Screen");
       
       enFindCurrencyOptions FindCurrencyOptions = (enFindCurrencyOptions)_ReadFindCurrencyOption();

       switch (FindCurrencyOptions)
       {
       case enFindCurrencyOptions::ByCode:
           _FindCurrencyByCode();
           break;
       case enFindCurrencyOptions::ByCountry:
           _FindCurrencyByCountry();
           break;

       }

        
    }




};

