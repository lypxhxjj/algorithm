// 旋转问题其实很绕，一些结论还是需要记住的。

// 右旋转公式（就是很符合直觉的那个公式）：
// inew = (iold + k) % n;
//
// 代码中，nums[i]只以i作为索引，所以i是iold；res的索引是inew。得出如上公式。
//
// 189. 轮转数组 https://leetcode.cn/problems/rotate-array/
void rotate(vector<int>& nums, int k) {
    vector<int> res(nums.size());
    for (int i = 0; i < nums.size(); i++) {
        res[(i + k) % nums.size()] = nums[i];
    }
    nums = res;
}

// 左旋转公式（简单由右旋转公式推导而来）：
// iold = (inew + k) % n;
//
// res[i]只以i作为索引，所以i是inew；s的索引是iold，所以得出如上结论。
//
// 剑指 Offer 58 - II. 左旋转字符串 https://leetcode.cn/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/
string reverseLeftWords(string s, int n) {
    string res;
    for (int i = 0; i < s.size(); i++) {
        res += s[(i + n) % s.size()];
    }
    return res;
}

// 旋转公式解决约瑟夫环问题：
// f(n)代表，n个元素剩下的那个索引；f(n - 1)表示n - 1个元素剩下的索引，而剩余n-1个元素，相比n个元素时，相当于将数组左旋转了k次。
// 即 f(n) = (f(n - 1) + k) % n
// 边界为 f(1) = 0。
//
// 比较难想的两个点：f的含义；利用左旋的性质。
//
// 1823. 找出游戏的获胜者 https://leetcode.cn/problems/find-the-winner-of-the-circular-game/
int findTheWinner(int n, int k) {
    int res = 0;
    for (int i = 2; i <= n; i++) {
        res = (res + k) % i;
    }
    return res + 1;
}

// 是否是一个旋转数组：利用旋转的性质解决
//
// 1752. 检查数组是否经排序和轮转得到 https://leetcode.cn/problems/check-if-array-is-sorted-and-rotated/
bool check(vector<int>& nums) {
    if (nums.size() < 3) return true;
    int cnt = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > nums[(i + 1) % nums.size()]) { // 这个真的妙，取模之后你可以永远相信i + 1不越界。
            cnt++;
        }
        if (cnt > 1) return false;
    }
    return true;
}