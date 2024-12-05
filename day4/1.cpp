#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool apply_mask(vector<vector<char>> mat, int x, int y,
                vector<vector<char>> mask) {
  for (int i = 0; i < mask.size(); i++) {
    for (int j = 0; j < mask[i].size(); j++) {
      int m = x + i, n = y + j;
      if (m >= mat.size() || n >= mat[m].size()) {
        return false;
      }

      if (mask[i][j] == '.') {
        continue;
      }

      if (mask[i][j] != mat[m][n]) {
        return false;
      }
    }
  }

  return true;
}

int solve(vector<vector<char>> mat) {
  vector<vector<char>> mask_horizontal = vector<vector<char>>{
      vector<char>{'X', 'M', 'A', 'S'},
  };
  vector<vector<char>> mask_horizontal_back = vector<vector<char>>{
      vector<char>{'S', 'A', 'M', 'X'},
  };
  vector<vector<char>> mask_vertical = vector<vector<char>>{
      vector<char>{'X'},
      vector<char>{'M'},
      vector<char>{'A'},
      vector<char>{'S'},
  };
  vector<vector<char>> mask_vertical_back = vector<vector<char>>{
      vector<char>{'S'},
      vector<char>{'A'},
      vector<char>{'M'},
      vector<char>{'X'},
  };
  vector<vector<char>> mask_diagonal_lr = vector<vector<char>>{
      vector<char>{'X', '.', '.', '.'},
      vector<char>{'.', 'M', '.', '.'},
      vector<char>{'.', '.', 'A', '.'},
      vector<char>{'.', '.', '.', 'S'},
  };
  vector<vector<char>> mask_diagonal_lr_back = vector<vector<char>>{
      vector<char>{'S', '.', '.', '.'},
      vector<char>{'.', 'A', '.', '.'},
      vector<char>{'.', '.', 'M', '.'},
      vector<char>{'.', '.', '.', 'X'},
  };
  vector<vector<char>> mask_diagonal_rl = vector<vector<char>>{
      vector<char>{'.', '.', '.', 'X'},
      vector<char>{'.', '.', 'M', '.'},
      vector<char>{'.', 'A', '.', '.'},
      vector<char>{'S', '.', '.', '.'},
  };
  vector<vector<char>> mask_diagonal_rl_back = vector<vector<char>>{
      vector<char>{'.', '.', '.', 'S'},
      vector<char>{'.', '.', 'A', '.'},
      vector<char>{'.', 'M', '.', '.'},
      vector<char>{'X', '.', '.', '.'},
  };

  vector<vector<vector<char>>> masks = vector<vector<vector<char>>>{
      mask_horizontal,    mask_horizontal_back, mask_vertical,
      mask_vertical_back, mask_diagonal_lr,     mask_diagonal_lr_back,
      mask_diagonal_rl,   mask_diagonal_rl_back};

  int sum = 0;
  for (int i = 0; i < mat.size(); i++) {
    for (int j = 0; j < mat[i].size(); j++) {
      for (auto &mask : masks) {
        if (apply_mask(mat, i, j, mask)) {
          sum++;
        }
      }
    }
  }

  return sum;
}

int main(int argc, char **argv) {
  assert(argc == 2);

  string filename = argv[1];

  ifstream input(filename);

  vector<vector<char>> mat(1, vector<char>());
  while (input.good()) {
    char c = input.get();
    if (c == '\n') {
      mat.push_back(vector<char>());
      continue;
    }

    mat.back().push_back(c);
  }
  mat.pop_back();

  cout << solve(mat) << endl;

  return 0;
}
