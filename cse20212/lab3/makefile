all: main

main: main.o BankAccount.o IRA.o CheckingAccount.o Package.o TwoDayPackage.o OvernightPackage.o CompTwoDayPackage.o CompOvernightPackage.o
	g++ main.o BankAccount.o IRA.o Package.o TwoDayPackage.o CheckingAccount.o OvernightPackage.o CompTwoDayPackage.o CompOvernightPackage.o -o main
	
main.o: main.cpp 
	g++ -c main.cpp
BankAccount.o: BankAccount.cpp
	g++ -c BankAccount.cpp
IRA.o: IRA.cpp
	g++ -c IRA.cpp
CheckingAccount.o: CheckingAccount.cpp
	g++ -c CheckingAccount.cpp
Package.o: Package.cpp
	g++ -c Package.cpp
TwoDayPackage.o: TwoDayPackage.cpp
	g++ -c TwoDayPackage.cpp
OvernightPackage.o: OvernightPackage.cpp
	g++ -c OvernightPackage.cpp
CompTwoDayPackage.o: CompTwoDayPackage.cpp
	g++ -c CompTwoDayPackage.cpp
CompOvernightPackage.o: CompOvernightPackage.cpp
	g++ -c CompOvernightPackage.cpp
	
clean: 
	rm -f *.o main; 
