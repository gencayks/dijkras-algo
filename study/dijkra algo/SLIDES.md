# Dijkstra's Algorithm - Presentation Slides
## CS1 Class | Applied Mathematics Perspective

---

## Slide 1: Title

# **Dijkstra's Shortest Path Algorithm**

### Finding Optimal Routes in Weighted Graphs

*Presented by: Applied Mathematics Student*  
*Course: CS1*

---

## Slide 2: The Problem We're Solving

### Real-World Applications

🗺️ **GPS Navigation** - Finding the shortest route from A to B

🌐 **Network Routing** - Internet packets finding the fastest path

🎮 **Game AI** - NPCs pathfinding around obstacles

📡 **Telecommunications** - Optimizing signal transmission

### The Mathematical Problem

> Given a weighted graph $G = (V, E)$ with non-negative edge weights,
> find the shortest path from source vertex $s$ to all other vertices.

---

## Slide 3: Graph Terminology

### What is a Graph?

```
        (1)
       / | \
      4  |  2
     /   |   \
   (0)   1   (2)
     \   |   /
      2  |  3
       \ | /
        (3)
```

| Term | Definition |
|------|------------|
| **Vertex (Node)** | A point in the graph (0, 1, 2, 3 above) |
| **Edge** | A connection between two vertices |
| **Weight** | The "cost" of traversing an edge |
| **Path** | A sequence of edges connecting vertices |
| **Shortest Path** | Path with minimum total weight |

---

## Slide 4: The Key Insight

### Greedy Choice Property

> **If we always process the unvisited vertex with the minimum distance,
> that distance MUST be the final shortest distance.**

### Why does this work?

1. All edge weights are **non-negative**
2. Any alternative path would go through unprocessed vertices
3. Those vertices have **greater or equal** distance
4. Adding non-negative weights can only make paths **longer**

**Mathematical proof:** By contradiction (see detailed notes)

---

## Slide 5: The Relaxation Operation

### Core Mathematical Operation

$$d[v] = \min(d[v], d[u] + w(u, v))$$

### What does this mean?

- $d[v]$ = our current best estimate of distance to vertex $v$
- $d[u]$ = confirmed shortest distance to vertex $u$
- $w(u, v)$ = weight of edge from $u$ to $v$

### Example:

```
If d[u] = 3 and w(u,v) = 2:
   d[v] = min(d[v], 3 + 2) = min(d[v], 5)
   
If current d[v] = 7, update to 5 (found shorter path!)
If current d[v] = 4, keep 4 (no improvement)
```

---

## Slide 6: Algorithm Steps

### High-Level Overview

```
1. INITIALIZE
   - Set distance to source = 0
   - Set distance to all others = ∞
   - Mark all vertices as unprocessed

2. REPEAT until all vertices processed:
   
   a. SELECT vertex u with minimum distance (among unprocessed)
   
   b. MARK u as processed
   
   c. RELAX all edges from u:
      For each neighbor v of u:
         If d[u] + w(u,v) < d[v]:
            d[v] = d[u] + w(u,v)
            parent[v] = u

3. RETURN distances and parents
```

---

## Slide 7: Step-by-Step Example

### Our Graph (Source = Vertex 0)

```
        (1)
       / | \
      4  |  2
     /   |   \
   (0)   1   (2)
     \   |   /
      2  |  3
       \ | /
        (3)----5----(4)
```

### Initial State

| Vertex | 0 | 1 | 2 | 3 | 4 |
|--------|---|---|---|---|---|
| d[] | **0** | ∞ | ∞ | ∞ | ∞ |
| Processed? | ❌ | ❌ | ❌ | ❌ | ❌ |

---

## Slide 8: Iteration 1

### Process Vertex 0 (distance = 0)

**Relax edges from 0:**
- Edge (0,1) weight 4: d[1] = min(∞, 0+4) = **4**
- Edge (0,3) weight 2: d[3] = min(∞, 0+2) = **2**

| Vertex | 0 | 1 | 2 | 3 | 4 |
|--------|---|---|---|---|---|
| d[] | 0 | 4 | ∞ | **2** | ∞ |
| Processed? | ✅ | ❌ | ❌ | ❌ | ❌ |

**Next: Select vertex 3 (minimum unprocessed distance = 2)**

---

## Slide 9: Iteration 2

### Process Vertex 3 (distance = 2)

**Relax edges from 3:**
- Edge (3,1) weight 1: d[1] = min(4, 2+1) = **3** ✓ Improved!
- Edge (3,2) weight 3: d[2] = min(∞, 2+3) = **5**
- Edge (3,4) weight 5: d[4] = min(∞, 2+5) = **7**

| Vertex | 0 | 1 | 2 | 3 | 4 |
|--------|---|---|---|---|---|
| d[] | 0 | **3** | 5 | 2 | 7 |
| Processed? | ✅ | ❌ | ❌ | ✅ | ❌ |

**Key insight: Path 0→3→1 (cost 3) is shorter than direct 0→1 (cost 4)!**

---

## Slide 10: Final Result

### After All Iterations

| Vertex | Distance | Path |
|--------|----------|------|
| 0 | 0 | (source) |
| 1 | 3 | 0 → 3 → 1 |
| 2 | 5 | 0 → 3 → 2 |
| 3 | 2 | 0 → 3 |
| 4 | 7 | 0 → 3 → 4 |

### Path Reconstruction

Use parent pointers to trace back:
- To reach vertex 4: parent[4]=3, parent[3]=0
- Path: 0 → 3 → 4

---

## Slide 11: C Implementation - Data Structures

### Graph Representation: Adjacency List

```c
/* Edge in adjacency list */
typedef struct Edge {
    int destination;      /* Target vertex */
    int weight;           /* Edge weight */
    struct Edge *next;    /* Next edge in list */
} Edge;

/* Graph structure */
typedef struct Graph {
    int num_vertices;     /* |V| */
    int num_edges;        /* |E| */
    Edge **adj_list;      /* Array of linked lists */
} Graph;
```

### Why Adjacency List?
- **Space:** O(V + E) vs O(V²) for matrix
- **Iterate neighbors:** O(degree) vs O(V)

---

## Slide 12: C Implementation - Core Algorithm

```c
/* Find minimum distance unprocessed vertex */
int find_min_vertex(int *distance, bool *processed, int n) {
    int min_dist = INF, min_v = -1;
    for (int v = 0; v < n; v++) {
        if (!processed[v] && distance[v] < min_dist) {
            min_dist = distance[v];
            min_v = v;
        }
    }
    return min_v;
}

/* Relaxation step */
if (distance[u] + weight < distance[v]) {
    distance[v] = distance[u] + weight;
    parent[v] = u;
}
```

---

## Slide 13: Complexity Analysis

### Time Complexity

| Implementation | EXTRACT-MIN | DECREASE-KEY | **Total** |
|---------------|-------------|--------------|-----------|
| Array | O(V) | O(1) | **O(V²)** |
| Binary Heap | O(log V) | O(log V) | **O((V+E) log V)** |
| Fibonacci Heap | O(log V)* | O(1)* | **O(V log V + E)** |

*\* amortized*

### When to Use Which?

- **Dense graphs** (E ≈ V²): Array implementation
- **Sparse graphs** (E ≈ V): Heap implementation

### Space Complexity: O(V)

---

## Slide 14: Important Limitations

### ⚠️ Dijkstra REQUIRES Non-Negative Weights!

**Why?**
```
        (A)
       /   \
      2    -5
     /       \
   (S)        (C)
     \       /
      3     1
       \   /
        (B)
```

With negative edge (A,C) = -5:
- Dijkstra finds S→B→C = 4
- But S→A→C = 2 + (-5) = -3 is shorter!

### For Negative Weights: Use Bellman-Ford Algorithm

---

## Slide 15: Common Mistakes in C

### 1. Integer Overflow

```c
/* WRONG - may overflow! */
if (distance[u] + weight < distance[v])

/* CORRECT - check for INF first */
if (distance[u] != INF && 
    distance[u] + weight < distance[v])
```

### 2. Memory Leaks

```c
/* Always free in reverse order of allocation */
free(edges);      /* Free inner first */
free(adj_list);   /* Then outer */
free(graph);      /* Then container */
```

### 3. Off-by-One Errors

Be consistent: vertices are 0-indexed or 1-indexed, not both!

---

## Slide 16: Extensions and Variations

### 1. A* Algorithm
Add heuristic for goal-directed search:
$$f(v) = g(v) + h(v)$$
Where $h(v)$ estimates distance from $v$ to goal.

### 2. Bidirectional Dijkstra
Search from both source and destination, meet in middle.
Approximately 2× faster for point-to-point queries.

### 3. All-Pairs Shortest Paths
Run Dijkstra from every vertex: O(V³) or O(V² log V + VE)
Or use Floyd-Warshall: O(V³) with smaller constant.

---

## Slide 17: Summary

### What We Learned

1. **Problem:** Finding shortest paths in weighted graphs

2. **Key Insight:** Greedy choice with relaxation

3. **Algorithm:**
   - Initialize distances (source = 0, others = ∞)
   - Repeatedly extract minimum, relax neighbors
   - Build shortest path tree

4. **Complexity:** O(V²) or O((V+E) log V) with heap

5. **Limitation:** Non-negative weights only!

---

## Slide 18: Practice Problems

### For Students

1. **Trace by hand:** Run Dijkstra on a 6-vertex graph

2. **Modify code:** Find shortest path between two specific vertices only (early termination)

3. **Compare:** Implement both array and heap versions, benchmark on different graph densities

4. **Extension:** Modify to return the k shortest paths

5. **Application:** Model a real-world problem as a shortest path problem (e.g., cheapest flight routing)

---

## Slide 19: References

1. Dijkstra, E.W. (1959). "A note on two problems in connexion with graphs". *Numerische Mathematik*. 1: 269–271.

2. Cormen, T.H., Leiserson, C.E., Rivest, R.L., Stein, C. *Introduction to Algorithms* (3rd ed.). MIT Press.

3. Sedgewick, R., Wayne, K. *Algorithms* (4th ed.). Addison-Wesley.

### Online Resources

- Visualgo.net - Algorithm Visualizations
- GeeksforGeeks - Implementation Examples

---

## Slide 20: Questions?

# Thank You!

### Code Available At:
`dijkstra.h`, `graph.c`, `dijkstra.c`, `main.c`

### To Run:
```bash
make
./dijkstra
```

---

*Prepared for CS1 Presentation - Applied Mathematics*
