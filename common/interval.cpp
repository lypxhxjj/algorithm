// 区间内有多少个小区间：区间标准化 + 简单相除
// 区间标准化两个方面含义：区间有效化，区间规格化。
//
// 1904. 你完成的完整对局数 https://leetcode.cn/problems/the-number-of-full-rounds-you-have-played/
int numberOfRounds(string loginTime, string logoutTime) {
    int inHour = stoi(loginTime.substr(0, 2));
    int inMin = stoi(loginTime.substr(3, 2));
    int outHour = stoi(logoutTime.substr(0, 2));
    int outMin = stoi(logoutTime.substr(3, 2));

    if (outMin < inMin) { // 区间有效化；
        outMin += 60;
        outHour--;
    }
    if (logoutTime < loginTime) { // 区间有效化
        outHour += 24;
    }
    if (inMin % 15 != 0) { // 区间规格化
        inMin = inMin + (15 - inMin % 15);
    }
    int deltaMin = outMin - inMin + (outHour - inHour) * 60;
    return deltaMin / 15;
}