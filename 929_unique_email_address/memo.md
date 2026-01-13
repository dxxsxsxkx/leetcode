# Step 1

## 1回目

### コード

左から見ていく。"@"が出てくるまでの間、1. "+" があったらそれ以降を無視して break する。2. "." があったら削除して続ける。
この処理で出てきたものを unordered_map に入れていって、最後は unique element の数を返す。

で、やってみたが以下のコードはTLE。

```cpp
#include <map>
#include <string>
#include <vector>

class Solution {
public:
    int numUniqueEmails(std::vector<std::string>& emails) {
        std::map<std::string, std::vector<std::string>> unique_to_addresses; 

        for (std::string email : emails) {
            std::string current_email = email; 
            // @の前後で切りたい
            for (int i = 0; i < current_email.size(); i++) {
                while (current_email[i] != '@') {
                    if (current_email[i] == '.') {
                        current_email.erase(i); 
                        continue; 
                    }
                    if (current_email[i] == '+') {
                        current_email.erase(i); 
                        break; 
                    }
                }
            }
            unique_to_addresses[current_email].push_back(email); 
        }
        return unique_to_addresses.size(); 
    }
};
```

### メモ

- 引数に入っているメアド自体を残しておく必要はないので set で十分。

- `erase(i)` は位置 i から末尾まで削除するので、インデックスが壊れる。
そもそも、インデックス操作をしている途中にインデックスを消すとおかしくなるので、別の方法を考えるべき。

## 2回目

### コード

[`std::string::substr`](https://cpprefjp.github.io/reference/string/basic_string/substr.html) を使って local とdomain を切り分ける。
`substr(pos, n)`で`pos`から`n`個の要素を返す。domainは末尾まで続くのでnを指定しなくても良い。

```cpp
#include <set>
#include <string>
#include <vector>

class Solution {
public:
    int numUniqueEmails(std::vector<std::string>& emails) {
        std::set<std::string> unique_emails; 
        for (const std::string email : emails) {
            int idx_at = email.find('@'); 

            std::string local = email.substr(0, idx_at); 
            std::string domain = email.substr(idx_at + 1); 

            std::string local_normalized; 
            for (char ch : local) {
                if (ch == '+') {
                    break; 
                }
                if (ch == '.') {
                    continue; 
                }
                local_normalized.push_back(ch); 
            }

            unique_emails.emplace(local_normalized + "@" + domain); 
        }

        return unique_emails.size(); 
    }
};
```

### メモ

- `std::string::find`の返り値の型は size_t なので`idx_at`も揃えた方が良いかも。

# Step 2

## 勉強

コピーを減らしていく。

- `&`をつける。email は変更されない。

`auto`を使っていく。

- `const auto& email : emails`で良いか。

不正な入力への応答。

- ["@"がない場合](https://github.com/Ryotaro25/leetcode_first60/pull/15#discussion_r1649824260)。あるいは、"@"が複数あるとどうなるか。
"@"がない場合には単に例外処理をすれば良いだろうが、"@"が複数ある場合は難しい...。不正なメールアドレスとして弾くことになるんだろうか。

  - `std::string::contains`はC++23から。

  - `rfind`も使える、今回はどっちでも良いかどこに"@"が出てきやすいかによって考えると良いだろう

関数化するかどうか。今回はそんな複雑でもないし良いのでは？と思った。

```cpp
string normalizeEmails(string email) {
  size_t idx_at = email.rfind('@'); 
  std::string normalized_email; 
  for (int i = 0; i < idx_at; i++) {
      if (email[i] == "+") {
          break; 
      }
      if (email[i] == '.') {
          continue; 
      }
      normalized_email += email[i]; 
  }
  normalized_email += email.substr(idx_at); 
}
```

[`std::erase`](https://cpprefjp.github.io/reference/deque/deque/erase_free.html)。

- `string`のメンバ関数ではない方。以下と等価。
  ```cpp
  auto it = remove(c.begin(), c.end(), value);
  auto r = distance(it, c.end());
  c.erase(it, c.end());
  return r;
  ```

[regex](https://cpprefjp.github.io/reference/regex.html)を使うと？
```cpp
#include <string>
#include <vector>
#include <unordered_set>
#include <regex>

class Solution {
public:
  int numUniqueEmails(std::vector<std::string>& emails) {
      std::unordered_set<std::string> unique_emails;

      std::regex format(R"(^([^@]+)@(.+)$)");

      for (const auto& email : emails) {
          std::smatch m;  // マッチ結果を格納する
          if (!std::regex_match(email, m, format)) {
              continue; 
          }

          std::string local  = m[1];
          std::string domain = m[2];

          local = std::regex_replace(local, std::regex(R"(\+.*$)"), "");

          local = std::regex_replace(local, std::regex(R"(\.)"), "");

          unique_emails.insert(local + "@" + domain);
      }

      return unique_emails.size();
  }
};
```

# Step 3

問題なくかけた。

# Step 4

## メモ

Return value optimization (RVO) について、[日本語レファレンス](https://cpprefjp.github.io/lang/cpp17/guaranteed_copy_elision.html)より。

> prvalueというカテゴリーの値を、オブジェクトの初期化のために使用する場合に、コピーが省略される。

- C++17で採用された仕様で、オブジェクトを初期化する場合にのみ機能する。代入では効かない。

- prvalue: pure rvalue、直感的には「値そのもの」のイメージ。つまりメモリ上の場所を指さない・一時的な値として振る舞う・参照できない。
