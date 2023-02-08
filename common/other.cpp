// 时间问题，转化成时分秒计算解决。
//
// 题目很简单，但是如果知晓将12:34之类的入参转化为整数分钟，就可极大简化逻辑。
//
// 1604. 警告一小时内使用相同员工卡大于等于三次的人 https://leetcode.cn/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/
class Solution {
public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        map<string,vector<int>> nameTimesMap;
        for (int i = 0;i < keyName.size();i++) {
            nameTimesMap[keyName[i]].push_back(stoi(keyTime[i].substr(0, 2)) * 60 + stoi(keyTime[i].substr(3,2)));
        }
        vector<string> res;
        for (auto& [name, times] : nameTimesMap) {
            sort(times.begin(), times.end());
            for (int i = 2; i < times.size(); i++) {
                if (times[i] - times[i - 2] <= 60) {
                    res.push_back(name);
                    break;
                }
            }
        }
        return res;
    }
};