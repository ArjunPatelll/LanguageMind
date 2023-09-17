





#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
using namespace std;

struct BSTNode
{
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
};

struct BSTNode *GetNewNode(int data)
{
    struct BSTNode *new_node = new BSTNode();

    new_node->data = data;
    new_node->left = new_node->right = NULL;

    return new_node;
};

struct BSTNode *Insert(struct BSTNode *root, int data)
{
    if (root == NULL)
    {
        root = GetNewNode(data);
    }
    else if (data <= root->data)
    {
        root->left = Insert(root->left, data);
    }
    else
    {
        root->right = Insert(root->right, data);
    }
    return root;
}

struct BSTNode *Search(struct BSTNode *root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->data == data)
    {
        return root;
    }
    else if (data <= root->data)
    {
        return Search(root->left, data);
    }
    else
    {
        return Search(root->right, data);
    }
}

struct BSTNode *FindMin(struct BSTNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

struct BSTNode *FindMax(struct BSTNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

int main()
{
    struct BSTNode *root = NULL;

    root = Insert(root, 121);
    root = Insert(root, 9);
    root = Insert(root, 11);
    root = Insert(root, 7);
    root = Insert(root, 8);
    root = Insert(root, 14);
    root = Insert(root, 5);
    root = Insert(root, 6);
    root = Insert(root, 12);
    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 4);
    root = Insert(root, 16);

    struct BSTNode *node7 = Search(root, 7);
    if (node7 != NULL)
    {
        cout << "Node with key 7 found in the BST\n";
    }
    else
    {
        cout << "Node with the key 7 not found in the BST\n";
    }

    struct BSTNode *minNode = FindMin(root);
    if (minNode != NULL)
    {
        cout << "Minimum value in the BST is " << minNode->data << endl;
    }
    else
    {
        cout << "BST is empty.\n";
    }
    struct BSTNode *maxNode = FindMax(root);
    if (maxNode != NULL)
    {
        cout << "Maximum value in the BST is " << maxNode->data;
    }
    else
    {
        cout << "BST is empty.\n";
    }

    return 0;
}
