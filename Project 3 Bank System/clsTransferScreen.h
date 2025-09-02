#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsTransferScreen : protected clsScreen
{
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer From: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        return AccountNumber;

    }

    static float ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadFloatNumber();

        while (Amount > SourceClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }


public:

	static void ShowTransferScreen()
	{
        _DrawScreenHeader("\t  Transfer Screen");
        string AccountNumber1 , AccountNumber2;
        cout << "\nPlease Enter Account Number To Transfer From : ";
        AccountNumber1 = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccountNumber1))
        {
            cout << "\nClient with[" << AccountNumber1 << "] does not exist. , Choose another one\n";
            AccountNumber1 = clsInputValidate::ReadString();
        }

        clsBankClient SourceClient = clsBankClient::Find(AccountNumber1);
        _PrintClient(SourceClient);

        cout << "\nPlease Enter Account Number To Transfer To : ";
        AccountNumber2 = clsInputValidate::ReadString();


        while (!clsBankClient::IsClientExist(AccountNumber2))
        {
            cout << "\nClient with[" << AccountNumber2 << "] does not exist. , Choose another one\n";
            AccountNumber2 = clsInputValidate::ReadString();
        }

        clsBankClient DestinationClient = clsBankClient::Find(AccountNumber2);
        _PrintClient(DestinationClient);

        double Amount = 0;
        cout << "\nEnter Transfer Amount ? ";
        Amount = clsInputValidate::ReadDblNumberBetween(1, SourceClient.AccountBalance, "Amount Exceeds the available Balance, Enter another Amount :");

        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = clsInputValidate::ReadChar();

        if (Answer == 'y' || Answer == 'Y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient))
            {
               
                cout << "\nTransfer done successfully.\n\n";
                
                _PrintClient(SourceClient);
                _PrintClient(DestinationClient);
            }

        }
        else
        {
            cout << "\nOperation Was Cancelled.\n";

        }
	}

};

