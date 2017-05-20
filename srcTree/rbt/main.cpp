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

  myrbt.insert(44);
  myrbt.insert(17);
  myrbt.insert(62);
  myrbt.insert(32);
  myrbt.insert(50);
  myrbt.insert(78);
  myrbt.insert(48);
  myrbt.insert(54);
  myrbt.insert(88);
  myrbt.erase(50);
  myrbt.debug();

  cout << "Size of Red-Black tree: " << myrbt.size() << endl;
  return 0;
}
