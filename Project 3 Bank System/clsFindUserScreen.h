#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include"clsInputValidate.h"
#include "clsUtil.h"


class clsFindUserScreen : protected clsScreen
{

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________________";
        cout << "\nFirstName    : " << User.FirstName;
        cout << "\nLastName     : " << User.LastName;
        cout << "\nFull Name    : " << User.FullName();
        cout << "\nEmail        : " << User.Email;
        cout << "\nPhone        : " << User.Phone;
        cout << "\nUser Name    : " << User.UserName;
        cout << "\nPassword     : " << User.Password;
        cout << "\nPermissions  : " << User.Permissions;
        cout << "\n___________________________\n";

    }

public:

    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\tFind User Screen");
        string UserName = "";
        cout << "\nPlease Enter User Name : ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {

            cout << "User Name is not Found, choose another one : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        if (!User.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was Not Found :-(\n";
        }


        _PrintUser(User);
    }


};

