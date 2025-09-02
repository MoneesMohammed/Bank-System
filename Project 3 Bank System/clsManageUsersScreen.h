#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{

    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6,
        
    };

    static short _ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static  void _GoBackToManageUsersMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menue...\n";

        system("pause>0");
        ShowManageUsersMenue();
    }

    static void _ShowListUsersScreen()
    {
        clsUsersListScreen::ShowUsersListScreen();
        

    }

    static void _ShowAddNewUsersScreen()
    {
      
        clsAddNewUserScreen::ShowAddNewUserScreen();

    }

    static void _ShowDeleteUserScreen()
    {
        
        clsDeleteUserScreen::ShowDeleteUserScreen();

    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
       
    }

    
    static void _PerfromMainMenueOption(enManageUsersMenueOptions ManageUsersOption)
    {
        switch (ManageUsersOption)
        {
        case enManageUsersMenueOptions::eListUsers:
        {
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        }
        case enManageUsersMenueOptions::eAddNewUser:
            system("cls");
            _ShowAddNewUsersScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenueOptions::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenueOptions::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenueOptions::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;

        case enManageUsersMenueOptions::eMainMenue:
            

            break;

       

            
        }

    }



public:
    static void ShowManageUsersMenue()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;
        }

        system("cls");
        _DrawScreenHeader("\tManage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tManage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User \n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enManageUsersMenueOptions)_ReadManageUsersMenueOption());
    }

};

