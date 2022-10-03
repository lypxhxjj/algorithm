/*
    有几个结论，比较奇特的，可以单独记下：
    1. INT_MAX + 1 = INT_MIN，所以 INT_MAX + 1 < INT_MAX；
    2. INT_MIN - 1 = INT_MAX，所以 INT_MIN - 1 > INT_MIN；
    3. abs(INT_MIN) = INT_MIN，所以 abs(INT_MIN) < 0。
*/

// 任何数字问题，一般不会限制n的正负号的，此时需要将负数转化为正数，从而简化处理逻辑。
int with_signed_n(int n) {
    if (n == INT_MIN) return -1;
    if (n < 0) return -1;
    return 0;
}

// 遍历 n 的每个 bit
void for_bit(int n) {
    while (n) {
        n >>= 1;
    }
}

// 遍历n的每个数字
void for_dig(int n) {
    while (n) {
        y /= 10;
    }
}
