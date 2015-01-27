#include <iostream>
#include <string>
#include <stack>
#include <math.h>

#include <cstdlib>
#include <unistd.h>

#include "stack.h"

using namespace std;

#if defined USE_STD_STACK
typedef std::stack<double> number_stack;
#elif defined USE_MY_STACK
typedef fightingirish::stack number_stack;
#elif defined USE_MY_STACK_TEMPLATE
typedef fightingirish::stack<double> number_stack;   //Use my templating
#endif

const bool interactive = isatty(0);
int linenum = 0;

void error (const char *s) {
  if (interactive) {
    cout << "error: " << s << endl;
  } else {
    cerr << "error: " << s << " on line " << linenum << endl;
  }
}

template <typename Stack, typename T>
int pop2 (Stack &stk, T &x, T &y) {
  if (stk.empty()) {
    error("stack underflow");
    return 1;
  }
  y = stk.top(); stk.pop();

  if (stk.empty()) {
    error("stack underflow");
    return 1;
  }
  x = stk.top(); stk.pop();

  return 0;
}

int main (int argc, char *argv[]) {
  string s;
  number_stack stk;
  char *end;
  double x, y;

  while (!cin.eof()) {   //While the user inputs information, keep performing the operations.  
    if (!stk.empty())
      cout << stk.top() << endl;

    if (interactive) cout << "> ";
    getline(cin, s);
    linenum++;

    x = strtod(s.c_str(), &end);
    if (*end == '\0') {
      stk.push(x);
    } else if (s == "+") {                  //Make all of the arithmetic operations work here:
      if (pop2(stk, x, y) == 0) {
	stk.push(x + y);
      }
    } else if (s == "-") {
      if (pop2(stk, x, y) == 0) {
	stk.push(x - y);
      }
    } else if (s == "*") {
      if (pop2(stk, x, y) == 0) {
	stk.push(x * y);
      }
    } else if (s == "/") {
      if (stk.top() == 0.0) {
	error("division by zero");
      } else if (pop2(stk, x, y) == 0) {
	stk.push(x / y);
      }
    } else if (s == "sqrt"){ 						//square root - no complex numbers here. 
      if (!(stk.top() < 0)) {  //If the number on the stack is NOT negative, get the number and take the square root of it. 
	double sq = stk.top();  stk.pop(); 
	stk.push(sqrt(sq)); 
      } else {
	error("You can't take the square root of a negative.");  //Error thrown when the number is negative. 
      }
    } else if (s == "drop") {
      if (!stk.empty()) {
	stk.pop();
      } else {
	error("stack underflow");
      }
    } else {
      error("couldn't understand input");
    }
  }
}
