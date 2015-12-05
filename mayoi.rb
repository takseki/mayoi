class Solver
  POS = 0
  NEG = 1

  # 動的計画法による探索
  # p(n, dir) : B から出発して、反転 n 回以内の経路数とする. dir は方向の初期状態.
             
  # 初期値4つの漸化式で表せる。
  #   p(0, +) = 0, p(0, -) = 1, p(1, +) = 2, p(1, -) = 1
  
  #   p(n, +) = p(n-1, -) + p(n-2, +) + 1 (ただし n >= 2)
  #   p(n, -) = p(n-1, +) + p(n-2, -) + 1 (ただし n >= 2)
  
  # 以下のように n の小さい方から計算していく.
  #   p(2, +) = p(1, -) + p(0, +) + 1 = 1 + 0 + 1 = 2
  #   p(2, -) = p(1, +) + p(0, -) + 1 = 2 + 1 + 1 = 4
  #   p(3, +) = p(2, -) + p(1, +) + 1 = 4 + 2 + 1 = 7
  #   p(3, -) = p(2, +) + p(1, -) + 1 = 2 + 1 + 1 = 4
  # なお、
  #   p(1, +) = p(2, +), p(3, +) = p(4, +), ...
  #   p(0, -) = p(1, -), p(2, -) = p(3, -), ...
  # のような性質があることも使えるが、大差ないと思われるのでやっていない。
  def solve(n)
    if n == 0
      return 0
    elsif n == 1
      return 2
    else
      # Ruby の多次元配列の生成の仕方に注意!
      dp_table = Array.new(n).map{ Array.new(2, 0) }
      dp_table[0][0] = 0
      dp_table[0][1] = 1
      dp_table[1][0] = 2
      dp_table[1][1] = 1
      for i in 2..n - 1
        dp_table[i][POS] = dp_table[i - 1][NEG] + dp_table[i - 2][POS] + 1
        dp_table[i][NEG] = dp_table[i - 1][POS] + dp_table[i - 2][NEG] + 1
      end
      return dp_table[n - 1][NEG] + dp_table[n - 2][POS] + 1
    end
  end
end


# マヨイドーロ問題.
# 標準入力から N を入力し、標準出力に P を出力する.
str = gets
n = str.to_i

solver = Solver.new;
p = solver.solve(n);

puts p
