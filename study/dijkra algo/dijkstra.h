/*
 * dijkstra.h - Dijkstra's Shortest Path Algorithm Header
 * 
 * Author: Applied Mathematics Student
 * Course: CS1 Presentation
 * 
 * This header defines the data structures and function prototypes
 * for implementing Dijkstra's algorithm in C.
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/*
 * CONSTANTS
 * ---------
 * MAX_VERTICES: Upper bound on graph size (memory consideration)
 * INF: Represents infinity (unreachable vertices)
 *      Using INT_MAX for mathematical correctness
 */
#define MAX_VERTICES 1000
#define INF INT_MAX

/*
 * GRAPH REPRESENTATION: Adjacency List
 * ------------------------------------
 * Why adjacency list over adjacency matrix?
 * 
 * Adjacency Matrix:
 *   - Space: O(V²) always
 *   - Edge lookup: O(1)
 *   - Iterate neighbors: O(V)
 * 
 * Adjacency List:
 *   - Space: O(V + E)
 *   - Edge lookup: O(degree)
 *   - Iterate neighbors: O(degree)
 * 
 * For sparse graphs (E << V²), adjacency list wins!
 */

/*
 * Edge - Represents a directed edge in the graph
 * 
 * Members:
 *   destination: Target vertex index
 *   weight:      Edge weight (must be >= 0 for Dijkstra)
 *   next:        Pointer to next edge (linked list)
 */
typedef struct Edge {
    int destination;
    int weight;
    struct Edge *next;
} Edge;

/*
 * Graph - Main graph data structure
 * 
 * Members:
 *   num_vertices: |V| - number of vertices
 *   num_edges:    |E| - number of edges
 *   adj_list:     Array of linked lists (one per vertex)
 * 
 * Memory Layout:
 * 
 *   Graph struct          adj_list array         Edge lists
 *   ┌──────────────┐      ┌───┐
 *   │ num_vertices │      │ 0 │──→ Edge → Edge → NULL
 *   │ num_edges    │      ├───┤
 *   │ adj_list ────┼─────→│ 1 │──→ Edge → NULL
 *   └──────────────┘      ├───┤
 *                         │ 2 │──→ NULL
 *                         └───┘
 */
typedef struct Graph {
    int num_vertices;
    int num_edges;
    Edge **adj_list;
} Graph;

/*
 * DijkstraResult - Output of the algorithm
 * 
 * Members:
 *   distance:     Array of shortest distances from source
 *   parent:       Array of parent vertices for path reconstruction
 *   source:       The source vertex used
 *   num_vertices: Number of vertices in result
 * 
 * Path Reconstruction:
 *   To find path from source to v:
 *     1. Start at v
 *     2. Follow parent[v] → parent[parent[v]] → ... → source
 *     3. Reverse to get path from source to v
 */
typedef struct DijkstraResult {
    int *distance;
    int *parent;
    int source;
    int num_vertices;
} DijkstraResult;

/*
 * FUNCTION PROTOTYPES
 * -------------------
 */

/* Graph Creation and Management */
Graph *create_graph(int vertices);
void add_edge(Graph *g, int src, int dest, int weight);
void add_undirected_edge(Graph *g, int v1, int v2, int weight);
void print_graph(Graph *g);
void free_graph(Graph *g);

/* Dijkstra's Algorithm */
DijkstraResult *dijkstra(Graph *g, int source);
DijkstraResult *dijkstra_heap(Graph *g, int source);

/* Result Display and Management */
void print_result(DijkstraResult *result);
void print_path(DijkstraResult *result, int destination);
void print_path_recursive(DijkstraResult *result, int destination);
int *get_path(DijkstraResult *result, int destination, int *path_length);
void free_result(DijkstraResult *result);

#endif /* DIJKSTRA_H */
