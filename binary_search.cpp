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

//使用long long 的思想，任何一个和都可能越界；
//有序数组和为target的索引；
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i = 0, j = numbers.size() - 1;
        while (i < j) {
            long long add = numbers[i] + numbers[j];
            if (add == target) return {i + 1, j + 1};
            else if (add > target) --j;
            else ++i;
        }
        return {};
    }
};

//实现lower_bound，end = mid是因为那种情况end也可能是解；
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int begin = 0, end = nums.size();
        while (begin < end) {                           //查找嘛，所以使用<；
            int mid = begin + (end - begin) / 2;
            if (nums[mid] == target) end--;
            else if (nums[mid] > target) end = mid;     //重点在end = mid，因为此时mid可能是解；
            else begin = mid + 1;
        }
        return begin;
    }
};
//猜数，原理完全一样，毕竟lower_bound；
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int begin = 1, end = n;
        while (begin < end) {                       //查找；
            int mid = begin + (end - begin) / 2;
            int result = guess(mid);
            if (result > 0) begin = mid + 1;
            else end = mid;                         //有可能是当前解哦
        }
        return begin;
    }
};
//计算开方数：要求结果尽量小，计算mid时上取整；
class Solution {
public:
    int mySqrt(int x) {
        if (x < 0) return -1;
        long long  begin = 0, end = x;
        while (begin < end) {
            long long mid = begin + (end - begin + 1) / 2;  //结果尽量小，需要上取整；
            long long mul = mid * mid;
            if (mul > x) end = mid - 1;
            else if (mul < x) begin = mid;
            else return mid;                                //等于的return出来，否则会出现死循环；
        }
        return begin;
    }
};
