#include <vector>
class Solution {
public:
    /**
     * @param n: non-negative integer, n posts
     * @param k: non-negative integer, k colors
     * @return: an integer, the total number of ways
     */
    int numWays(int n, int k) {
        // write your code here
        std::vector<int> memo(n + 1, -1);
        return countNumWays(n, k, memo);
    }
private:
    int countNumWays(int num_posts, const int num_colors, std::vector<int>& memo) {
        int UNDEFINED = -1;
        if (memo[num_posts] != UNDEFINED) {
            return memo[num_posts];
        }
        if (num_posts == 1) {
            return num_colors;
        }
        if (num_posts == 2) {
            return num_colors * num_colors;
        }

        int num_same_with_previous = countNumWays(num_posts - 2, num_colors, memo) * (num_colors - 1);
        int num_different_from_previous = countNumWays(num_posts - 1, num_colors, memo) * (num_colors - 1);

        memo[num_posts] = num_same_with_previous + num_different_from_previous;

        return memo[num_posts];
    }
};
