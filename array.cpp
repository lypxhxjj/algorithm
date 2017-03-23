//1-n缺失了一个，找到缺失的那个：数学的方法：
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int add1 = 0;
        int add2 = 0, i = 1;
        for (int num : nums) {
            add1 += num;
            add2 += i++;
        }
        return add2 - add1;
    }
};
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

//数组里存的是1-n，找到重复数字，不允许改变数组；那就是二分法；
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int begin = 1, end = nums.size() - 1;
        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            int cnt = count_if(nums.begin(), nums.end(), bind2nd(less<int>(), mid + 1));    //使用count_if统计，然后
            if (cnt > mid) end = mid;
            else begin = mid + 1;
        }
        return begin;
    }
};

//设计类题目，随机访问的话，肯定是vector，随机删除的话，可以使用unordered_map，还有list，明前前者好用，然后vector既然也需要随机删除，那么就需要使用pop_back();
class RandomizedCollection {
    vector<int> data;                               //vector用于随机访问，其pop_back()也可以随机删除，但是需要unordered_map保存其索引；
    unordered_map<int, priority_queue<int>> map;    //map需要使用priority_queue来保存索引，因为删除掉一个元素之后，改变另一个元素的索引，那个另一个元素索引不一定按顺序了；
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
        map[val].push((int)data.size() - 1);
        return res;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (map.find(val) == map.end())
            return false;
        int data_last_position = data.size() - 1;
        int val_last_position = map[val].top();         //基本原理就是根据map保存的索引将待删除的元素移到最后去，然后删除；
        int last_val = data[data_last_position];
        if (last_val == val) {
            data.pop_back();
            map[last_val].pop();
        }
        else {
            data[val_last_position] = last_val;
            data.pop_back();
            map[last_val].pop();
            map[last_val].push(val_last_position);
            map[val].pop();
        }
        if (map[val].size() == 0) 
            map.erase(val);                         //注意如果没有了，要erase一下；
        return true;
        
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return data[rand() % data.size()];      //不能加srand(0)，leetcode还不能解析出来；
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

//小专题：std::partition以及std::stable_partition的实现
/* 函数 __partition 将 __first 到 __last 的元素分为两个部分，第一部分为满足一元判断条件 __pred 的元素，第二部分为不满足一元判断条件的元素。
返回值为分割这两部分的分割位置。函数中至始至终 __first(不包括 __first) 之前的元素都是满足判断条件的。*/
template <class _ForwardIter, class _Predicate>
_ForwardIter __partition(_ForwardIter __first,
             _ForwardIter __last,
             _Predicate   __pred,
             forward_iterator_tag) {
  if (__first == __last) return __first;

  while (__pred(*__first))
    if (++__first == __last) return __first;    //先找到第一个需要被换走的
  _ForwardIter __next = __first;

  while (++__next != __last)    //从其后面找可以被换回来的；
    if (__pred(*__next)) {
      swap(*__first, *__next);
      ++__first;                //对被换走的将其换回来；
    }

  return __first;
}
/* 函数 __partition 将 __first 到 __last 之间的内容分割为两部分，前一部分为满足判断条件 __pred 的元素，
第二部分为不满足判断条件 __pred 的元素，返回值为分割这两部分的分割值。函数至始至终保证 __first(不包括 __first) 之前的元素都是满足条件的，
__last(包括 __last) 之后的元素都是不满足条件的，当 __first == __last，则 __first 被作为分割值返回。*/
template <class _BidirectionalIter, class _Predicate>
_BidirectionalIter __partition(_BidirectionalIter __first,
                   _BidirectionalIter __last,
                   _Predicate __pred,
                   bidirectional_iterator_tag) {
  while (true) {
    while (true)                    //就是一个从前面找，一个从后面找，找到了就交换；
      if (__first == __last)
    return __first;
      else if (__pred(*__first))
    ++__first;
      else
    break;
    --__last;
    while (true)
      if (__first == __last)                    //边界条件在循环的过程中就判断了，如果到达了最后，就直接返回；
    return __first;
      else if (!__pred(*__last))
    --__last;
      else
    break;
    iter_swap(__first, __last);
    ++__first;
  }
}
/* 函数 partition 将 __first 到 __last 之间的内容分割为两部分，第一部分为满足判断条件 __pred 的元素，
第二部分为不满足判断条件的元素。函数根据迭代器类型的不同调用之前定义的不同的 __partition 函数实现想要的功能。*/
template <class _ForwardIter, class _Predicate>
inline _ForwardIter partition(_ForwardIter __first,
                  _ForwardIter __last,
                  _Predicate   __pred) {
  __STL_REQUIRES(_ForwardIter, _Mutable_ForwardIterator);
  __STL_UNARY_FUNCTION_CHECK(_Predicate, bool, 
    typename iterator_traits<_ForwardIter>::value_type);
  return __partition(__first, __last, __pred, __ITERATOR_CATEGORY(__first));
}
/* __inplace_stable_partition 用来将 __first 到 __last 之间长度从 __first 开始为 __len 的部分分割成两部分，
第一部分为满足一元判断条件的部分，第二部分为不满足条件的部分，函数递归的进行，先对前半部分和后半部分分别调用 __inplace_stable_partition
函数使得这两部分都被各自被分割为两块，然后将前半部分的后一块和后半部分的前一块进行交换。假设递归函数中得到的分割序列是稳定的，
则当前函数得到的序列也是稳定的，又因为初始条件是稳定的，所以函数最终得到的序列是稳定的。*/
template <class _ForwardIter, class _Predicate, class _Distance>
_ForwardIter __inplace_stable_partition(_ForwardIter __first,
                    _ForwardIter __last,
                    _Predicate __pred, _Distance __len) {
  if (__len == 1)
    return __pred(*__first) ? __last : __first;
  _ForwardIter __middle = __first;
  advance(__middle, __len / 2);
  return rotate(__inplace_stable_partition(__first, __middle, __pred,   //注意返回值是不满足条件的第一个；
                       __len / 2),  
        __middle,                                                 //旋转的意思是，最后middle成为第一个元素了；
        __inplace_stable_partition(__middle, __last, __pred,    //这个的返回值也是不满足条件的第一个；
                       __len - __len / 2));
}
/* 函数 __stable_partition_adaptive 也是将 __first 到 __last 之间的内容分割为两部分，第一部分为满足判断条件的元素组成，
第二部分为不满足判断条件的元素组成，并且函数是稳定的。函数中根据 __buffer_size 的大小分两种情况，但需要分割的元素个数小于
__buffer_size 时，则将 __buffer 作为辅助空间，先将满足条件的元素放在以 __first 为首地址的空间内，
而将不满足条件的元素放在以 __buffer 为首地址的空间，最后将 __buffer 中暂存的元素复制到 __first 到 __last 之间满足条件的元素后面。
如果 __buffer_size 的大小小于需要分割的元素个数 __len ，则直接使用上面定义的方法实现稳定的分割。*/
template <class _ForwardIter, class _Pointer, class _Predicate, 
      class _Distance>
_ForwardIter __stable_partition_adaptive(_ForwardIter __first,
                     _ForwardIter __last,
                     _Predicate __pred, _Distance __len,
                     _Pointer __buffer,
                     _Distance __buffer_size) 
{
  if (__len <= __buffer_size) {         //空间足够的话，就使用额外空间的方法；
    _ForwardIter __result1 = __first;
    _Pointer __result2 = __buffer;
    for ( ; __first != __last ; ++__first)
      if (__pred(*__first)) {
    *__result1 = *__first;
    ++__result1;
      }
      else {
    *__result2 = *__first;
    ++__result2;
      }
    copy(__buffer, __result2, __result1);
    return __result1;
  }
  else {                                        //不够的话，就使用递归，原理同上；不过此时空间够了就使用空间来解决问题；
    _ForwardIter __middle = __first;
    advance(__middle, __len / 2);
    return rotate(__stable_partition_adaptive(
              __first, __middle, __pred,
              __len / 2, __buffer, __buffer_size),
            __middle,
            __stable_partition_adaptive(
              __middle, __last, __pred,
              __len - __len / 2, __buffer, __buffer_size));
  }
}
/* 函数 __stable_partition_aux 将 __first 到 __last 之间的内容分割为两部分，第一部分由满足条件 __pred 的元素组成，
第二部分有不满足条件的元素组成。函数首先申请一个足够容纳 __first 到 __last 之间的所有元素的临时缓冲区，如果申请成功，
则调用 __stable_partition_adaptive 函数实现分割，否则调用 __inplace_stable_partition 实现分割。*/
template <class _ForwardIter, class _Predicate, class _Tp, class _Distance>
inline _ForwardIter
__stable_partition_aux(_ForwardIter __first, _ForwardIter __last, 
               _Predicate __pred, _Tp*, _Distance*)
{
  _Temporary_buffer<_ForwardIter, _Tp> __buf(__first, __last);      //先看分配到足够的空间没；
  if (__buf.size() > 0)
    return __stable_partition_adaptive(__first, __last, __pred,
                       _Distance(__buf.requested_size()),
                       __buf.begin(), __buf.size());
  else
    return __inplace_stable_partition(__first, __last, __pred, 
                      _Distance(__buf.requested_size()));
}
/*函数 stable_partition 将 __first 到 __last 之间的内容分割为上面定义的两部分，具体的功能实现通过调用 __stable_partition_aux 函数来完成。*/
template <class _ForwardIter, class _Predicate>
inline _ForwardIter stable_partition(_ForwardIter __first,
                     _ForwardIter __last, 
                     _Predicate __pred) {
  __STL_REQUIRES(_ForwardIter, _Mutable_ForwardIterator);
  __STL_UNARY_FUNCTION_CHECK(_Predicate, bool,
      typename iterator_traits<_ForwardIter>::value_type);
  if (__first == __last)
    return __first;
  else
    return __stable_partition_aux(__first, __last, __pred,
                  __VALUE_TYPE(__first),
                  __DISTANCE_TYPE(__first));
}
