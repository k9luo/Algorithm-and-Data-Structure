/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
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
 * Header File Name: Quadratic_hash_table
 * File: Quadratic_hash_table.h
 *
 * Kai Luo
 * 2015-03-15
 * Version 1.0    Initial implementation
 *
 * This class implements a hash table using quadratic hashing
 *
 * No pre- or postconsitions.
 *
 * Private Member Variables:
 *  int count                    The number of occupied bins in the hash table
 *  int power                    The argument passed into constructor to define the bin size
 *  int array_size               The size of the hash table
 *  int mask                     The last index in the hash table
 *  Type *array                  The array stores the elements
 *  bin_state_t * occupied       The array that stores the status of each bin
 *
 *
 * Private Member Function:
 *  int hash( Type const & ) const         Determines the initial bin
 *
 *
 * Member Functions ( Constructor ):
 *  Quadratic_hash_table( int = 5 )        Creates a hash table with a size of 2^m and the default value of m is 5
 *
 *
 * Member Functions ( Destructor ):
 *  ~Quadratic_hash_table()                Deallocates the memory occupied by two arrays
 *
 *
 * Member Functions ( Accessors ):
 *  int size() const                       Returns the number of objects currently stored in the hash table
 *
 *  int capacity() const                   Returns the number of bins in the hash table
 *
 *  double load_factor() const             Returns the load factor of the hash table which is the ratio of occupied bins over the total number of bins
 *
 *  bool empty() const                     Returns true if the hash table is empty, false otherwise
 *
 *  bool member( Type const & ) const      Returns true if the argument is in the hash table, false otherwise
 *
 *  Type bin( int n ) const                Returns the entry in bin n
 *
 *  void print() const                     Prints out all elements in the hash table
 *
 *
 * Member Functions ( Mutators ):
 *  void insert( Type const & )            Inserts the argument into the hash table in the appropriate bin
 *
 *  bool erase( Type const & )             Removes the argument from the hash table
 *
 *  void clear()                           Removes all elements in the hash table
 *
 *
 * Bugs:
 * Todo:
 * Reference:
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
	private:
		int count;
		int power;
		int array_size;
		int mask;
		Type *array;
		bin_state_t *occupied;

		int hash( Type const & ) const;

	public:
		Quadratic_hash_table( int = 5 );
		~Quadratic_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadratic_hash_table<T> const & );
};

/*
 * Constructor
 *
 * Creates a hash table with the size of 2^m and the default value of m is 5
 *
 * Parameters:
 *  int m              The power of the size of the hash table
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new bin_state_t[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
}

// Your implementation here

/*
 * Destructor
 *
 * Deletes the memory allocated for two arrays
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table() {
    delete [] array;
    delete [] occupied;
}

/*
 * Size
 *
 * Returns the number of objects currently stored in the hash table
 *
 * No pre- or postconsitions and no parameters.
 *
 * Returns:
 *  Returns the number of objects currently stored in the hash table
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
int Quadratic_hash_table<Type>::size() const {
    return count;
}

/*
 * Capacity
 *
 * Returns the number of bins in the hash table
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  Returns the number of bins in the hash table
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
int Quadratic_hash_table<Type>::capacity() const {
    return array_size;
}

/*
 * Load_factor
 *
 * Returns the load factor of hash table which is the ratio of occupied bins over the total number of bins
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  Returns the load factor
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
double Quadratic_hash_table<Type>::load_factor() const {
    return static_cast<double>(size())/static_cast<double>(capacity());
}

/*
 * Empty
 *
 * Returns true if the hash table is empty, false otherwise
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  Returns true if the hash table is empty, false otherwise
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
bool Quadratic_hash_table<Type>::empty() const {
    return ( size() == 0 );
}

/*
 * Member
 *
 * Returns true if the argument is in the hash table, false otherwise
 *
 * No pre- or postconditions
 *
 * Parameters:
 *  Type const &obj         The argument to be checked
 *
 * Returns:
 *  Returns true if the argument is in the hash table, false otherwise
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
bool Quadratic_hash_table<Type>::member( const Type & obj ) const {
    
    // Returns true if the argument is in the hash table
    if ( array[hash(obj)] == obj && occupied[hash(obj)] == OCCUPIED ) {
        return true;
    }
    
    for ( int i = 0; i < capacity(); i++ ) {
        if ( array[i] == obj && occupied[i] == OCCUPIED ) {
            return true;
        }
    }
    
    // Returns false if the argument is not in the hash table
    return false;
}

/*
 * Bin
 *
 * Returns the entry in bin n
 *
 * No pre- or postconditions
 *
 * Parameters:
 *  int n                   The location of the object stored in the bin n
 *
 * Returns:
 *  Returns the entry in bin n
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
Type Quadratic_hash_table<Type>::bin( int n ) const {
    return array[n];
}

/*
 * Print
 *
 * Prints out all elements stored in the hash table
 *
 * No pre- or postconditions and no parameters
 *
 * Bugs:
 * Todo:
 * references:
 */
template <typename Type>
void Quadratic_hash_table<Type>::print() const {
    
    // Prints out all elements stored in the hash table
    for ( int i = 0; i < size(); i++ ) {
        std::cout << array[i] << " ; ";
    }
}

/*
 * Hash
 *
 * Returns the initial bin where stores the argument
 *
 * No pre- or postconditions
 *
 * Parameters:
 *  Type const &obj               The element to be checked where it should be placed in the hash table
 *
 * Returns:
 *  The location where the element should be placed into the hash table
 *
 * Bugs:
 * Todo:
 * Reference:
 */
template <typename Type>
int Quadratic_hash_table<Type>::hash( const Type & obj ) const {
    
    // Statically cast variables as int
    int M = capacity();
    int i = static_cast<int>(obj);
    
    // Taking the integer module M(i % M), and adding M if the value is negative
    if ( (i % M) < 0 ) {
        i = M + (i % M);
    } else {
        i = i % M;
    }
    
    // Using quadratic probing to locate where the argument should be placed
    for ( int k = 0; k < capacity(); k++ ) {
        i = (i + k ) % M;
        
        if ( occupied[i] != OCCUPIED ){
            return i;
        }
    }
    
    // Returns the location where the argument should be placed
    return i;
}

/*
 * Insert
 *
 * Inserts the argument into the hash table in the appropriate bin
 *
 * Preconditions:
 *  Throws an overflow exception if the hash table is already full
 *
 * Parameters:
 *  Type const &obj           The object to be inserted into the hash table
 *
 * Bugs:
 * Todo:
 * references:
 */
template <typename Type>
void Quadratic_hash_table<Type>::insert( const Type & obj ) {
    
    // Throws an overflow exception if the hash table is already full
    if ( size() == capacity() ) {
        throw overflow();
    }

    // Returns if the argument is already in the hash table
    if ( member(obj) ) {
        return;
    }
    
    // Locates where the argument should be placed
    int bin_num = hash(obj);
    
    array[bin_num] = obj;
    occupied[bin_num] = OCCUPIED;
    
    ++count;
}

/*
 * Erase
 *
 * Removes the argument from the hash table
 *
 * No pre- or postconditions and no parameters
 *
 * Parameters:
 *  Type const &obj          The element to be removed from the hash table
 *
 * Returns:
 *  Returns true if the argument is removed, false otherwise
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
bool Quadratic_hash_table<Type>::erase( const Type & obj ) {
    
    // Removes the argument if it is in the hash table and returns true
    if ( member(obj) ) {
        int hash_num = static_cast<int>(obj);
        
        if ( (hash_num % capacity() ) < 0 ) {
            hash_num = capacity() + ( hash_num % capacity() );
        } else {
            hash_num = hash_num % capacity();
        }
        
        if ( array[hash_num] == obj ) {
            occupied[hash_num] = ERASED;
            --count;
        }
        
        for ( int i = 0; i < capacity(); i++ ) {
            if ( array[i] == obj ) {
                occupied[i] = ERASED;
                --count;
            }
        }
        return true;
    }
    
    // Returns false if the argument is not in the hash table
    return false;
}

/*
 * Clear
 *
 * Removes all the elements in the hash table
 *
 * No pre- or postconditions and no parameters
 *
 * Bugs:
 * Todo:
 * References:
 */
template <typename Type>
void Quadratic_hash_table<Type>::clear() {
    delete [] array;
    delete [] occupied;
    
    count = 0;
    array = new Type[capacity()];
    occupied = new bin_state_t[capacity()];
    
    for ( int i = 0; i < capacity(); i++ ) {
        occupied[i] = UNOCCUPIED;
    }
}

template <typename T>
std::ostream &operator<<( std::ostream &out, Quadratic_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == UNOCCUPIED ) {
			out << "- ";
		} else if ( hash.occupied[i] == ERASED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif
