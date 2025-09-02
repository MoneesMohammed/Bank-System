#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrenciesListScreen : protected clsScreen
{

    static void _PrintCurrencyRecordList(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(28) << left << Currency.GetCountry();
        cout << "| " << setw(5) << left << Currency.GetCurrencyCode();
        cout << "| " << setw(43) << left << Currency.GetCurrencyName();
        cout << "| " << setw(10) << left << Currency.GetRate();
   
    }

public:


    static void ShowCurrenciesListScreen()
    {
      
        vector <clsCurrency> vCurrency = clsCurrency::GetCurrenciesList();

        string Title = "\tCurrencies List Screen";
        string SubTitle = "\t    (" + to_string(vCurrency.size()) + ") Currency.";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        cout << setw(8) << left << "" << "| " << left << setw(28) << "Country";
        cout << "| " << left << setw(5) << "Code";
        cout << "| " << left << setw(43) << "Name";
        cout << "| " << left << setw(10) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vCurrency.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In The System!";
        }
        else
        {
            for (clsCurrency Currency : vCurrency)
            {

                _PrintCurrencyRecordList(Currency);
                cout << endl;
            }

        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }




};

