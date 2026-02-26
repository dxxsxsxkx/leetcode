#include <unordered_map>
#include <string> 
#include <vector>
class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        TrieNode* root = buildTrie(wordDict);  // trie木 構築

        int n = s.size();
        std::vector<bool> table(n + 1, false);
        table[0] = true;

        for (int i = 0; i < n; ++i) {
            if (!table[i]) {
                continue;
            }

            TrieNode* node = root;
            for (int j = i; j < n; ++j) {
                // trie木に含まれていなかったら break する
                if (!node->children.count(s[j])){
                    break;
                }
                node = node->children[s[j]];

                if (node->isWord){
                    table[j + 1] = true;
                }
            }
        }

        return table[n];
    }
private: 
    struct TrieNode {
        bool isWord = false;
        std::unordered_map<char, TrieNode*> children;
    };
    TrieNode* buildTrie(std::vector<std::string>& words) {
        TrieNode* root = new TrieNode();

        for (auto& word : words) {
            TrieNode* node = root;
            for (char c : word) {
                if (!node->children.count(c))
                    node->children[c] = new TrieNode();
                node = node->children[c];  // ポインタを進める
            }
            node->isWord = true;  // 末端
        }
        return root;
    }
};
