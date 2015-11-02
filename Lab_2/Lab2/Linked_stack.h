/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  k9luo @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2015
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 * Header File Name:    Linked_stack
 * File:                Linked_stack.h
 *
 * Kai Luo
 * 2015-03-01
 * Version 1.0         Initial implementation.
 *
 * This class implements two linked stacks using the Double_sentinel_list and
 * Double_node file from Project 1.
 *
 * No pre- or postconditions.
 *
 * Private Member variables:
 *  static int const ARRAY_CAPACITY = 8     Constant that defines # of variables in each array
 *  Double_sentinel_list<Type *> list       The linked list that store the arrays
 *  int   itop                              The index of the last element in array
 *  int   stack_size                        The number of entries in the stacks
 *
 * Member Functions (Constructors):
 *  Linked_stack<Type>::Linked_stack()      Empty constructor that creates an empty stack
 *                                          of size 0
 *
 * Member Functions (Destructor):
 *  ~Linked_stack()                         Deletes the Linked list and the arrays in it
 *                                          and dellocate memory
 *
 * Member Functions (Copy Constructor):
 *  Linked_stack( Linked_stack const & )    Creates a new instance of linked stack with
 *                                          arrays identical to the argument
 * Member Functions (Accessors):
 *  Type    top() const                     Return the last element in the array
 *                                          at the top node of stack list
 *
 *  int     size() const                    Return the stack_size variable
 *
 *  bool    empty() const                   Return true if list is empty, false
 *                                          otherwise
 *
 *  int     list_size() const               Return the number of nodes in the stack list
 *
 * Member Functions (Mutators):
 *  void    swap( Linked_stack & )          Swap all member variables with the argument
 *
 *
 *  Linked_stack &operator =                Swap the member variables of this with
 *              ( Linked_stack )            a copy of the right-hand side of the operator.
 *
 *  void    push( Type const &obj )         Push the argument onto the top of stack
 *
 *  void    pop()                           Remove the last entry on the first node of
 *                                          stack
 *
 * Bugs:          Unknown
 * Todo:          Unknown
 * Reference:     Unknown
 *****************************************/

/**********************************************************
 * YOU MUST MODIFY THIS FUNCTION IF YOU DID NOT IMPLEMENT
 * Single_list.h IN PROJECT 1.  THIS REQUIRES YOU TO:
 *   1.  Change which header file is is included.
 *   2.  Change the type of the member variable 'list'.
 *   3.  Update the ostream<< operator so that it prints
 *       out the entries in your implementation.
 **********************************************************/

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_sentinel_list.h"
#include "Exception.h"
#include <iostream>

template <typename Type>
class Linked_stack {
	private:
		static int const ARRAY_CAPACITY = 8;

		Double_sentinel_list<Type *> list;
		int itop;
		int stack_size;

	public:
		Linked_stack();
		Linked_stack( Linked_stack const & );
		~Linked_stack();

		bool empty() const;
		int size() const;
		int list_size() const;

		Type top() const;

		void swap( Linked_stack & );
		Linked_stack &operator=( Linked_stack );
		void push( Type const &obj );
		Type pop();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Linked_stack<T> const & );
};

/*
 * Constructor
 *
 * Creates a new stack with a size of 0.
 *
 * No pre- or postconditions.
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
Linked_stack<Type>::Linked_stack():
stack_size( 0 ) {
	// Empty constructor
}

/*
 * Copy constructor
 *
 * Copies and creates a new instance of the stack passed in as argument.
 *
 * Parameters:
 *  Linked_stack const &stack
 *   The stack passed into the copy constructor.
 *
 * No pre- or postconditions.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Linked_stack<Type>::Linked_stack( Linked_stack const &stack ):
itop( stack.itop ),
stack_size( stack.stack_size ) {
	// enter your implementation here
    if ( stack.empty() ) {
        return;
    }
    
    // Iterate through all the entries of the linked list,
    //starting at the entry that the list head points to.
    for ( Double_node<Type *> *tmp = stack.list.head()->next(); tmp->next() != nullptr; tmp = tmp->next() ) {
        Type *tmp_array = new Type[ARRAY_CAPACITY];
        
        if ( tmp == stack.list.head()->next() ) {
            for (int i = 0; i <= stack.itop; ++i) {
                tmp_array[i] = (tmp->retrieve())[i];
            }
        } else {
            for (int i = 0; i <= Linked_stack<Type>::ARRAY_CAPACITY - 1; ++i) {
                tmp_array[i] = (tmp->retrieve())[i];
            }
        }
        
        list.push_back(tmp_array);
    }
}

/*
 * Destructor
 *
 * Deallocates the memory assigned to 'list' and the arraries that 'list' points to.
 *
 * No pre- or postconditions and no parameters.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Linked_stack<Type>::~Linked_stack() {
	// enter your implementation here
    while ( size() > 0 ) {
        pop();
    }
}

/*
 * Empty
 *
 * Returns true if the stack is empty (the size is 0), and false otherwise.
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  True if the stack is empty, false otherwise.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
bool Linked_stack<Type>::empty() const {
	// enter your implementation here
	return ( size() == 0 );
}

/*
 * Size
 *
 * Returns the number of objects currently stored in the stack.
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  The number of objects currently stored in the stack.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
int Linked_stack<Type>::size() const {
	// enter your implementation here
	return stack_size;
}

// Do not change this implementation
/*
 * List_size
 *
 * Returns the number of nodes in the linked list data structure.
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  The number of nodes in the linked list data structure.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
int Linked_stack<Type>::list_size() const {
	return list.size();
}

/*
 * Top
 *
 * Returns the object at the top of the stack.
 *
 * Pre-conditions:
 *  The stack must not be empty. Otherwise throw underflow exception.
 *
 * Returns:
 *  The object at the head of the queue.
 *
 * Bugs:
 * Todo:
 * References:
 */

template <typename Type>
Type Linked_stack<Type>::top() const {
	// enter your implementation here
    if ( empty() ) {
        throw underflow();
    }
    
	return ( list.head()->next()->retrieve()[itop] );
}

/*
 * Swap
 *
 * Swap the member variables of 'this' object and those of the argument 'stack'.
 *
 * Parameters:
 *  Linked_stack<Type> &stack
 *   The stack to be copied from.
 *
 * We are using the standard library 'swap' function.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
void Linked_stack<Type>::swap( Linked_stack<Type> &stack ) {
	std::swap( list, stack.list );
	std::swap( stack_size, stack.stack_size );
	std::swap( itop, stack.itop );
}

/*
 * Assignment operator
 *
 * Assign the argument to this stack.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Linked_stack<Type> &Linked_stack<Type>::operator=( Linked_stack<Type> rhs ) {
	swap( rhs );

	return *this;
}

/*
 * Push
 *
 * Insert the argument in the array that head node of the stack list points to. 
 * Create a new head node that points to a new array if the array pointed by 
 * the original head node is full
 *
 * Parameters:
 *  Type const &obj
 *   The object to be inserted at the top of the stack.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
void Linked_stack<Type>::push( Type const &obj ) {
	// enter your implementation here

    // Test boundary conditions on the size of the array pointed by the head node
    // and the size of stack
    if( itop + 1 == ARRAY_CAPACITY || stack_size == 0 ){
        
        // Create a new a new array pointed by the head node if the list is empty
        // or the array pointed by the head node is full. Reset itop.
        Type *array_stack = new Type[ARRAY_CAPACITY];
        list.push_front(array_stack);
        
        itop = 0;
    } else {
        ++itop;
    }
    
    // Increment stack size and push the argument to the stack
    ++stack_size;
    list.head()->next()->retrieve()[itop] = obj;
}

/*
 * Pop
 *
 * Remove the last entry in the array pointed by the head node then decrement itop. 
 * If the array is empty then deallocate the memory assigned to it and
 * set itop to ARRAY_CAPACITY - 1 
 *
 * Pre-conditions:
 *  The stack must not be empty. Otherwise throw underflow exception.
 *
 * Returns:
 *  The object at the end of the array pointed by the head node before popped
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Type Linked_stack<Type>::pop() {
	// enter your implementation here
    
    // Throw underflow if the stack is empty
    if ( empty() ) {
        throw underflow();
    }
    
	--stack_size;
    Type pop_element = list.head()->next()->retrieve()[itop];
    --itop;

    // Pop the head node in the linked list if the array that it points to is empty
    if ( itop == -1 ) {
        itop = ARRAY_CAPACITY - 1;
        delete[] list.head()->next()->retrieve();
        list.pop_front();
    }

	return pop_element;
}

// You will be required to modify this function in order to accomodate
// your implementation of a singly linked list in Project 1.

template <typename T>
std::ostream &operator<<( std::ostream &out, Linked_stack<T> const &stack ) {
	if ( stack.list.size() == 0 ) {
		out << "->0";
	} else if ( stack.list.size() == 1 ) {
		out << "->[ ";

		for ( int i = 0; i <= stack.itop; ++i ) {
			out << stack.list.front()[i] << " ";
		}

		out << "]->0";
	} else {
		out << "->";

		for ( Double_node<T *> *ptr = stack.list.head()->next(); ptr->next() != nullptr; ptr = ptr->next() ) {
			out << "[ ";

			if ( ptr == stack.list.head()->next() ) {
				for ( int i = 0; i <= stack.itop; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			} else {
				for ( int i = 0; i <= Linked_stack<T>::ARRAY_CAPACITY - 1; ++i ) {
					out << ptr->retrieve()[i] << " ";
				}
			}

			out << "]->";
		}

		out << "0";
	}

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
