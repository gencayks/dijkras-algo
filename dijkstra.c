/*
 * dijkstra.c - Dijkstra's Shortest Path Algorithm Implementation
 * 
 * This file contains the core algorithm with two implementations:
 * 1. Array-based: O(V²) - simple, good for dense graphs
 * 2. Heap-based:  O((V+E)logV) - optimized for sparse graphs
 * 
 * Mathematical Foundation:
 * -------------------------
 * Dijkstra's algorithm solves the Single-Source Shortest Path (SSSP) problem
 * for graphs with non-negative edge weights.
 * 
 * Key Insight: If we always process the unvisited vertex with minimum distance,
 * that distance must be final (optimal substructure + greedy choice).
 * 
 * Core Operation - Relaxation:
 *   d[v] = min(d[v], d[u] + w(u,v))
 * 
 * This operation "relaxes" the distance estimate to v by checking if
 * going through u provides a shorter path.
 */

#include "dijkstra.h"

/*============================================================================
 * ARRAY-BASED IMPLEMENTATION
 * 
 * Time Complexity:  O(V²)
 * Space Complexity: O(V)
 * 
 * Best for: Dense graphs where E ≈ V²
 *===========================================================================*/

/*
 * find_min_vertex - Finds unprocessed vertex with minimum distance
 * 
 * @distance:  Array of current shortest distances
 * @processed: Boolean array marking processed vertices
 * @n:         Number of vertices
 * 
 * This is the BOTTLENECK of the array implementation!
 * Called V times, each call is O(V), total: O(V²)
 * 
 * With a min-heap, this becomes O(log V), reducing total to O((V+E)log V)
 * 
 * Return: Index of minimum distance unprocessed vertex, or -1 if none found
 */
static int find_min_vertex(int *distance, bool *processed, int n) {
    int min_distance = INF;
    int min_vertex = -1;
    
    for (int v = 0; v < n; v++) {
        /* Only consider unprocessed vertices */
        if (!processed[v] && distance[v] < min_distance) {
            min_distance = distance[v];
            min_vertex = v;
        }
    }
    
    return min_vertex;
}

/*
 * dijkstra - Main algorithm implementation (array-based)
 * 
 * @g:      Pointer to the graph
 * @source: Starting vertex for shortest paths
 * 
 * Algorithm Phases:
 * -----------------
 * 1. INITIALIZATION: d[source] = 0, d[v] = ∞ for all v ≠ source
 * 2. MAIN LOOP: Repeat V times:
 *    a. EXTRACT-MIN: Find unprocessed vertex u with minimum d[u]
 *    b. PROCESS: Mark u as processed
 *    c. RELAX: For each neighbor v of u, update d[v] if d[u] + w(u,v) < d[v]
 * 
 * Loop Invariant:
 * At the start of each iteration:
 *   - For all processed vertices v: d[v] = δ(source, v) (true shortest path)
 *   - For all unprocessed vertices v: d[v] = shortest path using only processed vertices
 * 
 * Return: DijkstraResult containing distances and parent pointers
 */
DijkstraResult *dijkstra(Graph *g, int source) {
    /* Input validation */
    if (g == NULL) {
        fprintf(stderr, "Error: NULL graph in dijkstra()\n");
        return NULL;
    }
    if (source < 0 || source >= g->num_vertices) {
        fprintf(stderr, "Error: Invalid source vertex %d (valid: 0 to %d)\n",
                source, g->num_vertices - 1);
        return NULL;
    }
    
    int n = g->num_vertices;
    
    /* Allocate result structure */
    DijkstraResult *result = (DijkstraResult *)malloc(sizeof(DijkstraResult));
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for result\n");
        return NULL;
    }
    
    result->distance = (int *)malloc(n * sizeof(int));
    result->parent = (int *)malloc(n * sizeof(int));
    bool *processed = (bool *)calloc(n, sizeof(bool));
    
    if (result->distance == NULL || result->parent == NULL || processed == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for arrays\n");
        free(result->distance);
        free(result->parent);
        free(processed);
        free(result);
        return NULL;
    }
    
    result->source = source;
    result->num_vertices = n;
    
    /*
     * PHASE 1: INITIALIZATION
     * 
     * Mathematical formulation:
     *   d[s] = 0        (distance from source to itself is 0)
     *   d[v] = ∞        (all other vertices initially unreachable)
     *   parent[v] = -1  (no parent yet)
     */
    printf("\n[DIJKSTRA] Initializing from source vertex %d...\n", source);
    
    for (int v = 0; v < n; v++) {
        result->distance[v] = INF;  /* ∞ means unreachable */
        result->parent[v] = -1;     /* -1 means no parent */
    }
    result->distance[source] = 0;   /* Source has distance 0 */
    
    /*
     * PHASE 2: MAIN LOOP
     * 
     * Process all vertices. In each iteration:
     * 1. Extract the unprocessed vertex with minimum distance
     * 2. Mark it as processed (finalized)
     * 3. Relax all outgoing edges
     */
    printf("[DIJKSTRA] Processing vertices...\n");
    
    for (int iteration = 0; iteration < n; iteration++) {
        /*
         * EXTRACT-MIN
         * Find vertex u with minimum d[u] among unprocessed vertices
         */
        int u = find_min_vertex(result->distance, processed, n);
        
        /* If no reachable unprocessed vertex, graph has disconnected components */
        if (u == -1) {
            printf("[DIJKSTRA] No more reachable vertices after %d iterations\n", iteration);
            break;
        }
        
        /* If minimum distance is INF, remaining vertices are unreachable */
        if (result->distance[u] == INF) {
            printf("[DIJKSTRA] Remaining vertices unreachable from source\n");
            break;
        }
        
        /* Mark u as processed - its distance is now finalized */
        processed[u] = true;
        
        printf("  Iteration %d: Processing vertex %d (distance = %d)\n",
               iteration + 1, u, result->distance[u]);
        
        /*
         * RELAXATION
         * For each edge (u, v) with weight w:
         *   If d[u] + w < d[v], we found a shorter path to v through u
         *   Update: d[v] = d[u] + w, parent[v] = u
         */
        Edge *edge = g->adj_list[u];
        while (edge != NULL) {
            int v = edge->destination;
            int weight = edge->weight;
            
            /*
             * Relaxation condition:
             *   1. v must not be processed yet
             *   2. d[u] must not be INF (avoid overflow)
             *   3. Path through u must be shorter than current d[v]
             * 
             * Mathematical: d[v] = min(d[v], d[u] + w(u,v))
             */
            if (!processed[v] && 
                result->distance[u] != INF &&
                result->distance[u] + weight < result->distance[v]) {
                
                int old_dist = result->distance[v];
                result->distance[v] = result->distance[u] + weight;
                result->parent[v] = u;
                
                printf("    Relaxed edge (%d, %d): d[%d] updated from %s to %d\n",
                       u, v, v,
                       (old_dist == INF) ? "∞" : "previous",
                       result->distance[v]);
            }
            
            edge = edge->next;
        }
    }
    
    printf("[DIJKSTRA] Algorithm complete!\n\n");
    
    /* Clean up temporary array */
    free(processed);
    
    return result;
}

/*============================================================================
 * MIN-HEAP (PRIORITY QUEUE) IMPLEMENTATION
 * 
 * For sparse graphs, using a min-heap dramatically improves performance.
 * 
 * Time Complexity:  O((V + E) log V)
 * Space Complexity: O(V)
 *===========================================================================*/

/*
 * HeapNode - Node in the priority queue
 */
typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

/*
 * MinHeap - Priority queue data structure
 * 
 * Binary heap stored in array:
 *   - Parent of i: (i-1)/2
 *   - Left child of i: 2*i + 1
 *   - Right child of i: 2*i + 2
 * 
 * The position array allows O(1) lookup of a vertex's position in the heap,
 * which is essential for the DECREASE-KEY operation.
 */
typedef struct MinHeap {
    int size;
    int capacity;
    int *position;      /* position[v] = index of vertex v in heap */
    HeapNode **nodes;
} MinHeap;

/* Heap helper functions */
static MinHeap *create_min_heap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (heap == NULL) return NULL;
    
    heap->position = (int *)malloc(capacity * sizeof(int));
    heap->nodes = (HeapNode **)malloc(capacity * sizeof(HeapNode *));
    
    if (heap->position == NULL || heap->nodes == NULL) {
        free(heap->position);
        free(heap->nodes);
        free(heap);
        return NULL;
    }
    
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static HeapNode *create_heap_node(int v, int dist) {
    HeapNode *node = (HeapNode *)malloc(sizeof(HeapNode));
    if (node == NULL) return NULL;
    node->vertex = v;
    node->distance = dist;
    return node;
}

static void swap_heap_nodes(MinHeap *heap, int a, int b) {
    HeapNode *temp = heap->nodes[a];
    heap->nodes[a] = heap->nodes[b];
    heap->nodes[b] = temp;
    
    /* Update position array to maintain O(1) vertex lookup */
    heap->position[heap->nodes[a]->vertex] = a;
    heap->position[heap->nodes[b]->vertex] = b;
}

/*
 * heapify - Restores min-heap property by sifting down
 * 
 * @heap: Pointer to min-heap
 * @idx:  Index to start heapifying from
 * 
 * Time Complexity: O(log V)
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
 * extract_min - Removes and returns the minimum element
 * 
 * Time Complexity: O(log V)
 */
static HeapNode *extract_min(MinHeap *heap) {
    if (heap->size == 0) return NULL;
    
    HeapNode *root = heap->nodes[0];
    HeapNode *last = heap->nodes[heap->size - 1];
    
    heap->nodes[0] = last;
    heap->position[root->vertex] = heap->size - 1;
    heap->position[last->vertex] = 0;
    
    heap->size--;
    heapify(heap, 0);
    
    return root;
}

/*
 * decrease_key - Decreases the distance value of a vertex
 * 
 * @heap: Pointer to min-heap
 * @v:    Vertex whose key to decrease
 * @dist: New (smaller) distance value
 * 
 * This is the KEY OPTIMIZATION over the array implementation!
 * Instead of O(V) to find minimum, we maintain heap property in O(log V).
 * 
 * Time Complexity: O(log V)
 */
static void decrease_key(MinHeap *heap, int v, int dist) {
    int i = heap->position[v];
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

static void free_min_heap(MinHeap *heap, HeapNode **extracted, int num_extracted) {
    if (heap == NULL) return;
    
    /* Free nodes still in heap */
    for (int i = 0; i < heap->size; i++) {
        if (heap->nodes[i]) free(heap->nodes[i]);
    }
    
    /* Free extracted nodes */
    for (int i = 0; i < num_extracted; i++) {
        if (extracted[i]) free(extracted[i]);
    }
    
    free(heap->nodes);
    free(heap->position);
    free(heap);
}

/*
 * dijkstra_heap - Heap-optimized Dijkstra's algorithm
 * 
 * @g:      Pointer to the graph
 * @source: Starting vertex
 * 
 * Uses a min-heap priority queue for efficient EXTRACT-MIN and DECREASE-KEY.
 * 
 * Return: DijkstraResult containing distances and parent pointers
 */
DijkstraResult *dijkstra_heap(Graph *g, int source) {
    if (g == NULL || source < 0 || source >= g->num_vertices) {
        fprintf(stderr, "Error: Invalid input to dijkstra_heap()\n");
        return NULL;
    }
    
    int n = g->num_vertices;
    
    /* Allocate result */
    DijkstraResult *result = (DijkstraResult *)malloc(sizeof(DijkstraResult));
    if (result == NULL) return NULL;
    
    result->distance = (int *)malloc(n * sizeof(int));
    result->parent = (int *)malloc(n * sizeof(int));
    
    if (result->distance == NULL || result->parent == NULL) {
        free(result->distance);
        free(result->parent);
        free(result);
        return NULL;
    }
    
    result->source = source;
    result->num_vertices = n;
    
    /* Create and initialize min-heap */
    MinHeap *heap = create_min_heap(n);
    if (heap == NULL) {
        free_result(result);
        return NULL;
    }
    
    /* Track extracted nodes for proper memory cleanup */
    HeapNode **extracted = (HeapNode **)malloc(n * sizeof(HeapNode *));
    int num_extracted = 0;
    
    /* Initialize all vertices */
    for (int v = 0; v < n; v++) {
        result->distance[v] = INF;
        result->parent[v] = -1;
        heap->nodes[v] = create_heap_node(v, INF);
        heap->position[v] = v;
    }
    
    /* Source has distance 0 */
    result->distance[source] = 0;
    decrease_key(heap, source, 0);
    heap->size = n;
    
    printf("\n[DIJKSTRA-HEAP] Running optimized algorithm from source %d...\n", source);
    
    /* Main loop */
    while (heap->size > 0) {
        HeapNode *min_node = extract_min(heap);
        extracted[num_extracted++] = min_node;  /* Track for later freeing */
        int u = min_node->vertex;
        
        /* If distance is INF, remaining vertices are unreachable */
        if (result->distance[u] == INF) break;
        
        /* Process all neighbors */
        Edge *edge = g->adj_list[u];
        while (edge != NULL) {
            int v = edge->destination;
            
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
    
    printf("[DIJKSTRA-HEAP] Complete!\n\n");
    
    free_min_heap(heap, extracted, num_extracted);
    free(extracted);
    return result;
}

/*============================================================================
 * RESULT OUTPUT FUNCTIONS
 *===========================================================================*/

/*
 * print_result - Displays shortest distances from source
 */
void print_result(DijkstraResult *result) {
    if (result == NULL) {
        printf("(NULL result)\n");
        return;
    }
    
    printf("┌───────────────────────────────────────────────────────┐\n");
    printf("│         DIJKSTRA'S ALGORITHM RESULTS                  │\n");
    printf("│         Source Vertex: %d                              │\n", result->source);
    printf("├──────────┬────────────┬───────────────────────────────┤\n");
    printf("│  Vertex  │  Distance  │            Path               │\n");
    printf("├──────────┼────────────┼───────────────────────────────┤\n");
    
    for (int v = 0; v < result->num_vertices; v++) {
        printf("│    %2d    │", v);
        
        if (result->distance[v] == INF) {
            printf("     ∞      │ ");
        } else {
            printf("    %4d    │ ", result->distance[v]);
        }
        
        print_path(result, v);
        printf("\n");
    }
    
    printf("└──────────┴────────────┴───────────────────────────────┘\n");
}

/*
 * print_path_recursive - Helper for recursive path printing
 */
void print_path_recursive(DijkstraResult *result, int v) {
    if (v == result->source) {
        printf("%d", v);
        return;
    }
    if (result->parent[v] == -1) {
        printf("(unreachable)");
        return;
    }
    
    print_path_recursive(result, result->parent[v]);
    printf(" → %d", v);
}

/*
 * print_path - Prints the shortest path to a destination vertex
 */
void print_path(DijkstraResult *result, int destination) {
    if (result == NULL || destination < 0 || destination >= result->num_vertices) {
        return;
    }
    
    if (result->distance[destination] == INF) {
        printf("No path exists");
        return;
    }
    
    print_path_recursive(result, destination);
}

/*
 * get_path - Returns the path as an array
 * 
 * @result:      DijkstraResult structure
 * @destination: Target vertex
 * @path_length: Output parameter for path length
 * 
 * Return: Dynamically allocated array containing path vertices
 *         Caller must free this array!
 */
int *get_path(DijkstraResult *result, int destination, int *path_length) {
    if (result == NULL || destination < 0 || 
        destination >= result->num_vertices ||
        result->distance[destination] == INF) {
        *path_length = 0;
        return NULL;
    }
    
    /* First, count path length */
    int length = 0;
    int v = destination;
    while (v != -1) {
        length++;
        v = result->parent[v];
    }
    
    /* Allocate array */
    int *path = (int *)malloc(length * sizeof(int));
    if (path == NULL) {
        *path_length = 0;
        return NULL;
    }
    
    /* Fill array in reverse (destination to source), then it's already correct
       since we traced back from destination */
    v = destination;
    for (int i = length - 1; i >= 0; i--) {
        path[i] = v;
        v = result->parent[v];
    }
    
    *path_length = length;
    return path;
}

/*
 * free_result - Deallocates result structure
 */
void free_result(DijkstraResult *result) {
    if (result == NULL) return;
    
    free(result->distance);
    free(result->parent);
    free(result);
}
