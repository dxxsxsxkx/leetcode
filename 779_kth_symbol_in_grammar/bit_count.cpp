#include <cmath>
class Solution {
public:
    int kthGrammar(int n, int k) {
        int x = k - 1;
        int parity = 0;

        while (x > 0) {
            parity ^= (x & 1);
            x >>= 1;
        }

        return parity;
    }
};
