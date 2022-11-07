// 旋转问题其实很绕，一些结论还是需要记住的。

// 右旋转公式（就是很符合直觉的那个公式）：
// inew = (iold + k) % n;
//
// 表达式为：res[inew] = nums[iold]，简单带入即可
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
// 表达式为：res[inew] = nums[iold]，简单带入即可。
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

// 循环数组 + 索引/值 问题。
//
// 两个关键点：
// 1. 一定索引取模。如果不是索引需要转化为索引，取模的结果也是索引；
// 2. 灵活使用索引和值/个数：什么时候计算使用索引，什么时候计算使用值，可以灵活选择。
//
// 1560. 圆形赛道上经过次数最多的扇区 https://leetcode.cn/problems/most-visited-sector-in-a-circular-track/
vector<int> mostVisited(int n, vector<int>& rounds) {
    vector<int> res((rounds.back() + n - rounds[0]) % n + 1); // 这里也可认为是索引计算，然后转换为个数。
    for (int i = 0; i < res.size(); i++) {
        res[i] = (rounds[0] -1 + i) % n + 1; // 先转换到索引再取模，找到循环数组的位置 =》 然后根据索引找到值 =》值和索引的关系是相差1。
    }
    sort(res.begin(), res.end());
    return res;
}

// 重复N次问题
// 
// 这个解法很妙，如果存在，则一定满足 arr[i] == arr[i - m]，满足 (k-1) * m次才行，一旦不满足，需要重新计数。
//
// 1566. 重复至少 K 次且长度为 M 的模式 https://leetcode.cn/problems/detect-pattern-of-length-m-repeated-k-or-more-times/
bool containsPattern(vector<int>& arr, int m, int k) {
    if (m * k > arr.size()) return false;
    int cnt = 0;
    for (int i = 0, j = m; j < arr.size(); i++, j++) {
        if (arr[i] == arr[j]) {
            cnt++;
        } else {
            cnt = 0;
        }
        if (cnt == m * (k - 1)) {
            return true;
        }
    }
    return false;
}