#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Route {
private:
  int cur_pos;   // 現在の位置 (Y,A,B,C,Z を 0,1,2,3,4 に対応させる)
  int inv_times; // 反転回数
  int inv_times_limit;  // 反転の上限数 (N)
  
  // 進行方向
  enum {
    POS,
    NEG,
  } dir;

//  vector<int> route;  // 経路履歴 (デバッグ向け)

public:
  // 関数の戻り値
  enum {
    FINISH,     // 反転上限内で Y に到達
    CONTINUE,   // 探索継続
    FAIL,       // 反転上限を超えた または Z に到達
  };

  // 初期状態は X から B に来た時点
  Route(int limit) : cur_pos(2), inv_times(0), inv_times_limit(limit), dir(POS) {
//    route.push_back(cur_pos);
  }
  
  /*  
  Route(const Route& rhs) : cur_pos(rhs.cur_pos), inv_times(rhs.inv_times), inv_times_limit(rhs.inv_times_limit), dir(rhs.dir), route(rhs.route) {
  }
  */
  
  /*
  void print_route(const char* str) {
    cout << str << " : ";
    for (size_t i = 0; i < route.size(); i++) {
      cout << route.at(i);
    }
    cout << endl;
  }
  */
  
  int walk_pos() {
    if (dir != POS) {
      inv_times++;
    }
    cur_pos++;
    dir = POS;
//    route.push_back(cur_pos);
    
    // 判定
    if (cur_pos == 4) {
      return FAIL;
    }
    if (inv_times > inv_times_limit) {
      return FAIL;
    }
    return CONTINUE;
  }
  
  int walk_neg() {
    if (dir != NEG) {
      inv_times++;
    }
    cur_pos--;
    dir = NEG;
//    route.push_back(cur_pos);
        
    // 判定
    if (cur_pos == 0) {
      return FINISH;
    }
    if (inv_times > inv_times_limit) {
      return FAIL;
    }
    return CONTINUE;
  }
};

class Solver {
private:
  int n_routes;  // 経路数 (P)
  
public:
  Solver() {}

  // 経路探索して P を求める
  int solve(int limit_times) {
    n_routes = 0;
    Route r(limit_times);
    
    recur_solve(r);
    return n_routes;
  }

private:
  // 再帰による探索
  void recur_solve(Route& r) {
    // 状態をコピー
    Route r_neg(r);
    
    int result = r.walk_pos();
    if (result == Route::FINISH) {
      n_routes++;
//      r.print_route("OK");
    } else if (result == Route::FAIL) {
//      r.print_route("NG");
    } else {
      recur_solve(r);
    }
    
    result = r_neg.walk_neg();
    if (result == Route::FINISH) {
      n_routes++;
//      r_neg.print_route("OK");
    } else if (result == Route::FAIL) {
//      r_neg.print_route("NG");
    } else {
      recur_solve(r_neg);
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
  int p = solver.solve(n);

  cout << p << endl;
}
  
