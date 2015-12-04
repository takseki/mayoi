#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

static int P = 0;  // ルート数

class Mayoi {
private:
  int cur_pos;   // 現在の位置 (Y,A,B,C,Z を 0,1,2,3,4 に対応させる)
  int inv_times; // 反転回数
  int inv_times_limit;  // 反転の上限数 (N)
//  vector<int> route;  // 経路履歴 (デバッグ向け)

  // 進行方向
  enum {
    POS,
    NEG,
  } dir;
  
  // 関数の戻り値
  enum {
    FINISH,     // 反転上限内で Y に到達
    CONTINUE,   // 探索継続
    FAIL,       // 反転上限を超えた または Z に到達
  };

public:
  // 初期状態は X から B に来た時点
  Mayoi() : cur_pos(2), inv_times(0), dir(POS) {
//    route.push_back(cur_pos);
  }
  /*
  Mayoi(const Mayoi& rhs) : cur_pos(rhs.cur_pos), inv_times(rhs.inv_times), inv_times_limit(rhs.inv_times_limit), route(rhs.route), dir(rhs.dir) {
  }
  */

  void set_limit(int limit) {inv_times_limit = limit;}

  // 経路探索して P を求める
  void solve() {
    // 状態をコピー
    Mayoi s_in(*this);
    
    int result = walk_pos();
    if (result == FINISH) {
      P++;
//      print_route("OK");
    } else if (result == FAIL) {
//      print_route("NG");
    } else {
      solve();
    }
    
    result = s_in.walk_neg();
    if (result == FINISH) {
      P++;
//      s_in.print_route("OK");
    } else if (result == FAIL) {
//      s_in.print_route("NG");
    } else {
      s_in.solve();
    }
  }
  
private:
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


    
int main()
{
  Mayoi mayoi;

  // 与えられた N に対して P を求める
  int n;
  cin >> n;
  mayoi.set_limit(n);

  mayoi.solve();

  cout << P << endl;
}
  
