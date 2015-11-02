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
 * Header File Name:               Leftist_heap
 * File:                           Leftist_heap.h
 *
 * Kai Luo
 * 2015-03-03
 * Version 1.0                     Initial implementation
 *
 * This class is a balanced min-heap structure which implements an leftist heap.
 *
 * No pre- or postconditions.
 *
 * Private Member Varibles:
 *  Left_node<Type> *root_node                    The root node of the heap
 *  int heap_size                                 The number of nodes inside the heap
 *
 *
 * Member Functions( Constructors ):
 *  Leftist_heap()                                Empty constructor that creates an empty heap of size 0
 * 
 *
 * Member Functions( Copy constructor ):
 *  Leftist_heap( Leftist_heap const& )           Creates a copy of the heap passed into the copy constructor
 *
 *
 * Member Functions( Destructor ):
 *  ~Leftist_heap()                               CLears the heap
 *
 *
 * Member Functions( Accessors ):
 *  bool         empty() const                    Returns true if the heap is empty, false otherwise
 *
 *  int          size() const                     Returns the size of the heap
 *  
 *  int          null_path_length() const         Returns the null-path length of the root node
 *
 *  int          count( Type const & ) const      Returns the number of how many times that the argument appears in the heap
 *
 *  Type         top() const                      Returns the object stored in the root node
 *
 *
 * Member Functions( Mutators ):
 *  void         swap( Leftist_heap &heap)        Swaps two heaps
 *
 *  Leftist_heap &operator=( Leftist_heap )       Swaps heap with the argument and return the current heap
 *
 *  void         push( Type const & )             Pushes the argument into the heap
 *
 *  Type         pop()                            Pops the root node and return the value previously stored in it
 *
 *  void         clear()                          Clears the heap
 *
 *
 * Bugs:
 * Todo:
 * Reference:
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"
#include <queue>

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		Leftist_heap( Leftist_heap const & );
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		Leftist_heap &operator=( Leftist_heap );

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

/*
 * Constructor
 *
 * Creates an empty heap
 *
 * No pre- or postconditions.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}

/*
 * Copy constructor
 *
 * Performs a traversal of the tree structure inserting the objects into the new tree
 *
 * Parameters:
 *  Leftist_heap const &heap
 *   The heap passed into the copy constructor.
 *
 * No pre- or postconditions.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Leftist_heap<Type>::Leftist_heap( Leftist_heap const &heap ):
root_node( nullptr ),
heap_size( 0 ) {
    std::queue<Leftist_node<Type>*> heap_queue;

    // Test boundary conditions on the size of the heap
    if ( heap.empty() ) {
        return;
    }
    
    
    // Push the root node of the argument in the queue
    heap_queue.push( heap.root_node );
    
    while ( !heap_queue.empty() ) {
        Leftist_node<Type> *tmp_ptr = heap_queue.front();
        
        // Traverses through the argument heap and pushes the entries into a queue
        if ( tmp_ptr->left() != nullptr ) {
            heap_queue.push( tmp_ptr->left() );
        }
        
        if ( tmp_ptr->right() != nullptr ) {
            heap_queue.push( tmp_ptr->right() );
        }

        push(tmp_ptr->retrieve());
        heap_queue.pop();
        
    }
}

/*
 * Destructor
 *
 * Clears the heap.
 *
 * No pre- or postconditions and no parameters.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

template <typename Type>
Leftist_heap<Type> &Leftist_heap<Type>::operator=( Leftist_heap<Type> rhs ) {
	swap( rhs );

	return *this;
}

// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
// 
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

/*
 * Empty
 *
 * Returns true if the heap is empty, and false otherwise.
 *
 * No pre- or postconditions and no parameters.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
bool Leftist_heap<Type>::empty() const {
    return (root_node == nullptr);
}

/*
 * Size
 *
 * Returns the number of nodes currently stored in the heap.
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
int Leftist_heap<Type>::size() const {
    return heap_size;
}

/*
 * Null_path_length
 *
 * Returns the null-path length of the root node.
 *
 * No pre- or postconditions and no parameters.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
int Leftist_heap<Type>::null_path_length() const {
    return root_node->null_path_length();
}

/*
 * Count
 *
 * Returns the number of instances of the argument in the heap.
 *
 * No pre- or postconditions and no parameters.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
int Leftist_heap<Type>::count( const Type &obj ) const {
    return root_node->count( obj );
}

/*
 * Top
 *
 * Returns the element at the top of the heap
 *
 * Pre-conditions:
 *  The heap must not be empty. Otherwise throw underflow exception.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Type Leftist_heap<Type>::top() const {
    
    // Throw an underflow if the heap is empty
    if ( empty() ) {
        throw underflow();
    }
    
    return root_node->retrieve();
}

/*
 * Push
 *
 * Inserts the new element into the heap.
 *
 * No pre- or postconditions
 *
 * Parameters:
 *  const Type & obj
 *   The object that is going to be inserted into the heap
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
void Leftist_heap<Type>::push( const Type & obj) {
    Leftist_node<Type> * tmp = new Leftist_node<Type>( obj );
    
    root_node->push( tmp, root_node );
    
    ++heap_size;
}

/*
 * Pop
 *
 * Pop the least element in the heap and deletes its node.
 *
 * Pre-conditions:
 *  The heap must not be empty. Otherwise throw underflow exception.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Type Leftist_heap<Type>::pop() {
    if ( empty() ) {
        throw underflow();
    }
    
    Leftist_node<Type> *tmp = root_node;
    Type tmp_ele = root_node->retrieve();
    
    root_node = root_node->left();
    
    root_node->push( tmp->right(), root_node );
    
    --heap_size;
    
    delete tmp;
    
    return tmp_ele;
}

/*
 * Clear
 *
 * Clears the heap.
 *
 * No pre- or postconditions.
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
void Leftist_heap<Type>::clear() {
    root_node->clear();
    
    // Reset the root node and heap size
    root_node = nullptr;
    heap_size = 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
    
    std::queue<Leftist_node<T>*> heap_copy_queue;
    
    heap_copy_queue.push( heap.root_node );
    
    while ( !heap_copy_queue.empty() ) {
        Leftist_node<T> *tmp_obj = heap_copy_queue.front();
        
        out << ( tmp_obj->retrieve() ) << " << ";
        
        if ( tmp_obj->left() != nullptr ) {
            heap_copy_queue.push( tmp_obj->left() );
        }
        
        if ( tmp_obj->right() != nullptr ) {
            heap_copy_queue.push( tmp_obj->right() );
        }
        
        heap_copy_queue.pop();
    }
    return out;
}
    
// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
