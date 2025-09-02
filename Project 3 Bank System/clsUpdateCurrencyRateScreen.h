#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsScreen.h"
#include"clsCurrency.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
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



public:

    static void ShowUpdateCurrencyRateScreen()
    {
        _DrawScreenHeader("\tUpdate Currency Screen");

        string CurrencyCode = "";
        cout << "\nPlease Enter Currency Code : ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExistByCode(CurrencyCode))
        {
            cout << "Currency Code is not Found, Choose Another One : ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        _PrintCurrency(Currency);

        cout << "\nAre you sure you want to Update the Rate of this Currency y/n ? ";
        char Answer = clsInputValidate::ReadChar();

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate Currency Rate :";
            cout << "\n--------------------\n";
            cout << "\nEnter New Rate : ";
            Currency.UpdateRate(clsInputValidate::ReadFloatNumber());

            cout << "\nCurrency Rate Updated Successfully :-) \n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nOperation Was Cancelled.\n";

        }



    }


};

