# Step 1

## 1回目

ノードと階層を持つ構造体を作っておく。階層が同じノードをベクトルの同じ要素にまとめていく。

### コード

`step1.cpp` に記載。queue を使って BFS で書いた。

### メモ

- スムーズに解法のイメージとコードが思いついたのは良かった。
- ベクトルに新しい要素を作り、そこに値を入れるという二段の操作になっており、もっと短縮できたら良いと思った。
- 計算量は、全てのノードを queue に入れて見ていくのでノード数を $N$ として時間も空間も $O(N)$？

# Step 2

## 勉強

`std::map` を使っている人がいた。`while` のなかでベクトルに直接要素を入れていくのではなく、一度 map に入れて後から入れるというやり方。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/28/changes/69adafcf51d162aa3abe43e28b8daaf939a64c85#diff-cf025b844f42d569310cf861b77f1974f96ff8b070762727ad61fcfdb3fa3988R22-R26)

`queue` を使う必要は必ずしもないかも？使ったせいで混乱が生まれるなら辞めても良いかも。

- [参照](https://github.com/kazukiii/leetcode/pull/27/changes/494848ea14f3b52a1411d5620efa0857df5037eb#r1676071056)

## コード

名付けを変更した。

- `nodes_by_level` は `level_ordered_nodes` にした

# Step 3

問題なく書けた。
