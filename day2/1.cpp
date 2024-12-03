#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {
  assert(argc == 2);

  string filename = argv[1];

  ifstream input(filename);

  int sum = 0;
  string line;
  while (std::getline(input, line)) {
    int prev, at, sign = 0;
    std::istringstream lineStream(line);

    bool success = true;
    lineStream >> prev;
    while (lineStream >> at) {
      int dif = abs(at - prev);
      if (dif > 3 || dif < 1) {
        success = false;
        break;
      }

      if (sign == 0) {
        sign = at - prev > 0 ? 1 : -1;
      } else if ((at - prev > 0 && sign != 1) ||
                 (at - prev < 0 && sign != -1)) {
        success = false;
        break;
      }

      prev = at;
    }

    if (success)
      sum++;
  }

  cout << sum << endl;

  return 0;
}
