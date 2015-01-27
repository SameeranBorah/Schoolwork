/*
	John F. Lake, Jr.  Rational.cpp
	Implemnataion for the Rational.h file. 
*/

#include "Rational.h" 
#include <iostream> 
using namespace std; 

//Constructors: 
Rational::Rational(){  //Default sets the rational function to be 1/1
	numerator = 1; 
	denominator = 1; 
}
Rational::Rational(int n, int d){
	if(d==0){  //If the denominator is zero, give an error and set the denominator to be 1. 
		cout <<"ERROR: CANNOT DIVIDE BY ZERO!";
		numerator = n; 
		denominator = 1; 
	}
	else if(d<0 && n>00){ //If the denominator is less than zero and the numerator is greater than zero
		numerator = -n/GCD(n,d);  //Make the numerator negative and the denominator positive (e.g: 1/-1 becomes -1/1 (it's neater))
		denominator = -d/GCD(n,d); 
		int gcd = GCD(numerator,denominator); 
		numerator = numerator/gcd; 
		denominator = denominator/gcd; 
	}
	else{  //Other than that, just set the numerator and denominator appropriately given the gcd of the two. 
		int gcd = GCD(n,d); 
		numerator = n/gcd;  
		denominator = d / gcd; 
	}
}


//Setting numbers: 
void Rational::setNumbers(int n, int d){  //Similar to the constructor; lets the user set the num and dem of the rational number. 
	if(d==0){ 
		cout <<"ERROR: CANNOT DIVIDE BY ZERO!";
		this->numerator = n; 
		this->denominator = 1; 
	}
	else if(d<0 && n>0){
		numerator = -n/GCD(n,d);  //Make the numerator negative and the denominator positive (e.g: 1/-1 becomes -1/1 (it's neater))
		denominator = -d/GCD(n,d); 
		int gcd = GCD(numerator,denominator); 
		numerator = numerator/gcd; 
		denominator = denominator/gcd;
	}
	else{ 
		this->numerator = n/GCD(n,d); 
		this->denominator = d/GCD(n,d); 
	}
}


//Helper function to obtain the Greatest common divisor of x and y: 
int Rational::GCD(int x, int y){
	int t;   //temp variable to be used in the calculation. 
	if(x==y){
		return x;  //If x and y are the same, return x. 
	}
	else if(x>y){ //If x is the larger number
		while(y != 0){  //while y is not zero: 
      			 t = y;  //Assign temp to be the value of y (the smaller number.) 
      			 y = x % y;  //Assign y to be the remainder of x/y
      			 x = t; //x is now the old value of y
      		}		
      		return x; 
	}
	else{	//Same method for other case: 
		while(x != 0){
      			 t = x; 
      			 x = y % x; 
      			 y = t;
      		}		
      		return y; 
	}
}


//Functions used to add, subtract, multiply and divide, respectively: 
Rational Rational::add(Rational r){
	int d = this->denominator * r.denominator; 
	int n = (this->numerator * r.denominator) + (this->denominator * r.numerator);  
	Rational ret(n/GCD(n,d),d/GCD(n,d)); 
	return ret; 
} 
Rational Rational::subtract(Rational r){
	int d = this->denominator * r.denominator; 
	int n = (this->numerator * r.denominator) - (this->denominator * r.numerator);  
	Rational ret(n/GCD(n,d),d/GCD(n,d)); 
	return ret; 
}
Rational Rational::multiply(Rational r){
	int n = this->numerator * r.numerator; 
	int d = this->denominator * r.denominator; 
	Rational ret(n/GCD(n,d),d/GCD(n,d)); 
	return ret; 
}
Rational Rational::divide(Rational r){
	int n = this->numerator * r.denominator; 
	int d = this->denominator * r.numerator; 
	Rational ret(n/GCD(n,d),d/GCD(n,d)); 
	return ret; 
}
Rational Rational::inverse(Rational r){
	int d = this->numerator; 
	int n = this->denominator; 
	Rational ret(n/GCD(n,d),d/GCD(n,d)); 
	return ret; 
}

//Overloaded operators that use the above functions to work:   (Simple enough to write as inline functions)
Rational Rational::operator+(Rational r){return (*this).add(r);     	}  //Add
Rational Rational::operator-(Rational r){return (*this).subtract(r);	}  //Subtract
Rational Rational::operator*(Rational r){return (*this).multiply(r);	}  //Multiply
Rational Rational::operator/(Rational r){return (*this).divide(r); 	}  //Divide 
Rational Rational::operator^(Rational r){return (*this).inverse(r); 	}  //Inverse operator


//Overloaded << operator
ostream  &operator<<(ostream & out, Rational & r){
	if(r.denominator == 1){ //If the denominator is 1, just return the numerator (e.g: 4/1 returns 4)
		out <<r.numerator; 
		return out; 
	}
	else if (r.denominator <0 && r.numerator>0){ //If the denominator is less than zero and the numerator is greater than zero:
		out<<"-"<<r.numerator << "/" << (-1*r.denominator);  //5/-4 becomes -5/4
		return out; 
	}
	out << r.numerator << "/" << r.denominator;  //If nothing special, return numerator/denominator
	return out; //Allows for chaining of cout arguments
} 


//Function that calculates a few random functions, using all of the overloaded operators, including the inverse one (^): 
void calculateFunctions(Rational first, Rational second){
	cout <<"\n\n\n"; 
	cout << "Equation calculator:"<<endl; 
	cout << "x = " << first << endl; 
	cout << "y = " << second << endl<<endl; 
	Rational answer(1,1);  //Reuse this object to store answers and to return them to the user.  

 
	//First equation: 2x + 3
	cout<<"2x + 3=" << endl; 
	answer = (Rational(2,1) * first) + Rational(3,1);
	cout << answer<<endl<<endl; 
	
	
	//Second: 4x + 2y
	cout <<"4x + 2y="<<endl; 
	answer = Rational(4,1)*first + Rational(2,1)*second;
	cout <<answer<<endl<<endl; 
	
	//Third: (x + y)/(2x)
	cout << "(x + y)/(2x)="<<endl; 
	answer = (Rational(1,1)*first + second)/(Rational(2,1)*first);
	cout <<answer<<endl<<endl; 
	
	//This function uses an overloaded ^ operator, which takes a Rational number as an argument. (It would not let me compile first^;)
	//The ^ operator returns the inverse of the Rational number acting on it.  
	//Fourth: (given a slope m, this computes a perpindicular slope)
	cout <<"Slope (m) = "<<first<<endl; 
	cout <<"Perpendicular slope="<<endl; 
	answer = (first ^Rational(1,1)) * Rational(-1,1);  //Get the negative inverse of m. 
	cout << answer << endl<<endl; 
}


//"Interactive mode": 
int main(){
	
	//Prompt user for input for the two rational numbers: 
	int n,d; 
	cout <<endl<<endl << "Enter a numerator for the first rational number."<<endl; 
	cin>>n; 
	cout<<"Enter a denominator for the first rational number."<<endl;
	cin>>d; 
	Rational first(n,d);
	cout <<endl<<endl << "Enter a numerator for the second rational number."<<endl; 
	cin>>n; 
	cout<<"Enter a denominator for the second rational number."<<endl; 
	cin>>d; Rational second(n,d); 
	
	cout<<"First number: "<<first<<endl; 
	cout<<"Second number: "<<second<<endl; 
	calculateFunctions(first,second); 
	
}





