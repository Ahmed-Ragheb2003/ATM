#pragma warning (disable : 4996)
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>
using namespace std;

void ShowMainMenu();
void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();
void Login();

const string ClientsFileName = "Clients.txt";

void GoBackToMainMenu()
{
	cout << "\n\n\t\t\tPress any key to go back to Main Menu . . . ";
	system("pause>0");
	ShowMainMenu();
}

enum enMainMenu {
	eQuickWithdraw = 1, eNormalWithdraw = 2,
	eDeposit = 3, eCheckBalance = 4,ShowDataClient = 5 , eLogout = 6
};

struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

sClient CurrentClient;

vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable  

	// use find() function to get the position of the delimiters  
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word   
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());  // erase() until Position and move to next word. 
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}

sClient ConvertLineToRecord(string Line, string Separator = "#//#")
{
	sClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, Separator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double
	return Client;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Separator;
	stClientRecord += Client.PinCode + Separator;
	stClientRecord += Client.Name + Separator;
	stClientRecord += Client.Phone + Separator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

vector<sClient>LoadCleintsDataFromFile(string FileName)
{

    vector<sClient>vClient;
    
    fstream MyFile;
    
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClient.push_back(Client);
        }
    
        MyFile.close();
    }

    return vClient;

}

vector <sClient> SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();

    }
    return vClients;

}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient &C : vClients)
    {

        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }   
    }

    return false;
}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << left << setw(20) << Client.AccountNumber;
	cout << "| " << left << setw(15) << Client.PinCode;
	cout << "| " << left << setw(30) << Client.Name;
	cout << "| " << left << setw(15) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
	cout << "\n\t\t\tThe Following All Date To This Client.";
	cout << "\n_______________________________________________________";
	cout << "______________________________________________\n" << endl;

	cout << "| " << left << setw(20) << "Account Number";
	cout << "| " << left << setw(15) << "Pin Code";
	cout << "| " << left << setw(30) << "Client Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "______________________________________________\n" << endl;

	PrintClientRecordLine(CurrentClient);

	cout << endl;
    cout << "\n_______________________________________________________";
    cout << "______________________________________________\n" << endl;
}

short ReadChoiceMainMenu()
{
	short Choice = 0;
	
    do
	{
		cout << "Choose What do you want to do? [1 to 6]? ";	
        cin >> Choice;

	} while (Choice < 1 || Choice > 6);
	
    return Choice;
}

bool LoadClientInfo(string AccountNumber , string PinCode )
{
    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
        return true;
    else
        return false;
}

void Login()
{
    bool LoginFaild = false;
    string AccountNumber, PinCode;
    do
    {
        system("cls");
        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";

        if (LoginFaild)
        {
            cout << "Invalid Account Number/PinCode!\n";
        }

        cout << "Enter Account Number? ";
        cin >> AccountNumber;

        cout << "Enter Pin? ";
        cin >> PinCode;
        
        // NOT flase equle true to still return until found Client

        LoginFaild = !LoadClientInfo(AccountNumber, PinCode);

    } while (LoginFaild);

    ShowMainMenu();

}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
    char Answer = 'N';

    cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
    cin >> Answer;
    
    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }
        }
    }
    else
    {
        return false;
    }
    return false;
}

double ReadDepositAmount()
{
    double Amount = 0;
    cout << "Enter an amount Deposit: ";
    cin >> Amount;
    while (Amount <= 0)
    {
        cout << "Enter an amount Deposit: ";
        cin >> Amount;
    }
    return Amount;
}

void PerformDepositOption()
{
    double DepositAmount = ReadDepositAmount();
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients);
}

void showDepositScreen()
{
	system("cls");
	cout << "\n--------------------------------------------\n";
	cout << "\t\tDeposit Screen";
	cout << "\n--------------------------------------------\n";
    PerformDepositOption();
}

short ReadQuickWithdrawOption()
{
    short Choice = 0;

    while (Choice < 1 || Choice>9)
    {
        cout << "\nChoose what to do from [1] to [9]? ";
        cin >> Choice;
    }

    return Choice;
}

short getQuickWithDrawAmount(short QuickWithDrawOption)
{

    switch (QuickWithDrawOption)
    {
    case 1:
        return 100;
    case 2:
        return 250;
    case 3:
        return 300;
    case 4:
        return 450;
    case 5:
        return 500;
    case 6:
        return 750;
    case 7:
        return 800;
    case 8:
        return 1000;
    default:
        return 0;
    }
}

void PerformQuickWithdrawOption(short QuickWithDrawOption)
{
    if (QuickWithDrawOption == 9)//exit
        return;

    short WithDrawBalance = getQuickWithDrawAmount(QuickWithDrawOption);

    if (WithDrawBalance > CurrentClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, can Withdraw to Up " << CurrentClient.AccountBalance;
        cout << "\nPress any Key  to continue...";
        system("pause>0");
        ShowQuickWithdrawScreen();
        return;
    }

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients);
}

void ShowQuickWithdrawScreen()
{
    cout << "\n============================================\n";
    cout << "\tQuick Withdraw Screen";
    cout << "\n============================================\n";
    cout << "\t[1] 100"; cout << "\t\t[2] 250\n";
    cout << "\t[3] 300"; cout << "\t\t[4] 450\n";
    cout << "\t[5] 500"; cout << "\t\t[6] 750\n";
    cout << "\t[7] 800"; cout << "\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "\n============================================\n";
    cout << "Your Total Balance is: " << CurrentClient.AccountBalance << endl;
    PerformQuickWithdrawOption(ReadQuickWithdrawOption());
}

double ReadAmountWithDraw()
{
    double Amount = 0;
    cout << "Enter an amount WithDraw: ";
    cin >> Amount; 
    while (Amount <= 0)
    {
        cout << "Enter an amount WithDraw: ";
        cin >> Amount;
    }
    return Amount;
}

void PerformNormalWithdrawOption()
{

    double WithDrawBalance = ReadAmountWithDraw();

    if (WithDrawBalance > CurrentClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, can Withdraw to Up " << CurrentClient.AccountBalance;
        cout << "\nPress any Key  to continue...";
        system("pause>0");
        ShowNormalWithdrawScreen();
        return;
    }

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients);
}

void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << "\n--------------------------------------------\n";
	cout << "\t\tNormal Withdraw Screen";
	cout << "\n--------------------------------------------\n";
    PerformNormalWithdrawOption();
}

void ShowCheckBalanceScreen()
{
	system("cls");
	cout << "\n--------------------------------------------\n";
	cout << "\t\tCheck Balance Screen";
	cout << "\n--------------------------------------------\n";
	cout << "Current Total Balance : " << CurrentClient.AccountBalance << endl;
}

void PerformanceMainMenu(enMainMenu MainMenu)
{
	switch (MainMenu)
	{
	    case enMainMenu::eQuickWithdraw:
	    {
		    system("cls");
		    ShowQuickWithdrawScreen();
		    GoBackToMainMenu();
		    break;
	    }
	    case enMainMenu::eNormalWithdraw:
	    {
		    system("cls");
		    ShowNormalWithdrawScreen();
		    GoBackToMainMenu();
		    break;
	    }
	    case enMainMenu::eDeposit:
	    {
		    system("cls");
		    showDepositScreen();
		    GoBackToMainMenu();
		    break;
	    }
	    case enMainMenu::eCheckBalance:
	    {
		    system("cls");
		    ShowCheckBalanceScreen();
		    GoBackToMainMenu();
		    break;
	    }
	    case enMainMenu::ShowDataClient:
        {
            system("cls");
            ShowAllClientsScreen();
            GoBackToMainMenu();
            break;
        }
	    case enMainMenu::eLogout:
	    {
		    system("cls");
		    Login();
		    break;
	    }
	}
}

void ShowTimeAndData()
{
    time_t T = time(0);
    tm* now = localtime(&T);

    cout << "\n\t\t\t\t\tCurrent CLient : " <<CurrentClient.Name;
    cout << "\n\t\t\t\t\tCurrent  Date  : " << now->tm_mday<< "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900;
    cout << "\n\t\t\t\t\tCurrent  Time  : " << now->tm_hour  << ":" << now->tm_min << ":" << now->tm_sec << endl;

}

void ShowMainMenu()
{
	system("cls");
    cout << "\n" << setw(35) << "" << "______________________________________________\n";
    cout << "\n" << setw(35) << "" << "\t\t     ATM Project\n";
    cout << setw(35) << "" << "______________________________________________\n";
    ShowTimeAndData();
    cout << setw(35) << "" << "==============================================\n";
    cout << setw(35) << "" << "\t\tATM Main Menu Screen\n";
    cout << setw(35) << "" << "==============================================\n";
    cout << setw(35) << "" << "[1] Quick Withdraw.\n";
    cout << setw(35) << "" << "[2] Normal Withdraw.\n";
    cout << setw(35) << "" << "[3] Deposit.\n";
    cout << setw(35) << "" << "[4] Check Balance.\n";
    cout << setw(35) << "" << "[5] Show All Date Client.\n";
    cout << setw(35) << "" << "[6] Logout.\n";
    cout << setw(35) << "" << "==============================================\n";
    cout << setw(35) << "";
	PerformanceMainMenu((enMainMenu)ReadChoiceMainMenu());
}

int main()
{
	Login();
	system("pause>0");
}