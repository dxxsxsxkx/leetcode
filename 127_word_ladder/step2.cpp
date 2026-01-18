#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
        wordList.emplace_back(beginWord);
        std::vector<std::vector<int>> adjacency_list(wordList.size());
        makeAdjacencyList(wordList, adjacency_list);

        int idx_beginWord = wordList.size() - 1;
        std::queue<WordAndLevel> next_word_candidates;
        next_word_candidates.emplace(idx_beginWord, 1);

        std::vector<bool> checked_words(wordList.size());
        checked_words[idx_beginWord] = true;

        while (!next_word_candidates.empty()) {
            auto [current_word, level] = next_word_candidates.front();
            next_word_candidates.pop();

            if (wordList[current_word] == endWord) {
                return level;
            }
            
            for (const auto& adjacent_word : adjacency_list[current_word]) {
                if (!checked_words[adjacent_word]) {
                    checked_words[adjacent_word] = true;
                    next_word_candidates.emplace(adjacent_word, level + 1);
                }
            }
        }

        return 0;
    }

private: 
    struct WordAndLevel {
        int index;
        int level;
    };

    void makeAdjacencyList(
        const std::vector<std::string>& word_list, 
        std::vector<std::vector<int>>& adjacency_list
    ) {
        int n_words = word_list.size();

        for (int i = 0; i < n_words; ++i) {
            for (int j = i + 1; j < n_words; ++j) {
                if (areDifferentByOneWord(word_list[i], word_list[j])) {
                    adjacency_list[i].emplace_back(j);
                    adjacency_list[j].emplace_back(i);
                }
            }
        }        
    };

    bool areDifferentByOneWord(std::string_view word_a, std::string_view word_b) {
        int n_different_chars = 0;
        for (int i = 0; i < word_a.size(); ++i) {
            if (word_a[i] != word_b[i]) {
                ++n_different_chars;
            }
            if (n_different_chars > 1) {
                return false;
            }
        }
        return true;
    }
};
