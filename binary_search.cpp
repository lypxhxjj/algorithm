//二分查找的方法1：begin和end代表的数组的索引，[begin,end]代表可能解所在的区间，只有最后二者相等了，就可以找到了；	
//此题是针对找到，如果找不到就另说了；
//问题1：寻找旋转数组的最小值；
class Solution {
public:
    int findMin(vector<int>& arr) {
        if (arr.size() == 0) return 0;
        auto begin = arr.begin(), end = arr.end() - 1;
        while (begin < end) {                               //找一个数的话，那就不能相等，最后返回值是相等；
            auto mid = begin + (end - begin) / 2;
            int tmp = *end;
            if (*mid > tmp) begin = mid + 1;
            else if (*mid == tmp) end--;
            else end = mid;
        }
        return *begin;
    }
};

//判断一个数是否是完全平方数；
class Solution {
public:
    bool isPerfectSquare(int num) {
        int begin = 1, end = num;                       //begin和end代表的含义是第一个可能解和最后一个可能解；
        while (begin <= end) {
            long long mid = begin + (end - begin) / 2;  //long long的使用；
            long long mul = mid * mid;
            if (mul == num) return true;                //返回值是bool好办，直接在满足条件的地方返回true就好了；
            else if (mul > num) end = mid - 1;
            else begin = mid + 1;
        }
        return false;
    }
};
