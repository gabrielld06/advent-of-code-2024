#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int solve(const vector<int> &updates, const set<int> &has,
          const map<int, vector<int>> &rules) {
  set<int> seen;
  for (auto &e : updates) {
    auto it = rules.find(e);
    if (it != rules.end()) {
      bool all_seen = true;

      for (auto &rule : it->second) {
        if (has.find(rule) != has.end() && seen.find(rule) == seen.end()) {
          all_seen = false;
          break;
        }
      }

      if (!all_seen) {
        return 0;
      }
    }

    seen.insert(e);
  }

  int middle = updates.size() / 2;

  return updates[middle];
}

int main(int argc, char **argv) {
  assert(argc == 2);

  string filename = argv[1];

  ifstream input(filename);

  int x, y, ans = 0;
  string line;
  map<int, vector<int>> rules;
  while (getline(input, line)) {
    if (line == "") {
      break;
    }
    sscanf(line.c_str(), "%d|%d", &x, &y);

    rules[y].push_back(x);
  }

  set<int> has;
  vector<int> updates;
  while (input.good()) {
    input >> x;
    updates.push_back(x);
    has.insert(x);

    char c = input.get();
    if (c == '\n') {
      ans += solve(updates, has, rules);

      has = set<int>();
      updates = vector<int>();
    }
  }

  cout << ans << endl;

  return 0;
}
