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
}

size_t trie::size() {
  return strie.size();
}

void trie::insert(string s2add) { // O(n) on the length of the longest string
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
  strie.insert(s2add); // Insert our string in our map, this takes O(log(n)), on the number of strings we have in our set
}

trie::TrieNode *trie::new_node(TrieNode *par, char val) {
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

void trie::erase(string s2rem) {
  if(strie.find(s2rem) == strie.end()) return;

  TrieNode *leaf = find(root, s2rem, 0);

  for(int i = (int)s2rem.length() - 1; i >= 0; i--) {
    if(leaf->nchild > 0) { // If the node has any child, just mark it as non leaf
      leaf->isLeaf = false;
      strie.erase(s2rem);
      return;
    }

    TrieNode *par = leaf->parent;
    delete par->child[s2rem[i] - 'a'];
    par->child[s2rem[i] - 'a'] = NULL;
    par->nchild--;
    leaf = par;
  }

  strie.erase(s2rem);
}

trie::TrieNode *trie::find(TrieNode *cur, string s2find, int pos) {
  if(pos == s2find.length()) {
    return cur;
  }

  return find(cur->child[s2find[pos] - 'a'], s2find, pos + 1);
}

bool trie::occurs(string pref) {
  TrieNode *cur = root;
  for(auto i = 0; i < pref.length(); i++) {
    if(cur->child[pref[i] - 'a'] == NULL) return false;
    cur = cur->child[pref[i] - 'a'];
  }

  return true;
}

vector<string> trie::allWords() {
  vector<string> ans; // Resulting vector with all strings

  for(auto it = strie.begin(); it != strie.end(); it++) {
    ans.push_back(*it);
  }

  return ans;
}

string trie::lcp() {
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
  dfs(root, "");
}

// Just for debugging
void trie::dfs(TrieNode *cur, string s) {
  if(cur->isLeaf) {
    cout << "Word " << s << " is in our trie." << endl;
  }
  for(auto i = 0; i < 26; i++) {
    if(cur->child[i] != NULL) {
      char c = 'a' + i;
      cout << "Visiting " << c << endl;
      dfs(cur->child[i], s + c);
    }
  }
}
