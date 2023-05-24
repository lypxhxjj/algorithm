如何找到数组中不一样的那个数字？

最一般的做法，遍历数组所有元素，保存到hash计数，最后看哪个计数为1哪个就是所求，有木有更优的解法？

先判断前两个数组是否一样，决定了后面的逻辑怎么写。
```
if (arr[0] == arr[1]) {
    for (int i = 2; i < arr.size(); i++) {
        if (arr[i] != arr[0]) {
            return arr[i];
        }
    }
} else {
    return arr[2] == arr[0] ? arr[1];
}
```

eg题目：2451. 差值数组不同的字符串 https://leetcode.cn/problems/odd-string-difference/