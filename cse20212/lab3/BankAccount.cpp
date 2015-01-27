/*
	John F. Lake, Jr.  BankAccount.cpp
	Implementation for the BankAccount class
*/
#include "BankAccount.h"
#include <iostream> 
#include <string>
using namespace std; 

//Default constructor
BankAccount::BankAccount(){
		balance = 0; //Double because of cent values
		PIN = 1234;  
		accountNumber = 12345678; 
		bankName = "Peanut Butter and Jelly, LLC"; 
}
//Non-default constructor
BankAccount::BankAccount(double b,int p,int a,string bn){
		balance = b; 
		PIN = p;
		accountNumber = a;
		bankName = bn; 
}

//Print a message to the user
void BankAccount::print(){
	cout << "This is the base class for the bank account!"<<endl; 
	cout << "I have basic bank account information!"<<endl; 
}

