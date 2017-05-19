//-------------------------------------
//-------------------------------------
//||                                 ||
//||        Joao Rebelo Pires        ||
//||                                 ||
//||              2017               ||
//||                                 ||
//-------------------------------------
//-------------------------------------

#ifndef avl_h
#define avl_h

#include <functional> // Because of std::less

using namespace std;

template<class T>
class AVL {
public:
  // Variables


  // Methods
  AVL(); // Construct method for AVL tree
  void insert(T val); // Insert an element in AVL tree
  void debug(); // Function called or debugging
  T maxValue(); // Function that returns the maximum value in AVL tree
  T minValue(); // Function that returns the minimum value in AVL tree
  void parDebug(); // Function that prints the parents
  size_t size(); // Function that returns the size of the AVL tree
  bool find(T val); // Returns true if val is in AVL - If iterator ends up being implemented, change this

private:
  struct Node;

  // Variables
  Node *root;
  less<T> l; // For less comparations
  equal_to<T> eq; // For equal comparations
  size_t size_of_tree; // Size of AVL tree

  // Struct that defines each node in an AVL tree
  struct Node {
    T val; // Actual value in node
    Node *par; // Parent node
    Node *left; // Value to the left in tree
    Node *right; // Value to the right in tree
    int height; // Height of the node
  };

  // Methods
  int height(Node *cur); // Get the height of Node cur
  void addRoot(T val); // Add root to this AVL tree
  Node *new_node(T val); // Create a new node with parent par and value val
  Node *insertBST(T val); // Insert val in AVL tree like one usually does in a Binary Search Tree
  void printPreOrder(Node *cur); // Function for debug, prints AVL in pre order
  void balanceAVL(Node *cur); // Function for rebalancing the AVL tree
  int height_diff(Node *cur); // Function for the difference between the heights of the children of node cur
  void rotate(Node *cur); // Function that performs the rotation in case one needs to rotate the tree
  void parPrint(Node *cur); // Function that prints the parents
  bool find(Node *cur, T val); // returns true if val is in AVL
};

#endif
