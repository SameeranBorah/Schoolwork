#ifndef MORTGAGE_H
#define MORTGAGE_H
//Class definition
class Mortgage {

	private:   //Variables
		double Principal; 
		double Rate; 
		double Payment; 
	public:    //Methods
		Mortgage(); 
		Mortgage(double principal, double rate, double payment); 
		void credit(double value); 
		void amortize(); 
		double getPrincipal(); 
};
#endif
