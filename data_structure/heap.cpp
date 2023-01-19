// 啥时候使用堆？ 有序 && 快速查找 && 快速删除
//
// 核心思想：贪心。参考贪心章节。
//
// 条件：返回 nums1 的任意排列。
// 所以：可以对 nums1 任意处理了，比如排序。
//
// 为啥需要用堆？从arr1中找到数和arr2中的配对，第一需要快速找；第二需要找到即删。满足这俩条件的，就是堆了。
// 
// 870. 优势洗牌 https://leetcode.cn/problems/advantage-shuffle/
vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
    vector<int> res(nums1.size());

    map<int, int> val1CntMap;
    for (int num : nums1) {
        val1CntMap[num]++;
    }
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