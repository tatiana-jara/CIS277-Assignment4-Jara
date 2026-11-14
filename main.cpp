#include "TreeExplorer.h"

#include <iostream>
#include <vector>

namespace {

void printValues(const std::vector<int>& values)
{
    for (int value : values)
        std::cout << value << ' ';
    std::cout << '\n';
}

void showTree(const char* name, const TreeNode* root)
{
    std::cout << name << '\n';
    std::cout << "Preorder: ";
    printValues(preorder(root));
    std::cout << "Inorder: ";
    printValues(inorder(root));
    std::cout << "Postorder: ";
    printValues(postorder(root));
    std::cout << "Level order: ";
    printValues(levelOrder(root));
    std::cout << "Nodes: " << countNodes(root) << '\n';
    std::cout << "Leaves: " << countLeaves(root) << '\n';
    std::cout << "Height in levels: " << treeHeight(root) << '\n';
    std::cout << "Sum: " << sumValues(root) << "\n\n";
}

} // namespace

int main()
{
    // Tree A: binary search tree, built with explicit pointer connections.
    TreeNode* rootA = new TreeNode{50};
    rootA->left = new TreeNode{30};
    rootA->right = new TreeNode{70};
    rootA->left->left = new TreeNode{20};
    rootA->left->right = new TreeNode{40};
    rootA->right->left = new TreeNode{60};
    rootA->right->right = new TreeNode{80};

    // Tree B: a binary tree that does not follow BST ordering.
    TreeNode* rootB = new TreeNode{10};
    rootB->left = new TreeNode{30};
    rootB->right = new TreeNode{20};
    rootB->left->right = new TreeNode{5};
    rootB->right->right = new TreeNode{15};

    showTree("TREE A", rootA);
    showTree("TREE B", rootB);

    destroyTree(rootA);
    destroyTree(rootB);

    std::cout << std::boolalpha;
    std::cout << "Tree A root is null after destruction: " << (rootA == nullptr) << '\n';
    std::cout << "Tree B root is null after destruction: " << (rootB == nullptr) << '\n';
    return 0;
}
