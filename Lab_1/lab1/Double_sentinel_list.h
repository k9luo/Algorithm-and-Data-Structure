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
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	private:
		Double_node<Type> *list_head;
		Double_node<Type> *list_tail;

		int list_size;

	public:
		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node<Type> *head() const;
		Double_node<Type> *tail() const;
        
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list const & );

		void push_front( Type const & );
		void push_back( Type const & );

		Type pop_front();
		Type pop_back();

		int erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
    
	// Initiate list head and list tail
    list_head = new Double_node<Type>();
    list_tail = new Double_node<Type>();

    // Set the previous and next pointers of the head sentinel to nullptr and the address of the tail sentinel
	list_head->previous_node = nullptr;
	list_head->next_node = list_tail;
    
    // Set the previous and next pointers of the tail sentinel to the address of the head sentinel and nullptr
	list_tail->previous_node = list_head;
	list_tail->next_node = nullptr;

    // Set list size to 0
    list_size = 0;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const & list ):
list_head( nullptr ), 
list_tail( nullptr ),
list_size( 0 ) {

    // Throw an underflow if the list is empty
    if (list.empty()){
        return;
    }

	// Initiate list head and list tail
	this->list_head = new Double_node<Type>();
    this->list_tail = new Double_node<Type>();

	this->list_head->previous_node = nullptr;
	this->list_head->next_node = list_tail;
	this->list_tail->previous_node = list_head;
	this->list_tail->next_node = nullptr;

    // Set list size to 0
	this->list_size = 0;

    // Copy all the nodes within the linked list with elements stored in the same order
	for(Double_node<Type> *ptr = list.head()->next(); ptr != list.list_tail; ptr = ptr -> next()){
		this->push_back(ptr -> retrieve());
    }
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {

    // Delete each of the nodes in the list including the sentiels
    while (!empty()){
        pop_front();
    }
    delete list_head;
    delete list_tail;

}

template <typename Type>
int Double_sentinel_list<Type>::size() const {

    // Return the number of items in the list
	return list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {

    // Return ture if the list is empty
	return (list_head->next() == list_tail);
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {

    // Throw an underflow if the list is empty
    if( empty() ){
        throw underflow();
    }
    
    // Retrieve the object stored in the node pointed to by the next pointer of the list head
	return (list_head -> next() -> retrieve());
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {

    // Throw an underflow if the list is empty
    if( empty() ){
        throw underflow();
    }
    
    // Retrieve the object stored in the node pointed to by the previous pointer of the list tail
	return (list_tail -> previous() -> retrieve());
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {

    // Return the list head
	return list_head;
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {

    // Return the list tail
	return list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {

    int i = 0;

    // Iterate through the linked list and count the number of nodes storing a value equal to the argument
    for (Double_node<Type> *ptr = list_head; ptr != list_tail; ptr = ptr -> next()){
        if (ptr -> retrieve() == obj){
                ++i;
        }
    }	

    // Return the number of nodes in the linked list storing a value equal to the argument
    return i;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> const &rhs ) {
	Double_sentinel_list<Type> copy( rhs );

	swap( copy );
	
	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {

    // Place a new node in the front of the linked list
    Double_node<Type> *new_node = new Double_node<Type>(obj, head(), head() -> next());
    head() -> next_node -> previous_node = new_node;
    head() -> next_node = new_node;
	
	list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {

    // Place a new node at the back of the list
    Double_node<Type> *new_node = new Double_node<Type>(obj, tail() -> previous(), tail());
    tail() -> previous_node -> next_node = new_node;
    tail() -> previous_node = new_node;

	list_size++;
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_front() {

    if( empty() ){
        throw underflow();
    }

    Type e = list_head -> next() -> retrieve();

	Double_node<Type> *new_node = list_head -> next();

    list_head -> next_node = new_node -> next();

    list_head -> next_node -> previous_node = list_head;

    // Delete the first non-sentinel node at the front of the list
    delete new_node;
	list_size--;
    
    // Return the element of the popped node
	return e;
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_back() {

    if( empty() ){
        throw underflow();
    }

    Type e = list_tail -> previous() -> retrieve();

    Double_node<Type> *new_node = list_tail -> previous();

    list_tail -> previous_node = new_node -> previous();

    list_tail -> previous_node -> next_node = list_tail;

    // Delete the first non-sentinel node at the back of the list
    delete new_node; 
	list_size--;
    
    // Return the element of the popped node
	return e;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {

    if ( empty() ){
        throw underflow();
    }

    for (Double_node<Type> *ptr = head() -> next(); ptr != tail(); ptr = ptr -> next()){
        if(obj == ptr -> retrieve()){
            
            // Update the previous and next pointers of any other node within the linked list
            ptr -> previous_node -> next_node = ptr -> next();
            ptr -> next_node -> previous_node = ptr -> previous();

            // Delete the first node (from the front and other than the sentinels) in the linked list that contains the objext equal to the argument
            delete ptr;
			list_size--;
            
            // Return the number of nodes that were deleted
			return 1;
        }
    }

	return 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr -> next() ) {
		if ( ptr == list.head() || ptr == list.tail() ) {
			out << "->S";
		} else {
			out << "->" << ptr -> retrieve();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.head() || ptr == list.tail() ) {
			out << "->S";
		} else {
			out << "->" << ptr->retrieve();
		}
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
