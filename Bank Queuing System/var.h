#pragma once
#include<string>

//Time 
struct Time
{
	int hour=0;
	int min=0;
	int sec=0;
};
int	CurrentTime;
int Timer;

//Customers
const int CustomersTotal = 300; 
int CustomersYear = 0; //average number of customers/year
int AvgWeek = 0;
int CustomersWeek = 0; 
int CustomersDay = 0;
int Id = 0;
int ServedDay=0;

struct Customer
{
	int ID=NULL;
	Time Arrival;
	Time Waiting;
	Time EndOfWait;
	int TransactionNum;
	//char TransactionName[25];
	std::string TransactionName;  
	Time Leaving;
	//char served[7]="No";
	std::string served;
	bool Served=false;
	bool waiting=false;
	bool Done=false;
}Customers[CustomersTotal];

//enum Status {Arrival,Leaving} CStatus;


//Tellers
const int TellersTotal = 100;
int TellersNum = 0;
int AvailableTellers = 0;
int WorkHours;

struct Teller {
	int ID;
	bool Available = true;
	Time Idle;
	Time Working;
	Time Busy;
}Tellers[TellersTotal];



//Bank 
int BankHours;
int BankStart;

//Transactions
int TransactionsNum;

struct Transactions{
	//char Name[25];
	std::string Name;
	Time Transaction;
}Transactions[10];

