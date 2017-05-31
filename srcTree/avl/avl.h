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
  void debug(); // Function called or debugging
  void insert(T val); // Insert an element in AVL tree
  bool empty(); // Returns true if tree is empty
  void erase(T val); // Removes val from AVL
  bool find(T val); // Returns true if val is in AVL - If iterator ends up being implemented, change this
  T maxValue(); // Function that returns the maximum value in AVL tree
  T minValue(); // Function that returns the minimum value in AVL tree
  void parDebug(); // Function that prints the parents
  size_t size(); // Function that returns the size of the AVL tree

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
  void addRoot(T val); // Add root to this AVL tree
  void balanceAVL(Node *cur, bool rem = false); // Function for rebalancing the AVL tree. If rem = true, then we are balancing after removal
  void eraseBST(Node *cur); // Removes the val from AVL tree like one usually does in a Binary Search Tree
  bool find(Node *cur, T val); // returns true if val is in AVL
  Node *findNode(Node *cur, T val);
  int height(Node *cur); // Get the height of Node cur
  int height_diff(Node *cur); // Function for the difference between the heights of the children of node cur
  Node *insertBST(T val); // Insert val in AVL tree like one usually does in a Binary Search Tree
  Node *new_node(T val); // Create a new node with parent par and value val
  void parPrint(Node *cur); // Function that prints the parents
  void printPreOrder(Node *cur); // Function for debug, prints AVL in pre order
  void rotate(Node *cur); // Function that performs the rotation in case one needs to rotate the tree
  void transplant(Node *u, Node *v); // Transplants v into u's position
};

#endif
