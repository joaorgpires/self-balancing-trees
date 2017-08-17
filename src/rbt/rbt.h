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
#include <iterator> // For iterators
#include <iostream>

using namespace std;

enum Color {BLACK, RED};

template<class T>
class RBT {
public:
  // Variables


  // Methods
  RBT(); // Construct method for Red-Black tree
  void clear(); // Clears Red-Black tree
  void debug(); // Function called or debugging
  bool empty(); // Returns true if tree is empty
  void erase(T val); // Removes val from Red-Black tree
  bool find(T val); // Returns true if val is in Red-Black tree - If iterator ends up being implemented, change this
  void insert(T val); // Insert an element in Red-Black tree
  T maxValue(); // Function that returns the maximum value in Red-Black tree
  T minValue(); // Function that returns the minimum value in Red-Black tree
  size_t size(); // Function that returns the size of the Red-Black tree

private:
  struct Node;

  // Variables
  Node *root; // Root of Red-Black tree
  Node *sentinel; // Sentinel (Ref: Introduction to Algorithms, CLRS)
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
  void clear(Node *cur); // Clears Red-Black tree, recursively
  Color color(Node *cur); // Gets the color of node cur
  void eraseFixup(Node *cur); // Fixes colors after erasing a node
  bool find(Node *cur, T val); // Returns true if val is in Red-Black tree
  Node *findNode(Node *cur, T val); // Find node with value val
  void insertFixup(Node *cur); // Fixes colors after inserting a new node
  void left_rotate(Node *cur); // Performs a left rotation on node cur
  string printColor(Node *cur); // Prints color of node cur
  void printPreOrder(Node *cur); // Prints the whole tree in pre order
  void right_rotate(Node *cur); // Performs a right rotation on node cur
  void transplant(Node *u, Node* v); // Transplants v into u's position

public:
  /* -----------------------------
  ## Iterators
  ## -----------------------------
  ## This is just a simple try to implement iterators in this tree.
  ## ----------------------------- */
  class iterator : public std::iterator<std::random_access_iterator_tag, T> {
  private:
    Node *cur;
    Node *sentinel;
    Node *root;

  public:
    iterator() {
      this->cur = nullptr;
      this->sentinel = nullptr;
      this->root = nullptr;
    }

    iterator(Node *cur, Node *sentinel, Node *root) {
      this->cur = cur;
      this->sentinel = sentinel;
      this->root = root;
    }

    T &operator*() const {
      return cur->val;
    }

    bool operator==(const iterator &rhs) {
      return cur == rhs.cur;
    }

    bool operator!=(const iterator &rhs) {
      return cur != rhs.cur;
    }

    iterator operator++() {
      // Ref: SGI
      iterator i = *this;
      if(cur->right != sentinel) {
        cur = cur->right;
        while(cur->left != sentinel) cur = cur->left;
      }
      else {
        Node *y = cur->par;
        while(cur == y->right){
          cur = y;
          y = y->par;
        }
        if(cur->right != y) cur = y;
      }

      return i;
    }

    iterator operator++(int dummy) {
      // Ref: SGI
      if(cur->right != sentinel) {
        cur = cur->right;
        while(cur->left != sentinel) cur = cur->left;
      }
      else {
        Node *y = cur->par;
        while(cur == y->right){
          cur = y;
          y = y->par;
        }
        if(cur->right != y) cur = y;
      }

      return *this;
    }

    iterator operator--() {
      // Ref: SGI
      iterator i = *this;

      if(cur == sentinel) {
        cur = root;
        while(cur->right != sentinel) cur = cur->right;
      }
      else if (cur->left != sentinel) {
        Node *y = cur->left;
        while(y->right != sentinel)
        y = y->right;
        cur = y;
      }
      else {
        Node *y = cur->par;
        while(cur == y->left) {
          cur = y;
          y = y->par;
        }
        cur = y;
      }

      return i;
    }

    iterator operator--(int dummy) {
      // Ref: SGI
      if(cur == sentinel) {
        cur = root;
        while(cur->right != sentinel) cur = cur->right;
      }
      else if (cur->left != sentinel) {
        Node *y = cur->left;
        while(y->right != sentinel)
        y = y->right;
        cur = y;
      }
      else {
        Node *y = cur->par;
        while(cur == y->left) {
          cur = y;
          y = y->par;
        }
        cur = y;
      }

      return *this;
    }
  };

  // Iterator methods
  iterator begin(); // Intended to work as STL's begin (possibly with different complexity)
  iterator end(); // Intended to work as STL's end (possibly with different complexity)
  iterator find(T val, int dummy); // To distinguish from boolean returning function, intended to work as STL's find (possibly with different complexity)
  iterator upper_bound(T val); // Intended to work as STL's upper_bound (possibly with different complexity)
  iterator lower_bound(T val); // Intended to work as STL's lower_bound (possibly with different complexity)

private:
  // Iterator methods
  iterator find(Node *cur, T val, int dummy);
  iterator upper_bound(T val, Node *cur);
  iterator lower_bound(T val, Node *cur);
};

#endif
