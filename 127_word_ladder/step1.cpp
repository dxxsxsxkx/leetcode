#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList) {
        wordList.emplace_back(beginWord);
        std::map<std::string, std::vector<std::string>> adjacent_words = makeAdjacentList(wordList);

        std::queue<WordToLevel> next_word_candidates;
        next_word_candidates.emplace(beginWord, 1);

        std::set<std::string> checked_words;
        checked_words.emplace(beginWord);

        while (!next_word_candidates.empty()) {
            auto [current_word, level] = next_word_candidates.front();
            next_word_candidates.pop();

            if (current_word == endWord) {
                return level;
            }

            for (auto& adjacent_word : adjacent_words[current_word]) {
                if (!checked_words.contains(adjacent_word)) {
                    checked_words.emplace(adjacent_word);
                    next_word_candidates.emplace(adjacent_word, level + 1);
                }
            }
        }

        return 0;
    }

private: 
    struct WordToLevel {
        std::string word;
        int level;
    };

    std::map<std::string, std::vector<std::string>> makeAdjacentList(
        std::vector<std::string>& word_list
    ) {
        std::map<std::string, std::vector<std::string>> word_to_adjacents;
        for (int i = 0; i < word_list.size(); ++i) {
            for (int j = i + 1; j < word_list.size(); ++j) {
                if (areDifferentByOneWord(word_list[i], word_list[j])) {
                    word_to_adjacents[word_list[i]].emplace_back(word_list[j]);
                    word_to_adjacents[word_list[j]].emplace_back(word_list[i]);
                }
            }
        }
        return word_to_adjacents;
    };

    bool areDifferentByOneWord(std::string word_a, std::string word_b) {
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
