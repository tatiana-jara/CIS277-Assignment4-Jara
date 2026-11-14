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

## How to Run

On Linux/macOS:

```bash
./tree_explorer
./student_tests
python3 validate.py
```

On Windows PowerShell:

```powershell
.\tree_explorer.exe
.\student_tests.exe
python validate.py
```

The `validate.py` script runs the instructor's public tests. The GitHub Actions workflow also runs the validator automatically when changes are pushed to the repository.

## Tests and Results

### Tree A and Tree B Results

I compared the expected traversal sequences and measurements with the actual program output.

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

Both trees produced the expected results, and their root pointers were set to `nullptr` after destruction.

### Additional Student Tests

The following test cases are included in `tests/student_tests.cpp`.

| Test Case | Expected Result | Actual Result | Corrections |
|---|---|---|---|
| Empty tree | Empty traversals, zero measurements, safe repeated deletion | PASS | None |
| Single node (-4) | 1 node, 1 leaf, height 1, sum -4 | PASS | None |
| Left-only chain (10, 20, 30, 40) | 4 nodes, 1 leaf, height 4, sum 100 | PASS | None |
| Right-only chain (10, 20, 30, 40) | 4 nodes, 1 leaf, height 4, sum 100 | PASS | None |
| Duplicate, zero, and negative values | 6 nodes, 3 leaves, height 3, sum -1 | PASS | None |
| Repeated traversals and vector modification | Original tree and subsequent results remain unchanged | PASS | None |
| Destruction and rebuilding | New tree has sum -8; root becomes null after deletion | PASS | None |
| Additional uneven tree (12, -2, 7, 19, 25, 21) | 6 nodes, 2 leaves, height 4, sum 82 | PASS | None |

**Student Tests Result:** 62/62 checks passed.

### Public Validator Results

The instructor's `validate.py` was executed with ChatGPT assistance using GCC 14 and C++23.

- Required files and README headings: PASS
- Public behavioral tests: 96/96 PASS
- Demonstration compilation: PASS
- Overall public preflight: PASS

The latest GitHub Actions preflight also completed successfully.

### Memory Management Check

With ChatGPT assistance, the student tests were also executed using a memory checker. All 62 tests passed, and no memory errors were reported during that run.

I reviewed the `destroyTree()` logic, which deletes the left and right subtrees before deleting the parent node and then sets the root pointer to `nullptr`.

### Corrections and Final Results

No code corrections were required after the latest tests. The expected results matched the actual output, and both the student tests and public validator passed.

**My own student-tests summary:** [Copy summary and test date from your machine.]

**My own public-validator result:** [Run `python validate.py` after downloading the exact instructor files. Record PASS/FAIL and fixes. Do not claim a PASS before running it.]

**My own memory-check evidence:** [If you ran ASan, Valgrind, or another checker, record exact command and result. If unavailable, write a manual allocation/deletion trace. Example small-tree trace: allocate root and its child; destroy child; destroy root; clear root pointer.]

**Changes/corrections made during testing:** [Describe actual debugging steps, even if you made no corrections.]

## Analysis Questions

These are **AI-assisted sample answers to review and revise in your own words** before submitting.

1. **Traversals of subtree rooted at 30.** The subtree is 30 with left child 20 and right child 40. Preorder processes `30 20 40`; inorder processes `20 30 40`; postorder processes `20 40 30`. The visit order differs, but all process the same three values, so the sum remains `30 + 20 + 40 = 90`.

2. **Tree B versus BST.** Tree B is a binary tree because each node has no more than two children. It is not a BST: the value 30 appears in the left subtree of root 10, even though 30 > 10. Also, 15 is a right child of 20 even though 15 < 20. Its inorder output is `30 5 10 20 15`, which is not sorted because inorder follows pointer structure and does not sort values.

3. **Depth and height.** Node 40 has depth 2 because the path `50 → 30 → 40` has two edges. Depth counts edges from the root to a particular node. In this assignment, height counts levels along the longest downward path: Tree A has height 3, and an empty tree has height 0.

4. **FIFO queue.** Level order starts by enqueueing the root. It repeatedly dequeues the oldest waiting node, processes its value, then enqueues its left and right children. FIFO ensures that already-enqueued nodes at earlier levels are visited before nodes at later levels. This uses the same first-in, first-out behavior studied in the queue unit.

5. **Complexities.** For `n` nodes, height `h`, and maximum level width `w`, each depth-first traversal and recursive measurement takes O(n) time and uses O(h) recursion-stack space. Level order takes O(n) time and O(w) queue space. Each returned traversal vector separately uses O(n) space; that output storage is not included in the auxiliary stack/queue bounds. Destruction takes O(n) time and O(h) recursion-stack space. A balanced tree has O(log n) height, while a one-sided chain can have O(n) height. Ordinary traversal does not need dynamic-programming tabulation because each node is processed only once, without overlapping subproblems.

6. **Postorder deletion and pointer reference.** Delete the left and right subtrees before deleting the parent so the program can still read the parent's child pointers. Deleting a parent before accessing its child pointers would risk accessing freed memory and losing access to children. `TreeNode*& root` is a reference to the caller's pointer, so after deleting the nodes, assigning `root = nullptr` also clears the caller's pointer. Repeated destruction of that null pointer is safe.

## AI Use

**AI assistance used:** ChatGPT was used to explain the assignment and to generate draft C++ source files, traversal helpers, recursion-based measurements, safe tree destruction, independent tests, and this README scaffold. AI-assisted compilation and test runs were used to check the draft. The generated project initially had compiler warnings in diagram comments; those comments were revised, and it was recompiled without warnings.

**My decisions and edits:** [Describe at least one genuine choice you made, one change you accepted or rejected, and why. Do not claim changes you did not make.]

**My verification:** [Describe a specific test you personally ran, its expected and actual results, any corrections, plus the actual public-validator outcome.]

**What I learned / still need to practice:** [Explain, in your own words, a concept such as how preorder differs from inorder, why a queue implements level order, or why `TreeNode*&` can null the caller's pointer.]

**Development history:** [Briefly list meaningful commits: plan, implementation, tests, fixes, final documentation.]
