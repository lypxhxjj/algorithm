// 颜色不一样的小球排列，最多可以排多少个？
// 1. 将最大数量的小球拿出去，将剩余的小球按颜色分好堆。
// 2. 每次从每一堆中拿一个排列好，这样第二多的小球颜色可能挨着，但是其他的小球颜色一定不挨着。
// 3. 将颜色最多的小球，插板法到上述排列，可以优先从后面插入。这样就一定可以将第二多的小球给分离开。但是现在的问题是，最多的小球非常多怎么办？
// 4. 第二步排列了n个，那么就可以插入n+1个板，只要数量最多的小球数量不多于这个，那么就可以放下，多余这个就放不下，最多也就n * 2 + 1个了。
//
// 1953. 你可以工作的最大周数 https://leetcode.cn/problems/maximum-number-of-weeks-for-which-you-can-work/
long long numberOfWeeks(vector<int>& milestones) {
    if (milestones.size() == 0) return 0;
    if (milestones.size() == 1) return 1;

    int maxVal = milestones[0];
    long long sum = 0;
    for (int num : milestones) {
        maxVal = max(maxVal, num);
        sum += num;
    }
    sum -= maxVal;

    if (maxVal > sum + 1) {
        return sum * 2 + 1;
    }
    return sum + maxVal;
}