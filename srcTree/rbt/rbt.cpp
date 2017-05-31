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

// ######################################################################

template<class T>
RBT<T>::RBT() {
  root = new Node();
  sentinel = new Node();
  sentinel->par = sentinel->left = sentinel->right = sentinel;
  root = sentinel;
  size_of_tree = 0;
}

// ######################################################################

template<class T>
void RBT<T>::clear() {
  clear(root);
  root = sentinel;
  size_of_tree = 0;
}

// ######################################################################

template<class T>
void RBT<T>::debug() {
  cout << "START OF DEBUG" << endl;
  if(root == sentinel) {
    cout << "Empty tree." << endl;
    cout << "END OF DEBUG" << endl << endl;
    return;
  }

  cout << "Root: ";
  printPreOrder(root);

  cout << "END OF DEBUG" << endl << endl;
}

// ######################################################################

template<class T>
bool RBT<T>::empty() {
  return size_of_tree == 0;
}

// ######################################################################

template<class T>
void RBT<T>::erase(T val) {
  // Ref: Introduction to Algorithms, CLRS
  if(!find(val)) return; // If val is not in in Red-Black tree, return

  size_of_tree--;

  Node *cur = findNode(root, val);
  Node *next;
  Color cur_or_color = cur->col;

  if(cur->left == sentinel) {
    // Cur has no left child
    next = cur->right;
    transplant(cur, cur->right);
  }
  else if(cur->right == sentinel) {
    // Cur has no right child
    next = cur->left;
    transplant(cur, cur->left);
  }
  else {
    // Cur has two children
    Node *y = cur->right;
    while(y->left != sentinel) y = y->left; // Find minimum value from y
    next = y->right;
    cur_or_color = color(y);

    if(next == sentinel) next->par = y->par;

    if(y->par == cur) {
      next->par = y;
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

  if(cur_or_color == BLACK) eraseFixup(next);

  delete cur;
}

// ######################################################################

template<class T>
bool RBT<T>::find(T val) {
  return find(root, val);
}

// ######################################################################

template<class T>
void RBT<T>::insert(T val) {
  // Ref: Introduction to Algorithms, CLRS

  // Find if val is already in RBT tree
  if(find(val)) return;

  size_of_tree++;

  Node *next = new Node();
  next->val = val;

  Node *cur = root;
  Node *par = sentinel;

  while(cur != sentinel) {
    par = cur;
    if(l(next->val, cur->val)) cur = cur->left;
    else cur = cur->right;
  }

  next->par = par;

  if(par == sentinel) root = next;
  else if(l(next->val, par->val)) par->left = next;
  else par->right = next;

  next->left = sentinel;
  next->right = sentinel;
  next->col = RED;

  insertFixup(next);
}

// ######################################################################

template<class T>
T RBT<T>::maxValue() {
  Node *cur = root;
  while(cur->right != sentinel) cur = cur->right; // The max value in a Red-Black tree is the rightmost leaf

  return cur->val;
}

// ######################################################################

template<class T>
T RBT<T>::minValue() {
  Node *cur = root;
  while(cur->left != sentinel) cur = cur->left; // The min value in a Red-Black tree is the leftmost leaf

  return cur->val;
}

// ######################################################################

template<class T>
size_t RBT<T>::size() {
  return size_of_tree;
}

// ######################################################################

template<class T>
void RBT<T>::clear(Node *cur) {
  if(cur->left == sentinel && cur->right == sentinel) {
    if(cur->par->left == cur) cur->par->left = sentinel;
    else cur->par->right = sentinel;
    delete cur;
    return;
  }
  clear(cur->left);
  clear(cur->right);
  if(cur->par->left == cur) cur->par->left = sentinel;
  else cur->par->right = sentinel;
  delete cur;
}

// ######################################################################

template<class T>
Color RBT<T>::color(Node *cur) {
  if(cur == sentinel) return BLACK;
  if(cur->col == BLACK) return BLACK;
  return RED;
}

// ######################################################################

template<class T>
void RBT<T>::eraseFixup(Node *cur) {
  // Ref: Introduction to Algorithms, CLRS
  while(cur != root && color(cur) == BLACK) {
    if(cur == cur->par->left) {
      Node *w = cur->par->right;
      if(color(w) == RED) {
        // Case 1 - cur's sibling w is red. This transforms case 1 into case 2
        w->col = BLACK;
        cur->par->col = RED;
        left_rotate(cur->par);
        w = cur->par->right;
      }
      if(color(w->left) == BLACK && color(w->right) == BLACK) {
        // Case 2 - cur's sibling w is black, and both of w's children are black
        w->col = RED;
        cur = cur->par;
      }
      else {
        if(color(w->right) == BLACK) {
          // Case 3 - cur's sibling w is black, w's left child is red and w's right child is black. This transforms case 1 into case 2
          w->left->col = BLACK;
          w->col = RED;
          right_rotate(w);
          w = cur->par->right;
        }
        // Case 4 - cur's sibling w is black, and w's right child is red
        w->col = cur->par->col;
        cur->par->col = BLACK;
        w->right->col = BLACK;
        left_rotate(cur->par);
        cur = root;
      }
    }
    else {
      // Same as then clause with "right" and "left" exchanged
      Node *w = cur->par->left;
      if(color(w) == RED) {
        w->col = BLACK;
        cur->par->col = RED;
        right_rotate(cur->par);
        w = cur->par->left;
      }
      if(color(w->right) == BLACK && color(w->left) == BLACK) {
        w->col = RED;
        cur = cur->par;
      }
      else {
        if(color(w->left) == BLACK) {
          w->right->col = BLACK;
          w->col = RED;
          left_rotate(w);
          w = cur->par->left;
        }
        w->col = cur->par->col;
        cur->par->col = BLACK;
        w->left->col = BLACK;
        right_rotate(cur->par);
        cur = root;
      }
    }
  }

  cur->col = BLACK;
}

// ######################################################################

template<class T>
bool RBT<T>::find(Node *cur, T val) {
  if(cur == sentinel) return false; // If we end up at a leaf node, val is not in AVL tree
  if(eq(cur->val, val)) return true; // If current node has the same val, return true
  if(l(cur->val, val)) return find(cur->right, val); // If val is greater than the current node's val, go right
  return find(cur->left, val); // If val is less than the current node's val, go left
}

// ######################################################################

template<class T>
typename RBT<T>::Node *RBT<T>::findNode(Node *cur, T val) {
  if(eq(cur->val, val)) return cur; // If current node has the same val, return cur
  if(l(cur->val, val)) return findNode(cur->right, val); // If val is greater than the current node's val, go right
  return findNode(cur->left, val); // If val is less than the current node's val, go left
}

// ######################################################################

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
        cur->par->col = BLACK;
        uncle->col = BLACK;
        cur->par->par->col = RED;
        cur = cur->par->par;
      }
      else {
        if(cur == cur->par->left) {
          cur = cur->par;
          right_rotate(cur);
        }

        cur->par->col = BLACK;
        cur->par->par->col = RED;
        left_rotate(cur->par->par);
      }
    }
  }

  root->col = BLACK;
}

// ######################################################################

template<class T>
void RBT<T>::left_rotate(Node *cur) {
  // Ref: Introduction to Algorithms, CLRS
  Node *next = cur->right;
  cur->right = next->left;

  if(next->left != sentinel) next->left->par = cur;
  next->par = cur->par;

  if(cur->par == sentinel) root = next; // If cur was the root, we need to put y as the new root
  else if(cur == cur->par->left) cur->par->left = next;
  else cur->par->right = next;

  next->left = cur;
  cur->par = next;
}

// ######################################################################

template<class T>
string RBT<T>::printColor(Node *cur) {
  if(color(cur) == RED) return "RED";
  return "BLACK";
}

// ######################################################################

template<class T>
void RBT<T>::printPreOrder(Node *cur) {
  if(cur == sentinel) {
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

// ######################################################################

template<class T>
void RBT<T>::right_rotate(Node *cur) {
  // Ref: Introduction to Algorithms, CLRS
  Node *next = cur->left;
  cur->left = next->right;

  if(next->right != sentinel) next->right->par = cur;
  next->par = cur->par;

  if(cur->par == sentinel) root = next; // If cur was the root, we need to put y as the new root
  else if(cur == cur->par->left) cur->par->left = next;
  else cur->par->right = next;

  next->right = cur;
  cur->par = next;
}

// ######################################################################

template<class T>
void RBT<T>::transplant(Node *u, Node *v) {
  // Ref: Introduction to Algorithms, CLRS
  if(u->par == sentinel) root = v;
  else if(u == u->par->left) u->par->left = v;
  else u->par->right = v;

  v->par = u->par;
}

// ######################################################################

// ############################## ITERATOR ##############################

// ######################################################################

template<class T>
typename RBT<T>::iterator RBT<T>::begin() {
  if(empty()) return end();
  Node *cur = root;
  while(cur->left != sentinel) cur = cur->left;
  return iterator(cur, sentinel, root);
}

// ######################################################################

template<class T>
typename RBT<T>::iterator RBT<T>::end() {
  return iterator(sentinel, sentinel, root);
}

// ######################################################################

template<class T>
typename RBT<T>::iterator RBT<T>::find(T val, int dummy) {
  return find(root, val, dummy);
}

// ######################################################################

template<class T>
typename RBT<T>::iterator RBT<T>::find(Node *cur, T val, int dummy) {
  if(cur->val == val) return iterator(cur, sentinel, root);
  if(cur == sentinel) return end();
  if(cur->val < val) return find(cur->right, val, dummy);
  return find(cur->left, val, dummy);
}

// ######################################################################

template<class T>
typename RBT<T>::iterator RBT<T>::upper_bound(T val) {
  if(root == sentinel) return end();
  return upper_bound(val, root);
}

// ######################################################################

template<class T>
typename RBT<T>::iterator RBT<T>::upper_bound(T val, Node *cur) {
  if(val == cur->val) return iterator(cur, sentinel, root)++;
  if(val < cur->val) {
    if(cur->left == sentinel) return iterator(cur, sentinel, root);
    else return upper_bound(val, cur->left);
  }
  if(cur->right == sentinel) return iterator(cur, sentinel, root)++;
  else return upper_bound(val, cur->right);
}

// ######################################################################

template<class T>
typename RBT<T>::iterator RBT<T>::lower_bound(T val) {
  if(root == sentinel) return end();
  return lower_bound(val, root);
}

// ######################################################################

template<class T>
typename RBT<T>::iterator RBT<T>::lower_bound(T val, Node *cur) {
  if(val == cur->val) return iterator(cur, sentinel, root);
  if(val < cur->val) {
    if(cur->left == sentinel) return iterator(cur, sentinel, root)--;
    else return lower_bound(val, cur->left);
  }
  if(cur->right == sentinel) return iterator(cur, sentinel, root);
  else return lower_bound(val, cur->right);
}

// ######################################################################
