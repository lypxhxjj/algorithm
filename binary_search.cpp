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
//找到第一个坏的，不能从n + 1结束，因为n + 1调用isBadVersion未定义；
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int begin = 0, end = n;
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if (!isBadVersion(mid)) begin = mid + 1;
            else end = mid;
        }
        return begin;
    }
};
//加热器求半径的问题，这个题的解法值得研究研究；求半径时，处理的边界条件是左右各一个，如果是边界就用最大值代替；
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int res = 0;
        for (int house : houses) {
            auto it = lower_bound(heaters.begin(), heaters.end(), house);   //lower_bound得到的是大于等于house的位置；，要找半径所以得向前找；
            int res1 = (it == heaters.end()) ? INT_MAX : (*it - house);     //分别判断是不是最左值还是最右值，分别得出结果，然后取最大最小值；这个思路有点意思；
            int res2 = (it == heaters.begin()) ? INT_MAX : (house - *--it);
            res = max(res, min(res1, res2));
        }
        return res;
    }
};

//找到处于当前区间右边的索引，由于是索引，所以需要使用map，思路比较简单；
class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        map<int, int> lefts;
        for (int i = 0; i < intervals.size(); ++i) {
            lefts.insert({intervals[i].start, i});
        }
        vector<int> res;
        res.reserve(intervals.size());
        for (auto interval : intervals) {
            auto it = lefts.lower_bound(interval.end);
            if (it == lefts.end()) res.push_back(-1);
            else res.push_back((*it).second);
        }
        return res;
    }
};
//循环数组的问题，找到最小值，这种比找到某个值要简单，只需要nums[mid]和nums[end]比较就可以
class Solution {
public:
    int findMin(vector<int>& nums) {
        int begin = 0;
        int end = nums.size() - 1;
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if (nums[mid] > nums[end])              //如果允许相等的话，就需要end--这个语句了
                begin = mid  + 1;
            else 
                end = mid;
        }
        return nums[begin];
    }
};

//旋转数组中找到某个数，此时向哪边走需要判断哪边是有序的，还是根据nums[mid]和nums[end]比较就好，根据有序的情况不一样分别考虑向左还是向右，一共四种情况，比较容易理解的；
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int begin = 0, end = nums.size() - 1;
        while (begin <= end) {                          //这个属于找到找不到的问题，所以使用等于；
            int mid = begin + (end - begin) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < nums[end]) {                //需要先判断好哪边有序，然后再决定走哪边；
                if (target < nums[mid] || target > nums[end]) end = mid - 1;                //记住，根据有序的那边的边界和target比较决定走哪边；
                else begin = mid + 1;
            }
            else {
                if (target > nums[mid] || target < nums[begin]) begin = mid + 1;    //这里搞错了，想清楚要哪边，怎么要；
                else end = mid - 1;
            }
                                                        //如果nums中存在相等元素，则相等的时候是end--；
        }
        return -1;
    }
};

//找到蛇形有序数组中的某个数是否存在，可以使用两步二分法，第一步在第一列找，第二步在找到的行找；
//第一步无法使用lower_bound，所以得自己实现，两点，数组的最后一个元素的下一位置，也是可行解，end要放在那；第二点，lower_bound找到的是大于等于该树的点，
//upper_bound找到的是大于该数的点；所以找完之后需要判断是结果怎么样，是最后一个元素的下一位置怎么办，不是前两者咋办；（begin需要减1）
//蛇形数组变为一维数组的下标变化是：[i/n][i%n]  //这个就不再实现了
class Solution {
public:
    
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return false;
        int begin = 0, end = matrix.size();         //自定义实现lower_bound需要注意end的取值；
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if (matrix[mid][0] >= target) end = mid;
            else begin = mid + 1;
        }
        
        if (begin != matrix.size() && matrix[begin][0] == target) return true;
        else begin = begin == 0 ? 0: begin - 1;                                 //lower_bound实现后需要根据其意义，调整begin的位置；
        auto it = lower_bound(matrix[begin].begin(), matrix[begin].end(), target);
        if (it == matrix[begin].end()) return false;
        if (*it == target) return true;
        return false;
    }
};
/************************************************* 不是很明显使用二分法的题 ***************************************/
//找到重复数字，不允许改动数组；
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int begin = 1, end = nums.size() - 1;
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            int cnt = count_if(nums.begin(), nums.end(), bind2nd(less<int>(), mid + 1));    //二分查找 + 每次遍历一遍数组，此时复杂度才o(nlogn)
            if (cnt > mid) end = mid;                       //count_if用的很牛逼啊
            else begin = mid + 1;       //二分查找的最基本模型；
        }
        return begin;
    }
};

//查找二维数组中第k小的数，二维数组从左向右，从上向下是有序的，不是蛇形有序；
//此题最好的解法是使用优先队列，见数组专题，但是也可以使用二分查找；
//针对此题为什么一定有解在begin上，还不晓得为什么
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int length = matrix.size();
        int begin = matrix[0][0], end = matrix[length - 1][length - 1];     //二分查找新的思路，不管三七二十一，先找到最大值和最小值，取中点，然后看找到了没这样子；
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            int cnt = count_cnt(matrix, mid);
            if (cnt < k) begin = mid + 1;       //原本等于是可能是最优解，所以尽量凑到end = mid上去，而不是begin = mid上去；
            else end = mid;
        }
        return begin;
    
    }
    int count_cnt(vector<vector<int>>& matrix, int target) {    //用于找二维数组中比target数小的数据量，可以使用upper_bound直接求解；
        int i = matrix.size() - 1, j = 0;
        int res = 0;
        while (i >= 0 && j < matrix[0].size()) {                //此处使用的是从左下角，依次遍历每一列，没一列的i上边的数都是比target小的，加起来就好了；
            if (matrix[i][j] > target) --i;
            else if (matrix[i][j] <= target) {
                res += i + 1;
                j++;
            }
        }
        return res;
    }
};
//找到数组中的极大值，遍历一遍数组肯定可以得到，但是使用二分法可以更快的得到，因为mid位置比相邻元素肯定有一个大的，那么这个大的可能是解，如果不是的话，那么它后面的数还有比它大的，最差还是最后一个元素的
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int begin = 0;
        int end = nums.size() - 1;
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if (mid == nums.size() - 1 || nums[mid] > nums[mid + 1]) //二分查找思路与前面一样的；
                end = mid;
            else 
                begin = mid + 1;
        }
        return begin;
    }
};
