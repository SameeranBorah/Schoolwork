//This program will take 3 inputs from a user for the principal, interest rate, and monthly payment of a mortgage, and will produce an amortization table. 

#include <stdio.h> 
#include <stdbool.h>

int main(void){

	//Declare variables
	float intRate = 0;
	float totalPaid=0;  
	float principal = 0; 
	float monthPay = 0;  	
	float debt = 0; 
	int month=0; 
	int years = 0; 
	float temp= 0; 
	float intAccrued =0; 
	bool  correctValues = false; 

	//Prompt user and get values≈
	while(!correctValues)	{
		printf("MORTGAGE CALCULATOR\n\n"); 
		printf("What is your principal? ($) \n"); 
		scanf("%f",&principal); 
		printf("What interest rate do you have?\n(Enter as a decimal, such as 0.01 for 1%)\n"); 
		scanf("%f", &intRate); 
		printf("How much do you want to pay every month? ($) \n"); 
		scanf("%f",&monthPay); 
		if(principal>0 && intRate>0 && monthPay>0){
			correctValues = true;
		}else{
			printf("All of your values need to be positive.  Re-enter them.\n\n");  
		}	
	}
	printf("%10s%10s%10s%10s\n","Month","Payment","Interest","Balance"); 
	
	debt = principal; 
	
	
	while(debt>0){
		month++; 
		intAccrued = debt*(intRate/12);
		temp = debt;  
		debt += intAccrued; 
		debt -=  monthPay;
		
		 
		if(debt>temp){
			printf("You need to make a larger monthly payment!!!\n\n"); 
			return 0; 
		}
		if(debt <0){
			monthPay += debt;
			debt = 0;  
		}
		
		totalPaid+=monthPay; 
		
		 
		printf("%10u%10.0f%10.2f%10.2f\n",month,monthPay,intAccrued,debt); 
	 
	}

	years = month /  12; 
	month = month %  12;
	printf("Over the course of %d years and %d months, you have paid $%.2f on your mortgage.\n\n",years,month,totalPaid); 
	
	
}
