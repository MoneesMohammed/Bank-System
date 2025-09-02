#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsUtil.h"
#include"clsInputValidate.h"


class clsDeleteUserScreen : protected clsScreen
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

    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t  Delete User Screen");
        string UserName = "";
        cout << "\nPlease Enter User Name : ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is not Found, choose another one : \n";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        cout << "\nyou are sure you want to Delete this User y/n ?\n";
        char Answer = clsInputValidate::ReadChar();

        if (Answer == 'y' || Answer == 'Y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted Successfully :-) \n";
                _PrintUser(User);

            }
            else
            {
                cout << "\nError User was not Deleted because it's Empty\n";
            }


        }

    }

};

