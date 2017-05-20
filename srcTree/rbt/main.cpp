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
#include "rbt.cpp"

int main() {
  RBT<int> myrbt = RBT<int>();

  myrbt.insert(3);
  myrbt.debug();
  myrbt.insert(5);
  myrbt.debug();
  myrbt.insert(7);
  myrbt.debug();
  myrbt.insert(10);
  myrbt.debug();
  myrbt.insert(15);
  myrbt.debug();
  myrbt.insert(6);
  myrbt.debug();
  myrbt.insert(4);
  myrbt.debug();

  cout << "Size of Red-Black tree: " << myrbt.size() << endl;
  return 0;
}
