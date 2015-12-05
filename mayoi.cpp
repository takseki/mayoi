#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

// 進行方向
enum Dir {
  POS = 0,  // A(X)->B->C の方向
  NEG,      // 逆方向
};


class Solver {
public:
  Solver() {}

public:
  /**
     動的計画法による探索
       p(n, dir) : B から出発して、反転 n 回以内の経路数とする. dir は方向の初期状態.
     
     初期値4つの漸化式で表せる。
       p(0, +) = 0, p(0, -) = 1, p(1, +) = 2, p(1, -) = 1
     
       p(n, +) = p(n-1, -) + p(n-2, +) + 1 (ただし n >= 2)
       p(n, -) = p(n-1, +) + p(n-2, -) + 1 (ただし n >= 2)
     
     以下のように n の小さい方から計算していく.
       p(2, +) = p(1, -) + p(0, +) + 1 = 1 + 0 + 1 = 2
       p(2, -) = p(1, +) + p(0, -) + 1 = 2 + 1 + 1 = 4
       p(3, +) = p(2, -) + p(1, +) + 1 = 4 + 2 + 1 = 7
       p(3, -) = p(2, +) + p(1, -) + 1 = 2 + 1 + 1 = 4
     なお、
       p(1, +) = p(2, +), p(3, +) = p(4, +), ...
       p(0, -) = p(1, -), p(2, -) = p(3, -), ...
     のような性質があることも使えるが、大差ないと思われるのでやっていない。
  */
  unsigned long long solve(int n) {
    if (n == 0) {
      return 0;
    } else if (n == 1) {
      return 2;
    } else {
      vector<vector<unsigned long long> > dp_table(n, vector<unsigned long long>(2));
      dp_table[0][POS] = 0;
      dp_table[0][NEG] = 1;
      dp_table[1][POS] = 2;
      dp_table[1][NEG] = 1;
      for (int i = 2; i < n; i++) {
        dp_table[i][POS] = dp_table[i - 1][NEG] + dp_table[i - 2][POS] + 1;
        dp_table[i][NEG] = dp_table[i - 1][POS] + dp_table[i - 2][NEG] + 1;
      }
      return dp_table[n - 1][NEG] + dp_table[n - 2][POS] + 1;
    }
  }
};


/**
   マヨイドーロ問題.
   標準入力から N を入力し、標準出力に P を出力する.
 */
int main()
{
  // 与えられた N に対して P を求める
  int n;
  cin >> n;

  Solver solver;
  unsigned long long p = solver.solve(n);

  cout << p << endl;
}
