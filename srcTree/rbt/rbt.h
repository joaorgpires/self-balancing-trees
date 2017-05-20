//-------------------------------------
//-------------------------------------
//||                                 ||
//||        Joao Rebelo Pires        ||
//||                                 ||
//||              2017               ||
//||                                 ||
//-------------------------------------
//-------------------------------------

#ifndef rbt_h
#define rbt_h

/* -----------------------------
## A little background: (Ref: Introduction to Algorithms, CLRS)
## -----------------------------
## A Red-Black tree is a binary tree that satisfies the following **red-black
## properties**:
##
## 1. Every node is either red or black;
## 2. The root is black;
## 3. Every leaf (nullptr) is black;
## 4. If a node is red, then both its children are black;
## 5. For each node, all simple paths from the node to descendant leaves contain
## the same number of black nodes.
## ----------------------------- */

#include <functional> // Because of std::less

using namespace std;

enum Color {BLACK, RED};

template<class T>
class RBT {
public:
  // Variables


  // Methods
  RBT(); // Construct method for Red-Black tree
  void insert(T val); // Insert an element in Red-Black tree
  void debug(); // Function called or debugging
  //T maxValue(); // Function that returns the maximum value in Red-Black tree
  //T minValue(); // Function that returns the minimum value in Red-Black tree
  //void parDebug(); // Function that prints the parents
  size_t size(); // Function that returns the size of the Red-Black tree
  bool find(T val); // Returns true if val is in Red-Black tree - If iterator ends up being implemented, change this
  //void remove(T val); // Removes val from Red-Black tree

private:
  struct Node;

  // Variables
  Node *root;
  less<T> l; // For less comparations
  equal_to<T> eq; // For equal comparations
  size_t size_of_tree; // Size of Red-Black tree

  // Struct that defines each node in a Red-Black tree
  struct Node {
    T val; // Actual value in node
    Node *par; // Parent node
    Node *left; // Value to the left in tree
    Node *right; // Value to the right in tree
    Color col; // Color of the node
  };

  // Methods
  void left_rotate(Node *cur); // Performs a left rotation on node cur
  void right_rotate(Node *cur); // Performs a right rotation on node cur
  Color color(Node *cur); // Gets the color of node cur
  void printPreOrder(Node *cur);
  string printColor(Node *cur);
  bool find(Node *cur, T val); // Returns true if val is in Red-Black tree
  void insertFixup(Node *cur); // Fixes colors after inserting a new node
};

#endif
