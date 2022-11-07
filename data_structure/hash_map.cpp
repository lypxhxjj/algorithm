/*
这里主要介绍hashmap的hash函数。

1. 为啥要使用一个素数M作为数组的大小（取模的对象）？
因为只有对素数取模，才可以用到hash key的全部字段。因为转化为整数的hash key对M取模肯定除不尽，所以需要使用每个数字参与计算。
而如果不是一个素数，是一个100之类的数字，那么当key在特定情况下符合某些规律时（比如规律时100的倍数），会导致取模之后数据严重偏移。
我们希望的效果是：只要不相等，随机分配到任意一个上去。

2. 浮点数的hash函数如何实现的？
0-1之间的浮点数的hash函数，不是乘以M得到的，因为这样其实会导致：高位起的作用更大，低位基本没啥影响。所以一般思路是，强制转化为二进制，前32bit和后32bit做位运算得到hash值。

3. 字符串的hash值参考下面的函数。

4. hash值的缓存。
hash计算是有成本的，可以缓存起来以便下次直接使用。一般用于不可变的对象，比如java.String。String类中包含一个hash字段，会被优先使用，只有此字段为空，才会重新计算hash值。
*/

// 字符串的 hash 值
// M：前M个字节计算hash；
// R: 计算hash的base，一般用于表示进制，所以每多一次计算，相当于一次移位，但是不是必须，比如java.String使用的就是31。
// Q：一个大的素数，用于避免溢出的，尽量大一点，hash的冲突就小一点；
// 
int hash(const string& needle, int M, int R, int Q) {
    int res = 0;
    for (int i = 0; i < M; i++) {
        res = (res * R + needle[i]) % Q;
    }
    return res;
}


// hashmap与滑动窗口结合，并使用diff的场景。
//
// 即diff表示hashmap中预定义元素个数，后续只有和预定义的字符种类和个数都完全相同的时候，diff才会变为0。
//
// 438. 找到字符串中所有字母异位词: https://leetcode.cn/problems/find-all-anagrams-in-a-string/
vector<int> findAnagrams(string s, string p) {
    if (s.size() < p.size() || p.size() == 0) return {};
    
    unordered_map<char, int> cntMap; // 1. hashmap使用；
    for (char ch : p) {
        cntMap[ch]++;
    }
    
    int diff = cntMap.size(); // 2.diff的使用。
    for (int i = 0; i < p.size() - 1; i++) { // 可以将这部分合并到下边，其实就是j++变为不确定加加。但是多出来的j++看着好不舒服，所以暂时先不合并了。
        cntMap[s[i]]--;
        if (cntMap[s[i]] == 0) diff--; // 这种hashmap的加加减减和使用是可以合并到一个语句中的。
    }

    vector<int> res;
    for (int i = p.size() - 1, j = 0; i < s.size(); i++, j++) {
        cntMap[s[i]]--;
        if (cntMap[s[i]] == 0) diff--;
        if (0 == diff) {
            res.push_back(j);
        }
        cntMap[s[j]]++;
        if (cntMap[s[j]] == 1) diff++;
    }
    return res;
}

// hash表示线段的左右边界
//
// hash表示线段左右边界时，没一个新的元素加入到段中来，先明确写出left,right,newLeft,newRight。这样就可以很快速计算各种东西了。
// 另外的解法：hashmap中保存的是线段长度len，但是没有这种方式清晰，比较容易出错；
// 另外的解法：并查集。参考并查集章节。
// 另外的解法：为提升效率，hash可使用一个数组来标识（效率直接从352ms干到96ms），此时需要注意如下几点：
// 1. 0位置无法被使用，因为0需要被用于判断是否存在线段。需要跳过不使用;
// 2. 由于存在num - 1, num + 1这种，两边预留一个位置，0已提前预留，即只需最后预留一个位置;
// 3. 数据范围是1-maxLen，所以hash大小最小maxLen + 1个。
// 综合以上，hash需要 maxLen + 2 才行。
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
        if (hash.find(num - 1) != hash.end()) { // 和左边合并
            int left = hash[num - 1];
            int right = num - 1;
            int newRight = num; // 用之前，先定义出来，后续使用就很方便了。

            mCnt -= right - left + 1 == m ? 1 : 0;
            hash[left] = newRight;
            hash[newRight] = left;
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