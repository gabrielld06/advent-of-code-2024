#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool solve(vector<int> &levels, int order) {
  for (int i = 0; i < levels.size(); i++) {
    bool success = true;

    for (int j = 1; j < levels.size(); j++) {
      if (j == i)
        continue;

      int prev = j - 1 == i ? j - 2 : j - 1;
      if (prev < 0) {
        continue;
      }

      int dif = (order * levels[j]) + (order * -levels[prev]);
      if (dif < 1 || dif > 3) {
        success = false;
        break;
      }
    }

    if (success)
      return true;
  }

  return false;
}

int main(int argc, char **argv) {
  assert(argc == 2);

  string filename = argv[1];

  ifstream input(filename);

  int sum = 0;
  string line;
  while (std::getline(input, line)) {
    int x;
    std::istringstream lineStream(line);

    vector<int> levels;
    while (lineStream >> x) {
      levels.push_back(x);
    }

    if (solve(levels, -1) || solve(levels, 1)) {
      sum++;
    }
  }

  cout << sum << endl;

  return 0;
}
