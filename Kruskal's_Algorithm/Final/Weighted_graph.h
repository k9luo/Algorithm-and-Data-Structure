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
 * Header File Name:                     Weighted_graph
 * File:                                 Weighted_graph.h
 *
 * Kai Luo
 * 2015-03-31
 * Version 1.0                           Initial implementation.
 *
 * This class implements a weighted graph and finds its minimum spanning tree.
 *
 * No pre- or postconditions.
 *
 * Private Member variables:
 *
 *  static const double INF              Positive infinity
 *
 *  int dimension                        The total number of vertices
 *
 *  int edge_num                         The total number of edges
 *
 *  double **matrix                      The 2D lower triangular matrix stores the weight of each edge and corresponding vertices
 *
 *  int * vertex_deg                     The 1D array stores the degree of vertex
 *
 *
 * Private Member functions:
 *
 *  Weighted_graph( Weighted_graph const & )
 *
 *  Weighted_graph &operator=( Weighted_graph )
 *
 *
 * Member Functions (Constructor):
 *  Weighted_graph ( int = 10 )         Takes an argument n with a default value 10 and creates a lower triangular matrix
 *
 * Member Functions (Destructor):
 *  ~Weighted_graph()                   Deallocates memory which is assigned by the constructor
 *
 * Member Functions (Accessors):
 *  int degree(int) const               Returns the degree of the vertex passed into the argument
 *
 *  int edge_count() const              Returns the number of edges
 *
 *  std::pair<double,int> minimum_spanning_tree() const     Uses Kruskal's algorithm to find the minimum spanning tree of the given graph. Returns the the weight of the minimum spanning tree and the number of edges being tested
 *
 *
 * Member Functions (Mutators):
 *  bool insert( int, int, double )     Inserts an edge into the graph
 *
 *  bool erase_edge( int, int )         Erases an edge in the graph
 *
 *  void clear_edges()                  Removes all edges in the graph
 *
 *
 * Bugs:        Unknown
 * Todo:        Reduces runtime optimizes algorithms
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace Data_structures;

class Weighted_graph {
private:
    static const double INF;
    
    // Do not implement these functions!
    // By making these private and not implementing them, any attempt
    // to make copies or assignments will result in errors
    Weighted_graph( Weighted_graph const & );
    Weighted_graph &operator=( Weighted_graph );
    
    // your choice
    int dimension;
    int edge_num;
    double **matrix;
    int * vertex_deg;
    
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
 * Constructor
 *
 * Creates a lower triangle matrix to store the weight of each edge and the corresponding vertices and an array to store the degree of each vertex
 *
 * Parameters:
 *  int n              The number of vertices in the graph
 *
 * Bugs:
 * Todo:
 * References:
 */
Weighted_graph::Weighted_graph( int n ):
dimension( n ),
edge_num(0),
matrix( new double * [dimension] ),
vertex_deg( new int [dimension])
{
    // Initiates only one vertex in the graph if the initial vertex number if smaller than 1
    if ( dimension < 1 ) {
        dimension = 1;
    }
    
    // Initiates the weight of all edges to infinity and degrees of all vertices to 0
    for ( int i = 0; i < dimension; ++i ) {
        matrix[i] = new double[i+1];
        vertex_deg[i] = 0;

        for ( int j = 0; j <= i; ++j ) {
            matrix[i][j] = INF;
        }
    }
}

/*
 * Destructor
 *
 * Deletes the memory allocated for a triangular matrix and an array
 *
 * Bugs:
 * Todo:
 * References:
 */
Weighted_graph::~Weighted_graph() {
    
    // Deletes all entries stored the weight of edges
    for ( int i = 0; i < dimension; ++i ) {
        delete [] matrix[i];
    }
    
    delete [] matrix;
    delete [] vertex_deg;
}
/*
 * Degree
 *
 * Returns the degree of the vertex i in the graph
 *
 * Parameters:
 *  int i      The vertex to be checked
 *
 * Returns:
 *  The number of edges connected to the vertex i in the graph
 *
 * Bugs:
 * Todo:
 * Reference:
 */
int Weighted_graph::degree( int i ) const {
    
    // Throws an illegal argument if i is out of range
    if ( i < 0 || i > dimension-1 ) {
        throw illegal_argument();
    }
    
    return vertex_deg[i];
}

/*
 * Edge_count
 *
 * Returns the total number of edges in the graph
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  The total number of edges in the graph
 *
 * Bugs:
 * Todo:
 * Reference:
 */
int Weighted_graph::edge_count() const {
    return edge_num;
}

/*
 * Insert_edge
 *
 * Throws an illegal argument if i or j are out of the range or if the weight w is less than or equal to zero
 * Inserts a new edge from vertex i to vertex j or, if the edge already exists, updates the weight and returns true
 * Returns false if i equals j and are in the graph
 *
 * Parameters:
 *  int i, int j     Vertices to be connected
 *  double w         The weight of the edge
 *
 * Returns:
 *  Returns false if i equals j and true otherwise
 *
 * Bugs:
 * Todo:
 * Reference:
 */
bool Weighted_graph::insert_edge( int i, int j, double w ) {
    
    // Throws an illegal argument if the arguments are invalid
    if ( i < 0 || i > dimension-1 || j < 0 || j > dimension-1 || w <= 0 ) {
        throw illegal_argument();
    }
    
    // Returns false if it is forming an edge if the corresponding vertices are same
    if ( i == j ) {
        return false;
    }
    
    // Makes sure the first argument is always larger than the second argument
    if ( i < j ) {
        std::swap( i, j );
    }
    
    // Updates the weight of the edge and increments vertex counters and edge counter if forming a new edge
    if ( matrix[i][j] == INF ) {
        matrix[i][j] = w;
        ++vertex_deg[i];
        ++vertex_deg[j];
        ++edge_num;
    }
    
    // Updates the weight of the edge if it is an existing edge
    matrix[i][j] = w;
    
    return true;
}

/*
 * Erase_edge
 *
 * Erases the edge between vertices i and j
 * Throws an illegal argument if parameters are invalid
 *
 * Parameters:
 *  int i, int j     Corresponding vertices at the end of the edge
 *
 * Returns:
 *  Returns true if the edge is removed and false otherwise
 *
 * Bugs:
 * Todo:
 * Reference:
 */
bool Weighted_graph::erase_edge( int i, int j ){
    
    // Throws an illegal argument if parameters are invalid
    if ( i < 0 || i > dimension-1 || j < 0 || j > dimension-1 ) {
        throw illegal_argument();
    }
    
    // Swap arguments to update the lower triangular matrix
    if ( i < j ) {
        std::swap( i, j );
    }
    
    // Returns true if removing en edge or i equals j and false otherwise
    // Updates related variables if removing an edge
    if ( matrix[i][j] != INF || i == j ) {
        matrix[i][j] = INF;
        --vertex_deg[i];
        --vertex_deg[j];
        --edge_num;
        return true;
    } else {
        return false;
    }
}

/*
 * Clear_edges
 *
 * Deletes all edges in the graph and updates all related variables
 *
 * No pre- or postconditions and no parameters.
 *
 * Bugs:
 * Todo:
 * Reference:
 */
void Weighted_graph::clear_edges() {
    for ( int i = 0; i < dimension; i++ ){
        if ( degree(i) != 0 ) {
            for ( int j = 0; j <= i; ++j ) {
                if ( matrix[i][j] != INF ) {
                    matrix[i][j] = INF;
                }
            }
            vertex_deg[i] = 0;
        }
    }
    
    edge_num = 0;
}

/*
 * Sort_edge_set
 *
 * Compare function
 *
 * Bugs:
 * Todo:
 * Reference:
 */
bool sort_edge_set ( const std::pair<double, std::pair<int, int> >& lhs, const std::pair<double, std::pair<int, int> >& rhs){
    return lhs.first < rhs.first;
}

/*
 * Pair
 *
 * Implements Kruskal's algorithm with disjoint class to find the minimum spanning tree
 * Returns the total weight of the minimum spanning tree and the number of edges being tested
 *
 * No pre- or postconditions and no parameters.
 *
 * Returns:
 *  Returns the total weight of the minimum spanning tree and the number of edges being tested
 *
 * Bugs:
 * Todo:
 * Reference:
 */
std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    //int k = 0;
    double weight_sum = 0.0;
    int edge_num = 0;
    
    // Initiates a disjoint set
    // Uses disjoint sets to form a minimum spanning tree
    Disjoint_sets dset( dimension );
    
    // Initiates a vector stores each edge with its weight and vertices
    std::vector<std::pair<double, std::pair<int, int> > > edge_set;
    
    // Iterates through the lower triangular matrix and pushes all edges into edge_set
    for ( int i = 0; i < dimension; i++ ) {
        if ( degree(i) != 0 ) {
            for ( int j = 0; j <= i; ++j ) {
                if ( matrix[i][j] != INF ) {
                    edge_set.push_back( std::make_pair(matrix[i][j],std::make_pair(i, j)) );
                }
            }
        }
    }
    
    // Sorts all edges in the edge set by weight in an ascending sort
    std::sort(edge_set.begin(), edge_set.end(), sort_edge_set);
    
    // Iterates through the lower triangular
    for ( int i = 0; i < edge_count(); i++ ) {
        
        // Break the loop if the minimum spanning tree is found
        if ( dset.disjoint_sets() == 1 ) {
            break;
        }
        
        // If adding an edge creates a cycle, then only increment the number of edges being tested
        // Otherwise, add the edge to the minimum spanning tree and increment the sum of the weight and the number of edges being tested
        if ( dset.find(edge_set[i].second.first) == dset.find(edge_set[i].second.second) ){
            ++edge_num;
        } else {
            dset.set_union( edge_set[i].second.first, edge_set[i].second.second );
            weight_sum += edge_set[i].first;
            ++edge_num;
        }
    }
    
    /*std::vector< std::vector<double> > edge_set;
    

    edge_set.resize( edge_count() );
    
    for ( int i = 0; i < edge_count(); ++i ) {
        edge_set[i].resize(3);
    }
    
    for ( int i = 0; i < dimension; i++) {
        if ( degree(i) != 0 ) {
            for ( int j = 0; j <= i; ++j ) {
                if ( matrix[i][j] != INF ) {
                    edge_set[k][0] = matrix[i][j]; // weight
                    edge_set[k][1] = i; // vertex1
                    edge_set[k][2] = j; // vertex2
                    k++;
                }
            }
        }
    }
    
    struct myfunction {
        bool operator()(const std::vector<double>& lhs,
                        const std::vector<double>& rhs) const
        {
            return lhs[0] < rhs[0];
        }
    }sort_edge_set;
    
    std::sort ( edge_set.begin(), edge_set.end(), sort_edge_set );*/
    
    /*for ( int i = 0; i < edge_count(); i++ ) {
        std::cout << "edge set: " << edge_set[i][1] << " " << edge_set[i][2] << " " << edge_set[i][0] << std::endl;
    }*/

    /*for ( int i = 0; i < edge_count(); i++ ) {
        if ( dset.disjoint_sets() == 1 ) {
            break;
        }
        
        if ( dset.find(edge_set[i][1]) == dset.find(edge_set[i][2]) ){
            ++edge_num;
        }
        
        if ( dset.find(edge_set[i][1]) != dset.find(edge_set[i][2]) ) {
            dset.set_union( edge_set[i][1], edge_set[i][2] );
            weight_sum += edge_set[i][0];
            ++edge_num;
        }
        
        //std::cout << "weight_sum is " << weight_sum << std::endl;
        //std::cout << "edge_num is " << edge_num << std::endl;
    }*/
    
    return std::pair<double, int>( weight_sum, edge_num );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    // Your implementation
    
    return out;
}

#endif
