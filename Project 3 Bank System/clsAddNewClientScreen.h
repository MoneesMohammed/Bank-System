#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include"clsInputValidate.h"


class clsAddNewClientScreen :protected clsScreen
{
   static void _ReadClientInfo(clsBankClient& Client)
   {
        string FirstName = "", LastName = "", Email = "", Phone = "", PinCode = "";
        float Balance = 0;

        cout << "\nEnter FirstName : ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName : ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email : ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone : ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance : ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();

   }

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

    static void ShowAddNewClientScreen()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }

        _DrawScreenHeader("\t  Add New Client Screen");
        string AccountNumber = "";
        cout  << "\nPlease Enter Client Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number Is Already Used, Choose Another One : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);
        
        clsBankClient::enSaveResult SaveResult;

        SaveResult = NewClient.Save();


        switch (SaveResult)
        {
        case clsBankClient::svFaildEmptyObjact:
            cout << "\nError Account was not saved because it's Empty\n";
            break;
        case clsBankClient::svSucceeded:
            cout << "\nAccount Add New Successfully :-) \n";
            _PrintClient(NewClient);
            break;
        case clsBankClient::svFaildAccountNumberExists:
            cout << "\nError Account was not saved because it's Account Number Exists\n";
            break;
        default:
            break;
        }


    }

	


};

