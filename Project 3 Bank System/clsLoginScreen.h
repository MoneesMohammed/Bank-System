#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;


class clsLoginScreen : protected clsScreen
{
	

	static bool _Login()
	{
		short FaildLoginCount = 3;
		bool LoginFaild = false;
		string UserName = "", Password = "";
		

		do
		{
			
			 if (LoginFaild)
			 {
				 FaildLoginCount--;
				 cout << "\nInvalid UserName/Password : ";
				 cout << "\nYou have "<< FaildLoginCount <<" Trial(s) to login. \n\n";
			 }

			 if (FaildLoginCount == 0)
			 {
				 cout << "\nYour are Locked after 3 faild trails\n\n";
				 return false;
			 }

			cout << "Enter UserName : ";
			UserName = clsInputValidate::ReadString();

			cout << "Enter Password : ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:


	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tLogin Screen");

		return _Login();


	}


};

