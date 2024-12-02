#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  assert(argc == 2);

  string filename = argv[1];

  ifstream input(filename);

  int x, y;
  vector<int> l1;
  map<int, int> l2;

  input >> x >> y;
  while (input.good()) {
    l1.push_back(x);
    l2[y] += 1;

    input >> x >> y;
  }

  int sum = 0;
  for (int i = 0; i < l1.size(); i++) {
    sum += l1[i] * l2[l1[i]];
  }

  cout << sum << endl;

  return 0;
}
