/*
	John Lake	mortgage.cpp
	This is the implementation for the mortgage class. 
*/

#include "mortgage.h" 
#include <iostream> 
#include <iomanip>
using namespace std; 

//Default constructor
Mortgage::Mortgage(){
	Principal = 100000; 
	Rate = 0.05; 
	Payment = 600; 
}

//Non-default constructor
Mortgage::Mortgage(double principal, double rate, double payment){
	//Check for invalid inputs
	if(rate<0 || principal<0 || payment<=0 ){
		cout<<"Invalid rate, principal, or payment amount!!!"<<endl<<endl;
	}
	Principal = principal; 
	Rate = rate/100.0;  //Converts the rate from a percentage to a decimal rate. 
	Payment = payment; 
}

//Used to reduce from the principal
void Mortgage::credit(double value){
	Principal-=value; 
}

//Returns the current amount of debt
double Mortgage::getPrincipal(){
	return Principal; 
}

void Mortgage::amortize(){
	//Check for invalid inputs
	if(Rate<0){
		cout <<"This mortgage has an invalid interest Rate."<<endl<<endl; 
		return; 
	}
	else if(getPrincipal()<0){
		cout <<"This mortgage has a negative principal."<<endl<<endl; 
	}
	
	int month = 0;    //Used to give the end message for the total amount paid.  
	int years = 0; 
	double totalPaid = 0; 
	double temp = getPrincipal()+1; 
	
	//Display the top to each column: 
	cout<< setw(10)<< "Month:"<< setw(10)<<"Payment:"<<setw(10)<<"Interest:"<<setw(10)<<"Debt:"<<endl<<endl; 
	
	//While there is still a debt, calculate the payment for the next month and pay it.
	while(getPrincipal()>0 && temp > getPrincipal()){
		month++; 
		double intAccrued = getPrincipal()*(Rate/12); //interest added to principal that month; 
	        temp = getPrincipal();    //Used to check if the monthly payment is enough to reduce the debt. 
		Principal+=intAccrued;   //Add the interest to the principal, and subtract the monthly payment. 
		Principal-=Payment; 
		
		 //If the payment does not reduce the debt, the interest is too high or the payment is too low. 
		if(getPrincipal()>temp){
			cout << "You need to make a larger monthly payment!!!" <<endl; 
			return; 
		}
		//If the debt is less than zero (the payment was more than the debt), account for it here:  
		if(getPrincipal() <0){
			Payment += getPrincipal(); //getPrincipal returns a negative here, so the payment is going to be smaller for the last month. 
			Principal = 0;  
		}
		cout<< setprecision(2)<< fixed << setw(10) << month <<setw(10) <<Payment << setw(10) <<intAccrued<< setw(10) <<getPrincipal()<< endl;  
		totalPaid+=Payment; 
	}
	 //Calculate how much the user paid, and in how many months/years
	years = month /  12; 
	month = month %  12;
	cout << "Over the course of "<< years << " years and "<<month<<" months, you have paid $ "<<setprecision(2)<<fixed<<totalPaid<< endl<<endl;
}
