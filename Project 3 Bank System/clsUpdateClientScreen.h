#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include"clsInputValidate.h"

class clsUpdateClientScreen :protected clsScreen
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

    public:

   static void ShowUpdateClientScreen()
   {
       if (!_CheckAccessRights(clsUser::enPermissions::pUpdateClient))
       {
           return;
       }

       _DrawScreenHeader("\tUpdate Client Screen");
        string AccountNumber = "";
        cout << "\nPlease Enter Client Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {

            cout << "Account Number is not Found, choose another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nAre you sure you want to Update this Client y/n ?\n";
        char Answer = clsInputValidate::ReadChar();

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate Client Info :";
            cout << "\n--------------------\n";
            _ReadClientInfo(Client);


            clsBankClient::enSaveResult SaveResult;
            SaveResult = Client.Save();

            switch (SaveResult)
            {
            case clsBankClient::svFaildEmptyObjact:
                cout << "\nError Account was not saved because it's Empty\n";
                break;
            case clsBankClient::svSucceeded:
                cout << "\nAccount Updated Successfully :-) \n";
                _PrintClient(Client);
                break;
            default:
                break;
            }
        }
        

   }

};

