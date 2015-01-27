#ifndef ND_STACK_H
#define ND_STACK_H

#include <stdexcept>
#include <iostream>


// Uncomment *only one* of the following #defines...

// For a working stack class to understand how calc is supposed to work:
//#define USE_STD_STACK 1

// For the non-template skeleton defined in this file:
//#define USE_MY_STACK 1

// For the template class which you will write in this file:
#define USE_MY_STACK_TEMPLATE 1

namespace fightingirish {

template<class T>
struct node{
	T data; 
	node<T> * next; 
};

template <class T>
class llist{
		
  		public: 
  			llist(){
  				head = new node<T>; 
				head->next = NULL; 
			} 
  			~llist(){
				while(!empty()){
					pop_front(); 
				}
  				delete head; 
  			}
  			int empty() const{
  				if(head->next == NULL){
  					return 1; 
  				}
  				return 0; 
  			}
  			void push_front(const T& dat){
  					struct node<T> *n = new node<T>;
  					n->data = head->data; 
  					n->next = head->next;
					head->data = dat; 
  				head->next = n; 
				 
  			 
  			}
  			void pop_front(){
  				if(empty()){
  					throw std::runtime_error("Empty list");
  				}
  				else{
  					struct node<T> *t = head;
  					head = head->next; 
  					delete t; 
  					
  				}
  			}
  			T front() const{
  				return head->data; 
  			}
  		private: 
  			struct node<T> * head; 
  	
  	};
  
 	










  template <class T>
  class stack {
  public:
  
  
    stack() { 
      // Precondition: None.
      // Postcondition: The stack is empty.
      while(!empty()){
      	pop();  		//if there is anything on the stack, get rid of it. 
      }
    }

    bool empty() const {
      // Test whether the stack is empty.
      // Precondition: None.
      // Postcondition: Returns true if and only if the stack is empty.
      if (myStack.empty()){
      	return true;             //If the stack is empty, return true.  Othewise, return false. 
      }
      return false; 
    }

    void push(T x) { 
      // Push an element onto the stack.
      // Precondition: None.
      // Postcondition: The element x is added to the top of the stack.
      myStack.push_front(x);  //add x to the top.  
    }

   
    void pop() { 
      // Pop an element off the stack.
      // Precondition: The stack is not empty.
      // Postcondition: The top element is removed from the stack.
      if (!empty()){
      	myStack.pop_front();   //Pop the top element of the stack if the stack isn't empty. 
      }
      else{
     	 throw std::runtime_error("stack underflow");  //throw an error if it's empty. 
      }
    }

    T top() const { 
      // Return the top element on the stack.
      // Precondition: The stack is not empty.
      // Postcondition: The stack is unchanged, and the top element is returned.
      if (!empty()){
      	return myStack.front();   //get the front element of the list. 
      }
      else{
      	throw std::runtime_error("stack underflow");  //Throw an error if it's empty. 
      }
    }
    private: 
    
    llist<T> myStack;  //linked list used to simulate the behavior of a stack.   
  };
  
  
  
  

}

#endif
