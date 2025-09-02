#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsString.h"
#include "Global.h"
#include "clsUtil.h"

class clsUsersListScreen : protected clsScreen
{
    static void _PrintUsersRecordList(clsUser User)
    {
        cout << setw(8) << left << "" << "| " << setw(10) << left << User.UserName;
        cout << "| " << setw(25) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(20) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(10) << left << User.Permissions;

    }

public:

    static void ShowUsersListScreen()
    {
        vector <clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t  Users List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        cout << setw(8) << left << "" << "| " << left << setw(10) << "UserName";
        cout << "| " << left << setw(25) << "FullName"; 
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vUsers.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In The System!";
        }
        else
        {
            for (clsUser User : vUsers)
            {

                _PrintUsersRecordList(User);
                cout << endl;
            }

        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }


};

