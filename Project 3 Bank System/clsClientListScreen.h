#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>

class clsClientListScreen :protected clsScreen
{
    static void _PrintClientRecordList(clsBankClient Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }

public:

    static void ShowClientListScreen()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pListClient))
        {
            return;
        }

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        cout << setw(8) << left << "" << "| " << left << setw(15) << "AccountNumber";
        cout << "| " << left << setw(20) << "ClientName";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "PinCode";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vClients.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In The System!";
        }
        else
        {
            for (clsBankClient Client : vClients)
            {

                _PrintClientRecordList(Client);
                cout << endl;
            }

        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

