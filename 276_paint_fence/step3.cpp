class Solution {
public:
    /**
     * @param n: non-negative integer, n posts
     * @param k: non-negative integer, k colors
     * @return: an integer, the total number of ways
     */
    int numWays(int n, int k) {
        // write your code here
        if (n == 1) {
            return k;
        }
        if (n == 2) {
            return k * k;
        }

        int n_ways = 0;
        int previous_n_ways = k * k;
        int second_previous_n_ways = k;
        for (int i = 2; i < n; i++) {
            n_ways = (k - 1) * (previous_n_ways + second_previous_n_ways);
            second_previous_n_ways = previous_n_ways;
            previous_n_ways = n_ways;
        }   
        return n_ways;
    }
};
