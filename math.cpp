//将一个数拆分成n个数，其中n > 2，使得这个n个数的积最大。
//找规律得到的结果，在大于4的情况下，拆分成3 * 3 * 3。。。* n，这样子是最大的；最后的n是<=4的
class Solution {
public:
    int integerBreak(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        int res = 1;
        while (n > 4) {
            res *= 3;
            n -= 3;
        }
        return res * n;
    }
};
