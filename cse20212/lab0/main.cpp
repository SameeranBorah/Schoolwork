/*
	John Lake 	main.cpp
	Driver file for the mortgage class.  (Same as the prompt)
*/ 
#include "mortgage.h"
#include <iostream> 
using namespace std; 

int main(){
	
	Mortgage first(10000,5.0,500);   //Normal mortgage
	Mortgage second; 		 //Default constructor
	Mortgage bad(10000,-5,12);       //Invalid mortgage (will give error message as soon as the program hits this line.) 
	
	second.credit(10000);   //Credits the second mortgage (reduces the total from $100,000 to $90,000
	cout <<"Current balance after crediting second mortgage: "<<second.getPrincipal()<<endl;   //Print this to the user
	
	cout<<"Amortization schedule for the first mortgage:"<<endl; 
	first.amortize();  //Display the amortization table for the first mortgage.  
  

	
}
