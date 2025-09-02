#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsString.h"
#include "Global.h"
#include "clsUtil.h"


class clsAddNewUserScreen : protected clsScreen
{
    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;
        char Answer = 'a';

        cout << "\nDo you want to give full access? y/n? ";
        Answer = clsInputValidate::ReadChar();

        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
            
        }
        
        
            cout << "\nDo you want to give access to :\n";
            cout << "\nShow Client List? y/n? ";
            Answer = clsInputValidate::ReadChar();

            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pListClient;
            }

            cout << "\n\nAdd New Client? y/n? ";
            Answer = clsInputValidate::ReadChar();

            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pAddNewClient;
            }

            cout << "\n\nDelete Client? y/n? ";
            Answer = clsInputValidate::ReadChar();

            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pDeleteClient;
            }

            cout << "\n\nUpdate Client? y/n? ";
            Answer = clsInputValidate::ReadChar();

            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pUpdateClient;
            }

            cout << "\n\nFind Client? y/n? ";
            Answer = clsInputValidate::ReadChar();

            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pFindClient;
            }

            cout << "\n\nTransactions? y/n? ";
            Answer = clsInputValidate::ReadChar();

            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pTransactions;
            }

            cout << "\n\nManage Users? y/n? ";
            Answer = clsInputValidate::ReadChar();

            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pManageUsers;
            }

            cout << "\n\nLogin Register? y/n? ";
            Answer = clsInputValidate::ReadChar();

            if (Answer == 'y' || Answer == 'Y')
            {
                Permissions += clsUser::enPermissions::pLoginRegister;
            }

            return  Permissions;
        

    }
   
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName : ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName : ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email : ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone : ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password : ";
        User.Password = clsInputValidate::ReadString();
        cout << "\nEnter Permission : ";
        User.Permissions = _ReadPermissionsToSet();

    }

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

    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";
        cout << "\nPlease Enter UserName : ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "UserName Is Already Used, Choose Another One : ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);

        clsUser::enSaveResult SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case clsUser::svFaildEmptyObjact:
            cout << "\nError User was not saved because it's Empty\n";
            break;
        case clsUser::svSucceeded:
            cout << "\nUser Added Successfully :-) \n";
            _PrintUser(NewUser);
            break;
        case clsUser::svFaildAccountNumberExists:
            cout << "\nError User was not saved because it's User Name Exists\n";
            break;
        default:
            break;
        }


    }



};

