/*
 * main.c - Dijkstra's Algorithm Demonstration Program
 * 
 * This program demonstrates Dijkstra's shortest path algorithm
 * with multiple example graphs and verification tests.
 * 
 * Designed for CS1 students to understand:
 * 1. How the algorithm works step-by-step
 * 2. Graph representation in C
 * 3. Memory management patterns
 * 4. Testing and verification
 */

#include "dijkstra.h"
#include <string.h>

/*
 * EXAMPLE GRAPHS
 * ==============
 * We'll demonstrate with several carefully chosen graphs.
 */

/*
 * create_example_graph_1 - Simple 5-vertex graph
 * 
 * Visual representation:
 * 
 *         (1)
 *        /   \
 *       4     2
 *      /       \
 *    (0)        (2)
 *      \       /
 *       2     3
 *        \   /
 *         (3)----5----(4)
 *          |          
 *          1          
 *          |          
 *         (1)         
 * 
 * Full edge list (undirected):
 *   0-1: weight 4
 *   0-3: weight 2
 *   1-2: weight 2
 *   1-3: weight 1
 *   2-3: weight 3
 *   2-4: weight 6
 *   3-4: weight 5
 */
Graph *create_example_graph_1(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║  EXAMPLE GRAPH 1: Simple 5-Vertex Graph                  ║\n");
    printf("║                                                          ║\n");
    printf("║           (1)                                            ║\n");
    printf("║          /   \\                                           ║\n");
    printf("║         4     2                                          ║\n");
    printf("║        /       \\                                         ║\n");
    printf("║      (0)        (2)                                      ║\n");
    printf("║        \\       /   \\                                     ║\n");
    printf("║         2     3     6                                    ║\n");
    printf("║          \\   /       \\                                   ║\n");
    printf("║           (3)----5----(4)                                ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    Graph *g = create_graph(5);
    if (g == NULL) return NULL;
    
    /* Add undirected edges */
    add_undirected_edge(g, 0, 1, 4);
    add_undirected_edge(g, 0, 3, 2);
    add_undirected_edge(g, 1, 2, 2);
    add_undirected_edge(g, 1, 3, 1);
    add_undirected_edge(g, 2, 3, 3);
    add_undirected_edge(g, 2, 4, 6);
    add_undirected_edge(g, 3, 4, 5);
    
    return g;
}

/*
 * create_example_graph_2 - Directed graph with multiple shortest paths
 * 
 * Visual representation:
 * 
 *    (0)───10───>(1)───1───>(2)
 *     |           |          │
 *     5           2          │
 *     │           │          │
 *     v           v          │
 *    (4)<───3───(3)<────4────┘
 *     
 */
Graph *create_example_graph_2(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║  EXAMPLE GRAPH 2: Directed Graph                         ║\n");
    printf("║                                                          ║\n");
    printf("║      (0)───10───>(1)───1───>(2)                          ║\n");
    printf("║       │           │          │                           ║\n");
    printf("║       5           2          4                           ║\n");
    printf("║       │           │          │                           ║\n");
    printf("║       v           v          v                           ║\n");
    printf("║      (4)<───3───(3)<─────────┘                           ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    Graph *g = create_graph(5);
    if (g == NULL) return NULL;
    
    /* Add directed edges only */
    add_edge(g, 0, 1, 10);
    add_edge(g, 0, 4, 5);
    add_edge(g, 1, 2, 1);
    add_edge(g, 1, 3, 2);
    add_edge(g, 2, 3, 4);
    add_edge(g, 3, 4, 3);
    
    return g;
}

/*
 * create_example_graph_3 - Graph with disconnected component
 * 
 * Tests handling of unreachable vertices
 * 
 *    (0)───5───(1)       (3)───2───(4)
 *      \       /          │
 *       3     2           1
 *        \   /            │
 *         (2)            (5)
 */
Graph *create_example_graph_3(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║  EXAMPLE GRAPH 3: Disconnected Components                ║\n");
    printf("║                                                          ║\n");
    printf("║      (0)───5───(1)       (3)───2───(4)                   ║\n");
    printf("║        \\       /          │                              ║\n");
    printf("║         3     2           1                              ║\n");
    printf("║          \\   /            │                              ║\n");
    printf("║           (2)            (5)                             ║\n");
    printf("║                                                          ║\n");
    printf("║  Note: Starting from vertex 0, vertices 3,4,5 are       ║\n");
    printf("║        unreachable (distance = ∞)                        ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    Graph *g = create_graph(6);
    if (g == NULL) return NULL;
    
    /* Component 1: vertices 0, 1, 2 */
    add_undirected_edge(g, 0, 1, 5);
    add_undirected_edge(g, 0, 2, 3);
    add_undirected_edge(g, 1, 2, 2);
    
    /* Component 2: vertices 3, 4, 5 */
    add_undirected_edge(g, 3, 4, 2);
    add_undirected_edge(g, 3, 5, 1);
    
    return g;
}

/*
 * verify_result - Checks if algorithm output matches expected values
 */
bool verify_result(DijkstraResult *result, int *expected, int n) {
    if (result == NULL || expected == NULL) return false;
    
    bool correct = true;
    for (int i = 0; i < n; i++) {
        int got = result->distance[i];
        int exp = expected[i];
        
        if (got != exp) {
            printf("  ❌ Vertex %d: got %d, expected %d\n", i, 
                   (got == INF) ? -1 : got, 
                   (exp == INF) ? -1 : exp);
            correct = false;
        }
    }
    
    if (correct) {
        printf("  ✓ All distances match expected values!\n");
    }
    
    return correct;
}

/*
 * demo_path_reconstruction - Shows how to use the get_path function
 */
void demo_path_reconstruction(DijkstraResult *result, int dest) {
    int path_length;
    int *path = get_path(result, dest, &path_length);
    
    if (path == NULL) {
        printf("  No path exists to vertex %d\n", dest);
        return;
    }
    
    printf("  Path to vertex %d (length %d): ", dest, path_length);
    for (int i = 0; i < path_length; i++) {
        if (i > 0) printf(" → ");
        printf("%d", path[i]);
    }
    printf("\n");
    printf("  Total distance: %d\n", result->distance[dest]);
    
    free(path);  /* Don't forget to free! */
}

/*
 * run_comprehensive_demo - Main demonstration routine
 */
void run_comprehensive_demo(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                                                          ║\n");
    printf("║         DIJKSTRA'S SHORTEST PATH ALGORITHM               ║\n");
    printf("║                                                          ║\n");
    printf("║         Comprehensive Demonstration                      ║\n");
    printf("║         For CS1 - Applied Mathematics                    ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    /*
     * TEST 1: Simple undirected graph
     */
    printf("\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("                      TEST 1                               \n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    Graph *g1 = create_example_graph_1();
    if (g1 != NULL) {
        print_graph(g1);
        
        /* Run Dijkstra from vertex 0 */
        printf("\n>>> Running Dijkstra from vertex 0...\n");
        DijkstraResult *result1 = dijkstra(g1, 0);
        
        if (result1 != NULL) {
            print_result(result1);
            
            /* Verify results */
            printf("\n>>> Verification:\n");
            int expected1[] = {0, 3, 5, 2, 7};  /* Known correct values */
            verify_result(result1, expected1, 5);
            
            /* Demonstrate path reconstruction */
            printf("\n>>> Path Reconstruction Demo:\n");
            demo_path_reconstruction(result1, 4);
            demo_path_reconstruction(result1, 2);
            
            free_result(result1);
        }
        
        free_graph(g1);
    }
    
    /*
     * TEST 2: Directed graph
     */
    printf("\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("                      TEST 2                               \n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    Graph *g2 = create_example_graph_2();
    if (g2 != NULL) {
        print_graph(g2);
        
        printf("\n>>> Running Dijkstra from vertex 0...\n");
        DijkstraResult *result2 = dijkstra(g2, 0);
        
        if (result2 != NULL) {
            print_result(result2);
            
            printf("\n>>> Verification:\n");
            int expected2[] = {0, 10, 11, 12, 5};
            verify_result(result2, expected2, 5);
            
            free_result(result2);
        }
        
        free_graph(g2);
    }
    
    /*
     * TEST 3: Disconnected graph
     */
    printf("\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("                      TEST 3                               \n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    Graph *g3 = create_example_graph_3();
    if (g3 != NULL) {
        print_graph(g3);
        
        printf("\n>>> Running Dijkstra from vertex 0...\n");
        DijkstraResult *result3 = dijkstra(g3, 0);
        
        if (result3 != NULL) {
            print_result(result3);
            
            printf("\n>>> Verification:\n");
            int expected3[] = {0, 5, 3, INF, INF, INF};  /* 3,4,5 unreachable */
            verify_result(result3, expected3, 6);
            
            printf("\n>>> Path to unreachable vertex:\n");
            demo_path_reconstruction(result3, 3);
            
            free_result(result3);
        }
        
        free_graph(g3);
    }
    
    /*
     * TEST 4: Compare array vs heap implementation
     */
    printf("\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("         TEST 4: Array vs Heap Implementation              \n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    Graph *g4 = create_example_graph_1();
    if (g4 != NULL) {
        printf("\n>>> Array-based implementation:\n");
        DijkstraResult *result_array = dijkstra(g4, 0);
        
        printf(">>> Heap-based implementation:\n");
        DijkstraResult *result_heap = dijkstra_heap(g4, 0);
        
        if (result_array != NULL && result_heap != NULL) {
            printf("\n>>> Comparing results:\n");
            bool match = true;
            for (int i = 0; i < g4->num_vertices; i++) {
                if (result_array->distance[i] != result_heap->distance[i]) {
                    match = false;
                    printf("  ❌ Mismatch at vertex %d\n", i);
                }
            }
            if (match) {
                printf("  ✓ Both implementations produce identical results!\n");
            }
            
            printf("\n>>> Array implementation results:\n");
            print_result(result_array);
            
            free_result(result_array);
            free_result(result_heap);
        }
        
        free_graph(g4);
    }
}

/*
 * print_complexity_analysis - Educational output about algorithm complexity
 */
void print_complexity_analysis(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║            COMPLEXITY ANALYSIS                           ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║                                                          ║\n");
    printf("║  Implementation  │ EXTRACT-MIN │ DECREASE-KEY │ Total    ║\n");
    printf("║  ───────────────┼─────────────┼──────────────┼───────── ║\n");
    printf("║  Array          │    O(V)     │     O(1)     │ O(V²)    ║\n");
    printf("║  Binary Heap    │  O(log V)   │   O(log V)   │O((V+E)lgV)║\n");
    printf("║  Fibonacci Heap │  O(log V)*  │     O(1)*    │O(VlgV+E) ║\n");
    printf("║                                                          ║\n");
    printf("║  * amortized                                             ║\n");
    printf("║                                                          ║\n");
    printf("║  When to use which:                                      ║\n");
    printf("║  • Dense graphs (E ≈ V²): Array is simpler, same O(V²)  ║\n");
    printf("║  • Sparse graphs (E ≈ V): Heap gives O(V log V)         ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
}

/*
 * print_usage - Shows how to use this program
 */
void print_usage(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                    USAGE                                 ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║                                                          ║\n");
    printf("║  Compile:  gcc -Wall -o dijkstra main.c graph.c          ║\n");
    printf("║                                   dijkstra.c             ║\n");
    printf("║                                                          ║\n");
    printf("║  Or use:   make                                          ║\n");
    printf("║                                                          ║\n");
    printf("║  Run:      ./dijkstra                                    ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
}

/*
 * main - Program entry point
 */
int main(void) {
    /* Run the comprehensive demonstration */
    run_comprehensive_demo();
    
    /* Print educational complexity analysis */
    print_complexity_analysis();
    
    /* Print usage information */
    print_usage();
    
    printf("\n>>> Program complete. All memory freed.\n\n");
    
    return 0;
}
