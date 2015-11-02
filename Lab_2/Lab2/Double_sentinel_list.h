/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  y588liu@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
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

/**
Constructor
**/
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {

    list_head = new Double_node<Type>();                           //Create head and tail pointers that point to each other
    list_tail = new Double_node<Type>();                           //and nullptr
	list_head->next_node = list_tail;
	list_tail->previous_node = list_head;
}


/**
Copy constructor
**/
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head( nullptr ), 
list_tail( nullptr ),
list_size( 0 ) {
    if ( list.empty() ) {                                                           //Return if list is empty
            return;
        }
    
    list_head = new Double_node<Type>();                                            //Create head and tail pointers that point to each other
    list_tail = new Double_node<Type>();                                            //and nullptr
    list_head->next_node = list_tail;
    list_tail->previous_node = list_head;

   push_front(list.front());                                                        //Create the first node with the value of first node in list
   for(                                                                             //Loop through list to copy each node
        Double_node<Type> *original = list.head()->next()->next();
        original->next()!= nullptr;
        original = original->next()
    ){
       push_back(original->retrieve());
                                                                                    //copy new node with push back function
   }
}

//Destructor
template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    while(!empty()){
        pop_front();                                                    //Delete all nodes in the list by pop the front element each time it loops
    }
    delete list_head;
    delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    return list_size;                                                   //return list size
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    return (0 == list_size);                                            //return true if list size equals zero
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    if(empty()){
        throw underflow();                                              //throw underflow if list is empty
    }
    return head()->next()->retrieve();                                  //retrieves the value stored in the node after head node
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    if(empty()){
        throw underflow();
    }
    return tail()->previous()->retrieve();                              //retrieves the value stored in the node before tail node
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {
    return list_head;                                                   //retrieves the first node in list
}


template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {
    return list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {

    int counter = 0;
    for(Double_node<Type> *ptr = head()->next(); ptr->next() != nullptr; ptr = ptr->next()){
        if(ptr->retrieve() == obj){
            counter = counter + 1;
        }
    }
    return counter;
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
    Double_node<Type> *new_node = new Double_node<Type>(obj, head(), head()->next()) ;   //Create a new node with passed in value in between head and first node
    head()-> next() -> previous_node = new_node;                            //Set previous pointer of the original first node to the new node
    head()-> next_node = new_node;                                          //Set next pointer of head to new node
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    Double_node<Type> *new_node = new Double_node<Type>(obj, tail()->previous(), tail()); //Create a new node with passed in value in between tail and last node
    tail()-> previous() -> next_node = new_node;                              //Set next pointer of the original last node to the new node
    tail()-> previous_node = new_node;                                        //Set previous pointer of tail to new node
    list_size++;
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_front() {
    if(empty()){

        throw underflow();
    }
    Type value = front();
    Double_node<Type> *temp_node = head()->next();                            //Create a temp node which store the same adress as the first node

    temp_node->next()->previous_node = list_head;                             //Point previous node of the node after temp node to head
    head()->next_node = temp_node->next();                                    //Point next node of head to the node after temp node
    delete temp_node;                                                         //Remove the pointer which also delocates the first node
    list_size--;
    return value;
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_back() {
    if(empty()){
        throw underflow();
    }
    Double_node<Type> *temp_node = tail()->previous();                        //Create a temp node which store the same adress as the last node
    Type value = temp_node->retrieve();
    temp_node->previous()->next_node = tail();                                //Point next node of the node before temp node to tail
    tail()->previous_node = temp_node->previous();                            //Point previous node of head to the node before temp node
    delete temp_node;                                                         //Remove the pointer which also delocates the last node
    list_size--;
    return value;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {

    for(Double_node<Type> *ptr = head()->next(); ptr->next() != nullptr; ptr = ptr-> next()){      //loop through the list to check for equal elements
        if(ptr->retrieve() == obj){
            ptr->next()->previous_node = ptr->previous();                          //link the previous and next node of pointer
            ptr->previous()->next_node = ptr->next();
            delete ptr;                                                            //delete the pointer
            list_size--;
            return 1;
        }
    }
    return 0;                                                                      //return 0 if matching node was not found
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
    out << "head";

    for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
        if ( ptr == list.head() || ptr == list.tail() ) {
            out << "->S";
        } else {
            out << "->" << ptr->retrieve();
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