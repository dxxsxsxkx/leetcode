#include <algorithm>
#include <cstdint>
class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0) {
            return 0;
        }

        int64_t long_n = n; 
        int64_t long_abs_n = std::abs(long_n);
        double base = x;

        double pow_x_i = 1.0;
        while (long_abs_n > 0) {
            if (long_abs_n % 2 == 1) {
                pow_x_i *= base;
            }
            base *= base;
            long_abs_n >>= 1;
        }

        if (n < 0){
            pow_x_i = 1.0 / pow_x_i;
        }
        return pow_x_i;
    }
};
