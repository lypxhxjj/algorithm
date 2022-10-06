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
// 参考滑动窗口章节。
//
// 438. 找到字符串中所有字母异位词: https://leetcode.cn/problems/find-all-anagrams-in-a-string/