// Code by Imran
#include <iostream>
#include <string>
#include "Movie.h"
#include <sstream>
#include <vector>
#include <math.h> //this math library was used for the formula: int digitCountOfANumber = log10(Number) + 1; we need digit count to
using namespace std; //to determine however many 0's to print out if the int id is less than 8 digits

//***modeled RotateRight, RotateLeft, Insert, Remove, Pre/Post/Inorder traversal code off the corresponding lecture code****
template <typename key, typename value>
class Map {
public:
    struct Node {
        vector<value> movieList;
        key rating;
        Node* left;
        Node* right;
        int height; //where height = 1 for a root node, and the balance factor of a root node is 0

        //Each node represents one movie:
        Node(key _movieRating, value movie) {
            movieList.push_back(movie);
            rating = _movieRating;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };
    //Attributes
    Node* treeRoot = nullptr;
    int nodeCount = 0;

    //Functions
    Node* RotateLeft(Node* node) {
        Node* grandChild = node->right->left;
        Node* newParent = node->right;
        newParent->left = node;
        node->right = grandChild;
        return newParent;
    }
    Node* RotateRight(Node* node) {
        Node* grandChild = node->left->right;
        Node* newParent = node->left;
        newParent->right = node;
        node->left = grandChild;
        return newParent;
    }

    int CalculateHeight(Node* node) { //In the form: height = 1 + max(Height(children)), where Height is a 1-based height
        if (node != nullptr) {
            int leftSubtreeHeight = 0;
            int rightSubtreeHeight = 0;
            if (node->left == nullptr && node->right == nullptr) {
                return 1;  //A lead would have a height of 1
            }
            if (node->left != nullptr) {
                leftSubtreeHeight = CalculateHeight(node->left);
            }
            if (node->right != nullptr) {
                rightSubtreeHeight = CalculateHeight(node->right);
            }

            if (leftSubtreeHeight >= rightSubtreeHeight)
                return (1 + leftSubtreeHeight);
            else
                return (1 + rightSubtreeHeight);
        }
        else
            return 0;
    }

    int BalanceFactor(Node* node) {
        if (node != nullptr) {
            int leftSubtreeHeight;
            int rightSubtreeHeight;
            if (node->left == nullptr)
                leftSubtreeHeight = 0;
            else
                leftSubtreeHeight = CalculateHeight(node->left);
            if (node->right == nullptr)
                rightSubtreeHeight = 0;
            else
                rightSubtreeHeight = CalculateHeight(node->right);
            return (leftSubtreeHeight - rightSubtreeHeight);
        }
        else // if the passed in node is a nullptr
            return 0;
    }

    Node* BalanceSubTree(Node* root, int balanceFactor) {
        Node* newParent = nullptr;
        if (root != nullptr) {
            root->height = CalculateHeight(root);
            if (root->height >= 3 && (balanceFactor > 1 || balanceFactor < -1)) { //So only balance a tree if it needs balancing; otherwise we can just skip all of this
                int leftChildBalanceFactor;
                int rightChildBalanceFactor;
                if (balanceFactor > 1)
                    leftChildBalanceFactor = BalanceFactor(root->left);
                if (balanceFactor < -1)
                    rightChildBalanceFactor = BalanceFactor(root->right);
                if (balanceFactor == 2) {
                    if (leftChildBalanceFactor == 1) {
                        newParent = RotateRight(root);
                    } else if (leftChildBalanceFactor == -1) {
                        root->left = RotateLeft(root->left);
                        newParent = RotateRight(root);
                    }
                    else
                        newParent = RotateRight(root);
                } else if (balanceFactor == -2) {
                    if (rightChildBalanceFactor == 1) {
                        root->right = RotateRight(root->right);
                        newParent = RotateLeft(root);
                    } else if (rightChildBalanceFactor == -1) {
                        newParent = RotateLeft(root);
                    }
                    else
                        newParent = RotateLeft(root);
                }
                if (newParent == nullptr)
                    return root;
                newParent->height = CalculateHeight(newParent); //After balancing, we recalculate the heights of all nodes involved in the rotations
                newParent->left->height = CalculateHeight(newParent->left);
                newParent->right->height = CalculateHeight(newParent->right);

            } else {
                newParent = root;
            }
            return newParent;
        }
        else
            return root;
    }

    Node* Insert(Node* root, key movieRating, value movie) {
        if (root == nullptr) {
            return new Node(movieRating, movie);
        }
        else if (movieRating == root->rating) {
            root->movieList.push_back(movie);
        }
        else if (movieRating < root->rating) {
            root->left = Insert(root->left, movieRating, movie);
        }
        else if (movieRating > root->rating) {
            root->right = Insert(root->right, movieRating, movie);
        }

        int balanceFactor = BalanceFactor(root); //So using recursion, we'll check all the way from bottom up that each node is balanced; in this way, we
        root = BalanceSubTree(root, balanceFactor);    // find the first node that breaks the threshold T and balance it
        return root;
    }

    void InorderTraversal(Node* node, vector<vector<value>>& movieLists) {
        if (node == nullptr)
            cout << "";
        else {
            InorderTraversal(node->left, movieLists);
            movieLists.push_back(node->movieList);
            InorderTraversal(node->right, movieLists);
        }
    }

    void searchRating(Node* node, key rating, vector<Node*>& nodeCarrier) { //Using a reference means we can pass an updated value through the recursive stack
        if (node == nullptr) {
            cout << "";
        }
        else {
            if (node->rating == rating) { //this vector's element will be checked to see if the value of the 1st element is an actual id or 0;
                nodeCarrier[0] = node; //in this way, we'll know if our element is there
            }
            searchRating(node->left, rating, nodeCarrier);
            searchRating(node->right, rating, nodeCarrier);
        }
    }

    Node* findSmallestNode(Node* node) { //this function is used to find the inorder successor; so using it on a root's right node find the inorder successor
        if (node->left == nullptr)
            return node;
        else
            return findSmallestNode(node->left);
    }

    Node* Remove(Node* root, key rating) {
        if (rating < root->rating) { //if the root id is less than the id
            root->left = Remove(root->left, rating);
        }
        else if (rating > root->rating) { //if the root id is greater than the id
            root->right = Remove(root->right, rating);
        }
        else { //if the root id = the id, then delete the node with 3 cases:
            if (root->right == nullptr && root->left == nullptr) { //if the root has no children
                delete root;
                return nullptr;
            }
            else if (root->right != nullptr && root->left != nullptr) { //if the root has 2 children
                if (root->right->left == nullptr) { //if the inorder successor is the immediately right node
                    root->movieList = root->right->movieList;
                    root->rating = root->right->rating;
                    root->right = Remove(root->right, root->rating);
                }
                else {
                    Node* inorderSuccessor = findSmallestNode(root->right); //else if the inorder successor is the smallest node of the right subtree
                    root->movieList = inorderSuccessor->movieList;
                    root->rating = inorderSuccessor->rating;
                    root->right =  Remove(root->right, root->rating);
                }

            }
            else { //if the root has 1 child
                int balanceFactor = BalanceFactor(root);
                if (balanceFactor >= 0) { //if that 1 child is the left child
                    root->movieList = root->left->movieList;
                    root->rating = root->left->rating;
                    root->left = Remove(root->left, root->rating);
                }
                else { //else that 1 child is the right child
                    root->movieList = root->right->movieList;
                    root->rating = root->right->rating;
                    root->right = Remove(root->right, root->rating);
                }
            }
        }

        //Re-balance the root after passing it in
        int balanceFactor = BalanceFactor(root);
        root = BalanceSubTree(root, balanceFactor);
        return root;
    }

    ~Map() { //Destructor since we use heap memory: just spam delete on the tree node until it becomes a nullptr
        while (treeRoot != nullptr)
            treeRoot = Remove(treeRoot, treeRoot->rating);
    }

//Map functions for the purposes of Project 3:
    void insert(key rating, value movie) {
        treeRoot = Insert(treeRoot, rating, movie);
        treeRoot = BalanceSubTree(treeRoot,BalanceFactor(treeRoot)); //balancing the tree root just to double check
    }
    vector<value>& operator[](key movieRating) {
        Map::Node *node = nullptr;
        vector<Map::Node *> nodeCarrier;
        nodeCarrier.push_back(node);
        searchRating(treeRoot, movieRating, nodeCarrier); //nodeCarrier, which is passed by reference, will contain a node =
        return nodeCarrier[0]->movieList; //if there are movies with the inputted rating
    }
};
