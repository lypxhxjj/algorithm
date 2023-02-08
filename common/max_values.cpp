// 辅助数组保存当前的最大值算法。
//
// 关键点1： 如何能想到这个算法能解决这个问题？考虑下是否与最大值有关。
// 这个先作为范例题目背下来。(本质是异构问题)
//
// 关键点2：求最大值辅助数组的过程中，两个小方法，要么初始值为INT_MIN，此时多申请一个位置；要么赋值maxValues[0] = arr[0]；
//
// 关键点3：算法本身的问题。注意是当前位置i，是(i, last]的最小值不小于[0, i]的最大值，所以先比较后求minV。
// 1. 比较方式是特殊的，另外一个特殊点是，初始比较位置，是从INT_MIN开始，而不是最后一个元素。这个原因是，整个arr是其中一个结果的。
//
// 768. 最多能完成排序的块 II https://leetcode.cn/problems/max-chunks-to-make-sorted-ii/
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        if (arr.size() == 0) return 0;

        vector<int> maxValues(arr.size() + 1, INT_MIN);
        for (int i = 0; i < arr.size(); i++) {
            maxValues[i + 1] = max(maxValues[i], arr[i]);
        }

        int res = 0;
        int minValue = INT_MAX;
        for (int i = arr.size() - 1; i >= 0; i--) {
            if (minValue >= maxValues[i + 1]) {
                res++;
            }
            minValue = min(minValue, arr[i]);
        }
        return res;
    }
};