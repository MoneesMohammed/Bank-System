#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"


class clsLoginRegisterScreen : protected clsScreen
{
    

    static void _PrintUsersRecordList(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(15) << left << LoginRegisterRecord.Permissions;

    }


public:

	static void ShowLoginRegisterScreen()
	{
        if (!_CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return;
        }


        vector <clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

        string Title = "\tLogin Register Screen";
        string SubTitle = "\t    (" + to_string(vLoginRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(15) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vLoginRegisterRecord.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In The System!";
        }
        else
        {
            for (clsUser::stLoginRegisterRecord LoginRegisterRecord : vLoginRegisterRecord)
            {

                _PrintUsersRecordList(LoginRegisterRecord);
                cout << endl;
            }

        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
	}


};

