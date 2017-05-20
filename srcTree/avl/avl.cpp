//-------------------------------------
//-------------------------------------
//||                                 ||
//||        Joao Rebelo Pires        ||
//||                                 ||
//||              2017               ||
//||                                 ||
//-------------------------------------
//-------------------------------------

#include "avl.h"
#include <iostream> // Just for debugs

using namespace std;

template<class T>
AVL<T>::AVL() {
  root = new Node();
  root = nullptr;
  size_of_tree = 0;
}

template<class T>
int AVL<T>::height(Node *cur) {
  if(cur == nullptr) return -1;

  return cur->height;
}

template<class T>
void AVL<T>::insert(T val) {
  // Search if val is already in AVL tree. If it is, simply return
  if(find(val)) return;

  // Increment the size of the AVL tree
  size_of_tree++;

  if(root == nullptr) { // If we have no root yet, add it and return
    addRoot(val);
    return;
  }

  // First of all, insert the node as usual in any BST
  Node *next = insertBST(val);
  // Now we need to balance the AVL tree
  balanceAVL(next);
}

template<class T>
void AVL<T>::addRoot(T val) {
  Node *next = new_node(val);

  next->par = nullptr;

  root = next;
}

template<class T>
typename AVL<T>::Node *AVL<T>::new_node(T val) {
  Node *next = new Node();

  next->val = val;
  next->left = nullptr;
  next->right = nullptr;
  next->height = 0;

  return next;
}

template<class T>
typename AVL<T>::Node *AVL<T>::insertBST(T val) {
  // Ref: Introduction to Algorithms, CLRS
  Node *par = nullptr; // Parent node of root is nullptr
  Node *cur = root;
  Node *next = new_node(val);

  while(cur != nullptr) {
    par = cur;
    if(l(next->val, cur->val)) cur = cur->left;
    else cur = cur->right;
  }

  next->par = par;
  if(l(next->val, par->val)) par->left = next;
  else par->right = next;

  return next;
}

template<class T>
void AVL<T>::debug() {
  cout << "START OF DEBUG" << endl;
  cout << "Root: ";
  printPreOrder(root);

  cout << "END OF DEBUG" << endl << endl;
}

template<class T>
void AVL<T>::printPreOrder(Node *cur) {
  if(cur == nullptr) {
    //cout << "Null with height " << height(cur) << endl;
    cout << endl;
    return;
  }

  cout << cur->val << " with height: " << height(cur) << endl;
  cout << "Left of " << cur->val << ": ";
  printPreOrder(cur->left);
  cout << "Right of " << cur->val << ": ";
  printPreOrder(cur->right);
}

template<class T>
T AVL<T>::maxValue() {
  Node *cur = root;
  while(cur->right != nullptr) cur = cur->right; // The max value in an AVL tree is the rightmost leaf

  return cur->val;
}

template<class T>
T AVL<T>::minValue() {
  Node *cur = root;
  while(cur->left != nullptr) cur = cur->left; // The min value in an AVL tree is the leftmost leaf

  return cur->val;
}

template<class T>
void AVL<T>::balanceAVL(Node *cur, bool rem) {
  //cout << "Balancing after inserting " << cur->val << endl;
  while(cur->par != nullptr) {
    if(rem) cur->par->height = max(height(cur->par->left), height(cur->par->right)) + 1;
    else cur->par->height = max(height(cur->par), height(cur) + 1);
    //cout << cur->par->val << " " << height_diff(cur->par) << endl;
    if(height_diff(cur->par) > 1) {
      rotate(cur->par);
      if(!rem) return; // If we are inserting, we can stop recursion to root
    }

    cur = cur->par;
  }
}

template<class T>
int AVL<T>::height_diff(Node *cur){
  return abs(height(cur->left) - height(cur->right));
}

template<class T>
void AVL<T>::rotate(Node *cur) {
  //cout << cur->val << ": Need to rotate!" << endl;
  Node *a, *b, *c, *t1, *t2, *t3, *t4; // Find these satisfying the property a < b < c and everything t1 < everything t2 < everything t3 < everything t4

  if(height(cur->left) > height(cur->right)) {
    if(height(cur->left->left) > height(cur->left->right)) {
      // Case left left
      c = cur;
      b = cur->left;
      a = cur->left->left;

      // t1 - handle nullptr
      //if(cur->left->left != nullptr)
      t1 = cur->left->left->left;
      //else t1 = nullptr;

      // t2 - handle nullptr
      //if(cur->left->left != nullptr)
      t2 = cur->left->left->right;
      //else t2 = nullptr;

      // t3 - handle nullptr
      //if(cur->left != nullptr)
      t3 = cur->left->right;
      //else t3 = nullptr;

      // t4 - handle nullptr
      //if(cur != nullptr)
      t4 = cur->right;
      //else t4 = nullptr;
    }
    else {
      // Case left right
      c = cur;
      a = cur->left;
      b = cur->left->right;

      // t1 - handle nullptr
      //if(cur->left != nullptr)
      t1 = cur->left->left;
      //else t1 = nullptr;

      // t2 - handle nullptr
      //if(cur->left->right != nullptr)
      t2 = cur->left->right->left;
      //else t2 = nullptr;

      // t3 - handle nullptr
      //if(cur->left->right != nullptr)
      t3 = cur->left->right->right;
      //else t3 = nullptr;

      // t4 - handle nullptr
      //if(cur != nullptr)
      t4 = cur->right;
      //else t4 = nullptr;
    }
  }
  else {
    if(height(cur->right->left) < height(cur->right->right)) {
      // Case right right
      a = cur;
      b = cur->right;
      c = cur->right->right;

      // t1 - handle nullptr
      //if(cur != nullptr)
      t1 = cur->left;
      //else t1 = nullptr;

      // t2 - handle nullptr
      //if(cur->right != nullptr)
      t2 = cur->right->left;
      //else t2 = nullptr;

      // t3 - handle nullptr
      //if(cur->right->right != nullptr)
      t3 = cur->right->right->left;
      //else t3 = nullptr;

      // t4 - handle nullptr
      //if(cur->right->right != nullptr)
      t4 = cur->right->right->right;
      //else t4 = nullptr;
    }
    else {
      // Case right left
      a = cur;
      c = cur->right;
      b = cur->right->left;

      // t1 - handle nullptr
      //if(cur != nullptr)
      t1 = cur->left;
      //else t1 = nullptr;

      // t2 - handle nullptr
      //if(cur->right->left != nullptr)
      t2 = cur->right->left->left;
      //else t2 = nullptr;

      // t3 - handle nullptr
      //if(cur->right->left != nullptr)
      t3 = cur->right->left->right;
      //else t3 = nullptr;

      // t4 - handle nullptr
      //if(cur->right != nullptr)
      t4 = cur->right->right;
      //else t4 = nullptr;
    }
  }

  b->left = a;
  b->right = c;
  a->left = t1;
  a->right = t2;
  c->left = t3;
  c->right = t4;

  a->height = max(height(t1), height(t2)) + 1;
  c->height = max(height(t3), height(t4)) + 1;
  b->height = max(height(a), height(c)) + 1;
  b->par = cur->par;

  if(cur == root) root = b;
  else if(cur->par->left == cur) b->par->left = b;
  else b->par->right = b;

  a->par = b;
  c->par = b;

  if(t1 != nullptr) t1->par = a;
  if(t2 != nullptr) t2->par = a;
  if(t3 != nullptr) t3->par = c;
  if(t4 != nullptr) t4->par = c;
}

template<class T>
void AVL<T>::parDebug() {
  cout << "-------PARENT DEBUG-------" << endl;
  parPrint(root->left);
  parPrint(root->right);
  cout << "-------END OF PARENT DEBUG-------" << endl << endl;
}

template<class T>
void AVL<T>::parPrint(Node *cur) {
  if(cur == nullptr) return;

  cout << "Parent of " << cur->val << ": " << cur->par->val << endl;
  parPrint(cur->left);
  parPrint(cur->right);
}

template<class T>
size_t AVL<T>::size() {
  return size_of_tree;
}

template<class T>
bool AVL<T>::find(T val) {
  return find(root, val);
}

template<class T>
bool AVL<T>::find(Node *cur, T val) {
  if(cur == nullptr) return false; // If we end up at a leaf node, val is not in AVL tree
  if(eq(cur->val, val)) return true; // If current node has the same val, return true
  if(l(cur->val, val)) return find(cur->right, val); // If val is greater than the current node's val, go right
  return find(cur->left, val); // If val is less than the current node's val, go left
}

template<class T>
void AVL<T>::remove(T val) {
  if(!find(val)) return;

  size_of_tree--;

  Node *r = findNode(root, val);
  bool left;
  Node *par = r->par;
  (r == par->left) ? left = true : left = false;
  removeBST(r);

  if(par == nullptr) {
    root->height = max(height(root->left), height(root->right)) + 1;
    if(left) balanceAVL(root->left, true);
    else balanceAVL(root->right, true);
  }
  else {
    par->height = max(height(par->left), height(par->right)) + 1;
    balanceAVL(par, true);
  }
}

template<class T>
typename AVL<T>::Node *AVL<T>::findNode(Node *cur, T val) {
  if(eq(cur->val, val)) return cur; // If current node has the same val, return cur
  if(l(cur->val, val)) return findNode(cur->right, val); // If val is greater than the current node's val, go right
  return findNode(cur->left, val); // If val is less than the current node's val, go left
}

template<class T>
void AVL<T>::removeBST(Node *cur) {
  // Ref: Introduction to Algorithms, CLRS
  if(cur->left == nullptr) transplant(cur, cur->right);
  else if(cur->right == nullptr) transplant(cur, cur->left);
  else { // Balance if we have problems with y->right children
    Node *y = cur->right;
    while(y->left != nullptr) y = y->left;
    if(y->par != cur) {
      transplant(y, y->right);
      y->right = cur->right;
      y->right->par = y;
      y->right->height = max(height(y->right->left), height(y->right->right)) + 1;
    }
    transplant(cur, y);
    y->left = cur->left;
    y->left->par = y;
    y->left->height = max(height(y->left->left), height(y->left->right)) + 1;

    if(y->right != nullptr && height_diff(y->right) > 1) {
      rotate(y->right);
    }
    y->height = max(height(y->left), height(y->right)) + 1;
  }

  delete cur;
}

template<class T>
void AVL<T>::transplant(Node *u, Node *v) {
  // Ref: Introduction to Algorithms, CLRS
  if(u->par == nullptr) root = v;
  else if(u == u->par->left) u->par->left = v;
  else u->par->right = v;

  if(v != nullptr) v->par = u->par;
}
