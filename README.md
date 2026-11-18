# CIS-277 Assignment 4: Binary Tree Explorer

## Student

Tatiana Jara

## Design

### Initial plan 

My plan for this assignment is to build two binary trees using dynamically allocated nodes and pointers in C++23.

Node Structure: I will use a TreeNode structure containing an integer value and two pointers, left and right, initially set to nullptr.

Tree Construction: I will create Tree A and Tree B using new and connect the nodes manually with their left and right pointers.

Traversals: I will implement preorder, inorder, and postorder using recursion. Each traversal will use a helper function that passes a vector by reference to collect the values. For level-order traversal, I will use a FIFO queue.

Base Case: If a node is nullptr, the recursive function will stop. Empty trees should return empty traversal vectors and zero for their measurements.

Tree Measurements: I will create recursive functions to count nodes and leaves, calculate the height, and add all node values.

Memory Management: I will use postorder deletion to release every dynamically allocated node. After deleting the tree, I will set the root pointer to nullptr to avoid dangling pointers.

Testing: I will compare the program's output with my predicted results for Tree A and Tree B. I will also test empty trees, single nodes, chains, duplicate values, and negative values.

### Tree diagrams

Tree A (BST):

```text
          50
         /  \
        30   70
       / \   / \
      20 40 60 80
```

Tree B (binary tree, not a BST):

```text
          10
         /  \
        30   20
          \    \
           5    15
```

### My predictions 

### Tree Predictions and Reasoning

**Tree A — Binary Search Tree**

| Operation | Predicted Result |
|---|---|
| Preorder | 50 30 20 40 70 60 80 |
| Inorder | 20 30 40 50 60 70 80 |
| Postorder | 20 40 30 60 80 70 50 |
| Level Order | 50 30 70 20 40 60 80 |
| Nodes | 7 |
| Leaves | 4 |
| Height | 3 |
| Sum | 350 |

**Tree B — Non-BST Binary Tree**

| Operation | Predicted Result |
|---|---|
| Preorder | 10 30 5 20 15 |
| Inorder | 30 5 10 20 15 |
| Postorder | 5 30 15 20 10 |
| Level Order | 10 30 20 5 15 |
| Nodes | 5 |
| Leaves | 2 |
| Height | 3 |
| Sum | 80 |

### Traversal Reasoning

**Preorder Traversal — Tree A**

**Rule: Root → Left → Right**

1. Visit the root: **50**.
2. Move to the left child of 50: **30**.
3. Visit the left child of 30: **20**.
4. Visit the right child of 30: **40**.
5. Return to the root and move to the right child of 50: **70**.
6. Visit the left child of 70: **60**.
7. Visit the right child of 70: **80**.

**Final Preorder Sequence:** `50 30 20 40 70 60 80`

In preorder traversal, I visit the parent node first, then complete the entire left subtree before moving to the right subtree.

### Implementation approach

The tree nodes are dynamically allocated and connected explicitly in `main.cpp`. `TreeExplorer.cpp` has private recursive helpers for preorder, inorder, and postorder; each helper appends to one vector passed by reference. Level order uses `std::queue<const TreeNode*>`. Recursive measurements use null-pointer base cases. `destroyTree(TreeNode*& root)` deletes children before parents and clears the caller's pointer.

## How to Compile

This project uses C++23. From the repository root, compile the main program and student tests using:

```bash
g++ -std=c++23 -Wall -Wextra -pedantic main.cpp TreeExplorer.cpp -o tree_explorer
g++ -std=c++23 -Wall -Wextra -pedantic -I. tests/student_tests.cpp TreeExplorer.cpp -o student_tests
```

For memory checking with AddressSanitizer and UndefinedBehaviorSanitizer:

```bash
g++ -std=c++23 -Wall -Wextra -pedantic -fsanitize=address,undefined -fno-omit-frame-pointer -g -I. tests/student_tests.cpp TreeExplorer.cpp -o student_tests_asan
```

## How to Run

On Linux/macOS or GitHub Codespaces:

```bash
./tree_explorer
./student_tests
python3 validate.py
```

To run the memory check in GitHub Codespaces:

```bash
ASAN_OPTIONS=detect_leaks=1 ./student_tests_asan
```

On Windows PowerShell:

```powershell
.\tree_explorer.exe
.\student_tests.exe
python validate.py
```

The instructor's public validator also runs automatically through GitHub Actions when changes are pushed to the repository.
## Tests and Results

### 1. Tree A and Tree B Results

I compiled and ran `main.cpp` using C++23 in GitHub Codespaces. I compared the expected traversal sequences and measurements with the actual program output.

**Tree A — Binary Search Tree**

| Test | Expected | Actual |
|---|---|---|
| Preorder | 50 30 20 40 70 60 80 | 50 30 20 40 70 60 80 |
| Inorder | 20 30 40 50 60 70 80 | 20 30 40 50 60 70 80 |
| Postorder | 20 40 30 60 80 70 50 | 20 40 30 60 80 70 50 |
| Level Order | 50 30 70 20 40 60 80 | 50 30 70 20 40 60 80 |
| Nodes | 7 | 7 |
| Leaves | 4 | 4 |
| Height | 3 | 3 |
| Sum | 350 | 350 |

**Tree B — Non-BST Binary Tree**

| Test | Expected | Actual |
|---|---|---|
| Preorder | 10 30 5 20 15 | 10 30 5 20 15 |
| Inorder | 30 5 10 20 15 | 30 5 10 20 15 |
| Postorder | 5 30 15 20 10 | 5 30 15 20 10 |
| Level Order | 10 30 20 5 15 | 10 30 20 5 15 |
| Nodes | 5 | 5 |
| Leaves | 2 | 2 |
| Height | 3 | 3 |
| Sum | 80 | 80 |

**Result:** Both trees produced the expected results. After calling `destroyTree()`, both root pointers were confirmed to be `nullptr`.

### 2. Independent Student Tests

I compiled and ran `tests/student_tests.cpp` using C++23 in GitHub Codespaces.

The following table shows the test cases, expected results, actual results, and corrections.

| Test Case / Input | Expected Result | Actual Result | Corrections |
|---|---|---|---|
| Empty tree (`nullptr`) | Empty traversals, 0 nodes, 0 leaves, height 0, sum 0; repeated destruction is safe | PASS — All matched | None |
| Singleton (-4) | All traversals [-4], 1 node, 1 leaf, height 1, sum -4 | PASS — All matched | None |
| Left-only chain (10 → 20 → 30 → 40) | 4 nodes, 1 leaf, height 4, sum 100; preorder [10, 20, 30, 40], inorder [40, 30, 20, 10] | PASS — All matched | None |
| Right-only chain (10 → 20 → 30 → 40) | 4 nodes, 1 leaf, height 4, sum 100; inorder [10, 20, 30, 40], postorder [40, 30, 20, 10] | PASS — All matched | None |
| Duplicate, zero, and negative values | 6 nodes, 3 leaves, height 3, sum -1; all values are preserved | PASS — All matched | None |
| Repeated traversals and vector modification | Later traversal results and the original tree remain unchanged | PASS — Tree unchanged | None |
| Destruction and rebuilding | First tree sum 4; rebuilt tree preorder [-10, 2], sum -8; root becomes null after destruction | PASS — All matched | None |
| Additional uneven tree (12, -2, 7, 19, 25, 21) | 6 nodes, 2 leaves, height 4, sum 82 | PASS — All matched | None |

**Student Tests Result: 62/62 checks passed.**

All expected results matched the actual results.

### 3. Public Validator Results

I ran the instructor's official Assignment 4 validator through GitHub Actions using GCC 14 and C++23.

**Results:**

- Required files and README headings: PASS
- Public behavioral tests: 96/96 PASS
- Main demonstration compilation: PASS
- Overall public preflight: PASS

**Public Validator Result: 96/96 behavioral checks passed.**

The public validator confirmed that the program compiled and passed the required behavioral checks. I also ran my independent student tests separately.

### 4. Memory Management Check

I compiled and ran tests/student_tests.cpp using AddressSanitizer and UndefinedBehaviorSanitizer in GitHub Codespaces.

Result: 62/62 tests passed. No memory errors, undefined behavior, or memory leaks were reported during the execution.

The destroyTree() function uses postorder deletion to delete the left and right subtrees before the parent node. It also sets the root pointer to nullptr after destruction.

### 5. Corrections and Final Results

No C++ code corrections were necessary after the final tests.

The main program produced the expected output for Tree A and Tree B, all 62 independent student tests passed, and the instructor's public validator passed all 96 behavioral checks.

The results confirmed that the traversal functions, tree measurements, vector independence, and cleanup behavior worked correctly for the tested cases.

## Analysis Questions

### 1. Trace the preorder, inorder, and postorder processing steps for the subtree rooted at 30 in Tree A. Explain why the sequences change while the sum does not.

For the subtree rooted at 30 in Tree A:

```text
       30
      /  \
     20   40
```

- **Preorder (Root → Left → Right):** 30 20 40
- **Inorder (Left → Root → Right):** 20 30 40
- **Postorder (Left → Right → Root):** 20 40 30

The sequences are different because each traversal visits the nodes in a different order. However, the sum remains the same because all three traversals visit the same nodes.

**Sum:** 30 + 20 + 40 = 90

### 2. Explain why Tree B is a binary tree but not a BST, using a specific violated ordering relationship. Why is its inorder sequence not sorted?

Tree B is a valid binary tree because each node has at most two children. However, it is not a Binary Search Tree (BST) because it does not follow the BST ordering rule.

For example, node 30 is the left child of node 10, but 30 is greater than 10. Also, node 15 is the right child of node 20, but 15 is smaller than 20.

**Inorder sequence:** 30 5 10 20 15

The sequence is not sorted because Tree B does not follow BST ordering. Inorder traversal visits nodes in left-root-right order without sorting their values.

### 3. Give the depth of node 40 in Tree A and distinguish depth in edges from this assignment's height in levels.

The depth of node 40 in Tree A is **2 edges** because the path from the root is:

50 → 30 → 40

Depth measures the number of edges from the root to a specific node. Height measures the longest downward path in a tree.

In this assignment, height is measured in levels rather than edges. Therefore, Tree A has a height of **3 levels**.

### 4. Explain how the FIFO queue produces level order. Connect this to the queue behavior from earlier work.

Level-order traversal uses a FIFO queue to visit nodes one level at a time, from left to right.

The root is added to the queue first. When a node is removed, its value is processed, and its left and right children are added to the back of the queue.

This process continues until the queue is empty.

For Tree A, the level-order sequence is:

**50 30 70 20 40 60 80**

This follows the same FIFO concept used in earlier queue assignments.

### 5. For n nodes, height h, and maximum level width w, explain the time and auxiliary space for depth-first traversal, level-order traversal, measurements, and destruction. Discuss the O(n) returned vector separately from the call stack or queue. Compare the height of a balanced tree with a chain. Explain why a normal traversal does not need dynamic-programming tabulation.

| Operation | Time Complexity | Auxiliary Space |
|---|---|---|
| Preorder, Inorder, Postorder | O(n) | O(h) |
| Level Order | O(n) | O(w) |
| Count Nodes | O(n) | O(h) |
| Count Leaves | O(n) | O(h) |
| Tree Height | O(n) | O(h) |
| Sum Values | O(n) | O(h) |
| Destroy Tree | O(n) | O(h) |

All operations take O(n) time because they visit each node once. Recursion uses O(h) stack space, while level order uses O(w) queue space. Traversal result vectors require an additional O(n) space.

A balanced tree has height O(log n), while a chain has height O(n). Dynamic-programming tabulation is unnecessary because normal traversals do not repeat subproblems.

### 6. Explain why deletion uses postorder and what TreeNode*& changes in the caller. What would go wrong if the parent were deleted before reading its child pointers?

The `destroyTree()` function uses postorder deletion (Left → Right → Root) because the children must be deleted before their parent.

The parameter `TreeNode*& root` is a reference to a pointer. This allows the function to modify the caller's original root pointer and set it to `nullptr` after deletion.

If the parent were deleted before accessing its child pointers, the program could attempt to access memory that had already been released. This would cause undefined behavior and could also prevent the remaining nodes from being deleted correctly.

## AI Use

I used ChatGPT to help me understand binary trees, recursion, traversal methods, and memory management. ChatGPT guided me step by step on how to use GitHub Codespaces and explained how to compile and run the program. It also introduced me to AddressSanitizer and UndefinedBehaviorSanitizer, explained their purpose, and provided the commands to check for memory errors. I executed these commands in Codespaces and reviewed the results.

I reviewed the code and worked through the traversal examples to understand how the functions operate. I kept the required function signatures and used explicit pointer connections to build both trees instead of a BST insertion function.

To verify my work, I ran the main program, the independent student tests, and the instructor's public validator. My student tests passed 62/62 checks, and the public validator passed 96/96 checks. I also ran the tests with Sanitizer enabled, and no memory errors were reported.

One test that helped me understand traversal order was the left-only chain, where preorder and inorder produced different sequences.

Through this assignment, I learned more about recursive traversals, vectors, FIFO queues, and postorder deletion. I also learned how to use Sanitizer to check memory management. I still need more practice writing recursive functions independently.
