# ChatGPT Recommended

### Recommended Data Structures and Justification for Implementation

| **Requirement**                                                                 | **Recommended Data Structure**                         | **Alternative(s)**                                             | **Justification**                                                                                                                                                                                                                                                                         |
|---------------------------------------------------------------------------------|-------------------------------------------------------|----------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Add new actor/movie, Update details**                                        | **Hash Table**                                        | Lists, Binary Search Tree (BST)                               | Hash tables allow for efficient insertion and retrieval of actor/movie details using keys (e.g., name or title). They perform well for constant-time average complexity \(O(1)\) in most scenarios. BST is slower (\(O(\log n)\)) and lists are inefficient for search (\(O(n)\)).            |
| **Display actors within age range (sorted by age)**                            | **Binary Search Tree (BST)**                          | AVL Tree, Lists                                               | BST keeps data sorted and provides efficient in-order traversal (\(O(n)\)) for sorted output. AVL tree ensures balanced structure but is more complex to implement. Lists require sorting during each query (\(O(n \log n)\)).                                                                |
| **Display movies released in the past 3 years (sorted)**                       | **Binary Search Tree (BST)**                          | AVL Tree, Linked Lists                                        | BST offers sorted data and efficient range queries (\(O(\log n)\)). AVL trees guarantee balance but come with higher implementation complexity. Linked lists would require linear traversal (\(O(n)\)) for filtering and sorting.                                                             |
| **Display all movies an actor starred in (alphabetically)**                    | **Hash Table**                                        | Linked List, Binary Search Tree                               | Hash table offers fast retrieval of an actor’s movie list (\(O(1)\) average). Linked lists would require traversal (\(O(n)\)) for each lookup, and BST would need traversal for sorting (\(O(\log n)\) for insertion and sorting).                                                             |
| **Display all actors in a particular movie (alphabetically)**                  | **Hash Table**                                        | Binary Search Tree                                            | Hash table provides fast mapping of movies to actors (\(O(1)\) average). A BST could store actors sorted alphabetically but would be slower for insertion (\(O(\log n)\)) and retrieval compared to hash tables.                                                                             |
| **Display actors an actor knows (within two levels of movies)**                | **Graph (Adjacency List)**                            | Hash Table, Linked List                                       | Graphs efficiently model relationships and traversal (e.g., BFS/DFS). Adjacency lists reduce memory overhead compared to matrices and support neighbor queries efficiently. Hash tables or lists are not suitable for multi-level relational queries.                                           |
| **Sorting movies/actors alphabetically or by other criteria**                  | **Merge Sort**                                        | Quick Sort, Insertion Sort                                    | Merge sort is stable, efficient (\(O(n \log n)\)) for large datasets, and guarantees performance regardless of input order. Quick sort can be faster in practice but has worst-case \(O(n^2)\) complexity. Insertion sort is too slow (\(O(n^2)\)) for large datasets.                         |
| **Search for an actor/movie (by name/title)**                                  | **Hash Table**                                        | Binary Search Tree                                            | Hash table ensures \(O(1)\) average search complexity, significantly outperforming BST (\(O(\log n)\)) for direct lookups.                                                                                                                                                                 |
| **Recommendation system (based on actor/movie ratings)**                      | **Heap (Min/Max)**                                    | AVL Tree, Hash Table                                          | Heaps provide efficient top-k queries (\(O(\log n)\) for insertion/deletion), ideal for finding best/worst-rated actors/movies. AVL trees can also handle sorting but are more complex to maintain. Hash tables don’t support sorting directly.                                             |

### Best and Most Efficient Structure: **Hash Table**
**Justification:**
- **Efficiency:** Hash tables excel in frequent insertions, deletions, and direct access queries, all of which are central to this assignment.
- **Flexibility:** They provide \(O(1)\) average complexity for lookups, making them suitable for mapping relationships like actor-to-movies and movie-to-actors.
- **Alternatives:** While BSTs offer sorted output and AVL ensures balanced structure, their complexity and slower operations (\(O(\log n)\)) are less suited for high-frequency operations.

### Summary of Advanced Features
1. **Graph Representation:** Efficiently model actor-to-actor relationships using adjacency lists for BFS/DFS traversal.
2. **Heap Integration:** Use heaps for rating-based recommendations.

This balanced approach ensures both simplicity and optimal performance for all core features while meeting assignment requirements.

# Compiling
```bash
g++ src/*.cpp -Iinclude -o MovieApp.exe
```