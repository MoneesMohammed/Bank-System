#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsUser.h"
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"

class clsTransferLogScreen : protected clsScreen
{
    static void _PrintTransferLogRecordList(clsBankClient::stTransferLogRecord TransferLogRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(20) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(10) << left << TransferLogRecord.SourceAccountNumber;
        cout << "| " << setw(10) << left << TransferLogRecord.DestinationAccountNumber;
        cout << "| " << setw(10) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.SourceBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.DestinationBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.UserName;

    }


public:

    static void ShowTransferLogScreen()
    {
      
        vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogListList();

        string Title = "\Transfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        cout << setw(8) << left << "" << "| " << left << setw(20) << "Date/Time";
        cout << "| " << left << setw(10) << "S.Acct";
        cout << "| " << left << setw(10) << "D.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (vTransferLogRecord.size() == 0)
        {
            cout << "\t\t\t\tNo Clients Available In The System!";
        }
        else
        {
            for (clsBankClient::stTransferLogRecord TransferLogRecord : vTransferLogRecord)
            {

                _PrintTransferLogRecordList(TransferLogRecord);
                cout << endl;
            }

        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }



};

