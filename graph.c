/*
 * graph.c - Graph Data Structure Implementation
 * 
 * This file implements the graph abstraction using adjacency lists.
 * 
 * Key Design Decisions:
 * 1. Adjacency list for space efficiency on sparse graphs
 * 2. Linked list for edge storage (simple, O(1) insertion)
 * 3. Defensive programming with input validation
 * 4. Careful memory management to prevent leaks
 */

#include "dijkstra.h"

/*
 * create_graph - Allocates and initializes a new graph
 * 
 * @vertices: Number of vertices in the graph
 * 
 * Algorithm:
 * 1. Validate input (positive, within bounds)
 * 2. Allocate Graph structure
 * 3. Allocate array of Edge pointers
 * 4. Initialize all lists to NULL (empty)
 * 
 * Time Complexity: O(V) - must initialize V list heads
 * Space Complexity: O(V) - array of V pointers
 * 
 * Return: Pointer to newly created graph, or NULL on failure
 * 
 * IMPORTANT: Caller is responsible for calling free_graph() later!
 */
Graph *create_graph(int vertices) {
    /* Input validation */
    if (vertices <= 0) {
        fprintf(stderr, "Error: Number of vertices must be positive (got %d)\n", vertices);
        return NULL;
    }
    if (vertices > MAX_VERTICES) {
        fprintf(stderr, "Error: Too many vertices (%d > %d max)\n", vertices, MAX_VERTICES);
        return NULL;
    }
    
    /* Allocate the main graph structure */
    Graph *g = (Graph *)malloc(sizeof(Graph));
    if (g == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for graph structure\n");
        return NULL;
    }
    
    /* Initialize fields */
    g->num_vertices = vertices;
    g->num_edges = 0;
    
    /*
     * Allocate array of adjacency list heads
     * Using calloc to initialize all pointers to NULL
     * 
     * calloc(n, size) vs malloc(n * size):
     *   - calloc zero-initializes memory
     *   - calloc checks for overflow in n * size
     *   - malloc may be slightly faster but requires explicit initialization
     */
    g->adj_list = (Edge **)calloc(vertices, sizeof(Edge *));
    if (g->adj_list == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for adjacency lists\n");
        free(g);  /* Clean up already allocated memory */
        return NULL;
    }
    
    /* All adj_list[i] are NULL thanks to calloc */
    return g;
}

/*
 * add_edge - Adds a directed edge to the graph
 * 
 * @g:      Pointer to the graph
 * @src:    Source vertex index (0 to V-1)
 * @dest:   Destination vertex index (0 to V-1)
 * @weight: Edge weight (should be >= 0 for Dijkstra)
 * 
 * Creates edge: src ──(weight)──> dest
 * 
 * Implementation Note:
 * New edges are inserted at the HEAD of the adjacency list.
 * This gives O(1) insertion but edges appear in reverse order of insertion.
 * 
 * Time Complexity: O(1)
 */
void add_edge(Graph *g, int src, int dest, int weight) {
    /* Defensive programming: validate all inputs */
    if (g == NULL) {
        fprintf(stderr, "Error: NULL graph pointer in add_edge()\n");
        return;
    }
    
    if (src < 0 || src >= g->num_vertices) {
        fprintf(stderr, "Error: Source vertex %d out of range [0, %d)\n", 
                src, g->num_vertices);
        return;
    }
    
    if (dest < 0 || dest >= g->num_vertices) {
        fprintf(stderr, "Error: Destination vertex %d out of range [0, %d)\n", 
                dest, g->num_vertices);
        return;
    }
    
    /*
     * Warning for negative weights
     * Dijkstra's algorithm REQUIRES non-negative weights!
     * The algorithm will still run but produce incorrect results.
     */
    if (weight < 0) {
        fprintf(stderr, "WARNING: Negative edge weight %d on edge (%d, %d)\n", 
                weight, src, dest);
        fprintf(stderr, "         Dijkstra's algorithm requires non-negative weights!\n");
        fprintf(stderr, "         Consider using Bellman-Ford instead.\n");
    }
    
    /* Allocate new edge node */
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    if (new_edge == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for edge\n");
        return;
    }
    
    /* Initialize edge data */
    new_edge->destination = dest;
    new_edge->weight = weight;
    
    /*
     * Insert at head of list
     * 
     * Before: adj_list[src] -> A -> B -> NULL
     * After:  adj_list[src] -> new_edge -> A -> B -> NULL
     */
    new_edge->next = g->adj_list[src];
    g->adj_list[src] = new_edge;
    
    g->num_edges++;
}

/*
 * add_undirected_edge - Adds an undirected edge (two directed edges)
 * 
 * @g:      Pointer to the graph
 * @v1:     First vertex
 * @v2:     Second vertex
 * @weight: Edge weight
 * 
 * Creates: v1 ←──(weight)──→ v2
 * 
 * Convenience function for undirected graphs.
 * Internally calls add_edge twice.
 */
void add_undirected_edge(Graph *g, int v1, int v2, int weight) {
    add_edge(g, v1, v2, weight);
    add_edge(g, v2, v1, weight);
}

/*
 * print_graph - Displays the graph structure
 * 
 * @g: Pointer to the graph
 * 
 * Output format shows each vertex and its outgoing edges
 * with weights in parentheses.
 */
void print_graph(Graph *g) {
    if (g == NULL) {
        printf("(NULL graph)\n");
        return;
    }
    
    printf("\n");
    printf("┌─────────────────────────────────────────┐\n");
    printf("│           GRAPH STRUCTURE               │\n");
    printf("│  Vertices: %-4d    Edges: %-4d          │\n", 
           g->num_vertices, g->num_edges);
    printf("├─────────────────────────────────────────┤\n");
    
    for (int v = 0; v < g->num_vertices; v++) {
        printf("│ %2d: ", v);
        
        Edge *e = g->adj_list[v];
        if (e == NULL) {
            printf("(no outgoing edges)");
        }
        
        int edge_count = 0;
        while (e != NULL) {
            if (edge_count > 0) printf(", ");
            printf("→%d(w=%d)", e->destination, e->weight);
            e = e->next;
            edge_count++;
        }
        printf("\n");
    }
    
    printf("└─────────────────────────────────────────┘\n");
}

/*
 * free_graph - Deallocates all memory used by the graph
 * 
 * @g: Pointer to the graph to free
 * 
 * Memory Deallocation Order (LIFO - Last In First Out):
 * 1. Free all Edge nodes in each adjacency list
 * 2. Free the adj_list array
 * 3. Free the Graph structure
 * 
 * This order is CRITICAL to prevent:
 * - Memory leaks (not freeing allocated memory)
 * - Use-after-free bugs (accessing freed memory)
 * - Double-free errors (freeing same memory twice)
 * 
 * Time Complexity: O(V + E) - must visit all edges
 */
void free_graph(Graph *g) {
    if (g == NULL) return;
    
    /* First, free all edge nodes */
    for (int v = 0; v < g->num_vertices; v++) {
        Edge *current = g->adj_list[v];
        
        while (current != NULL) {
            Edge *temp = current;      /* Save pointer to current */
            current = current->next;    /* Move to next BEFORE freeing */
            free(temp);                 /* Now safe to free */
        }
    }
    
    /* Then free the array of list heads */
    free(g->adj_list);
    
    /* Finally free the graph structure itself */
    free(g);
}
