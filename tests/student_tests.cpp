#include "TreeExplorer.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

int checks = 0;
int failures = 0;

template <typename T>
std::string asText(const T& value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

std::string asText(const std::vector<int>& values)
{
    std::ostringstream stream;
    stream << '[';
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0)
            stream << ", ";
        stream << values[i];
    }
    stream << ']';
    return stream.str();
}

template <typename T>
void check(const std::string& label, const T& actual, const T& expected)
{
    ++checks;
    if (actual == expected) {
        std::cout << "PASS: " << label << " | expected: " << asText(expected)
                  << " | actual: " << asText(actual) << '\n';
    } else {
        ++failures;
        std::cout << "FAIL: " << label << " | expected: " << asText(expected)
                  << " | actual: " << asText(actual) << '\n';
    }
}

void testEmptyTree()
{
    TreeNode* root = nullptr;
    const std::vector<int> empty;
    check("empty preorder", preorder(root), empty);
    check("empty inorder", inorder(root), empty);
    check("empty postorder", postorder(root), empty);
    check("empty level order", levelOrder(root), empty);
    check("empty node count", countNodes(root), std::size_t{0});
    check("empty leaf count", countLeaves(root), std::size_t{0});
    check("empty height", treeHeight(root), 0);
    check("empty sum", sumValues(root), 0LL);
    destroyTree(root);
    destroyTree(root);
    check("repeated empty destruction", root == nullptr, true);
}

void testSingleton()
{
    TreeNode* root = new TreeNode{-4};
    const std::vector<int> one{-4};
    check("singleton preorder", preorder(root), one);
    check("singleton inorder", inorder(root), one);
    check("singleton postorder", postorder(root), one);
    check("singleton level order", levelOrder(root), one);
    check("singleton nodes", countNodes(root), std::size_t{1});
    check("singleton leaves", countLeaves(root), std::size_t{1});
    check("singleton height", treeHeight(root), 1);
    check("singleton sum", sumValues(root), -4LL);
    destroyTree(root);
    check("singleton destruction", root == nullptr, true);
}

void testLeftChain()
{
    TreeNode* root = new TreeNode{10};
    root->left = new TreeNode{20};
    root->left->left = new TreeNode{30};
    root->left->left->left = new TreeNode{40};
    check("left chain preorder", preorder(root), std::vector<int>{10, 20, 30, 40});
    check("left chain inorder", inorder(root), std::vector<int>{40, 30, 20, 10});
    check("left chain postorder", postorder(root), std::vector<int>{40, 30, 20, 10});
    check("left chain level order", levelOrder(root), std::vector<int>{10, 20, 30, 40});
    check("left chain nodes", countNodes(root), std::size_t{4});
    check("left chain leaves", countLeaves(root), std::size_t{1});
    check("left chain height", treeHeight(root), 4);
    check("left chain sum", sumValues(root), 100LL);
    destroyTree(root);
    check("left chain destruction", root == nullptr, true);
}

void testRightChain()
{
    TreeNode* root = new TreeNode{10};
    root->right = new TreeNode{20};
    root->right->right = new TreeNode{30};
    root->right->right->right = new TreeNode{40};
    check("right chain preorder", preorder(root), std::vector<int>{10, 20, 30, 40});
    check("right chain inorder", inorder(root), std::vector<int>{10, 20, 30, 40});
    check("right chain postorder", postorder(root), std::vector<int>{40, 30, 20, 10});
    check("right chain level order", levelOrder(root), std::vector<int>{10, 20, 30, 40});
    check("right chain nodes", countNodes(root), std::size_t{4});
    check("right chain leaves", countLeaves(root), std::size_t{1});
    check("right chain height", treeHeight(root), 4);
    check("right chain sum", sumValues(root), 100LL);
    destroyTree(root);
    check("right chain destruction", root == nullptr, true);
}

void testRepeatedValuesAndSnapshots()
{
    // Shape: root 0; left -3 and right 0.
    // Left -3 has children -3 and 0. Right 0 has right child 5.
    TreeNode* root = new TreeNode{0};
    root->left = new TreeNode{-3};
    root->right = new TreeNode{0};
    root->left->left = new TreeNode{-3};
    root->left->right = new TreeNode{0};
    root->right->right = new TreeNode{5};

    const std::vector<int> expectedPre{0, -3, -3, 0, 0, 5};
    check("duplicates preorder", preorder(root), expectedPre);
    check("duplicates inorder", inorder(root), std::vector<int>{-3, -3, 0, 0, 0, 5});
    check("duplicates postorder", postorder(root), std::vector<int>{-3, 0, -3, 5, 0, 0});
    check("duplicates level order", levelOrder(root), std::vector<int>{0, -3, 0, -3, 0, 5});
    check("duplicates nodes", countNodes(root), std::size_t{6});
    check("duplicates leaves", countLeaves(root), std::size_t{3});
    check("duplicates height", treeHeight(root), 3);
    check("duplicates sum", sumValues(root), -1LL);

    std::vector<int> changed = preorder(root);
    changed[0] = 777;
    check("independent vector snapshot", preorder(root), expectedPre);
    check("tree unchanged after vector edit", root->value, 0);
    check("repeated inorder call", inorder(root), std::vector<int>{-3, -3, 0, 0, 0, 5});
    destroyTree(root);
    check("duplicates destruction", root == nullptr, true);
}

void testRebuildAfterDestruction()
{
    TreeNode* root = new TreeNode{3};
    root->left = new TreeNode{1};
    check("before rebuild sum", sumValues(root), 4LL);
    destroyTree(root);
    check("after first destruction", root == nullptr, true);

    root = new TreeNode{-10};
    root->right = new TreeNode{2};
    check("rebuilt preorder", preorder(root), std::vector<int>{-10, 2});
    check("rebuilt sum", sumValues(root), -8LL);
    destroyTree(root);
    destroyTree(root);
    check("after second destruction", root == nullptr, true);
}

void testExtraUnevenTree()
{
    // Shape: root 12; left -2 (right child 7); right 19,
    // with right child 25, whose left child is 21.
    TreeNode* root = new TreeNode{12};
    root->left = new TreeNode{-2};
    root->right = new TreeNode{19};
    root->left->right = new TreeNode{7};
    root->right->right = new TreeNode{25};
    root->right->right->left = new TreeNode{21};
    check("extra uneven preorder", preorder(root), std::vector<int>{12, -2, 7, 19, 25, 21});
    check("extra uneven inorder", inorder(root), std::vector<int>{-2, 7, 12, 19, 21, 25});
    check("extra uneven postorder", postorder(root), std::vector<int>{7, -2, 21, 25, 19, 12});
    check("extra uneven level order", levelOrder(root), std::vector<int>{12, -2, 19, 7, 25, 21});
    check("extra uneven nodes", countNodes(root), std::size_t{6});
    check("extra uneven leaves", countLeaves(root), std::size_t{2});
    check("extra uneven height", treeHeight(root), 4);
    check("extra uneven sum", sumValues(root), 82LL);
    destroyTree(root);
    check("extra uneven destruction", root == nullptr, true);
}

} // namespace

int main()
{
    testEmptyTree();
    testSingleton();
    testLeftChain();
    testRightChain();
    testRepeatedValuesAndSnapshots();
    testRebuildAfterDestruction();
    testExtraUnevenTree();

    std::cout << "\nStudent test summary: " << (checks - failures)
              << '/' << checks << " passed.\n";
    return failures == 0 ? 0 : 1;
}
