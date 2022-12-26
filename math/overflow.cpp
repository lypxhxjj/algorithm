/*
 c++中有符号的溢出会抛出异常，认为是一种未定义行为，所以没有办法直接使用有符号的溢出来处理问题，那么怎么判断溢出呢？
*/

// 处理溢出问题的方式1：
// 1. 使用无符号数计算；
// 2. 使用除法校验是否溢出
//
// 7. 整数反转: https://leetcode.cn/problems/reverse-integer/
//
// 这种解法因为引入了无符号数，所以一些坑就出现了：
// 1. res是无符号数，强制加上符号，可能会溢出：https://leetcode.cn/submissions/detail/369378998/
bool isOverflow1(unsigned int res, int dig) {
    return (res * 10 + dig) / 10 != res;
}

// 处理溢出问题的方式2：
// 基于INT_MAX计算临界值，然后去比对。
//
// 7. 整数反转: https://leetcode.cn/problems/reverse-integer/
//
// 如果比较简单，这个方式校验可简化到一行代码，参考math.go:
// 29. 两数相除： https://leetcode.cn/problems/divide-two-integers/
bool isOverflow2(int base, int dig) {
    const int maxBase = INT_MAX / 10;
    const int maxDig = INT_MAX % 10;
    return base > maxBase || (base == maxBase && dig > maxDig); // 本质就是一行代码
}

// 处理溢出的方式3：
// 使用long long。int的问题使用long long 基本是可以不溢出的
// 但是使用long long 只能解决int类型参数溢出问题，无法解决long long 本身参数类型溢出问题。
//
// 7. 整数反转: https://leetcode.cn/problems/reverse-integer/
//
// 强制转化，需要注意，所有需要计算的地方最好都转化为long long
// 1. res > INT_MAX + 1。不等式右边会抛出异常。(https://leetcode.cn/submissions/detail/369379961/)
bool isOverflow(long long base, int dig) {
    return false;
}

// 总之，推荐的方式首选long long；其次是INT_MAX校验法。(long long的比较简单，这里代码就不写了)
//
// 负数转化为正数：一般就是单独考虑INT_MIN + 直接转化就可以，逻辑一般都比较简单；
//
// 主干编程法：可以先不考虑溢出，写代码，最后再考虑溢出。
//
// 溢出的方式：一行代码，与INT_MAX/10，与INT_MAX% 10相比较即可。
//
// 7. 整数反转: https://leetcode.cn/problems/reverse-integer/
int reverse(int x) {
    if (x == INT_MIN) return 0;
    if (x < 0) return -reverse(-x);

    int res = 0;
    while (x) {
        int dig = x % 10;
        if (res > INT_MAX / 10 || (res == INT_MAX / 10 && dig >= INT_MAX % 10)) { // 主干编程法之外的部分，一点也不突兀。
            return 0;
        }
        res = res * 10 + dig;
        x /= 10;
    }
    return res;
}

// 溢出判断：INT_MAX判断法。
//
// 正负数问题，没有办法全部转化为正数，只能通过flag，内部溢出判断复杂了些。
//
// 主干编程法：溢出逻辑最后再写，优先主干编程，那么逻辑非常清晰了。
//
// 如何判断溢出？正常思路是正负数分类讨论的，但这里做了简化，一旦超过INT_MAX，那么要么就是INT_MAX，要么就是INT_MIN。一定是溢出状态，所以不需要分类讨论了。
// 结论：既然正负号其实不需要分类讨论的，那么上一题（7）是否可以不再将负数转化为正数再解决？ 不可以。负数不能参与取模运算，结论是未定义的。
//
// 8. 字符串转换整数 (atoi) https://leetcode.cn/problems/string-to-integer-atoi/
int myAtoi(string s) {
    if (s.size() == 0) {
        return 0;
    }

    int i = 0;
    while (i < s.size() && s[i] == ' ') i++;

    int flag = 1;
    if (i < s.size() && (s[i] == '-' || s[i] == '+')) {
        flag = s[i] == '+' ? 1 : -1;
        i++;
    }

    int res = 0;
    while (i < s.size() && isdigit(s[i])) {
        int dig = s[i] - '0';
        if (res > INT_MAX / 10 || (res == INT_MAX / 10 && dig > INT_MAX % 10)) { // 不需要分类讨论正负数了，只要超过INT_MAX就一定是溢出状态了。
            return flag > 0 ? INT_MAX : INT_MIN;
        }
        res = res * 10 + dig;
        i++;
    }
    return res * flag;
}