//-------------------------------------
//-------------------------------------
//||                                 ||
//||        Joao Rebelo Pires        ||
//||                                 ||
//||              2017               ||
//||                                 ||
//-------------------------------------
//-------------------------------------

#include <iostream>
#include "trie.h"

using namespace std;

set<string> myset;

int main() {
  trie t;

  t.insert("joao");
  t.insert("vanda");
  t.insert("ana");
  t.insert("ananas");
  t.insert("anaconda");
  t.insert("antigo");
  t.insert("rui");
  vector<string> words = t.allWords();

  cout << t.size() << endl;
  for(auto& word : words) {
    cout << word << " is in our trie." << endl;
  }

  t.erase("anaconda");

  words = t.allWords();

  cout << "After erasing anaconda:" << endl;
  cout << t.size() << endl;
  for(auto& word : words) {
    cout << word << " is in our trie." << endl;
  }

  return 0;
}
