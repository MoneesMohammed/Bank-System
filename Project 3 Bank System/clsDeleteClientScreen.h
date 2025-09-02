#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include"clsInputValidate.h"


class clsDeleteClientScreen :protected clsScreen
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

public:

    static void ShowDeleteClientScreen()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }

        _DrawScreenHeader("\t  Delete Client Screen");
        string AccountNumber = "";
        cout << "\nPlease Enter Client Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not Found, choose another one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nyou are sure you want to Delete this Client y/n ?\n";
        char Answer = clsInputValidate::ReadChar();

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nAccount Deleted Successfully :-) \n";
                _PrintClient(Client);

            }
            else
            {
                cout << "\nError Account was not Deleted because it's Empty\n";
            }


        }

    }


};

