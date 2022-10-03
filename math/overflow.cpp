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
// 7. 整数反转: https://leetcode.cn/problems/reverse-integer/
bool isOverflow2(int base, int dig) {
    const int maxBase = INT_MAX / 10;
    const int maxDig = INT_MAX % 10;
    return base > maxBase || (base == maxBase && dig > maxDig);
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