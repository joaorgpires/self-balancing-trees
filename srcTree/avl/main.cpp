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
#include "avl.h"
#include "avl.cpp" // clang++ will not compile without this

using namespace std;

int main() {
  AVL<int> myavl = AVL<int>();

  myavl.insert(3);
  //myavl.debug();
  //myavl.parDebug();
  myavl.insert(1);
  //myavl.debug();
  //myavl.parDebug();
  myavl.insert(5);
  //myavl.debug();
  //myavl.parDebug();
  myavl.insert(7);
  //myavl.debug();
  //myavl.parDebug();
  myavl.insert(8);
  //myavl.debug();
  //myavl.parDebug();
  myavl.insert(6);
  //myavl.debug();
  //myavl.parDebug();
  myavl.insert(2);
  //myavl.debug();
  //myavl.parDebug();
  myavl.insert(9);
  //myavl.debug();
  //myavl.parDebug();
  myavl.insert(10);
  //myavl.debug();
  //myavl.parDebug();

  cout << "Min value: " << myavl.minValue() << endl;
  cout << "Max value: " << myavl.maxValue() << endl;
  cout << "Size of the AVL tree: " << myavl.size() << endl;
  if(myavl.find(2)) cout << "2 is in AVL tree." << endl;
  if(!myavl.find(11)) cout << "11 is not in AVL tree." << endl;

  return 0;
}
