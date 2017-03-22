//遍历数组使用加逼法，可以降低一次循环；（前提有序，所以复杂度至少为o(nlogn)）
//4个数加和为target
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) return {};
        sort(nums.begin(), nums.end());
        set<vector<int>> set;                               //为避免结果重复，可以使用set保存结果，不可以使用unordered_set，因为没有对应的散列函数；
        for (int i = 0; i < nums.size() - 3; ++i) {
            for (int j = i + 1; j < nums.size() - 2; ++j) {
                int left = target - nums[i] - nums[j];
                int k = j + 1,m = nums.size() - 1;
                while (k < m) {
                    int add = nums[k] + nums[m];
                    if (add == left) {
                        set.insert({nums[i], nums[j], nums[k], nums[m]});
                        k++;
                    }
                    else if (add > left) m--;
                    else k++;
                    
                }
            }
        }
        return {set.begin(), set.end()};
    }
};
//使用hashmap先保存两个数的和，这样可以将复杂度将为o（n ^ 2）;
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        set<vector<int>> res;
        unordered_map<int, vector<pair<int, int>>> map;             //hashmap装的是索引对；
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                if (i == j) continue;           
                map[nums[i] + nums[j]].push_back({i, j});
            }
        }
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                int add = target - nums[i] - nums[j];
                if (map.find(add) != map.end()) {
                    for (pair<int, int> loc : map[add]) {
                        if (i != j && i != loc.first && i != loc.second && j != loc.first && j != loc.second) { //不能重复；
                            vector<int> tmp {nums[i], nums[j], nums[loc.first], nums[loc.second]};      //不能重复
                            sort(tmp.begin(), tmp.end());
                            res.insert(tmp);
                        }
                    }
                }
            }
        }
        return {res.begin(), res.end()};
    }
};

//4个数求和的问题，都可以使用hashmap转化为o(n^2)的问题；
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int res = 0;
        unordered_map<int, int> map;
        for (int i = 0; i < A.size(); ++i) 
            for (int j = 0; j < B.size(); ++j) 
                map[A[i] + B[j]]++;
        for (int i = 0; i < C.size(); ++i) {
            for (int j = 0; j < D.size(); ++j) {
                int add = C[i] + D[j];
                if (map.find(-add) != map.end()) {
                    res += map[-add];
                }
            }
        }
        return res;
            
    }
};

//数组的第二种方式：采用函数来解决一个一个的小问题：数独是否合法，两个有序数组的中位数
class Solution {
    bool row_check(vector<vector<char>>&board, int i) {
        unordered_set<char> set;
        for (char ch : board[i]) {
            if (ch == '.') continue;
            else if (set.find(ch) != set.end()) return false;
            else set.insert(ch);
        }
        return true;
    }
    bool col_check(vector<vector<char>>& board, int j) {
        unordered_set<char> set;
        for (int i = 0; i < board.size(); ++i) {
            if (board[i][j] == '.') continue;
            else if (set.find(board[i][j]) != set.end()) return false;
            else set.insert(board[i][j]);
        }
        return true;
    }
    bool squre_check(vector<vector<char>>& board, int i, int j) {
        unordered_set<char> set;
        for (int k = 0; k < 3; k++) {
            for (int m = 0; m < 3; m++) {
                char ch = board[i + k][j + m];
                if (ch == '.') continue;
                else if (set.find(ch) != set.end()) return false;
                else set.insert(ch);
            }
        }
        return true;
        
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); ++i)
            if(!row_check(board, i)) return false;
        for (int i = 0; i < board[0].size(); ++i)
            if (!col_check(board, i)) return false;
        for (int i = 0; i < board.size(); i += 3) {
            for (int j = 0; j < board.size(); j += 3)
                if (!squre_check(board, i, j)) return false;
        }
        return true;
    }
};
//两个数组中找到重复数字：两个方法，（hashmap） + （排序+两个指针）；
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> result;
        for (int i = 0, j = 0; i < nums1.size() && j < nums2.size();) {
            if (nums1[i] == nums2[j]) {
                result.push_back(nums1[i]);
                ++i,++j;
            }
            else if (nums1[i] < nums2[j])
                ++i;
            else
                ++j;
        }
        return result;
    }
};

//二维有序数组中找到第k小的数，基本找第k小的数都可以使用这个方法
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int, vector<int>> pq;                //优先队列的方法来解决第k小/大的问题；
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {        
                pq.push(matrix[i][j]);                      //入队，如果队的大小超了，就pop();
                if (pq.size() > k) pq.pop();
            }
        }
        return pq.top();
    }
};

//找到第3大的数:
/** 如果使用优先队列找到第k大的数，默认是大顶堆，还可以使用小顶堆，小顶堆pop()的是小的，top()的也是小的；
*/
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        set<int> set;                       //第几大的数，可以使用set+ erase，还可以使用priority_queue，但是set的好处是可以去重；
        for (int num : nums) {
            set.insert(num);
            if (set.size() > 3)
                set.erase(set.begin());
        }
        return set.size() < 3 ? *set.rbegin() : *set.begin();   //最后一个元素使用rbegin()
    }
};
//找到第3大，3毕竟太特殊了，所以完全可以遍历一遍就可以找到，不过，如果不考虑重复，还需要小技巧；
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long long first = LLONG_MIN, second = LLONG_MIN, third = LLONG_MIN; //使用LLONG_MIN以便最后的return；
        for (int num : nums) {
            if (num > first) {
                third = second;
                second = first;
                first = num;
            }
            else if (num < first && num > second) {             //判断的时候，没有等于，而且需要判断两项；
                third = second;
                second = num;
            }
            else if (num < second && num > third) {
                third = num;
            }
        }
        return third == LLONG_MIN ? first : third;
    }
};

//数组中数据只差相差k的数据对；没有顺序，不能重复；
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if (k < 0) return 0;
        set<int> set;                       //set保存出现过的数；
        map<int, int> map;                  //map保存结果；
        for (int num : nums) {
            if (set.find(k + num) != set.end())     //k肯定大于0，这里k < 0认为是0，更好的应该认为是-k，所以肯定second大一些；
               map.insert({num, k + num});
            if (set.find(num - k) != set.end())
                map.insert({num - k, num});
            set.insert(num);
        }
        return map.size();
        
    }
};
//timeSeries是放毒的时间点，durations是毒气的作用间隔，求最大的毒气作用时间
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.size() == 0) return 0;
        int res = duration;                                     //至少是一个间隔，代表最后一个数释放的作用时间；
        for (int i = 1; i < timeSeries.size(); ++i) {
            if (timeSeries[i] - timeSeries[i - 1] > duration)   //前后两个数距离大时，前一个数的作用时间是duration；
                res += duration;
            else
                res += timeSeries[i] - timeSeries[i - 1];       //距离比较小的话，前一个数的作用时间是二者之差；
        }
        return res;
    }
    
};
//求连续二进制1的个数；
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int res = 0;
        int tmp = 0;
        for (int num : nums) {
            if (num == 1) 
                res = max(++tmp, res);      //这里，每次给tmp++的时候更新res，可以不用在最后单独考虑tmp和res之间的关系，虽然感觉后者更好一些；
            else
                tmp = 0;
        }
        return res;
    }
};

//1-n缺几个数，找到缺的几个：特点就在于数据被限制在了1-n，所以可以采用将数据看做索引的方式；
/**此种问题有几种解法：
（1）允许改变原数组时，置为相反数；
（2）允许改变原数组时，将那个位置的数，放到其正确的位置上去；
（3）允许改变原数组时，将数据扩展到n * 2;
（4）不允许改变原数组时，使用二分查找加循环处理；
*/
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[abs(nums[i]) - 1] < 0)
                continue;
            nums[abs(nums[i]) - 1] *= -1;
        }
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0)
                res.push_back(i + 1);
        }
        return res;
    }
};
//找到出现两次的数组；
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;                                //由于只是两次，所以不需要使用set;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[abs(nums[i]) - 1] < 0) 
                res.push_back(abs(nums[i]));            //要加进来谁，需要注意；
            else
                nums[abs(nums[i]) - 1] *= -1;
        }
        return res;
    }
};

//设计类题目，随机访问的话，肯定是vector，随机删除的话，可以使用unordered_map，还有list，明前前者好用，然后vector既然也需要随机删除，那么就需要使用pop_back();
class RandomizedCollection {
    vector<int> data;
    unordered_map<int, vector<int>> map;    //这个hashmap的value保存的是key的索引；如果不允许重复，这个就不需要vector了
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool res = true;
        if (map.find(val) != map.end())
            res = false;
        data.push_back(val);
        map[val].push_back((int)data.size() - 1);
        return res;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (map.find(val) == map.end())
            return false;
        int data_last_position = data.size() - 1;
        int val_last_position = map[val].back();
        int last_val = data[data_last_position];
        swap(data[data_last_position], data[val_last_position]);    //交换到最后一个位置来删除；
        data.pop_back();
        *(map[last_val].rbegin()) = val_last_position;
        map[val].pop_back();
        if (map[val].size() == 0) 
            map.erase(val);
        return true;
        
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        srand(0);
        if (data.size() == 0) return -1;
        int location = rand() % (data.size());      //取余之前需要判断是否为空；
        return data[location];
    }
};

//生命游戏问题：一个活cell周围有1个0个4个及以上的生命时，会死掉；一个死cell周围有三个活的的时候会复活；其余死就死，活就活，不变；
//问题的难点，在于就是完全相互的作用，且作用一次，就是你判定为其最后是死掉，那么下次它为neighbor时，应该判定为原来的状态；
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int depth = board.size(), width = depth ? board[0].size() : 0;      //技巧1：一行代码得到width和depth；
        for (int i = 0; i < depth; ++i) {
            for (int j = 0; j < width; ++j) {
                int cnt = 0;
                for (int m = max(0, i - 1); m < min(depth, i + 2); ++m) {       //技巧2：如果找到其四周的坐标；  技巧3：使用depth，width这种有含义的，容易理解
                    for (int n = max(0, j - 1); n < min(width, j + 2); ++n) {
                        cnt += (board[m][n] & 1);                               //既然使用最后一位来判断死活，那下边赋值的2和3必须是其原来的状态；
                    }
                }
                if (board[i][j] == 0 && cnt == 3) board[i][j] = 2;              //2的最后一位与其原来是死的状态相同；
                if (board[i][j] == 1 && (cnt > 4 || cnt < 3)) board[i][j] = 3;  //只需要考虑这两种，死而复活或者活变死两种情况；
            }
        }
        for (int i = 0; i < depth; ++i) {
            for (int j = 0; j < width; ++j) {
                if (board[i][j] == 2) board[i][j] = 1;                             //状态找完了，就需要更新状态了；
                else if (board[i][j] == 3) board[i][j] = 0;
            }
        }
    }
};
