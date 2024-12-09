#include <iostream>
using namespace std;

template <typename T>
class TreeNode 
{
public:
    T data;   
    TreeNode* left;  
    TreeNode* right; 

    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class Tree {
private:
    TreeNode<T>* root; 

    TreeNode<T>* add(TreeNode<T>* node, T value) 
    {
        if (!node) 
        {
            return new TreeNode<T>(value);
        }
        if (value < node->data) 
        {
            node->left = add(node->left, value);
        }
        else 
        {
            node->right = add(node->right, value);
        }
        return node;
    }

    TreeNode<T>* copyTree(TreeNode<T>* node) 
    {
        if (!node) return nullptr;
        TreeNode<T>* newNode = new TreeNode<T>(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    void deleteTree(TreeNode<T>* node) 
    {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    TreeNode<T>* eraseNode(TreeNode<T>* node, T key) 
    {
        if (!node) return nullptr;
        if (key < node->data) 
        {
            node->left = eraseNode(node->left, key);
        }
        else if (key > node->data) 
        {
            node->right = eraseNode(node->right, key);
        }
        else 
        {
            if (!node->left) 
            {
                TreeNode<T>* rightSubtree = node->right;
                delete node;
                return rightSubtree;
            }
            else if (!node->right) 
            {
                TreeNode<T>* leftSubtree = node->left;
                delete node;
                return leftSubtree;
            }
            else 
            {
                TreeNode<T>* minLargerNode = findMin(node->right);
                node->data = minLargerNode->data;
                node->right = eraseNode(node->right, minLargerNode->data);
            }
        }
        return node;
    }

    TreeNode<T>* findMin(TreeNode<T>* node) 
    {
        while (node && node->left) 
        {
            node = node->left;
        }
        return node;
    }

    void inOrderTraversal(TreeNode<T>* node) const 
    {
        if (node) 
        {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }

public:
    Tree() : root(nullptr) {}

    Tree(const Tree& other) : root(copyTree(other.root)) {}

    ~Tree() 
    {
        deleteTree(root);
    }

    Tree& operator=(const Tree& other) 
    {
        if (this == &other) return *this;
        deleteTree(root);
        root = copyTree(other.root);
        return *this;
    }

    void add(T value) 
    {
        root = add(root, value);
    }

    void erase(T key) 
    {
        root = eraseNode(root, key);
    }

    void printInOrder() const 
    {
        inOrderTraversal(root);
        cout << endl;
    }
};

int main() 
{
    Tree<int> intTree;

    intTree.add(50);
    intTree.add(30);
    intTree.add(70);
    intTree.add(20);
    intTree.add(40);
    intTree.add(60);
    intTree.add(80);

    cout << "In-order traversal of the tree: " << endl;
    intTree.printInOrder();

    cout << "\nErasing 50:" << endl;
    intTree.erase(50);
    intTree.printInOrder();

    Tree<int> copiedTree = intTree;
    cout << "\nCopied tree (in-order):" << endl;
    copiedTree.printInOrder();

    Tree<int> assignedTree;
    assignedTree = intTree;
    cout << "\nAssigned tree (in-order):" << endl;
    assignedTree.printInOrder();
}

