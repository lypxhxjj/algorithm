// 遍历 n 的每个 bit
void for_bit(int n) {
    while (n) {
        n >>= 1;
    }
}

// 公式：a&c ^ b&c = (a^b) & c
// 记忆： 布尔代数里异或就是加，与就是乘，所以符合分配律
//
// 下题需要简单的推导即可。举几个例子即可。
// 1835. 所有数对按位与结果的异或和 https://leetcode.cn/problems/find-xor-sum-of-all-pairs-bitwise-and/
int getXORSum(vector<int>& arr1, vector<int>& arr2) {
    int xor1 = 0, xor2 = 0;
    for (int num : arr1) {
        xor1 ^= num;
    }
    for (int num : arr2) {
        xor2 ^= num;
    }
    return xor1 & xor2;
}

// 如何对一个数字后几个bit进行异或：先与再异或
//
// 注意，此题要的是，让xor最大的那个k，所以一定比kxor小的。
//
// 1829. 每个查询的最大异或值 https://leetcode.cn/problems/maximum-xor-for-each-query/
vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
    int threshold = 1 << maximumBit;
    int kxor = threshold - 1;

    vector<int> res(nums.size());
    int xorVal = 0;
    for (int i = 0; i < nums.size(); i++) {
        xorVal ^= nums[i];
        res[i] = (xorVal & kxor) ^ kxor; // 先与再异或，就完成了对后面几个bit的异或操作。
    }
    reverse(res.begin(), res.end());
    return res;
}