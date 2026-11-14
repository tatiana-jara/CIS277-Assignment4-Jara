# CIS-277 Assignment 4: Binary Tree Explorer

## Student

- Name: **[Write your name]**
- Course: CIS-277
- Language: C++23
- Repository: **[Paste your public GitHub repository URL]**

## Design

### Initial plan (required: write this yourself)

**IMPORTANT:** Your instructor requires your own initial plan written before coding or asking AI to implement the program. Do not falsely claim this was written earlier if it was not. Retain your original plan if you already wrote one. The questions below are prompts, **not a completed personal plan**.

1. **Node fields:** [In your own words, explain `value`, `left`, and `right`.]
2. **Base case:** [What does each recursive function do when the pointer is `nullptr`?]
3. **Collecting traversals:** [How does one `std::vector<int>&` receive the visited values?]
4. **Ownership and cleanup:** [Who owns each `new TreeNode`, and how do you safely release it?]
5. **Changes after the initial plan:** [Describe any changes and when they were made.]

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

### My predictions (complete by hand, separate from actual output)

| Tree | Operation | My predicted result |
|---|---|---|
| A | Preorder | [Fill in] |
| A | Inorder | [Fill in] |
| A | Postorder | [Fill in] |
| A | Level order | [Fill in] |
| A | Nodes / Leaves / Height / Sum | [Fill in] |
| B | Preorder | [Fill in] |
| B | Inorder | [Fill in] |
| B | Postorder | [Fill in] |
| B | Level order | [Fill in] |
| B | Nodes / Leaves / Height / Sum | [Fill in] |

**My hand trace of one traversal:** [Show your steps, using the actual child connections, before comparing with the program.]

### Implementation approach

The tree nodes are dynamically allocated and connected explicitly in `main.cpp`. `TreeExplorer.cpp` has private recursive helpers for preorder, inorder, and postorder; each helper appends to one vector passed by reference. Level order uses `std::queue<const TreeNode*>`. Recursive measurements use null-pointer base cases. `destroyTree(TreeNode*& root)` deletes children before parents and clears the caller's pointer.

## How to Compile

Use a compiler supporting C++23. From the repository root:

```bash
g++ -std=c++23 -Wall -Wextra -pedantic main.cpp TreeExplorer.cpp -o tree_explorer
g++ -std=c++23 -Wall -Wextra -pedantic -I. tests/student_tests.cpp TreeExplorer.cpp -o student_tests
```

For a memory check with GCC/Clang AddressSanitizer and UndefinedBehaviorSanitizer (when supported):

```bash
g++ -std=c++23 -Wall -Wextra -pedantic -fsanitize=address,undefined -fno-omit-frame-pointer -g -I. tests/student_tests.cpp TreeExplorer.cpp -o student_tests_asan
```

## How to Run

On Linux/macOS:

```bash
./tree_explorer
./student_tests
python3 validate.py
```

On Windows PowerShell (assuming `g++` and Python are installed):

```powershell
.\tree_explorer.exe
.\student_tests.exe
python validate.py
```

If running the sanitizer build on Linux/macOS:

```bash
ASAN_OPTIONS=detect_leaks=1 ./student_tests_asan
```

**Important:** Download the instructor-provided `validate.py`, `tests/public_tests.cpp`, and `.github/workflows/validate.yml` from the separate Assignment 4 Validator page. Keep these files unchanged. They are **not included in this starter package**.

## Tests and Results

### Instructor-supplied expected results

| Result | Tree A | Tree B |
|---|---|---|
| Preorder | 50 30 20 40 70 60 80 | 10 30 5 20 15 |
| Inorder | 20 30 40 50 60 70 80 | 30 5 10 20 15 |
| Postorder | 20 40 30 60 80 70 50 | 5 30 15 20 10 |
| Level order | 50 30 70 20 40 60 80 | 10 30 20 5 15 |
| Nodes | 7 | 5 |
| Leaves | 4 | 2 |
| Height (levels) | 3 | 3 |
| Sum | 350 | 80 |

### Independent student test cases

The provided `tests/student_tests.cpp` draft includes the cases below. The implementation was tested in the generated example environment with GCC 14.2.0 in C++23 mode: **62/62 checks passed**. The sanitizer build also completed with exit code 0, with no sanitizer findings in that run. **Run the tests yourself and record your own results here before submission.**

| Test input / exact shape | Expected | My actual result | Corrections I made |
|---|---|---|---|
| Empty tree, destroy null twice | Empty traversals; counts/height/sum 0; no crash | [Run and fill] | [Fill] |
| Single node -4 | All traversals -4; nodes 1; leaves 1; height 1; sum -4 | [Run and fill] | [Fill] |
| Four-node left chain 10→20→30→40 | Height 4; one leaf; preorder 10 20 30 40; inorder 40 30 20 10 | [Run and fill] | [Fill] |
| Four-node right chain 10→20→30→40 | Height 4; one leaf; inorder 10 20 30 40; postorder 40 30 20 10 | [Run and fill] | [Fill] |
| Root 0; left -3 with children -3 and 0; right 0 with right child 5 | Six nodes; three leaves; height 3; sum -1; duplicate/zero/negative values retained | [Run and fill] | [Fill] |
| Repeated traversals and modified returned vector | A later traversal and node values remain unchanged | [Run and fill] | [Fill] |
| Destroy, rebuild with -10 and right child 2, destroy twice | Rebuilt sum -8; roots null after deletion | [Run and fill] | [Fill] |
| Extra uneven tree: root 12; left -2→right 7; right 19→right 25→left 21 | Six nodes; two leaves; height 4; sum 82 | [Run and fill] | [Fill] |

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
