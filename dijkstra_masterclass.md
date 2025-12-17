# Dijkstra's Algorithm: A Comprehensive Masterclass
## For CS1 Students | From Applied Mathematics & Systems Programming Perspectives

---

# Part 1: Mathematical Foundations

## 1.1 The Shortest Path Problem

**Definition:** Given a weighted graph $G = (V, E)$ where:
- $V$ = set of vertices (nodes)
- $E$ = set of edges connecting vertices
- $w: E \rightarrow \mathbb{R}^+$ = weight function (non-negative edge weights)

**Goal:** Find the minimum total weight path from source vertex $s$ to all other vertices.

## 1.2 Why Dijkstra's Algorithm Works: The Greedy Principle

Dijkstra's algorithm relies on the **optimal substructure** property:

> If $P$ is a shortest path from $s$ to $v$ passing through $u$, then the subpath from $s$ to $u$ must also be a shortest path.

**Proof by Contradiction:**
Suppose the subpath $s \rightsquigarrow u$ is not shortest. Then there exists a shorter path $s \rightsquigarrow u'$. Replacing the subpath would give us a shorter total path to $v$, contradicting that $P$ was shortest.

## 1.3 The Relaxation Operation

The core mathematical operation is **edge relaxation**:

$$
d[v] = \min(d[v], d[u] + w(u, v))
$$

Where:
- $d[v]$ = current best known distance to vertex $v$
- $d[u]$ = confirmed shortest distance to vertex $u$  
- $w(u, v)$ = weight of edge from $u$ to $v$

## 1.4 Invariants and Correctness

**Loop Invariant:** At the start of each iteration:
1. For each vertex $v \in S$ (processed set): $d[v] = \delta(s, v)$ (true shortest distance)
2. For each vertex $v \notin S$: $d[v]$ is the shortest path using only vertices in $S$

**Termination:** The algorithm terminates after $|V|$ iterations since one vertex is added to $S$ per iteration.

---

# Part 2: Algorithm Design

## 2.1 Pseudocode

```
DIJKSTRA(G, w, s):
    // Initialization
    for each vertex v ∈ V:
        d[v] ← ∞
        parent[v] ← NULL
    d[s] ← 0
    
    S ← ∅                    // Set of processed vertices
    Q ← V                    // Priority queue of unprocessed vertices
    
    while Q ≠ ∅:
        u ← EXTRACT-MIN(Q)   // Get vertex with minimum d[u]
        S ← S ∪ {u}
        
        for each neighbor v of u:
            if d[u] + w(u,v) < d[v]:     // Relaxation
                d[v] ← d[u] + w(u,v)
                parent[v] ← u
                DECREASE-KEY(Q, v, d[v])
    
    return d[], parent[]
```

## 2.2 Complexity Analysis

| Implementation | EXTRACT-MIN | DECREASE-KEY | Total Time |
|---------------|-------------|--------------|------------|
| Array | $O(V)$ | $O(1)$ | $O(V^2)$ |
| Binary Heap | $O(\log V)$ | $O(\log V)$ | $O((V+E)\log V)$ |
| Fibonacci Heap | $O(\log V)$ amortized | $O(1)$ amortized | $O(V\log V + E)$ |

**For dense graphs** ($E \approx V^2$): Array implementation is optimal
**For sparse graphs** ($E \approx V$): Heap implementation is better

---

# Part 3: C Implementation

## 3.1 Data Structures

```c
/*
 * dijkstra.h - Dijkstra's Algorithm Header
 * Author: Applied Mathematics Student
 * Course: CS1 Presentation
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* Constants */
#define MAX_VERTICES 1000
#define INF INT_MAX

/* 
 * Graph representation using adjacency list
 * More memory efficient for sparse graphs: O(V + E)
 * vs adjacency matrix: O(V²)
 */

/* Edge structure for adjacency list */
typedef struct Edge {
    int destination;      /* Target vertex */
    int weight;           /* Edge weight (must be non-negative!) */
    struct Edge *next;    /* Pointer to next edge in list */
} Edge;

/* Graph structure */
typedef struct Graph {
    int num_vertices;     /* Number of vertices |V| */
    int num_edges;        /* Number of edges |E| */
    Edge **adj_list;      /* Array of adjacency lists */
} Graph;

/* Result structure to hold algorithm output */
typedef struct DijkstraResult {
    int *distance;        /* Shortest distances from source */
    int *parent;          /* Parent pointers for path reconstruction */
    int source;           /* Source vertex */
    int num_vertices;
} DijkstraResult;

/* Function prototypes */
Graph *create_graph(int vertices);
void add_edge(Graph *g, int src, int dest, int weight);
void free_graph(Graph *g);
DijkstraResult *dijkstra(Graph *g, int source);
void print_result(DijkstraResult *result);
void print_path(DijkstraResult *result, int destination);
void free_result(DijkstraResult *result);

#endif /* DIJKSTRA_H */
```

## 3.2 Graph Implementation

```c
/*
 * graph.c - Graph Data Structure Implementation
 */

#include "dijkstra.h"

/*
 * create_graph - Allocates and initializes a new graph
 * @vertices: Number of vertices in the graph
 * 
 * Memory Layout:
 * +----------------+
 * |  Graph struct  |
 * +----------------+
 *        |
 *        v
 * +---+---+---+---+
 * | 0 | 1 | 2 |...| adj_list array (pointers to Edge)
 * +---+---+---+---+
 *   |   |   |
 *   v   v   v
 *  NULL Edge->Edge->NULL  (linked lists)
 *
 * Return: Pointer to new graph, or NULL on failure
 */
Graph *create_graph(int vertices) {
    if (vertices <= 0 || vertices > MAX_VERTICES) {
        fprintf(stderr, "Error: Invalid number of vertices\n");
        return NULL;
    }
    
    /* Allocate graph structure */
    Graph *g = (Graph *)malloc(sizeof(Graph));
    if (g == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for graph\n");
        return NULL;
    }
    
    g->num_vertices = vertices;
    g->num_edges = 0;
    
    /* Allocate array of adjacency list heads */
    g->adj_list = (Edge **)calloc(vertices, sizeof(Edge *));
    if (g->adj_list == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for adjacency list\n");
        free(g);
        return NULL;
    }
    
    /* All lists initialized to NULL by calloc */
    return g;
}

/*
 * add_edge - Adds a directed edge to the graph
 * @g: Pointer to the graph
 * @src: Source vertex (0-indexed)
 * @dest: Destination vertex (0-indexed)
 * @weight: Edge weight (must be >= 0 for Dijkstra)
 *
 * For undirected graphs, call this twice:
 *   add_edge(g, u, v, w);
 *   add_edge(g, v, u, w);
 */
void add_edge(Graph *g, int src, int dest, int weight) {
    /* Input validation */
    if (g == NULL) {
        fprintf(stderr, "Error: NULL graph pointer\n");
        return;
    }
    if (src < 0 || src >= g->num_vertices ||
        dest < 0 || dest >= g->num_vertices) {
        fprintf(stderr, "Error: Vertex index out of bounds\n");
        return;
    }
    if (weight < 0) {
        fprintf(stderr, "Warning: Negative weight! Dijkstra requires non-negative weights\n");
        /* Proceeding anyway, but results will be incorrect */
    }
    
    /* Create new edge */
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    if (new_edge == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for edge\n");
        return;
    }
    
    new_edge->destination = dest;
    new_edge->weight = weight;
    
    /* Insert at head of adjacency list (O(1) insertion) */
    new_edge->next = g->adj_list[src];
    g->adj_list[src] = new_edge;
    
    g->num_edges++;
}

/*
 * free_graph - Deallocates all graph memory
 * @g: Pointer to graph to free
 *
 * CRITICAL: Always free in reverse order of allocation
 * to prevent memory leaks and dangling pointers
 */
void free_graph(Graph *g) {
    if (g == NULL) return;
    
    /* Free each adjacency list */
    for (int i = 0; i < g->num_vertices; i++) {
        Edge *current = g->adj_list[i];
        while (current != NULL) {
            Edge *temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    /* Free the array of list heads */
    free(g->adj_list);
    
    /* Free the graph structure itself */
    free(g);
}
```

## 3.3 Dijkstra's Algorithm - Array Implementation

```c
/*
 * dijkstra.c - Dijkstra's Shortest Path Algorithm
 * 
 * Time Complexity: O(V²) - suitable for dense graphs
 * Space Complexity: O(V)
 */

#include "dijkstra.h"

/*
 * find_min_vertex - Finds unprocessed vertex with minimum distance
 * @distance: Array of current shortest distances
 * @processed: Boolean array marking processed vertices
 * @n: Number of vertices
 *
 * This is the bottleneck: O(V) per call, called V times = O(V²)
 * Can be optimized with priority queue (min-heap) to O(log V)
 *
 * Return: Index of minimum distance unprocessed vertex, or -1 if none
 */
static int find_min_vertex(int *distance, bool *processed, int n) {
    int min_distance = INF;
    int min_vertex = -1;
    
    for (int v = 0; v < n; v++) {
        if (!processed[v] && distance[v] < min_distance) {
            min_distance = distance[v];
            min_vertex = v;
        }
    }
    
    return min_vertex;
}

/*
 * dijkstra - Main algorithm implementation
 * @g: Pointer to the graph
 * @source: Starting vertex for shortest paths
 *
 * Mathematical basis:
 * - Maintains invariant: processed vertices have correct shortest paths
 * - Greedy choice: always process closest unprocessed vertex
 * - Relaxation: d[v] = min(d[v], d[u] + w(u,v))
 *
 * Return: DijkstraResult structure with distances and parent pointers
 */
DijkstraResult *dijkstra(Graph *g, int source) {
    if (g == NULL || source < 0 || source >= g->num_vertices) {
        fprintf(stderr, "Error: Invalid input to dijkstra()\n");
        return NULL;
    }
    
    int n = g->num_vertices;
    
    /* Allocate result structure */
    DijkstraResult *result = (DijkstraResult *)malloc(sizeof(DijkstraResult));
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    
    result->distance = (int *)malloc(n * sizeof(int));
    result->parent = (int *)malloc(n * sizeof(int));
    bool *processed = (bool *)calloc(n, sizeof(bool));
    
    if (result->distance == NULL || result->parent == NULL || processed == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        free(result->distance);
        free(result->parent);
        free(processed);
        free(result);
        return NULL;
    }
    
    result->source = source;
    result->num_vertices = n;
    
    /*
     * INITIALIZATION PHASE
     * d[s] = 0, d[v] = ∞ for all v ≠ s
     * parent[v] = -1 (no parent yet)
     */
    for (int i = 0; i < n; i++) {
        result->distance[i] = INF;
        result->parent[i] = -1;
    }
    result->distance[source] = 0;
    
    /*
     * MAIN LOOP
     * Process all vertices
     */
    for (int count = 0; count < n; count++) {
        /*
         * EXTRACT-MIN: Find vertex u with minimum d[u]
         * among unprocessed vertices
         */
        int u = find_min_vertex(result->distance, processed, n);
        
        /* If no reachable unprocessed vertex, we're done */
        if (u == -1 || result->distance[u] == INF) {
            break;
        }
        
        /* Mark u as processed (add to set S) */
        processed[u] = true;
        
        /*
         * RELAXATION PHASE
         * For each neighbor v of u, check if path through u is shorter
         */
        Edge *edge = g->adj_list[u];
        while (edge != NULL) {
            int v = edge->destination;
            int weight = edge->weight;
            
            /*
             * Relaxation condition:
             * If d[u] + w(u,v) < d[v], we found a shorter path
             * 
             * Note: Check for overflow when d[u] is INF
             */
            if (!processed[v] && 
                result->distance[u] != INF &&
                result->distance[u] + weight < result->distance[v]) {
                
                /* Update distance and parent */
                result->distance[v] = result->distance[u] + weight;
                result->parent[v] = u;
            }
            
            edge = edge->next;
        }
    }
    
    free(processed);
    return result;
}

/*
 * print_result - Displays shortest distances from source
 * @result: Pointer to DijkstraResult structure
 */
void print_result(DijkstraResult *result) {
    if (result == NULL) return;
    
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║   Dijkstra's Algorithm Results         ║\n");
    printf("║   Source Vertex: %d                     ║\n", result->source);
    printf("╠════════════════════════════════════════╣\n");
    printf("║  Vertex  │  Distance  │    Path        ║\n");
    printf("╠══════════╪════════════╪════════════════╣\n");
    
    for (int i = 0; i < result->num_vertices; i++) {
        printf("║    %2d    │", i);
        if (result->distance[i] == INF) {
            printf("     ∞      │");
        } else {
            printf("    %4d    │", result->distance[i]);
        }
        printf(" ");
        print_path(result, i);
        printf("\n");
    }
    printf("╚════════════════════════════════════════╝\n");
}

/*
 * print_path - Recursively prints path from source to destination
 * @result: Pointer to DijkstraResult structure
 * @destination: Target vertex
 *
 * Uses parent pointers to reconstruct path
 * Recursive approach: print path to parent, then print self
 */
void print_path(DijkstraResult *result, int destination) {
    if (result == NULL || destination < 0 || destination >= result->num_vertices) {
        return;
    }
    
    if (result->distance[destination] == INF) {
        printf("No path");
        return;
    }
    
    /* Base case: reached source */
    if (destination == result->source) {
        printf("%d", destination);
        return;
    }
    
    /* Recursive case: print path to parent first */
    print_path(result, result->parent[destination]);
    printf(" → %d", destination);
}

/*
 * free_result - Deallocates result structure memory
 * @result: Pointer to DijkstraResult to free
 */
void free_result(DijkstraResult *result) {
    if (result == NULL) return;
    
    free(result->distance);
    free(result->parent);
    free(result);
}
```

## 3.4 Priority Queue (Min-Heap) Optimized Version

```c
/*
 * dijkstra_heap.c - Optimized Dijkstra with Min-Heap Priority Queue
 * 
 * Time Complexity: O((V + E) log V)
 * Space Complexity: O(V)
 * 
 * Better for sparse graphs where E << V²
 */

#include "dijkstra.h"

/* Min-Heap Node */
typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

/* Min-Heap Structure */
typedef struct MinHeap {
    int size;           /* Current number of elements */
    int capacity;       /* Maximum capacity */
    int *position;      /* position[v] = index of vertex v in heap */
    HeapNode **nodes;   /* Array of heap node pointers */
} MinHeap;

/*
 * Heap Helper Functions
 */
static MinHeap *create_min_heap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->position = (int *)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->nodes = (HeapNode **)malloc(capacity * sizeof(HeapNode *));
    return heap;
}

static HeapNode *create_heap_node(int v, int dist) {
    HeapNode *node = (HeapNode *)malloc(sizeof(HeapNode));
    node->vertex = v;
    node->distance = dist;
    return node;
}

static void swap_heap_nodes(MinHeap *heap, int a, int b) {
    HeapNode *temp = heap->nodes[a];
    heap->nodes[a] = heap->nodes[b];
    heap->nodes[b] = temp;
    
    /* Update position array */
    heap->position[heap->nodes[a]->vertex] = a;
    heap->position[heap->nodes[b]->vertex] = b;
}

/*
 * heapify - Maintains min-heap property (sift down)
 * @heap: Pointer to min-heap
 * @idx: Index to heapify from
 *
 * Time: O(log V)
 */
static void heapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < heap->size && 
        heap->nodes[left]->distance < heap->nodes[smallest]->distance) {
        smallest = left;
    }
    
    if (right < heap->size && 
        heap->nodes[right]->distance < heap->nodes[smallest]->distance) {
        smallest = right;
    }
    
    if (smallest != idx) {
        swap_heap_nodes(heap, smallest, idx);
        heapify(heap, smallest);
    }
}

/*
 * extract_min - Removes and returns minimum element
 * @heap: Pointer to min-heap
 *
 * Time: O(log V)
 * Return: Pointer to minimum node
 */
static HeapNode *extract_min(MinHeap *heap) {
    if (heap->size == 0) return NULL;
    
    /* Root has minimum */
    HeapNode *root = heap->nodes[0];
    
    /* Replace root with last node */
    HeapNode *last = heap->nodes[heap->size - 1];
    heap->nodes[0] = last;
    
    /* Update positions */
    heap->position[root->vertex] = heap->size - 1;
    heap->position[last->vertex] = 0;
    
    heap->size--;
    heapify(heap, 0);
    
    return root;
}

/*
 * decrease_key - Decreases distance value of a vertex
 * @heap: Pointer to min-heap
 * @v: Vertex whose key to decrease
 * @dist: New (smaller) distance value
 *
 * Time: O(log V)
 * This is the key optimization over array implementation!
 */
static void decrease_key(MinHeap *heap, int v, int dist) {
    /* Get index of v in heap */
    int i = heap->position[v];
    
    /* Update distance */
    heap->nodes[i]->distance = dist;
    
    /* Sift up while smaller than parent */
    while (i > 0 && heap->nodes[i]->distance < heap->nodes[(i - 1) / 2]->distance) {
        swap_heap_nodes(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

static bool is_in_heap(MinHeap *heap, int v) {
    return heap->position[v] < heap->size;
}

static void free_min_heap(MinHeap *heap) {
    for (int i = 0; i < heap->capacity; i++) {
        if (heap->nodes[i]) free(heap->nodes[i]);
    }
    free(heap->nodes);
    free(heap->position);
    free(heap);
}

/*
 * dijkstra_heap - Heap-optimized Dijkstra's algorithm
 * @g: Pointer to graph
 * @source: Source vertex
 *
 * Return: DijkstraResult with shortest paths
 */
DijkstraResult *dijkstra_heap(Graph *g, int source) {
    int n = g->num_vertices;
    
    /* Allocate result */
    DijkstraResult *result = (DijkstraResult *)malloc(sizeof(DijkstraResult));
    result->distance = (int *)malloc(n * sizeof(int));
    result->parent = (int *)malloc(n * sizeof(int));
    result->source = source;
    result->num_vertices = n;
    
    /* Create min-heap */
    MinHeap *heap = create_min_heap(n);
    
    /* Initialize */
    for (int v = 0; v < n; v++) {
        result->distance[v] = INF;
        result->parent[v] = -1;
        heap->nodes[v] = create_heap_node(v, result->distance[v]);
        heap->position[v] = v;
    }
    
    /* Source has distance 0 */
    result->distance[source] = 0;
    decrease_key(heap, source, 0);
    heap->size = n;
    
    /* Main loop */
    while (heap->size > 0) {
        /* Extract vertex with minimum distance */
        HeapNode *min_node = extract_min(heap);
        int u = min_node->vertex;
        
        /* Process all neighbors */
        Edge *edge = g->adj_list[u];
        while (edge != NULL) {
            int v = edge->destination;
            
            /* If v is still in heap and shorter path found */
            if (is_in_heap(heap, v) && 
                result->distance[u] != INF &&
                result->distance[u] + edge->weight < result->distance[v]) {
                
                result->distance[v] = result->distance[u] + edge->weight;
                result->parent[v] = u;
                decrease_key(heap, v, result->distance[v]);
            }
            edge = edge->next;
        }
    }
    
    free_min_heap(heap);
    return result;
}
```

## 3.5 Main Program - Demo and Testing

```c
/*
 * main.c - Dijkstra's Algorithm Demonstration
 * 
 * This program demonstrates the algorithm with a sample graph
 * and verifies correctness with known examples.
 */

#include "dijkstra.h"

/*
 * create_sample_graph - Creates a test graph
 *
 * Graph visualization:
 *
 *        (1)
 *       / | \
 *      4  |  2
 *     /   |   \
 *   (0)   1   (2)
 *     \   |   /
 *      2  |  3
 *       \ | /
 *        (3)---5---(4)
 *
 * Adjacency representation (directed edges):
 * 0 -> 1 (4), 0 -> 3 (2)
 * 1 -> 0 (4), 1 -> 2 (2), 1 -> 3 (1)
 * 2 -> 1 (2), 2 -> 3 (3), 2 -> 4 (6)
 * 3 -> 0 (2), 3 -> 1 (1), 3 -> 2 (3), 3 -> 4 (5)
 * 4 -> 2 (6), 4 -> 3 (5)
 */
Graph *create_sample_graph(void) {
    Graph *g = create_graph(5);
    
    /* Make it undirected by adding edges both ways */
    add_edge(g, 0, 1, 4); add_edge(g, 1, 0, 4);
    add_edge(g, 0, 3, 2); add_edge(g, 3, 0, 2);
    add_edge(g, 1, 2, 2); add_edge(g, 2, 1, 2);
    add_edge(g, 1, 3, 1); add_edge(g, 3, 1, 1);
    add_edge(g, 2, 3, 3); add_edge(g, 3, 2, 3);
    add_edge(g, 2, 4, 6); add_edge(g, 4, 2, 6);
    add_edge(g, 3, 4, 5); add_edge(g, 4, 3, 5);
    
    return g;
}

/*
 * print_graph - Displays graph structure
 * @g: Pointer to graph
 */
void print_graph(Graph *g) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║         Graph Structure                ║\n");
    printf("║   Vertices: %d    Edges: %d             ║\n", 
           g->num_vertices, g->num_edges);
    printf("╠════════════════════════════════════════╣\n");
    
    for (int i = 0; i < g->num_vertices; i++) {
        printf("║ Vertex %d: ", i);
        Edge *e = g->adj_list[i];
        while (e != NULL) {
            printf("→%d(%d) ", e->destination, e->weight);
            e = e->next;
        }
        printf("\n");
    }
    printf("╚════════════════════════════════════════╝\n");
}

int main(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                                                          ║\n");
    printf("║       DIJKSTRA'S SHORTEST PATH ALGORITHM                 ║\n");
    printf("║       CS1 Presentation - Applied Mathematics             ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    /* Create and display sample graph */
    Graph *g = create_sample_graph();
    print_graph(g);
    
    /* Run Dijkstra from vertex 0 */
    printf("\n>>> Running Dijkstra's Algorithm from vertex 0...\n");
    DijkstraResult *result = dijkstra(g, 0);
    
    if (result != NULL) {
        print_result(result);
        
        /* Verify results */
        printf("\n>>> Verification:\n");
        printf("    Expected distances from vertex 0:\n");
        printf("    Vertex 0: 0 (source)\n");
        printf("    Vertex 1: 3 (0→3→1)\n");
        printf("    Vertex 2: 5 (0→3→1→2)\n");
        printf("    Vertex 3: 2 (0→3)\n");
        printf("    Vertex 4: 7 (0→3→4)\n");
        
        /* Check correctness */
        int expected[] = {0, 3, 5, 2, 7};
        bool correct = true;
        for (int i = 0; i < 5; i++) {
            if (result->distance[i] != expected[i]) {
                correct = false;
                printf("    ❌ Mismatch at vertex %d: got %d, expected %d\n",
                       i, result->distance[i], expected[i]);
            }
        }
        if (correct) {
            printf("    ✓ All distances correct!\n");
        }
        
        free_result(result);
    }
    
    /* Test from different source */
    printf("\n>>> Running from vertex 2...\n");
    result = dijkstra(g, 2);
    if (result != NULL) {
        print_result(result);
        free_result(result);
    }
    
    /* Clean up */
    free_graph(g);
    
    printf("\n>>> Memory freed. Program complete.\n\n");
    
    return 0;
}
```

---

# Part 4: Step-by-Step Execution Trace

## 4.1 Visual Walkthrough

Let's trace the algorithm on our sample graph starting from vertex 0:

```
Initial State:
┌─────────┬─────────┬─────────┬─────────┬─────────┐
│ Vertex  │    0    │    1    │    2    │    3    │    4    │
├─────────┼─────────┼─────────┼─────────┼─────────┤
│ d[]     │    0    │    ∞    │    ∞    │    ∞    │    ∞    │
│ parent  │   -1    │   -1    │   -1    │   -1    │   -1    │
│ processed│  false │  false  │  false  │  false  │  false  │
└─────────┴─────────┴─────────┴─────────┴─────────┘
```

**Iteration 1:** Extract min = vertex 0 (distance 0)
- Relax edge (0,1): d[1] = min(∞, 0+4) = 4, parent[1] = 0
- Relax edge (0,3): d[3] = min(∞, 0+2) = 2, parent[3] = 0

```
After Iteration 1:
┌─────────┬─────────┬─────────┬─────────┬─────────┐
│ d[]     │    0    │    4    │    ∞    │    2    │    ∞    │
│ parent  │   -1    │    0    │   -1    │    0    │   -1    │
│ processed│  TRUE  │  false  │  false  │  false  │  false  │
└─────────┴─────────┴─────────┴─────────┴─────────┘
```

**Iteration 2:** Extract min = vertex 3 (distance 2)
- Relax edge (3,1): d[1] = min(4, 2+1) = 3, parent[1] = 3 ✓ (improved!)
- Relax edge (3,2): d[2] = min(∞, 2+3) = 5, parent[2] = 3
- Relax edge (3,4): d[4] = min(∞, 2+5) = 7, parent[4] = 3

```
After Iteration 2:
┌─────────┬─────────┬─────────┬─────────┬─────────┐
│ d[]     │    0    │    3    │    5    │    2    │    7    │
│ parent  │   -1    │    3    │    3    │    0    │    3    │
│ processed│  TRUE  │  false  │  false  │  TRUE  │  false  │
└─────────┴─────────┴─────────┴─────────┴─────────┘
```

**Iteration 3:** Extract min = vertex 1 (distance 3)
- Relax edge (1,2): d[2] = min(5, 3+2) = 5 (no improvement)

**Iteration 4:** Extract min = vertex 2 (distance 5)
- Relax edge (2,4): d[4] = min(7, 5+6) = 7 (no improvement)

**Iteration 5:** Extract min = vertex 4 (distance 7)
- No unprocessed neighbors

**Final Result:**
```
┌─────────┬─────────┬─────────┬─────────┬─────────┐
│ Vertex  │    0    │    1    │    2    │    3    │    4    │
├─────────┼─────────┼─────────┼─────────┼─────────┤
│ d[]     │    0    │    3    │    5    │    2    │    7    │
│ path    │    0    │  0→3→1  │ 0→3→1→2 │   0→3   │  0→3→4  │
└─────────┴─────────┴─────────┴─────────┴─────────┘
```

---

# Part 5: Makefile for Compilation

```makefile
# Makefile for Dijkstra's Algorithm Project
# 
# Usage:
#   make          - Build the project
#   make debug    - Build with debug symbols
#   make clean    - Remove build artifacts
#   make run      - Build and run

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O2

SRC = main.c graph.c dijkstra.c
OBJ = $(SRC:.c=.o)
TARGET = dijkstra

# Default target: release build
all: CFLAGS += $(RELEASE_FLAGS)
all: $(TARGET)

# Debug build
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile
%.o: %.c dijkstra.h
	$(CC) $(CFLAGS) -c $< -o $@

# Run
run: all
	./$(TARGET)

# Clean
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all debug clean run
```

---

# Part 6: Important Considerations

## 6.1 When to Use Dijkstra's Algorithm

✅ **Use when:**
- All edge weights are non-negative
- You need single-source shortest paths
- Graph is relatively dense (use array) or sparse (use heap)

❌ **Don't use when:**
- Graph has negative edge weights → Use **Bellman-Ford** instead
- You need all-pairs shortest paths → Consider **Floyd-Warshall**
- Graph is unweighted → Use **BFS** (simpler and faster)

## 6.2 Common Pitfalls in C Implementation

1. **Integer Overflow:** When adding distances, check for `INF`:
   ```c
   if (distance[u] != INF && distance[u] + weight < distance[v])
   ```

2. **Memory Leaks:** Always free in reverse order of allocation

3. **Off-by-One Errors:** Be consistent with 0-indexed vs 1-indexed vertices

4. **Uninitialized Memory:** Use `calloc` or explicitly initialize arrays

## 6.3 Extensions and Variations

- **A\* Algorithm:** Add heuristic for goal-directed search
- **Bidirectional Dijkstra:** Search from both source and target
- **Parallel Dijkstra:** Process independent vertices concurrently

---

# Part 7: Exercises for Students

1. **Trace Exercise:** Run Dijkstra on a 6-vertex graph by hand

2. **Coding Exercise:** Modify the code to find the shortest path between two specific vertices (not all vertices)

3. **Analysis Exercise:** Compare the performance of array vs heap implementation on graphs of different densities

4. **Extension Exercise:** Implement path reconstruction that returns the actual path as an array

---

# References

1. Dijkstra, E.W. (1959). "A note on two problems in connexion with graphs". *Numerische Mathematik*. 1: 269–271.

2. Cormen, T.H., et al. *Introduction to Algorithms* (3rd ed.). MIT Press.

3. Sedgewick, R., Wayne, K. *Algorithms* (4th ed.). Addison-Wesley.

---

*Document prepared for CS1 Presentation*
*Applied Mathematics Department*
