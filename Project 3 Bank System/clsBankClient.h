#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"clsString.h"
#include"clsPerson.h"
#include "Global.h"
#include "clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode {EmptyMode , UpdateMode , AddNewMode };
	 enMode _Mode;

    string _AccountNumber;
	string _PinCode;
	float  _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line , string Separator= "#//#")
	{
		vector<string> vClient = clsString::Split(Line, Separator);
		return clsBankClient(UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stof(vClient[6]));
		
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
	  return Client.FirstName + Separator + Client.LastName + Separator + Client.Email + Separator + Client.Phone + Separator + Client.AccountNumber()
			+ Separator + Client.PinCode + Separator + to_string(Client.AccountBalance);

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(EmptyMode, "", "", "", "", "", "", 0);
	}

	
	static vector <clsBankClient> _LoadClientDataFromFile()
	{
		vector <clsBankClient> _vClient;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
                
				_vClient.push_back(Client);

				
			}
			
			MyFile.close();
		}

		return  _vClient;
	}

	static void _SaveClientDataFromFile(vector <clsBankClient> vClient)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{
			
			for(clsBankClient C : vClient)
			{  
				if (!C._MarkedForDelete)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
				
			}


			MyFile.close();
		}



	}



	void _Update()
	{
		vector <clsBankClient> _vClient;
		_vClient = _LoadClientDataFromFile();

		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientDataFromFile(_vClient);

	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app);

		if (MyFile.is_open())
		{

		    MyFile << stDataLine << endl;
			
			MyFile.close();
		}

	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _Delete()
	{
		vector <clsBankClient> vClient;
		vClient = _LoadClientDataFromFile();

		for (int i = 0; vClient.size() >= i; i++)
		{
			if (vClient[i].AccountNumber() == AccountNumber())
			{
				vClient.erase(vClient.begin() + i);
				break;
			}

		}

		_SaveClientDataFromFile(vClient);

		*this = _GetEmptyClientObject();
	}


	string _PrepareTransferLogRecord(double Amount ,clsBankClient DestinationClient,string Seperator = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;;
		TransferLogRecord += CurrentUser.UserName ;
		
		return TransferLogRecord;
	}

	void _RegisterTransferLog(double Amount, clsBankClient DestinationClient)
	{
		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient);
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#")
	{
		stTransferLogRecord TransferLogRecord;
		vector <string> vTransferLogRecord = clsString::Split(Line, Separator);

		TransferLogRecord.DateTime                 = vTransferLogRecord[0];
		TransferLogRecord.SourceAccountNumber             = vTransferLogRecord[1];
		TransferLogRecord.DestinationAccountNumber        = vTransferLogRecord[2];
		TransferLogRecord.Amount                   = stod(vTransferLogRecord[3]);
		TransferLogRecord.SourceBalanceAfter      = stod(vTransferLogRecord[4]);
		TransferLogRecord.DestinationBalanceAfter = stod(vTransferLogRecord[5]);
		TransferLogRecord.UserName                 = vTransferLogRecord[6];

		return TransferLogRecord;
	}

public:


	clsBankClient(enMode Mode,string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode , float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		 
		_Mode           = Mode;
		_AccountNumber  = AccountNumber;
		_PinCode        = PinCode;
		_AccountBalance = AccountBalance;

	}

	bool IsEmpty() { return (_Mode == enMode::EmptyMode); }

	string AccountNumber() { return _AccountNumber; } //Read Only Property

	void   SetPinCode(string PinCode) { _PinCode = PinCode; }
	string GetPinCode(){ return _PinCode; }

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void   SetAccountBalance(float AccountBalance) { _AccountBalance = AccountBalance; }
	float GetAccountBalance() { return _AccountBalance; }

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClient;
		string Line;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
         
		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

				vClient.push_back(Client);

			}

			MyFile.close();
		}


		return _GetEmptyClientObject();

	}


	static clsBankClient Find(string AccountNumber , string PinCode)
	{
		vector<clsBankClient> vClient;
		string Line;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}

				vClient.push_back(Client);

			}

			MyFile.close();
		}


		return _GetEmptyClientObject();

	}

	enum enSaveResult{svFaildEmptyObjact , svSucceeded , svFaildAccountNumberExists};

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
		{
			if(IsEmpty()) return enSaveResult::svFaildEmptyObjact;
            
			break;
		}
		case clsBankClient::UpdateMode:
		{
			_Update();
			return enSaveResult::svSucceeded;
			break;
		}
		case clsBankClient::AddNewMode:
		{
			if (IsClientExist(_AccountNumber))
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

	bool Delete()
	{
		vector <clsBankClient> _vClient;
		_vClient = _LoadClientDataFromFile();

		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientDataFromFile(_vClient);

		*this = _GetEmptyClientObject();
		
		return true;

	}


	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		 return clsBankClient(AddNewMode, "", "", "", "", AccountNumber, "", 0);

	}


	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());

	}

	static vector <clsBankClient> GetClientsList()
	{

		return  _LoadClientDataFromFile();


	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClient = clsBankClient::GetClientsList();
		double TotalBalances = 0;

		for (clsBankClient Client : vClient)
		{

			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}


	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();

	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
          _AccountBalance -= Amount;
		  Save();
		}
		

		return true;
	}


	bool Transfer(double Amount ,clsBankClient & DestinationClient)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient);

		return true;
	}

	struct stTransferLogRecord
	{
		string DateTime, SourceAccountNumber , DestinationAccountNumber, UserName;
		double Amount , SourceBalanceAfter , DestinationBalanceAfter;
	};

	static vector <stTransferLogRecord> GetTransferLogListList()
	{

		vector <stTransferLogRecord> vTransferLogRecord;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			stTransferLogRecord TransferLogRecord;

			while (getline(MyFile, Line))
			{
				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogRecord.push_back(TransferLogRecord);


			}

			MyFile.close();
		}

		return  vTransferLogRecord;


	}


};

