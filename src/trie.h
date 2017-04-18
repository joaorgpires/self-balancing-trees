//-------------------------------------
//-------------------------------------
//||                                 ||
//||        Joao Rebelo Pires        ||
//||                                 ||
//||              2017               ||
//||                                 ||
//-------------------------------------
//-------------------------------------

// For now, let us implement this only for strings
// Each node will have a boolean marking it as a leaf (or not)
// In order to get everything on trie, we could probably do a dfs and get a vector of strings
// Or simply have a map that saves all words in set, which is way easier, right Joao?
// Maybe keep a set with each TrieNode, to help with iterator

#ifndef trie_h
#define trie_h

#include <string>
#include <set>
#include <vector>

using namespace std;

class trie {
public:
  //Methods:
  trie();
  size_t size();
  void insert(string s2add); // Name is self explanatory
  void erase(string s2rem); // Name is self explanatory
  bool occurs(string pref); // Checks if pref is a prefix of any word in trie
  vector<string> allWords(); // Returns a vector with all the words present in the trie, lexicographicaly ordered
  string lcp(); // Longest common prefix
  void debug(); // Just for debugging

private:
  struct TrieNode;

  // Struct that defines each node in my trie
  struct TrieNode {
    TrieNode *parent; // Parent of the current trie node
    char value; // Actual value in node/edge from parent to current node
    int nchild; // Number of child nodes of current node
    bool isLeaf; // If a word ends in this node, this is set to true

    TrieNode *child[26]; // The child nodes for a node are 26, 1 for each letter in the alphabet
  };

  // Variables
  TrieNode *root; // Root of this trie
  set<string> strie; // Set of strings that exist in our trie

  // Methods
  TrieNode *new_node(TrieNode *par, char val); // Creates and returns a new node
  TrieNode *find(TrieNode *cur, string s2find, int pos); // Finds the node where s2find ends
  void dfs(TrieNode *cur, string s); // Just for debugging
};

#endif


// Probably will not be used, as it makes no sense to have an iterator in a Trie (?)
/*
public:
// Iterator implementation, you can ignore if you want until -----------------------------------
class iterator : public std::iterator<std::random_access_iterator_tag, char> {
private:
TrieNode *cur;
public:
iterator() {
this->cur = NULL;
}

iterator(const iterator & it) {
this->cur = it.cur;
}

iterator(const trie *cur) {
this->cur = cur;
}
};
//-----------------------------------
*/
