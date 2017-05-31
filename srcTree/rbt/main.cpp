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
#include "rbt.cpp" // Since we are using templates, it is important to include this file in order to guarantee that everything is well linked.
#include <ctime> // Library for time tests
#include <vector>

using namespace std;

RBT<int> rbt = RBT<int>();
vector<int> v;

int main() {
  clock_t fst, snd;
  int n; cin >> n;
  double tm;

  fst = clock();
  for(int i = 0; i < n; i++) {
    int k; cin >> k;
    v.push_back(k);
    rbt.insert(k);
  }
  snd = clock();

  tm = 1000.0 * (snd - fst) / CLOCKS_PER_SEC;

  cout << "Insertion: " << tm << " milliseconds." << endl;

  fst = clock();
  cout << "Minimum value: " << rbt.minValue() << endl;
  snd = clock();

  tm = 1000.0 * (snd - fst) / CLOCKS_PER_SEC;

  cout << "Minimum: " << tm << " milliseconds." << endl;

  fst = clock();
  cout << "Maximum value: " << rbt.maxValue() << endl;
  snd = clock();

  tm = 1000.0 * (snd - fst) / CLOCKS_PER_SEC;

  cout << "Maximum: " << tm << " milliseconds." << endl;

  fst = clock();
  for(auto i : v) rbt.erase(i);
  snd = clock();

  tm = 1000.0 * (snd - fst) / CLOCKS_PER_SEC;

  cout << "Delition: " << tm << " milliseconds." << endl;


  /* ------ IF you want to test things with iterators:
  rbt.insert(2);
  rbt.insert(20);
  rbt.insert(18);
  rbt.insert(90);
  rbt.insert(80);
  rbt.insert(40);
  rbt.insert(42);
  rbt.insert(73);

  RBT<int>::iterator it = rbt.find(73, 0);
  RBT<int>::iterator prev = it;
  RBT<int>::iterator next = it;
  prev--;
  next++;

  cout << "Find 73? " << *it << endl;
  cout << "Next to 73? " << *next << endl;
  cout << "Prev to 73? " << *prev << endl;

  it = rbt.upper_bound(42);
  cout << "Upper bound 42? " << *it << endl;
  it = rbt.upper_bound(43);
  cout << "Upper bound 43? " << *it << endl;

  it = rbt.lower_bound(73);
  cout << "Lower bound 73? " << *it << endl;
  it = rbt.lower_bound(72);
  cout << "Lower bound 72? " << *it << endl;

  #  ------ */

  return 0;
}
