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
  //t.debug();

  return 0;
}
