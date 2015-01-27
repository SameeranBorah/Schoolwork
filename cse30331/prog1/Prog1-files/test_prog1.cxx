#include <string>
#include <stack>
#include <iostream>
#include <cstdlib>

#include "stack.h"

using namespace std;

#if defined USE_STD_STACK
  typedef std::stack<double> double_stack;
  typedef std::stack<string> string_stack;
  typedef std::stack<int> int_stack;
#elif defined USE_MY_STACK
  typedef fightingirish::stack double_stack;
#elif defined USE_MY_STACK_TEMPLATE
  typedef fightingirish::stack<double> double_stack;
  typedef fightingirish::stack<string> string_stack;
  typedef fightingirish::stack<int> int_stack;
#endif

template <typename T>
void test_equal(const T& x, const T& y) {
  cout << x << " == " << y << ":\t";
  cout << (x == y ? "PASSED" : "FAILED") << endl;
}

int main (int argc, char *argv[]) {
  cout << "==== testing stack<double> ====" << endl;
  double_stack ds;
  test_equal(ds.empty(), true);
  ds.push(42.0);
  test_equal(ds.empty(), false);
  test_equal(ds.top(), 42.0);
  ds.push(123.0);
  test_equal(ds.top(), 123.0);
  ds.pop();
  test_equal(ds.empty(), false);
  test_equal(ds.top(), 42.0);
  ds.pop();
  test_equal(ds.empty(), true);

#if defined USE_STD_STACK || USE_MY_STACK_TEMPLATE
  cout << "==== testing stack<string> ====" << endl;
  string_stack cs;
  test_equal(cs.empty(), true);
  cs.push("foo");
  test_equal(cs.empty(), false);
  test_equal(cs.top(), string("foo"));
  cs.push("bar");
  test_equal(cs.top(), string("bar"));
  cs.pop();
  test_equal(cs.empty(), false);
  test_equal(cs.top(), string("foo"));
  cs.pop();
  test_equal(cs.empty(), true);

  cout << "==== large-scale random test ====" << endl;
  std::stack<int> iss;
  int_stack is;
  while (iss.size() < 1000000) {
    int action = rand() % 3;
    if (action > 0) {
      int r = rand();
      iss.push(r);
      is.push(r);
    } else if (iss.size() > 0) {
      iss.pop();
      is.pop();
    }
    if (rand() % 1000000 == 0 && iss.size() > 0)
      test_equal(is.top(), iss.top());
  }
  while (iss.size() > 0) {
    iss.pop();
    is.pop();
  }
  test_equal(is.empty(), true);
#else
  cout << "stack should be a template class:\tFAILED" << endl;
#endif  
}
