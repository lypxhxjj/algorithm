// 贪心算法都是很明显的，但是比较麻烦的是贪心算法的证明。

// 本题重点：贪心的证明：反证法 + 替换
//
// 优先买价格便宜的。反证法 + 替换。
// 反证法：如果不是买最便宜的，买了贵的，那么便宜的一定可以直接替换那个贵的。
//
// 1833. 雪糕的最大数量 https://leetcode.cn/problems/maximum-ice-cream-bars/
int maxIceCream(vector<int>& costs, int coins) {
    sort(costs.begin(), costs.end());
    int sum = 0;
    for (int i = 0; i < costs.size(); i++) {
        sum += costs[i];
        if (sum > coins) {
            return i;
        }
    }
    return costs.size();
}

// 本题重点：贪心的证明：要淘汰的越小越好。
// 
// 下面的这个论证的很精彩：
//  假设排完序的结果为a1<=b1<=a2<=b2<=...<=an<=bn
// 那么a1应该跟谁一组呢？
// a1作为全局最小值，无论跟谁一组a1都会被累加进答案，相反，a1的搭档会被永久排除。
// 既然如此，莫不如排除一个较小的数，即给a1找一个“最小的搭档”b1。
//
// 561. 数组拆分 https://leetcode.cn/problems/array-partition/
int arrayPairSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int res = 0;
    for (int i = nums.size() - 2; i>= 0; i-=2) {
        res += nums[i];
    }
    return res;
}

// 什么时候不能用贪心？一次贪心可能带来接下来几次的最坏结果，结果将贪心带来的好处给中和掉了。
//
// 本题，不能使用优先吃2/3的方式贪心，因为吃完2/3可能会引起接下来的1，不如全部1/2更快。
//
// 1553. 吃掉 N 个橘子的最少天数 https://leetcode.cn/problems/minimum-number-of-days-to-eat-n-oranges/
unordered_map<int, int> cache;
int minDays(int n) {
    if (n == 1) return 1;
    if (cache.count(n) != 0) return cache[n];
    int res = 0;
    if (n % 6 == 0) {
        res = min(minDays(n / 2) + 1, minDays(n / 3) + 1);
    }
    else if (n % 3 == 0) {
        res = min(minDays(n / 3) + 1, minDays(n - 1) + 1);
    } 
    else if (n % 2 == 0) {
        res = min(minDays(n / 2) + 1, minDays(n - 1) + 1);
    }
    else {
        res =  1 + minDays(n -1);
    }
    cache[n] = res;
    return res;
}

// 贪心的证明：我们需要最大值，那么可以让别人尽量少。
//
// 两步：
// 1. 每次让B尽量少，所以B从最后开始拿，最后的1/3是B的，前边2/3是A和你的；
// 2. A 虽然拿大的那个，但是可以让A尽量小。所以A拿最大的那个时候，我们可以拿第二大，让A拿不到第二大的。
// ps.如果只分析「你」如何拿到最大，不太好分析。
//
// 1561. 你可以获得的最大硬币数目 https://leetcode.cn/problems/maximum-number-of-coins-you-can-get/
int maxCoins(vector<int>& piles) {
    int res = 0;
    sort(piles.begin(), piles.end());
    for (int i = piles.size() - 2, j = 0; j < piles.size() / 3; j++, i-=2) {
        res += piles[i];
    }
    return res;
}

// 贪心
//
// 如果希望后续依然能满足，那么肯定希望当前这俩数尽量小；如果希望前边继续符合条件，那么希望当前这俩数不那么小。
// 所以，优先变到可能的最小。
//
// 665. 非递减数列 https://leetcode.cn/problems/non-decreasing-array/
bool checkPossibility(vector<int>& nums) {
    bool isFind = false;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] >= nums[i - 1]) {
            continue;
        }
        if (isFind) {
            return false;
        }
        isFind = true;
        if (i == 1) {
            nums[i - 1] = INT_MIN;
        } else if (nums[i] >= nums[i - 2]) { // i位置只能变大，所有优先将i-1位置变小。
            nums[i - 1] = nums[i - 2];
        else {
            nums[i] = nums[i - 1]; // 不得已再变大i位置，但也只能变到和i-1一样大。
        }
    }
    return true;
}

// 不知道能不能说服未来的我
//
// 核心思想：贪心。每个arr2中的元素，从arr1中找第一个比它大的。如何证明？
// 因为要两个元素配对，从arr2角度来说，肯定希望匹配到的arr1元素越小越好，因为可以让比我大的元素也有所匹配；
// 从arr1角度来说，肯定希望匹配到的arr2越大越好，因为可以让比我小的元素也有所匹配。
//
// 贪心会带来更坏的结果吗？比如两个比较接近的数配对了，会造成啥？会造成比arr2[i]小的数失去机会，但是机会其实让给了arr2[i]，并没有造成损失。
// 
// 870. 优势洗牌 https://leetcode.cn/problems/advantage-shuffle/
vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
    vector<int> res(nums1.size());

    map<int, int> val1CntMap;
    for (int num : nums1) {
        val1CntMap[num]++;
    }
    sort(nums1.begin(), nums1.end());
    for (int i = 0; i < nums2.size(); i++) {
        auto it = val1CntMap.upper_bound(nums2[i]);
        if (it == val1CntMap.end()) {
            it = val1CntMap.begin();
        }
        res[i] = it->first;
        if (--it->second == 0) {
            val1CntMap.erase(it);
        }
    }
    return res;
}