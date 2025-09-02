#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "clsPerson.h"
#include "clsDate.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode, UpdateMode, AddNewMode };
	enMode _Mode;
	string _UserName, _Password;
	int _Permissions;
	
	bool _MarkedForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
	{
		vector<string> vUser = clsString::Split(Line, Separator);
		return clsUser(UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], clsUtil::DecryptText(vUser[5]), stoi(vUser[6]));

	}


	static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
	{
		return User.FirstName + Separator + User.LastName + Separator + User.Email + Separator + User.Phone + Separator + User.UserName
			+ Separator + clsUtil::EncryptText(User.Password) + Separator + to_string(User.Permissions);

	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(EmptyMode, "", "", "", "", "", "", 0);
	}


	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> _vUser;
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				_vUser.push_back(User);


			}

			MyFile.close();
		}

		return  _vUser;
	}

	static void _SaveUsersDataFromFile(vector <clsUser> vUser)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsUser User : vUser)
			{
				if (!User._MarkedForDelete)
				{
					DataLine = _ConvertUserObjectToLine(User);
					MyFile << DataLine << endl;
				}

			}


			MyFile.close();
		}



	}

	void _Update()
	{
		vector <clsUser> _vUser;
		_vUser = _LoadUsersDataFromFile();

		for (clsUser& User : _vUser)
		{
			if (User.UserName == GetUserName())
			{
				User = *this;
				break;
			}
		}

		_SaveUsersDataFromFile(_vUser);

	}


	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	 


	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord +=  UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}


	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Separator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> vLoginRegisterRecord = clsString::Split(Line, Separator);
		LoginRegisterRecord.DateTime = vLoginRegisterRecord[0];
		LoginRegisterRecord.UserName = vLoginRegisterRecord[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegisterRecord[2]);
		LoginRegisterRecord.Permissions = stoi(vLoginRegisterRecord[3]);
		return LoginRegisterRecord;
	}
	

public:

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone , string UserName , string Password , int Permissions ) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode        = Mode;
		_UserName    = UserName;
		_Password    = Password;
		_Permissions = Permissions;
		
	}

	

	

	enum enPermissions { eAll = -1 ,pListClient = 1 , pAddNewClient = 2 , pDeleteClient = 4 , pUpdateClient = 8 
		                , pFindClient = 16 ,  pTransactions = 32 , pManageUsers = 64 , pLoginRegister = 128};


	bool IsEmpty() { return (_Mode == enMode::EmptyMode); }

	bool MarkedForDeleted() { return _MarkedForDelete; }

	void   SetUserName(string UserName) { _UserName = UserName; }
	string GetUserName() { return _UserName; }

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void   SetPassword(string Password) { _Password = Password; }
	string GetPassword() { return _Password; }

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void  SetPermissions(int Permissions) { _Permissions = Permissions; }
	int   GetPermissions() { return _Permissions; }

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	

	static clsUser Find(string UserName)
	{
		vector<clsUser> vUser;
		string Line;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{

				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}

				vUser.push_back(User);

			}

			MyFile.close();
		}


		return _GetEmptyUserObject();

	}


	static clsUser Find(string UserName , string Password)
	{
		vector<clsUser> vUser;
		string Line;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{

				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

				vUser.push_back(User);

			}

			MyFile.close();
		}


		return _GetEmptyUserObject();

	}


	enum enSaveResult { svFaildEmptyObjact, svSucceeded, svFaildAccountNumberExists };

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
		{
			if (IsEmpty()) return enSaveResult::svFaildEmptyObjact;

			break;
		}
		case clsUser::UpdateMode:
		{
			_Update();
			return enSaveResult::svSucceeded;
			break;
		}
		case clsUser::AddNewMode:
		{
			if (IsUserExist(_UserName))
			{
				return enSaveResult::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}

			break;
		}

		default:
			break;
		}



	}


	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());

	}

	bool Delete()
	{
		vector <clsUser> _vUser;
		_vUser = _LoadUsersDataFromFile();

		for (clsUser& User : _vUser)
		{
			if (User.UserName == GetUserName())
			{
				User._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataFromFile(_vUser);

		*this = _GetEmptyUserObject();

		return true;

	}

	static clsUser GetAddNewUserObject(string AccountNumber)
	{
		return clsUser(AddNewMode, "", "", "", "", AccountNumber, "", 0);

	}

	static vector <clsUser> GetUsersList()
	{

		return  _LoadUsersDataFromFile();


	}

	

	static vector <stLoginRegisterRecord> GetLoginRegisterList()
	{

		vector <stLoginRegisterRecord> vLoginRegisterRecord;
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{
				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);


			}

			MyFile.close();
		}

		return  vLoginRegisterRecord;


	}


	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;

	}

	struct stLoginRegisterRecord
	{
		string DateTime, UserName, Password;
		int Permissions;
	};



    void RegisterLogin()
	{
		string stDataLine = _PrepareLogInRecord();
		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}



};

