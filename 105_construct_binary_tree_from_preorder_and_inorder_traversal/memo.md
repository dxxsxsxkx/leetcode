# Step 1

選挙があって忙しく1週間開いてしまったが、再開。

## 1回目

全く思いつかなかった。

### メモ

PR とコードを見ながら言っていることを理解する。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/31/changes/71d16952d6b4e0f8b375eb89f21901bf26eb2148#diff-157083ccc144ea085e93b731f3478b676c815bf2bc90519662a8be0b9d50041c)
  > preorderの要素からinorderのindexを取得して、そのindexの左側が左のnodeに右側が右のnodeに紐づく
  - ちょっとよくわからなかったのでLLMに聞いてみて、以下のように理解した。
    - preorder の最初の要素が root になる。その要素を inorder の方で探すと、その左側の要素は全て root を基準にした左部分木の要素に、右側の要素は全て右部分木の要素になる。これを再帰で繰り返す。
  - 実際にコードに落とし込むにはどうしたらいいだろう？まず、ノードの値と inorder のインデックスを合わせた hash map を作る。各ステップでは preorder の対象となる範囲を受け取り、その部分木の根を決め、左右に伸ばす。

## 2回目

### コード

`step1.cpp` に書いた。

# Step 2

## 勉強

preorder に破壊的変更を加えながら（頭の要素を取っては消し、を繰り返す）木を作るやり方。わかりやすい。破壊的変更を行う点をどう考えるかになる。

```cpp
// 処理の部分だけ書いた

// 取って消す
int root_val = preorder[0];
preorder.erase(preorder.begin());

TreeNode* node = new TreeNode(root_val);

int inorder_index;
for (i = 0; i < inorder.size(); ++i) {
  if (inorder[i] == root_val) {
    inorder_index = i;
  }
}

std::vector<int>::iterator position = inorder.begin() + inorder_index;
std::vector<int> left_inorder(inorder.begin(), position);
std::vector<int> right_inorder(position + 1, inorder.end());

node->left = buildTree(preorder, left_inorder);
node->right = buildTree(preorder, right_inorder);

return node;
```

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/31/changes/71d16952d6b4e0f8b375eb89f21901bf26eb2148#diff-11ea32d6605059b89469bdbb93c61faa80b72b5704c9ceb1221615388145714c)。

- Hash map を使っていないため間に挟まる inorder のインデックス取得が冗長だが、これは次のように `find` を使うことで解決できる。
  ```cpp
  auto position = find(inorder.begin(), inorder.end(), value);
  ```

- よく考えたら破壊的変更を行う必要はなく、関数の外で preorder のインデックスを管理すれば良いと思った。これで `step2.cpp` を書いた。
  - ベクトルのコピーが重そうなので、`buildTree` に範囲を持たせるようにするとさらに良くなる。こうすると `step1.cpp` との差分は hash map を使うかどうかだけになりそう。

# Step 3

`unordered_map` を使って書いた。`step3.cpp`。
