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
 * Header File Name:       Leftist_node
 * File:                   Leftist_node.h
 *
 * Kai Luo
 * 2015-03-03
 * Version 1.0             Initial implementation
 *
 * This class implements a leftist node used in a leftist heap.
 *
 * No pre- or postconditions.
 *
 * Private Member Variables:
 *  Type             element                                  The value stored in the node
 *  Leftist_node     *left_tree                               The root node of the left sub-tree
 *  Leftist_node     *right_tree                              The root node of the right sub-tree
 *  int              heap_null_path_length                    The null-path length of this node
 *
 *
 * Member Functions ( Constructors ):
 *  Leftist_node( Type const & )                              Creates a node storing the argument of size
 *
 *
 * Member Functions ( Accessors ):
 *  bool            empty() const                             Returns true if the node is empty, false otherwise
 *
 *  Type            retrieve() const                          Returns the value stored in the node
 *
 *  Leftist_node    *left() const                             Returns the left sub-tree of current node
 *
 *  Leftist_node    *right() const                            Returns the right sub-tree of the current node
 *
 *  int             null_path_length() const                  Returns the null-path length of the current node
 *
 *  int             count( Type const & ) const               Returns the number of instances in the heap
 *
 *
 * Member Functions ( Mutators ):
 *  void             push( Leftist_node *, Leftist_node *& )   Pushes the first node and its children in to the heap
 *
 *  void             clear()                                   Clears the heap
 *
 *
 * Bugs:            Unknown
 * Todo:            Unknown
 * Reference:       Unknown
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

/*
 * Constructor
 *
 * Creates a node
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

/*
 * Empty
 *
 * Returns if the node is empty
 *
 * No pre- or postconditions and parameters.
 *
 * Return:
 *  Returns true if the node is empty, false otherwise.
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

// You must implement everything

/*
 * Retrieve
 *
 * Returns the element stored in this node.
 *
 * No pre- or postconditions.
 *
 * Returns:
 *  Returns the element stored in this node.
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	return element;
}

/*
 * Left
 *
 * Returns the address of the root node of the left sub-tree.
 *
 * No pre- or postconditions.
 *
 * Returns:
 *  Returns the address of the root node of the left sub-tree.
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const {
	return left_tree;
}

/*
 * Right
 *
 * Returns the address of the root node of the right sub-tree.
 *
 * No pre- or postconditions.
 *
 * Return:
 *  Returns the address of the root node of the right sub-tree.
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const {
	return right_tree;
}

/*
 * Null_path_length
 *
 * Returns the member variable null-path length unless this is the null pointer,
 * in which case, return -1.
 *
 * No pre- or postconditions.
 *
 * Return:
 *  Return thr null-path length or -1
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	if ( empty() ) {
		return -1;
	} else {
        
        // Returns the null-path length
		return 1+std::min( left()->null_path_length(), right()->null_path_length() );
	}
}

/*
 * Count
 *
 * Returns the number of instances of the argument in this sub-tree.
 *
 * No pre- or postconditions.
 *
 * Parameters:
 *  Type const & obj
 *   The argument passed in the function to check how many times it appears in the heap
 *
 * Return:
 *  The total number of the argument appears in the heap
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
int Leftist_node<Type>::count( Type const & obj ) const {
	int counter = 0;

	if ( !empty() ) {
		if ( retrieve() == obj ) {
			counter = 1 + left()->count(obj) + right()->count(obj);
		} else if ( retrieve() < obj ) {
			counter = left()->count(obj) + right()->count(obj);
		} else {
			counter = 0;
        }
    }

	return counter;
    
}

/*
 * Push
 *
 * Insert a new heap into the current heap
 *
 * No pre- or postconditions.
 *
 * Parameters:
 *  Leftist_node<Type> *new_heap
 *   The root node of the heap that is going to be inserted
 *
 *  Leftist_node<Type> *&ptr_to_this
 *   The root node of the heap that combines with the new_heap passed into the funtion
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this ) {
	
    // Test boundary conditions on the size of the argument passed into
    if ( new_heap->empty() ) {
        return;
    }
    
    // Test boundary conditions on current heap size
    // If this is null, set the pointer to this to be the new heap and return
    if ( this == nullptr ) {
		ptr_to_this = new_heap;
		return;
        
        // Push the new node onto the right sub-tree if the curent node is storing
        // a value less-than-or-equal-to the value stored in the root of the new heap
	} else if ( retrieve() <= new_heap->retrieve() ) {
		right_tree->push( new_heap,right_tree );
		
        // Update the null-path length and if the left-sub-tree has a smaller
        // null-path length than the right sub-tree, swap the two sub-trees
		if ( left()->null_path_length() < right()->null_path_length() ) {
            heap_null_path_length = 1 + right()->null_path_length();
			std::swap( left_tree, right_tree );
		}
        
        // Set the pointer to this be the new heap and push this node into the new heap
	} else {
        ptr_to_this = new_heap;
        ptr_to_this->push( this, right_tree );
	}
}

/*
 * Clear
 *
 * Return if the heap is already empty; otherwise, clear the heap
 *
 * No pre- or postconditions.
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
void Leftist_node<Type>::clear() {
    
    // Test boundary conditions if the heap is already empty
	if ( this == nullptr ) {
		return;
	}
    
    // Clear the heap
    left()->clear();
    right()->clear();
    
	delete this;
}

#endif
