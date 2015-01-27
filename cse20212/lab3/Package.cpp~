/*
	John F. Lake, Jr. Package.cpp
	Implementation for the package class that uses inheritance
*/
#include "Package.h" 
#include <string> 
#include <iostream>
using namespace std; 

//Non-Default; checks for errors: 
Package::Package(string toN, 
		 string fromN,
	       	 string toA,
		 string fromA,
		 string toC,
		 string fromC,
		 string toS, 
		 string fromS,
		 int toZ, 
		 int fromZ,
		 double w, 
		 double c){
		 
	//Initialize info about sender/recipient: 
	toName = toN; 
	fromName = fromN; 
	toAddress = toA; 
	fromAddress = fromA; 
	toCity = toC; 
	fromCity = fromC; 
	toState = toS; 
	fromState = fromS; 
	toZip = toZ; 
	fromZip = fromZ;  
			
	//Checks if the weight is greater than zero and if the cost is greater than or equal to zero (it could ship for free if cost = 0); 
	if(w>0) weight = w; 
	else{
		weight = 2.5; 
		cout << "You cannot have a negative weight!"<<endl; 
	}
	if(c>=0) costPerOunce = c; 
	else{
		c = 3.00; 
		cout << "You cannot have a negative cost!"<<endl; 
	}
	shipCost = weight*costPerOunce; 
} 

//Returns the cost of the package
double Package::CalculateCost(){
	double cost= (getWeight()*getCostPerOunce());
	return cost; 
}

//Returns the weight
double Package::getWeight(){
	return weight; 
} 
//Returns the cost per ounce of the package
double Package::getCostPerOunce(){
	return costPerOunce; 
} 
//Sets the private shipCost variable to d
void  Package::setShipCost(double d){
	shipCost = d; 
} 



//Accessor Methods
string Package::getToName(){return toName;} 
string Package::getFromName(){return fromName; } 
string Package::getToAddress(){return toAddress;} 
string Package::getFromAddress(){return fromAddress;} 
string Package::getToCity(){return toCity; } 
string Package::getFromCity(){return fromCity; } 
string Package::getToState(){return toState; } 
string Package::getFromState(){return fromState; } 
int Package::getToZip(){return toZip;} 
int Package::getFromZip(){return fromZip;} 

//Mutator Methods (for composition mostly)
void Package::setToName(string s){toName = s; } 
void Package::setFromName(string s){fromName = s; } 
void Package::setToAddress(string s){toAddress=s;} 
void Package::setFromAddress(string s){fromAddress=s;} 
void Package::setToCity(string s){} 
void Package::setFromCity(string s){} 
void Package::setToState(string s){} 
void Package::setFromState(string s){} 
void Package::setToZip(int z){toZip = z; } 
void Package::setFromZip(int z){fromZip = z; } 


