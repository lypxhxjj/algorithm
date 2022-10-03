// 字符串查找：暴力法
// 里面一个查找的小技巧，很好用
int strStr(string haystack, string needle) {
    if (haystack.size() < needle.size()) return -1;
    if (needle.size() == 0) return 0;
    for (int i = 0; i + needle.size() - 1 < haystack.size(); i++) {
        for (int j = 0; j < needle.size(); j++) {
            if (needle[j] != haystack[i + j]) {
                break;
            }
            if (j == needle.size() - 1) { // 这里判断。
                return i;
            }
        }
    }
    return -1;
}

// 字符串查找：自定义hash的方式
// M：前M个字节计算hash；
// R: 计算hash的base，一般用于表示进制，所以每多一次计算，相当于一次移位，但是不是必须，比如java.String使用的就是31。
// Q：一个大的素数，用于避免溢出的，尽量大一点，hash的冲突就小一点；
//
// 28. 找出字符串中第一个匹配项的下标： https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
int hash(const string& needle, int M, int R, int Q) {
    int res = 0;
    for (int i = 0; i < M; i++) {
        res = (res * R + needle[i]) % Q;
    }
    return res;
}

int strStr(string haystack, string needle) {
    if (haystack.size() < needle.size() || needle.size() == 0) return -1;

    int R = 256; // 认为是256进制；
    int Q = 40013; // 因为下面要计算RM，为避免RM * R溢出，需要保证(Q-1)^2 <= INT_MAX, INT_MAX的开方向下取整大概46340 
    int RM = 1; // 用于滑动窗口的左指针右移。

    for (int i = 0; i < needle.size()-1; i++) { // 注意要的是R的n-1次幂；
        RM = RM * R % Q;
    }

    int targetHash = hash(needle, needle.size(), R, Q);

    int currHash = hash(haystack, needle.size() - 1, R, Q);
    for (int i = needle.size() - 1, j = 0; i < haystack.size(); i++, j++) {
        currHash = (currHash * R + haystack[i]) % Q;
        if (currHash == targetHash && haystack.substr(j, needle.size()) == needle) {
            return j;
        }
    currHash = (currHash - haystack[j] * RM % Q + Q) % Q; // 这里有个重点。两点：所有乘法之后都要取模，所有减法之前都要加Q。
    }
    return -1;
}