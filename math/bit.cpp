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
// 本题思路：
// 1. 可用异或性质：a ^ b == c 可推导出 a ^ c == b，而最大值是全1，所以可以反向异或。
// 2. 反向异或之前需要先截断；
// 3. 题目的描述是从后向头计算，这里使用了从头向后计算；有点绕，貌似不如直接两次循环呀。
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

// 位运算问题：有些问题明显只是bit级别的修改，这个时候只按位运算去考虑问题就是最好的了。
//
// 本题思路：
// 1. 第一个操作产生一个1：所以需要计算所有1的数量；
// 2. 第二个操作产生0，那么找最靠左的1就可以知道需要执行多少次了。
//
// 1558. 得到目标数组的最少函数调用次数 https://leetcode.cn/problems/minimum-numbers-of-function-calls-to-make-target-array/
int oneNum(int n) {
    int res = 0;
    while (n) {
        n &= n - 1;
        res++;
    }
    return res;
}

// 得到最高位后边有多少个0，比如1001，有3个。注意不支持负数。
int mostLeftShift(int n) {
    int res = 0;
    while (n > 1) { // n>1统计后边有多少0；n：包括最高位有多少bit。
        n >>= 1;
        res++;
    }
    return res;
}

int minOperations(vector<int>& nums) {
    int leftShiftAll = 0;
    int res = 0;
    for (int num : nums) {
        leftShiftAll = max(leftShiftAll, mostLeftShift(num));
        res += oneNum(num);
    }
    return res + leftShiftAll;
}

// UTF8编码校验
//
// 如何根据一个字节的前几个bit来获取大小信息。移位运算和二进制法的使用值得借鉴。
//
// 393. UTF-8 编码验证 https://leetcode.cn/problems/utf-8-validation/
class Solution {
    int size(int byte) {
        if ((byte >> 7) == 0) return 1;
        if ((byte >> 5) == 0b110) return 2;
        if ((byte >> 4) == 0b1110) return 3;
        if ((byte >> 3) == 0b11110) return 4;
        return 0;
    }
public:
    bool validUtf8(vector<int>& data) {
        if (data.size() == 0) return true;
        int i = 0;
        while (i < data.size()) {

            int sz = size(data[i]);
            if (sz == 0 || i + sz > data.size()) return false; // split 的思路

            for (int j = 1; j < sz; j++) {
                if ((data[i + j] >> 6) != 0b10) return false;
            }
            
            i += sz;
        }
        return true;
    }
};

// 位运算：如何使用位运算解决问题的经典方法
//
// 两个关键点：
// 1. 定义int作为bitmap;
// 2. 用到的bit不多的话，使用1,2,4,8数字去或。
//
// 2299. 强密码检验器 II https://leetcode.cn/problems/strong-password-checker-ii/
class Solution {
public:
    bool strongPasswordCheckerII(string password) {
        if (password.size() < 8) return false;

        int bitInfo = 0;
        for (int i = 0; i < password.size(); i++) {
            char ch = password[i];
            if (i > 0 && password[i] == password[i - 1]) {
                return false;
            }
            if (ch >= 'a' && ch <= 'z') {
                bitInfo |= 1;
            } else if (ch >= 'A' && ch <= 'Z') {
                bitInfo |= 2;
            } else if (ch >= '0' && ch <= '9') {
                bitInfo |= 4;
            } else if (string("!@#$%^&*()-+").find(ch) != string::npos) {
                bitInfo |= 8;
            }
        }
        return bitInfo == 15;
    }
};