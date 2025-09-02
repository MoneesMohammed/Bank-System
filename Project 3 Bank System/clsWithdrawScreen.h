#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include"clsInputValidate.h"


class clsWithdrawScreen : protected clsScreen
{

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number ? ";
        AccountNumber = clsInputValidate::ReadString();

        return AccountNumber;
    }

public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t  Withdraw Screen");
        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with[" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nPlease Enter Withdraw amount : ";
        //Amount = clsInputValidate::ReadDblNumber();
        Amount = clsInputValidate::ReadDblNumberBetween(1, Client.AccountBalance, "Cannot withdraw, Insufficient Balance! , try again Enter Withdraw Amount :");

        cout << "\nyou are sure you want to perform this transactions ?\n";
        char Answer = clsInputValidate::ReadChar();

        if ( Answer == 'y' || Answer == 'Y' )
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdrawed Successfully.\n\n";
                cout << "New Balance Is :" << Client.AccountBalance << endl;
            }
            else
            {
                cout << "\nCannot withdraw, Insufficient Balance!.\n\n";
                cout << "Amout to withdraw is : " << Amount << endl;
                cout << "Your Balance is:" << Client.AccountBalance << endl;

            }
          
         
        }
        else
        {
          cout << "\nOperation Was Cancelled.\n";

        }



    }



};

