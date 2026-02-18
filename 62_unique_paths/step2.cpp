#include <algorithm>
#include <cstdint>
class Solution {
public:
    int uniquePaths(int m, int n) {
        int N = m + n - 2;
        int K = std::min(m - 1, n - 1);
        int64_t result = 1;

        // calculate nCk by step-by-step multiplication
        for (int i = 1; i <= K; i++) {
            result = result * (N - K + i) / i;
        }

        return result;
    }
};
