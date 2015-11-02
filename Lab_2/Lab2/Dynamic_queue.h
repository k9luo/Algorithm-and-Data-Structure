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
 *
 * Class_name: Dynamic_queue
 * File:       Dynamic_queue.h
 *
 * Kai Luo
 * 2015-02-05
 * Version 1.0                  Initial implementation
 *
 * This class implementations a queue using an aray. The capacity of the queue
 * changes dynamically after insertions or deletions.
 *
 * No pre- or postconditions.
 *
 * Private Member variables:
 * Type, Type *array                                 A pointer to an array used as a queue
 * int   ihead                                       The head index
 * int   entry_count                                 The size of array
 * int   initial_capacity                            The initial capacity of the array
 * int   array_capacity                              The current capacity of the array
 *
 * Member Functions ( Constructors ):
 *  Dynamic_queue( int n = 10 )                      Allocates memory for the array with initial
 *                                                   capacity, sets invalid capacity to 1. Default
 *                                                   capacity is 10.
 *
 * Member Functions ( Destructor ):
 *  ~Dynamic_queue()                                 Deletes array and dellocate memory
 *
 * Member Functions ( Copy Constructor ):
 *  Dynamic_queue( Dynamic_queue const & ) creates a new instance
 *                                         of the queue. (O(n))
 *
 * Member Functions ( Accessors ):
 *  Type              head() const                   Return object at head of queue. Throw underflow
 *                                                   exception if list is empty
 *
 *  int               size() const                   Return number of objects stored in the queue
 *
 *  bool              empty() const                  Return true if list is empty, false otherwise
 *
 *  int               capacity() const               Return current capacit of the queue
 *
 * Member Functions ( Accessors ):
 *  Type              head() const                   Return object at head of queue. Throw underflow
 *                                                   exception if list is empty
 *
 *  int               size() const                   Return number of objects stored in the queue
 *
 *  bool              empty() const                  Return true if list is empty, false otherwise
 *
 *  int               capacity() const               Return current capacit of the queue
 *
 * Member Functions (Mutators):
 *  void              swap( Dynamic_queue &);        Swap all member variables with passed in queue
 *
 *  Dynamic_queue &operator= ( Dynamic_queue & );    Swap the member variables of this with a copy
 *                                                   of the right-hand side of the operator
 *
 *  Type              dequeue()                      Removes object at the head of the queue
 *
 *  void              clear()                        Empties the queue by resetting the member variables.
 *                                                   Resize the array to the initial capacity
 *
 * Bugs:              Unknown
 * Todo:              Unknown
 * Reference:         None
 *****************************************/

#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "ece250.h"
#include "Exception.h"

template <typename Type>
class Dynamic_queue {
	private:
		int initial_capacity;
		int array_capacity;
		Type *array;
		int ihead;
		int itail;
		int entry_count;
		// other integer member variables, as necessary

	public:
		Dynamic_queue( int = 10 );
		Dynamic_queue( Dynamic_queue const & );
		~Dynamic_queue();

		Type head() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Dynamic_queue & );
		Dynamic_queue &operator=( Dynamic_queue );
		void enqueue( Type const & );
		Type dequeue();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Dynamic_queue<T> const & );
};

/*
 * Constructor
 *
 * Creates a new queue with a capacity of at least one.
 * The default capacity is 10.
 *
 * The queue is initially empty, and reset itail to -1.
 *
 * No pre- or postconditions.
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( int n ):
initial_capacity( std::max( n, 1 ) ),
array_capacity( initial_capacity ),
array( new Type[initial_capacity] ),
ihead( 0 ),
itail( initial_capacity - 1 ),
entry_count( 0 ) {
    // Enter your implementation here.
    itail = -1;
}

/*
 * Copy constructor
 * 
 * Copies and creates a new instance of the queue passed in as argument.
 *
 * Parameters:
 *  Dynamic_queue const &queue
 *   The queue passed into the copy constructor.
 *
 * No pre- or postconditions.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( Dynamic_queue const &queue ):
initial_capacity( queue.initial_capacity ),
array_capacity( queue.array_capacity ),
array( new Type[array_capacity] ),
ihead( queue.ihead ),
itail( queue.itail ),
entry_count( queue.entry_count ) {
	// The above initializations copy the values of the appropriate
	// member variables and allocate memory for the data structure;
	// however, you must still copy the stored objects.

	// Enter your implementation here.
    // Iterate queue and copy each stored objects to the new queue.
    for ( int i = 0; i < queue.array_capacity; i++ ) {
        array[i] = queue.array[i];
    }
}

/*
 * Destructor
 *
 * Deallocates the memory assigned to 'array'.
 *
 * No pre- or postconditions and no parameters.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Dynamic_queue<Type>::~Dynamic_queue() {
	// Enter your implementation here.
    delete [] array;
}

/*
 * Size
 *
 * Returns the number of objects currently stored in the dynamic queue.
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  The number of objects currently stored in the dynamic queue.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
int Dynamic_queue<Type>::size() const {
	// Enter your implementation here.
	return entry_count;
}

/*
 * Capacity
 *
 * Returns the current capacity of the queue.
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  The current capacity of the queue.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
int Dynamic_queue<Type>::capacity() const {
	// Enter your implementation here.
	return array_capacity;
}

/*
 * Empty
 *
 * Returns true if the queue is empty (the size is 0), and false otherwise.
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  True if the queue is empty, false otherwise.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
bool Dynamic_queue<Type>::empty() const {
	// Enter your implementation here.
	return ( size() == 0 );
}

/*
 * Head
 *
 * Returns the object at the head of the queue.
 *
 * Pre-conditions:
 *  The queue must not be empty. Otherwise throw underflow exception.
 *
 * Returns:
 *  The object at the head of the queue.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Type Dynamic_queue<Type>::head() const {
	// Enter your implementation here.
    if ( empty() ) {
        throw underflow();
    }
    
	return array[ihead];
}

/*
 * Swap
 *
 * Swap the member variables of 'this' object and those of the argument 'queue'.
 *
 * Parameters:
 *  Dynamic_queue<Type> &queue
 *   The queue to be copied from.
 *
 * We are using the standard library 'swap' function.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
void Dynamic_queue<Type>::swap( Dynamic_queue<Type> &queue ) {
	std::swap( initial_capacity, queue.initial_capacity );
	std::swap( array_capacity, queue.array_capacity );
	std::swap( array, queue.array );
	std::swap( ihead, queue.ihead );
	std::swap( itail, queue.itail );
	std::swap( entry_count, queue.entry_count );
}

/*
 * Assignment operator
 *
 * Assign the argument to this queue.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Dynamic_queue<Type> &Dynamic_queue<Type>::operator=( Dynamic_queue<Type> rhs ) {
	swap( rhs );
	
	return *this;
}

/*
 * Enqueue
 *
 * Insert the argument at the tail of the queue.
 * If the array is full before the argument is placed into the queue,
 * the capacity of the array is first doubled.
 *
 * Parameters:
 *  Type const &obj
 *   The object to be inserted at the tail of the queue.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
void Dynamic_queue<Type>::enqueue( Type const &obj ) {
	// Enter your implementation here.
    
    // Test boundary conditions on size().
    if ( size() == capacity() ) {
        
        // Double the array capacity if the array is full.
        array_capacity = 2 * array_capacity;
		Type *tmp = new Type[ capacity() ];
		
        // Test boundary conditions on the locations of ihead and itail.
		if ( ihead <= itail ) {
            
            // Copy each objects from the array to the tmp_array.
			for ( int i = 0; i < size(); i++ ) {
				tmp[i] = array[i];
			}
		} else {
            
            // Copy each objects from the array to the tmp_array.
			for ( int i = ihead; i < size(); i++) {
				tmp[i - ihead] = array[i];
			}
			for ( int i = 0; i < ihead; i++) {
				tmp[size() - ihead + i] = array[i];
			}
		}

		delete [] array;
		array = tmp;
		ihead = 0;
		itail = size()-1;
        
    } else if ( size() < capacity() ) {
        
        // If the array is not full and the itail is at the end of the array
        // then add argument at the beginning of the array.
		if ( itail == (capacity() - 1) ) {
			itail = -1;
		}
	}
		
		++itail;
		entry_count++;
        array[itail] = obj;	
}
    
/*
 * Dequeue
 *
 * Removes the object at the head of the queue.
 * If, after the object is removed, the array is one-quarter (1/4) full
 * and the array capacity is greater than the initial capacity,
 * the capacity of the array is halved.
 *
 * Pre-conditions:
 *  The queue must not be empty. Otherwise throw underflow exception.
 *
 * Returns:
 *  The object at the head of queue before dequeue
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Type Dynamic_queue<Type>::dequeue() {
	// Enter your implementation here.
    
    // Throw underflow if the queue is already empty.
    if ( empty() ) {
        throw underflow();
    }

    
    // Corrected
    --entry_count;

    if ( empty() ) {
        ihead = 0;
        itail = 0;
    }
    
    
    
    // Store the object at the head of the queue before popped.
    Type head = array[ihead];
    
    // Test boundary conditions on the location of ihead if it is at the end of the queue.
    // If so, move ihead to the beginning od the array. Otherwise increament ihead.
    if ( ihead == capacity()-1 ) {
        ihead = 0;
    } else {
        ++ihead;
    }
    
    
    // Test boundary conditions on size() if the array is 1/4 full and the array capacity
    // is greater than the initial capacity
    if ( size() <= capacity() / 4 && capacity() >= 2 * initial_capacity ) {
        
        // Shrink the array capacity to half
        int tmp_capacity = capacity() / 2;
        Type *tmp_array = new Type[tmp_capacity];
        
        // Test boundary conditions on the locations of ihead and itail
        // Copy each object from the array to tmo_array
        /*if ( ihead < itail ){
            for ( int i = 0; i <= tmp_capacity; i++ ) {
                tmp_array[i] = array[i];
            }
        } else {
            for ( int i = ihead; i < capacity(); i++){
				tmp_array[i- (capacity() / 2)] = array[i];
            }
        }*/
        
        if ( ihead < itail ) {
            for ( int i = 0; i < size(); i++ ) {
                tmp_array[i] = array[ihead+i];
            }
            ihead = 0;
            itail = size() - 1;
        } else if ( ihead == itail ) {
            tmp_array[0] = array[ihead];
            ihead = 0;
            itail = 0;
        } else {
            int j = 0;
            int k = 0;
            
            while ( ihead+j < capacity() ) {
                tmp_array[j] = array[ihead+j];
                j++;
            }
            
            while ( k<=itail ) {
                tmp_array[j] = array[k];
                j++;
                k++;
            }
            ihead = 0;
            itail = size() - 1;
        }
        
        array_capacity = tmp_capacity;
        delete [] array;
        array = tmp_array;
    }
    
    return head;
}

/*
 * Clear()
 *
 * Empties the queue; set the queue size to 0 and the capacity to the initial capacity.
 *
 * There is no parameters or pre-conditions
 *
 * Bugs:
 * Todo:
 * References:
 */

template <typename Type>
void Dynamic_queue<Type>::clear() {
	// Enter your implementation here.
    Type *tmp = new Type[initial_capacity];
    ihead = 0;
    itail = -1;
    array_capacity = initial_capacity;
    entry_count = 0;
    
    delete [] array;
    
    array = tmp;
}

// You can modify this function however you want:  it will not be tested

template <typename Type>
std::ostream &operator<<( std::ostream &out, Dynamic_queue<Type> const &queue ) {
	// I don't know how you are implementing your queue so I cannot print it.
	// If you want, you can print whatever you want here and then call cout
	// in the driver.

	// Remember to redirect to out, e.g.,
	//      out << "Hello!";
    
    for ( int i = 0; i < queue.capacity(); i++) {
        out << queue.array[i] << ",";
    }
    
    out << std::endl;
    out << "ihead is " << queue.ihead << std::endl;
    out << "itail is " << queue.itail << std::endl;
    
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
