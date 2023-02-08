
// hash表示线段的左右边界
//
// hash表示线段左右边界时，每一个新的元素加入到段中来，先明确写出left,right,newLeft,newRight。这样就可以很快速计算各种东西了。
// 另外的解法：hashmap中保存的是线段长度len，但是没有这种方式清晰，比较容易出错；
// 另外的解法：并查集。参考并查集章节。
// 另外的解法：为提升效率，hash可使用一个数组来标识（效率直接从352ms干到96ms），此时需要注意如下几点：
// 1. 0位置无法被使用，因为0需要被用于判断是否存在线段。需要跳过不使用;
// 2. 由于存在num - 1, num + 1这种，两边预留一个位置，0已提前预留，即只需最后预留一个位置;
// 3. 数据范围是1-maxLen，所以hash大小最小maxLen + 1个。
// 综合以上，hash需要 maxLen + 2 才行。
//
// 约束条件：这里需要整数各不相同。
// 
// 1562. 查找大小为 M 的最新分组 https://leetcode.cn/problems/find-latest-group-of-size-m/
int findLatestStep(vector<int>& arr, int m) {
    unordered_map<int, int> hash;
    int mCnt = 0;
    int step = -1;
    for (int i = 0; i < arr.size(); i++) {
        int num = arr[i];
        hash[num] = num; // 自成一个新的段；
        int len = 1;
        if (hash.find(num - 1) != hash.end()) {
            int left = hash[num - 1];
            int right = num - 1;
            int newRight = num; // 用之前，先定义出来，后续使用就很方便了。

            mCnt -= right - left + 1 == m ? 1 : 0;
            hash[left] = newRight;
            hash[newRight] = left; // WARN：一旦定义好，那么中间的元素不再使用才行，不然会污染边界元素。
            len = newRight - left + 1;
        }
        if (hash.find(num + 1) != hash.end()) {
            int left = num + 1;
            int right = hash[num + 1];
            int newLeft = hash[num];

            mCnt -= right - left + 1 == m ? 1 : 0;
            hash[newLeft] = right;
            hash[right] = newLeft;
            len = right - newLeft + 1;
        }
        if (len == m) {
            mCnt++;
        }
        if (mCnt > 0) {
            step = i + 1;
        }
    }
    return step;
}

// hash表示线段的左右边界（线段的含义：连续整数）
//
// 至少3个数，如何处理？当需要新建一个序列时，一次找够三个数，而前边还有没有两个数，需要一个hashmap来统计；
//
// 连续子序列问题，可以使用hash表，但是这里的tailMap，只需要保存线段的右端，为了满足条件，tailMap的含义是右端点是谁的个数。
//
// 659. 分割数组为连续子序列 https://leetcode.cn/problems/split-array-into-consecutive-subsequences/
bool isPossible(vector<int>& nums) {
    unordered_map<int, int> cntMap;
    unordered_map<int, int> tailMap; // 线段右端点的个数。

    for (int num : nums) {
        cntMap[num]++;
    }
    for (int i = 0; i < nums.size(); i++) {
        if (cntMap[nums[i]] == 0) { // 这个元素已经被访问过了。
            continue;
        } else if (tailMap[nums[i]-1] > 0) { // 存在前边的元素，和前边元素凑成一组。
            tailMap[nums[i]-1]--;
            tailMap[nums[i]]++;
            cntMap[nums[i]]--;
        } else if (cntMap[nums[i] + 1] > 0 && cntMap[nums[i] + 2] > 0) { // 没有前边元素，自成一个新段。WARN：顺序不关心的话，需要排序（比如第一个元素就拿到了最大的）
            tailMap[nums[i] + 2]++;
            cntMap[nums[i]]--;
            cntMap[nums[i] + 1]--;
            cntMap[nums[i] + 2]--;
        } else {
            return false;
        }
    }
    return true;
}

// 字符相关的hash：如何避免字符串hash的乱七八糟
//
// 乱七八糟体现在，为了性能，一般不使用unordered_map，而是使用数组。
// 而key是字符的时候，字符串转索引需要一步，最后使用的时候也还需要相同的步骤，显得很乱。
// 方案：申请hash的时候申请到'z' + 1个。
// 
// 2325. 解密消息 https://leetcode.cn/problems/decode-the-message/
class Solution {
public:
    string decodeMessage(string key, string message) {
        char ch['z' + 1] = {0};                 // 申请'z' + 1个。
        char begin = 'a';
        for (int i = 0; i < key.size(); i++) {
            if (key[i] >= 'a' && key[i] <= 'z') { // 空格的检查，其实也可以通过ch[' '] = ' '处理，就不需要这行代码了。
                if (ch[key[i]] > 0) {
                    continue;
                }
                ch[key[i]] = begin++;
            }
        }
        for (int i = 0; i < message.size(); i++) {
            if (message[i] >= 'a' && message[i] <= 'z') {
                message[i] = ch[message[i]];
            }
        }
        return message;
    }
};