#pragma once
#include <iostream>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsString.h"
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"


using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{

    enum enCurrenciesMainOptions { eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eShowMainMenue = 5  };
        
    static short _ReadCurrenciesMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }

    static  void _GoBackToCurrenciesMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currencies Menue...\n";

        system("pause>0");
        ShowCurrenciesMenue();
    }
   
    static void _ShowCurrenciesListScreen()
    {
        //cout << "\nList Currencies Screen Will be here...\n"; 
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
       // cout << "\nFind Currency Screen Will be here...\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        //cout << "\nUpdate Rate Screen Will be here...\n";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
       // cout << "\nCurrency Calculator Screen Will be here...\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();

    }


    static void _PerfromCurrenciesMainMenueOption(enCurrenciesMainOptions CurrenciesMainMenueOption)
    {
        switch (CurrenciesMainMenueOption)
        {
        case enCurrenciesMainOptions::eListCurrencies:
        
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenue();
            break;
        
        case enCurrenciesMainOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;

        case enCurrenciesMainOptions::eUpdateRate:
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrenciesMenue();
            break;

        case enCurrenciesMainOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenue();
            break;

        case enCurrenciesMainOptions::eShowMainMenue:
           

            break;
        }
    }

public:


    static void  ShowCurrenciesMenue()
    {

        system("cls");
        _DrawScreenHeader("\tCurrency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exhange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrenciesMainMenueOption((enCurrenciesMainOptions)_ReadCurrenciesMainMenueOption());
    }




};

