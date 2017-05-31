//-------------------------------------
//-------------------------------------
//||                                 ||
//||        Joao Rebelo Pires        ||
//||                                 ||
//||              2017               ||
//||                                 ||
//-------------------------------------
//-------------------------------------

#include "trie.h"
#include <iostream>

using namespace std;

trie::trie() {
  root = new TrieNode(); // Make sure to do this, otherwise you will get seg fault!

  root->parent = NULL;
  root->value = '\0';
  root->nchild = 0;
  root->isLeaf = false;
  for(auto i = 0; i < 26; i++) {
    root->child[i] = NULL;
  }

  n_words = 0;
}

size_t trie::size() {
  return n_words;
}

void trie::insert(string s2add) { // O(n) on the length of the longest string
  if(find(s2add)) return; // If s2add is already in our trie, do nothing

  n_words++; // If s2add is a new word, increment the number of words in our trie

  auto cur = root;
  for(auto i = 0; i < s2add.length(); i++) {
    int letter = s2add[i] - 'a';
    if(cur->child[letter] == NULL) { // In case the node does not exist yet, create it. Just continue if it does
      TrieNode *next = new_node(cur, s2add[i]);
      cur->child[letter] = next;
    }

    cur = cur->child[letter];
  }

  cur->isLeaf = true;
}

typename trie::TrieNode *trie::new_node(TrieNode *par, char val) {
  TrieNode *next = new TrieNode();
  next->parent = par;
  next->value = val;
  next->nchild = 0;
  next->isLeaf = false;

  for(auto i = 0; i < 26; i++) {
    next->child[i] = NULL;
  }

  par->nchild++;

  return next;
}

bool trie::find(string s2find) {
  if(!occurs(s2find)) return false; // If s2find is not a prefix in our trie, it is not a word for sure
  TrieNode *leaf = find(root, s2find, 0);

  if(!leaf->isLeaf) return false;

  return true;
}

void trie::erase(string s2rem) {
  if(!find(s2rem)) return; // If leaf node is not a leaf, it means that s2rem is only a prefix, not a word

  TrieNode *leaf = find(root, s2rem, 0);

  n_words--;

  if(leaf->nchild > 0) { // If the node has any child, just mark it as non leaf
    leaf->isLeaf = false;
    return;
  }

  for(int i = (int)s2rem.length() - 1; i >= 0; i--) {
    if(leaf->nchild > 0) { // If the node has any child, just leave it as it is and return
      return;
    }

    TrieNode *par = leaf->parent;
    delete par->child[s2rem[i] - 'a'];
    par->child[s2rem[i] - 'a'] = NULL;
    par->nchild--;
    leaf = par;
  }
}

typename trie::TrieNode *trie::find(TrieNode *cur, string s2find, int pos) {
  if(pos == s2find.length()) { // If we find the leaf node, return it
    return cur;
  }

  if(cur->child[s2find[pos] - 'a'] == NULL) { // If we find a node that has no child nodes while reading word s2find, s2find is not in our trie
    return NULL;
  }

  return find(cur->child[s2find[pos] - 'a'], s2find, pos + 1);
}

bool trie::occurs(string pref) {
  if(find(root, pref, 0) == NULL) return false;

  return true;
}

vector<string> trie::allWords() {
  vector<string> ans; // Resulting vector with all strings

  dfs(root, "", ans);

  return ans;
}

string trie::lcp(string beg) {
  TrieNode *cur = root;
  string ans = ""; // Resulting lcp

  while(cur->nchild > 0) { // Do loop while current has any child
    if(cur->nchild != 1) return ans; // If node has more than one child, then return lcp
    for(auto i = 0; i < 26; i++) { // Search for the child
      if(cur->child[i] != NULL) {
        char c = i + 'a';
        ans += c;
        cur = cur->child[i];
        break;
      }
    }
  }

  return ans;
}

// Just for debugging
void trie::debug() {
  vector<string> ans;
  dfs(root, "", ans);
}

// Just for debugging
void trie::dfs(TrieNode *cur, string s, vector<string> &ans) {
  //cout << "Cur child: " << cur->nchild << endl;
  if(cur->isLeaf) {
    //cout << "Word " << s << " is in our trie." << endl;
    ans.push_back(s);
  }
  for(auto i = 0; i < 26; i++) {
    if(cur->child[i] != NULL) {
      char c = 'a' + i;
      //cout << "Visiting " << c << endl;
      //cout << cur->child[i]->nchild << endl;
      dfs(cur->child[i], s + c, ans);
    }
  }
}
