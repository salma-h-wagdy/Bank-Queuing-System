#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include "var.h"
#include"func.h"
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<cstring>


using namespace std;



void SaveData() {
	ifstream CustomerR;
	ofstream CustomerW;
	CustomerR.open("C:/Users/Salma/source/repos/Bank Queuing System/Customer.txt");
	CustomerW.open("C:/Users/Salma/source/repos/Bank Queuing System/Customer.txt", ios::out); //saves data to txt file
	CustomerW << "Id   " << "Arrival   " << "Waiting   " << "Leaving   " << "Transaction Type   " << "Served?   " << endl;
	for (int j = 0;j <= Id;j++) {  //priority list
		for (int x = 0;x < CustomersDay;x++) {
			if (Customers[x].ID == j) {
				CustomerW << Customers[x].ID << "      ";
				CustomerW << Customers[x].Arrival.hour << "." << Customers[x].Arrival.min << "      ";
				CustomerW << Customers[x].Waiting.hour << "." << Customers[x].Waiting.min << "      ";
				CustomerW << Customers[x].Leaving.hour << "." << Customers[x].Leaving.min << "        ";
				//for (int i = 0;i < sizeof(Customers[x].TransactionName);i++){
				//	//CustomerW.write((char*)Customers[x].TransactionName,20);
				//	CustomerW << Customers[x].TransactionName[i];
			 //   }
				CustomerW << Customers[x].TransactionName << "       ";
				CustomerW<< Customers[x].served << endl;
			}
		}
	}
	CustomerW << "Customers per day:" << CustomersDay << endl;
	CustomerW << "Served Customers per day:" << ServedDay;
	CustomerW.close();
	CustomerR.close();

	ofstream TellerW("C:/Users/Salma/source/repos/Bank Queuing System/Teller.txt", ios::app); //saves data to txt file
	TellerW << "Id:       " << "   Working hours" << "  Idle hours" << endl;
	for (int x = 0;x < TellersNum;x++) {
		TellerW << Tellers[x].ID << "     ";
		TellerW << Tellers[x].Working.hour << "." << Tellers[x].Working.min << "           ";
		TellerW << Tellers[x].Idle.hour << "." << Tellers[x].Idle.min << endl;
	}
	TellerW.close();

}


int main() {
	srand(time(0)); //random number generator using current time

	//Requesting info from user.

	cout << "                               __________________________________\n                               WELCOME TO THE BANK QUEUING SYSTEM. \n                               ----------------------------------\n\nPlease input the required information :\n -----------------------------------" << endl;
	cout << "Required number of bank tellers (<=100) : ";
	cin >> TellersNum;
	while (TellersNum>100) { //if number >100
		cout << "Invalid input , number >100\n Please input Required number of bank tellers (<=100) :  ";
		cin >> TellersNum;
	}
	cout << endl << "Required working hours for each teller : ";
	cin >> WorkHours ;
	cout << endl << "Required Bank working hours : ";
	cin >> BankHours;
	cout << endl << "Required Bank Opening hour : ";
	cin >> BankStart;
	cout << endl << "Average number of served customers per year (>=30,000): ";
		cin >> CustomersYear;
		while (CustomersYear < 30000) { //if number <30,000
			cout << "Invalid input , number < 30,000\n Please input Average number of served customers per year (>=30,000): ";
			cin >> CustomersYear;
		}
		AvgWeek = CustomersYear / 52;
	cout << endl << "Average number of Customers per week ( >= Customers per year/52) :  ";
	cin >> CustomersWeek;
	while (CustomersWeek < AvgWeek) {
		cout << "Invalid input, number of Customers per week< Customers per year/52\n Please input Average number of Customers per week : ";
			cin >> CustomersWeek;
	}
	cout << endl << "Please input required number of transactions:(<=10)";
	cin >> TransactionsNum;
	cin.clear();
	cout << endl << "Please input Name ,Required durations for each transaction (hours/mins) : \n" << endl;
	for (int t = 0;t < TransactionsNum;t++) {
		cout <<endl<< "Transaction [" << t+1 << "] Name  (word1_word2):  ";
		cin>>Transactions[t].Name;
		cin.ignore(100,'\n');                                                              ////////to avoid newline inputted by another variable
		cout <<endl<< "Transaction [" << t + 1 << "] required duration :" << endl;
		cout << endl<<"hours: ";
		cin >> Transactions[t].Transaction.hour;
		cout <<endl<< "minutes: ";
		cin >> Transactions[t].Transaction.min;
	}
	cout << "Please wait a moment...";


	CustomersDay = CustomersWeek / 6;

	//CustomersDay = (rand() % AvgCustomersDay) + 1; // ---> random number of customers <= average/day 

	CustomerArrival();
	BankSim();
	TellerInfo();
	Served();
	SaveData();
	cout <<endl<< "_____________________________________ \n Number of served customers/day =" << ServedDay << endl;
	cout << "__________________________________________________________________________ \n Data saved." << endl;
	cout << " Generated info can be viewed in attached text file. Thank You For Your Time!\n __________________________________________________________________________";

	return 0;
}

//Customer Arrival Time
void CustomerArrival() {
	for (int i = 0;i < CustomersDay;i++) {
		Customers[i].Arrival.hour = (rand() % BankHours);
		Customers[i].Arrival.min = (rand() % 60);
		//Customers[i].Arrival.sec = (rand() % 60);
	}
}
//simulates time passage during bank hours

void BankSim() {
	for (int H = 0;H < BankHours;H++) {    //current hour
		for (int M = 0;M < 60;M++) {       //current minute
			//for (int S = 0;S < 60;S++) {   //current second

				//sets teller as available when transaction is done
				for (int x = 0;x < TellersNum;x++) {
					if (H == Tellers[x].Busy.hour && M == Tellers[x].Busy.min ) {
						Tellers[x].Available = true;
						//AvailableTellers++;
					}
					if (Tellers[x].Working.hour >= WorkHours) { //////////////
						Tellers[x].Available = false;
						//AvailableTellers--;
					}

				}



				for (int i = 0;i < CustomersDay;i++) {
					if (Customers[i].Arrival.hour == H && Customers[i].Arrival.min == M /*&& Customers[i].Arrival.sec == S*/) { //arrival time
						Id++;
						Customers[i].ID = Id; //sets id , measures priority
						Customers[i].waiting = true;
						//break;
					}
				}
					//if teller is available
					for (int x = 0;x < TellersNum;x++) {
						if(Tellers[x].Available == true) {
							for (int j = 0;j <= Id;j++) {  //priority list
								for (int i = 0;i < CustomersDay;i++) {
									if (Customers[i].ID == j && Customers[i].waiting == true) {
										while (Customers[i].Done == false) {
										Customers[i].waiting = false;
										Tellers[x].Available = false;   //sets teller as unavailable

										//measuring waiting time
										Customers[i].Waiting.hour = H - Customers[i].Arrival.hour;
										Customers[i].Waiting.min = M - Customers[i].Arrival.min;

										if (Customers[i].Waiting.min < 0) {
											Customers[i].Waiting.min += 60;
										}
										if (Customers[i].Waiting.sec < 0) {
											Customers[i].Waiting.sec += 60;
										}

											//AvailableTellers--;

											Customers[i].EndOfWait.hour = Customers[i].Arrival.hour + Customers[i].Waiting.hour; //end of waiting time
											Customers[i].EndOfWait.min = Customers[i].Arrival.min + Customers[i].Waiting.min;

											if (Customers[i].EndOfWait.min >= 60) {
												int h= (Customers[i].EndOfWait.min / 60);
												Customers[i].EndOfWait.hour += h;
												Customers[i].EndOfWait.min = (Customers[i].EndOfWait.min % 60);
											}

											Customers[i].TransactionNum = rand() % (TransactionsNum+1); //random transaction

											if (Customers[i].TransactionNum >= TransactionsNum) { //if transaction is unavailable
												Customers[i].Served = false;
												Customers[i].served = "No";
												Customers[i].TransactionName = "Unknown      ";
												Customers[i].Leaving.hour = Customers[i].EndOfWait.hour; //Opening/closing account
												Customers[i].Leaving.min = Customers[i].EndOfWait.min;
												Tellers[x].Available = true;
											}

											else if (Customers[i].TransactionNum < TransactionsNum) { //if transaction is available
												for (int t = 0;t < TransactionsNum;t++) {
													if (Customers[i].TransactionNum == t) {
														Customers[i].Leaving.hour = Customers[i].EndOfWait.hour + Transactions[t].Transaction.hour ; //Opening/closing account
														Customers[i].Leaving.min = Customers[i].EndOfWait.min + Transactions[t].Transaction.min;
														Customers[i].TransactionName = Transactions[t].Name;
														Customers[i].Served = true;
														Customers[i].served = "   Yes";
														
													}
												}
											}
											
											

											//Measures time properly
											if (Customers[i].Leaving.min >= 60) {
												int h= (Customers[i].Leaving.min / 60);
												Customers[i].Leaving.hour += h;
												Customers[i].Leaving.min = (Customers[i].Leaving.min % 60);
											}

											//Tellers working hour

											Tellers[x].Working.hour += (Customers[i].Leaving.hour - Customers[i].EndOfWait.hour); //measures teller working hours
											Tellers[x].Working.min += (Customers[i].Leaving.min - Customers[i].EndOfWait.min);

											Tellers[x].Busy.hour = Customers[i].Leaving.hour ; //measures exact time teller will be available
											Tellers[x].Busy.min = Customers[i].Leaving.min ;

										
											if (Tellers[x].Working.min < 0) {
												Tellers[x].Working.min += 60;
											}
											if (Tellers[x].Working.min >= 60) {
												int h= (Tellers[x].Working.min / 60);
												Tellers[x].Working.hour += h;
												Tellers[x].Working.min = (Tellers[x].Working.min % 60);
											}

											Customers[i].Done = true;



										}
										
									}
									if (Tellers[x].Available == false)
										break;
								}
								if (Tellers[x].Available == false)
									break;
							}
						}
					}

				
			
		}
	}
}

//Tellers Id ,idle time

void TellerInfo() {
	for (int j = 0;j < TellersNum;j++) {
		Tellers[j].ID = j+1;
		Tellers[j].Idle.hour = WorkHours - Tellers[j].Working.hour;
		if (Tellers[j].Working.min > 0 && Tellers[j].Working.hour == 0){
			Tellers[j].Idle.hour = WorkHours - 1;
		Tellers[j].Idle.min = 60 - Tellers[j].Working.min;
	}
		if(Tellers[j].Working.min>0&& Tellers[j].Working.hour>0)
		Tellers[j].Idle.min = 60 - Tellers[j].Working.min;
		if(Tellers[j].Working.hour>6)
			Tellers[j].Idle.min = Tellers[j].Working.min;
		if (Tellers[j].Working.hour == 6)
			Tellers[j].Idle.min =0- Tellers[j].Working.min;


	
	}
}

//Number of served customers 

void Served() {
	for (int i = 0;i < CustomersDay;i++) {
		Customers[i].Arrival.hour += BankStart;
		Customers[i].Leaving.hour += BankStart;

		if (Customers[i].Served == true) {
			ServedDay++;
			
		}
		if (Customers[i].Done == false) {
			Customers[i].Waiting.hour = BankHours - Customers[i].Arrival.hour+ BankStart;
			Customers[i].Waiting.min = 60- Customers[i].Arrival.min;
			Customers[i].Leaving.hour = BankHours + BankStart;
			Customers[i].Served = false;
			Customers[i].served = "No";
			Customers[i].TransactionName = "Unknown      ";
		}
	}
	
}









//void load_data() {
//
//	ifstream criminal_load("C:/Users/Salma/OneDrive/Desktop/login/Criminal.txt");  //opens criminal file
//	if (criminal_load.is_open()) {
//		while (criminal_load.peek() != EOF) {
//			getline(criminal_load, criminal_ID);
//			getline(criminal_load, name);
//			getline(criminal_load, age);
//			criminals[num_criminals].criminal_ID = criminal_ID;
//			criminals[num_criminals].name = name;
//			criminals[num_criminals].age = stoi(age);
//
//			num_criminals++;
//
//		}
//		criminal_load.close();
//	}
//	ifstream crime_load("C:/Users/Salma/OneDrive/Desktop/login/Crime.txt");   //opens crime file
//	if (crime_load.is_open()) {
//		while (crime_load.peek() != EOF) {
//			getline(crime_load, crime_ID);
//			getline(crime_load, type);
//			getline(crime_load, status);
//			getline(crime_load, date);
//
//			crimes[num_crimes].crime_ID = crime_ID;
//			crimes[num_crimes].type = type;
//			crimes[num_crimes].status = status;
//			crimes[num_crimes].date = date;
//			num_crimes++;
//
//		}
//		crime_load.close();
//	}
//
//}




//tellers idle time
//for (int j = 0;j <= TellersNum;j++) {
//	Tellers[j].ID = j;
//	Tellers[j].Idle.hour = WorkHours.hour - Tellers[j].Working.hour;
//	Tellers[j].Idle.min = WorkHours.min - Tellers[j].Working.min;

		//if tellers are unavailable
		/*CurrentTime = time(0);
		while (TellersNum == 0) {
			Timer = time(0) - CurrentTime;
		}
		Customers[i].Waiting.hour = Timer / 60 / 60;
		Customers[i].Waiting.min = Timer % 60;*/
		//Customers[i].Waiting.sec = Timer;

		//if tellers are available

//		if (TellersNum > 0) {
//			for (int i = 0;i <= TellersNum;i++) {
//				if (Tellers[i].Available = true) {
//					Tellers[i].Available = false;   //sets teller as unavailable
//					TellersNum--;
//					break;
//				}
//
//			}
//			Customers[i].TransactionNum = (rand() % 4) + 1;
//
//			Customers[i].Leaving.hour = Customers[i].Arrival.hour + Customers[i].Waiting.hour; //adding waiting time
//			Customers[i].Leaving.min = Customers[i].Arrival.min+ Customers[i].Waiting.min;
//
//			switch (Customers[i].TransactionNum) {
//			case 1: {
//				Customers[i].Leaving.hour += Transactions.Account.hour; //Opening/closing account
//				Customers[i].Leaving.min += Transactions.Account.min;
//				Customers[i].Served = true;
//				break;
//			}
//			case 2: {
//				Customers[i].Leaving.hour += Transactions.Deposit.hour;//Depositing
//				Customers[i].Leaving.min += Transactions.Deposit.min;
//				Customers[i].Served = true;
//				break;
//			}
//			case 3: {
//				Customers[i].Leaving.hour += Transactions.Withdraw.hour;//Withdrawal
//				Customers[i].Leaving.min += Transactions.Withdraw.min;
//				Customers[i].Served = true;
//				break;
//			}
//			case 4: {
//				Customers[i].Leaving.min += Transactions.ShowBalance.min;//Showing Balance
//				Customers[i].Leaving.sec += Transactions.ShowBalance.sec;
//				Customers[i].Served = true;
//				break;
//			}
//			default:{
//					Customers[i].Served = false;
//					break;
//			}
//			}
//			
//
//			//Tellers working hours
//			for (int j = 0;j <= TellersNum;j++) {
//				if (Tellers[j].Available = false) {
//					Tellers[j].Available = true;   //sets teller as available
//					TellersNum++;
//					Tellers[j].Working.hour += Customers[i].Leaving.hour - Customers[i].Arrival.hour; //measures teller working hours
//					Tellers[j].Working.min += Customers[i].Leaving.min - Customers[i].Arrival.min;
//				}
//				break;
//				
//			}
//			
//			
//		}
//	
//
//	//tellers idle time
//	for (int j = 0;j <= TellersNum;j++) {
//		Tellers[j].ID = j;
//			Tellers[j].Idle.hour = WorkHours.hour - Tellers[j].Working.hour;
//			Tellers[j].Idle.min = WorkHours.min - Tellers[j].Working.min;
//		
//
//	}
//
//}

