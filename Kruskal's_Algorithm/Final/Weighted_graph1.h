/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  y588liu @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2015
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
 * -http://stackoverflow.com/questions/4284132/c-sorting-struct-based-on-one-of-each-property
 * Header File Name:    Quadratic_hash_table
 * File:                Quadratic_hash_table.h
 *
 * Yijia Liu
 * 2015-04-06
 * Version 1.0         Initial implementation.
 *
 * This class implements a hash table using an array and other variables
 *
 * No pre- or postconditions.
 *
 * Private Member variables:
 *
 *  static const double INF                 staticly defined infinity
 *
 *  int graph_size                          The total number of vertices
 *
 *  int edge_size                           The number of edges in the graph
 *
 *  int * vertice_degree                    The degree of each vertice
 *
 *  double ** matrix                        The two dimentional matrix that stores the weight of
 *                                          each edge
 *
 *  std::list<edge_t> edge_list             The list used to sort the edges
 *
 *
 * Private Member function:
 *
 *  Weighted_graph( Weighted_graph const & )
 *
 *  Weighted_graph &operator=( Weighted_graph )
 *
 *
 * Member Functions (Constructors):
 *  Weighted_graph( int = 10 )              The constructor takes argument n and
 *                                          creates a triangular matrix of size n * n
 *
 * Member Functions (Destructor):
 *  ~Weighted_graph()                       The destructor deallocates memory allocated by the
 *                                          constructor
 *
 *
 * Member Functions (Accessors):
 *  int     degree( int ) const             Return the degree of given vertex
 *
 *  int     edge_count() const              Return the number of edges in the graph
 *
 *  std::pair<double, int> minimum_spanning_tree() const             
 *                                          Use Kruskal's algorithm to find a minimum spanning
 *                                          tree of the graph and return the weight of the minimum 
 *                                          spanning tree and number of edges tested
 *
 *
 * Member Functions (Mutators):
 *  bool    insert_edge( int, int, double ) Insert edge connecting first two parametera with 
 *                                          weight as the third parameter
 *
 *  bool    erase_edge( int, int )          Erase edge connecting the two parameters
 *
 *  void    clear_edges()                   Remove all edges in the graph
 *
 *
 * Bugs:          Unknown
 * Todo:          Improve runtime
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>

#include <list>
#include <stdexcept>
#include "Exception.h"
#include "Disjoint_sets.h"

typedef struct {
    int v1;
    int v2;
    double weight;
} edge_t;

class Weighted_graph {
	private:
		static const double INF;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice
        int graph_size;
        int edge_size;
        int * vertice_degree;
        double ** matrix;
        std::list<edge_t> edge_list;

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

/*
 * Weighted_graph::Weighted_graph( int n )
 *
 * The constructor creates a triangular matrix with size n * n
 * and initialize all variables. The graph size is defaulted to 10
 * is no smaller than one.
 *
 * Parameters:
 *  int n       The total number of vertices
 *
 * Bugs:
 * Todo:
 * References:
 */
Weighted_graph::Weighted_graph( int n ){
    
    //Set number of vertices to one if n is smaller than that
    if(n < 1){
        n = 1;
    }
    
    graph_size = n;
    edge_size = 0;
    vertice_degree = new int[n];
    matrix = new double * [n];
    
    //Initialize all entries in the matrix with infinity
    for ( int i = 0; i < n; i++ ) {
        
        vertice_degree[i] = 0;
        matrix[i] = new double[i+1];
        
        for ( int j = 0; j < i; j++ ) {
            matrix[i][j] = INF;
        }
        
        matrix[i][i] = 0;
    }

}

/*
 * Weighted_graph::~Weighted_graph()
 *
 * The destructor deletes the memory allocated for
 * the matrix and the array for storing degrees of vertices
 *
 * Parameters: none
 *
 * Bugs:
 * Todo:
 * References:
 */
Weighted_graph::~Weighted_graph() {
    
    //Delete each horizontal array first
    //Then delete the double array
    for ( int i = 0; i < graph_size; ++i ) {
        delete [] matrix[i];
    }
    delete [] matrix;
    delete [] vertice_degree;
}

/*
 * int Weighted_graph::degree(int i) const
 *
 * Return the degree at vertex i
 *
 * Parameters:
 *  int i   The vertice to be checked
 *
 * Returns:
 *  The number of edges connected to the vertice
 */
int Weighted_graph::degree(int i) const{
    
    //Throw illegal argument if i is invalid
    if (i < 0 || i >= graph_size) {
        throw illegal_argument();
    }
    
    return vertice_degree[i];
}

/*
 * int Weighted_graph::edge_count() const
 *
 * Return the total number of edges in the graph
 *
 * Parameters:  none
 *
 * Returns:
 *  The number of edges in the graph
 */
int Weighted_graph::edge_count() const{
    
    return edge_size;
}

/*
 * bool Weighted_graph::insert_edge( int i, int j, double d )
 *
 * Insert edge connecting vertices i and j with weight d into the graph.
 * Return true if the vertice is not connected to itself and false otherwise.
 * If the edge already existed then update the weight.
 *
 * Parameters:
 *  int i, int j    vertices to be connected by the edge
 *  double d        weight of the edge
 *
 * Returns:
 *  Return true if the edge is updated and false if it is not
 */
bool Weighted_graph::insert_edge( int i, int j, double d ) {
    
    //Throw illegal argument if the arguments are invalid
    if (i < 0 || i >= graph_size || j < 0 || j >= graph_size || d <= 0) {
        throw illegal_argument();
    }
    
    //Return false if the edge is connecting itself
    if(j == i){
        return false;
    }
    
    //Make sure the first index is always larger than the second
    //since it's a triangular matrix
    if (i < j) {
        std::swap(i, j);
    }
    
    //If the edge is new than increment edge count and degrees on each
    //vertices.
    if (matrix[i][j] == INF) {
        edge_size ++;
        vertice_degree[i] ++;
        vertice_degree[j] ++;
    }
    
    //Always update the edge weight regarless if a previous edge exists
    matrix[i][j] = d;
    
    return true;
}

/*
 * bool Weighted_graph::erase_edge( int i, int j)
 *
 * Remove the edge connecting i and j and update related variables
 *
 * Parameters:
 *  int i, int j    vertices connected by the target edge
 *
 * Returns:
 *  Return true if the edge is removed and false if it is not
 */
bool Weighted_graph::erase_edge( int i, int j) {
    
    //Throw illegal argument if parameters are invalid
    if (i < 0 || i >= graph_size || j < 0 || j >= graph_size) {
        throw illegal_argument();
    }
    
    //Swap index if necessary
    if (i < j) {
        std::swap(i, j);
    }
    
    //If there was an edge then remove it by setting weight as infinity
    //and return true. Otherwise return false.
    if (matrix[i][j] != INF) {
        matrix[i][j] = INF;
        vertice_degree[i] --;
        vertice_degree[j] --;
        edge_size --;
        return true;
    }
    return false;
}

/*
 * void Weighted_graph::clear_edges()
 *
 * Remove all edges in the graph by resetting distance between all
 * vertices as infinity and edge count to zero
 *
 * Parameters:  none
 *
 * Returns: none
 */
void Weighted_graph::clear_edges(){
    
    edge_size = 0;
    
    for (int i = 0; i < graph_size; i++) {
        vertice_degree[i] = 0;
        
        for (int j = 0; j < i; j++) {
            matrix[i][j] = INF;
        }
    }
}

/*
 * bool compareWeight(const edge_t &lhs, const edge_t &rhs)
 *
 * Helper function for sorting struct objects according to weight attribute
 *
 */
bool compareWeight(const edge_t &lhs, const edge_t &rhs){
    return lhs.weight < rhs.weight;
}

/*
 * std::pair<double, int> Weighted_graph::minimum_spanning_tree() const
 *
 * Run through Kruskal's algorithm using disjoint class to find a minimum
 * spanning tree of the graph. Return the sum of each edge's weight on the tree
 * and total number of edges that the algorithm has tested
 *
 * Parameters:  none
 *
 * Returns:
 *  std::pair<double, int>  pair of data that stores the weight of number of visited edges
 */
std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    
    //create a temp list that's used for sorting edges
    //and two temp variables to store the weight and edge counter
    std::list<edge_t> node_list;
    double weightCounter = 0;
    int edgeCounter = 0;
    
    //Push each edge in the matrix to the list
    for (int i = 0; i < graph_size; i++) {
        for (int j = 0; j < i; j++) {
            if (matrix[i][j] != INF) {
                edge_t temp = {i,j,matrix[i][j]};
                node_list.push_back(temp);
            }
        }
    }
    
    // Sort the list of node_t objects based on weight
    node_list.sort(&compareWeight);
    
    // Using a disjoint set to find the minimum spanning tree
    // Keep adding edges to the tree set when the graph is not connected
    Data_structures::Disjoint_sets::Disjoint_sets tree_set = Data_structures::Disjoint_sets::Disjoint_sets(graph_size);
    
    while (!node_list.empty() && tree_set.disjoint_sets() != 1) {
        int row = node_list.front().v1;
        int column = node_list.front().v2;
        node_list.pop_front();
        
        //The set union function was modified to return true if an union is set
        //and false otherwise. Increment the weight if an edge is added to the mst.
        if(tree_set.set_union(row, column)){
            weightCounter += matrix[row][column];
        }
        
        //Increment the edge counter everytime an edge is tested.
        edgeCounter++;
    }
    
	return std::pair<double, int>( weightCounter, edgeCounter );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}

#endif
