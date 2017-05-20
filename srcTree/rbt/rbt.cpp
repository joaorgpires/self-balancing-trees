//-------------------------------------
//-------------------------------------
//||                                 ||
//||        Joao Rebelo Pires        ||
//||                                 ||
//||              2017               ||
//||                                 ||
//-------------------------------------
//-------------------------------------

#include "rbt.h"
#include <iostream> // Just for debugs

using namespace std;

template<class T>
RBT<T>::RBT() {
  root = new Node();
  root = nullptr;
  size_of_tree = 0;
}

template<class T>
void RBT<T>::left_rotate(Node *cur) {
  // Ref: Introduction to Algorithms, CLRS
  Node *next = cur->right;
  cur->right = next->left;

  if(next->left != nullptr) next->left->par = cur;
  next->par = cur->par;

  if(cur->par == nullptr) root = next; // If cur was the root, we need to put y as the new root
  else if(cur == cur->par->left) cur->par->left = next;
  else cur->par->right = next;

  next->left = cur;
  cur->par = next;
}

template<class T>
void RBT<T>::right_rotate(Node *cur) {
  // Ref: Introduction to Algorithms, CLRS
  Node *next = cur->left;
  cur->left = next->right;

  if(next->right != nullptr) next->right->par = cur;
  next->par = cur->par;

  if(cur->par == nullptr) root = next; // If cur was the root, we need to put y as the new root
  else if(cur == cur->par->left) cur->par->left = next;
  else cur->par->right = next;

  next->right = cur;
  cur->par = next;
}

template<class T>
Color RBT<T>::color(Node *cur) {
  if(cur == nullptr) return BLACK;
  if(cur->col == BLACK) return BLACK;
  return RED;
}

template<class T>
void RBT<T>::insert(T val) {
  // Ref: Introduction to Algorithms, CLRS

  // Find if val is already in RBT tree
  if(find(val)) return;

  size_of_tree++;

  Node *next = new Node();
  next->val = val;

  Node *cur = root;
  Node *par = nullptr;

  while(cur != nullptr) {
    par = cur;
    if(l(next->val, cur->val)) cur = cur->left;
    else cur = cur->right;
  }

  next->par = par;

  if(par == nullptr) root = next;
  else if(l(next->val, par->val)) par->left = next;
  else par->right = next;

  next->left = nullptr;
  next->right = nullptr;
  next->col = RED;

  insertFixup(next);
}

template<class T>
void RBT<T>::debug() {
  cout << "START OF DEBUG" << endl;
  cout << "Root: ";
  printPreOrder(root);

  cout << "END OF DEBUG" << endl << endl;
}

template<class T>
void RBT<T>::printPreOrder(Node *cur) {
  if(cur == nullptr) {
    //cout << "Null with height " << height(cur) << endl;
    cout << endl;
    return;
  }

  cout << cur->val << " with color: " << printColor(cur) << endl;
  cout << "Left of " << cur->val << ": ";
  printPreOrder(cur->left);
  cout << "Right of " << cur->val << ": ";
  printPreOrder(cur->right);
}

template<class T>
string RBT<T>::printColor(Node *cur) {
  if(color(cur) == RED) return "RED";
  return "BLACK";
}

template<class T>
bool RBT<T>::find(T val) {
  return find(root, val);
}

template<class T>
bool RBT<T>::find(Node *cur, T val) {
  if(cur == nullptr) return false; // If we end up at a leaf node, val is not in AVL tree
  if(eq(cur->val, val)) return true; // If current node has the same val, return true
  if(l(cur->val, val)) return find(cur->right, val); // If val is greater than the current node's val, go right
  return find(cur->left, val); // If val is less than the current node's val, go left
}

template<class T>
void RBT<T>::insertFixup(Node *cur) {
  // Ref: Introduction to Algorithms, CLRS
  while(color(cur->par) == RED) {
    if(cur->par == cur->par->par->left) {
      Node *uncle = cur->par->par->right;
      if(color(uncle) == RED) {
        // Case 1 - cur's uncle is red
        cur->par->col = BLACK;
        uncle->col = BLACK;
        cur->par->par->col = RED;
        cur = cur->par->par;
      }
      else {
        if(cur == cur->par->right) {
          // Part of case 2 that does not overlap case 3 - Cur's uncle is black and cur is a right child
          cur = cur->par;
          left_rotate(cur);
        }

        // Case 3 (and rest of case 2) - Cur's uncle is black and cur is a left child
        cur->par->col = BLACK;
        cur->par->par->col = RED;
        right_rotate(cur->par->par);
      }
    }
    else {
      // Same as then clause with "right" and "left" exchanged
      Node *uncle = cur->par->par->left;
      if(color(uncle) == RED) {
        // Case 1 - cur's uncle is red
        cur->par->col = BLACK;
        uncle->col = BLACK;
        cur->par->par->col = RED;
        cur = cur->par->par;
      }
      else {
        if(cur == cur->par->left) {
          // Part of case 2 that does not overlap case 3 - Cur's uncle is black and cur is a left child
          cur = cur->par;
          right_rotate(cur);
        }

        // Case 3 (and rest of case 2) - Cur's uncle is black and cur is a right child
        cur->par->col = BLACK;
        cur->par->par->col = RED;
        left_rotate(cur->par->par);
      }
    }
  }

  root->col = BLACK;
}

template<class T>
size_t RBT<T>::size() {
  return size_of_tree;
}

template<class T>
void RBT<T>::erase(T val) {
  // Ref: Introduction to Algorithms, CLRS
  if(!find(val)) return; // If val is not in in Red-Black tree, return

  size_of_tree--;

  Node *cur = findNode(root, val);
  Node *next;
  Color cur_or_color = cur->col;

  if(cur->left == nullptr) {
    // Cur has no left child
    next = cur->right;
    transplant(cur, cur->right);
  }
  else if(cur->right == nullptr) {
    // Cur has no right child
    next = cur->left;
    transplant(cur, cur->left);
  }
  else {
    // Cur has two children
    Node *y = cur->right;
    while(y->left != nullptr) y = y->left; // Find minimum value from y
    next = y->right;
    cur_or_color = color(cur);

    if(y->par == cur) {
      if(next != nullptr) next->par = y;
    }
    else {
      transplant(y, y->right);
      y->right = cur->right;
      y->right->par = y;
    }

    transplant(cur, y);
    y->left = cur->left;
    y->left->par = y;
    y->col = color(cur);
  }

  if(cur_or_color == BLACK);

  delete cur;
}

template<class T>
void RBT<T>::transplant(Node *u, Node *v) {
  // Ref: Introduction to Algorithms, CLRS
  if(u->par == nullptr) root = v;
  else if(u == u->par->left) u->par->left = v;
  else u->par->right = v;

  if(v != nullptr) v->par = u->par;
}

template<class T>
typename RBT<T>::Node *RBT<T>::findNode(Node *cur, T val) {
  if(eq(cur->val, val)) return cur; // If current node has the same val, return cur
  if(l(cur->val, val)) return findNode(cur->right, val); // If val is greater than the current node's val, go right
  return findNode(cur->left, val); // If val is less than the current node's val, go left
}
