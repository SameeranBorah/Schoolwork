/*
	John Lake PalindromeTest.cpp
	File which gets user inputs for vectors, and determines whether they are palindromes or not. 
*/

#include <iostream> 
#include <vector> 
using namespace std; 

int main(){
	//Variables used: 
	int going = 1;
	int palindrome = 1; 
	vector<int> myVec; 
	vector<int>::const_iterator forward; 
	vector<int>::const_reverse_iterator reverse; 
	 
	//Get user input
	while(going){
		cout<< "Enter a value to enter into the vector.  Enter -1 to stop."<<endl; 
		int temp;  		//Temporary variable 
		cin >> temp;  		//Send the standard input to the temp variable
		if(temp==-1){  		//If the user enters -1, end the loop.  
			going=0;
		}
		else{  
			myVec.push_back(temp); //Add temp to the vector. 
		}
	}


	
	reverse = myVec.rbegin();   					//The reverse iterator starts at the end of myVec 
	for(forward= myVec.begin();forward!=myVec.end();++forward){ 	 //Loop through the forward iterator
		if(*forward != *reverse) palindrome = 0;  		//if the forward and reverse iterators do not match, it is not a palindrome. 
		++reverse; 						//Increment the reverse iterator (as the forward iterator will increment as well. 
	}
	
	//Send the user a confirmation message. 
	if(palindrome){
		 cout <<"This vector is a palindrome!" << endl; 
	}
	else{
		cout <<"This vector is NOT a palindrome!"<<endl; 
	}
}
