
// 配对问题，一般使用的是栈：
// 1. 栈中保存的都是索引；
// 2. 消消乐时，正常能算出的是从i到消位置的大小，但是处理不了()()的情况，所以不能那么计算；
// 3. 根据消消乐，遇到左括号入栈是没有问题的；但是遇到右括号，就需要分类讨论了（假设此时栈中是A B，到来的是C）
// （1）B和C成对，消除。此时计算以C为末尾的最大长度是A-C，因为A-C之间的数据都被消消乐了；
// （2）B和C不成对，那么B也是右括号，说明到B为止，没办法消了，结果又来了一个右括号C，所以以C结尾的肯定也不能构成结果；
// （3）B和C不成对时，C必须入栈，因为对于以后来说，你消消乐可以，但是没办法越过C了，因为C及其之前的是以右括号比左括号多结束的。此时的C是作为消消乐的左边界存在的；
// （4）B和C不成对时，B就可以出栈了，左边界只有一个C就可以了，反正越不过去C。这样，不论栈顶的B是左括号还是右括号，都需要出栈，区别在于如果是右括号，C需要入栈；如果是左括号，说明发现了结果，需要更新结果。
//
// 以上是理解，数据结构内部是什么样子的？
// 1. 保存的是索引，且一直不为空。（初始化一个-1进去）
// 2. 左括号直接入栈的；
// 3. 右括号遇到左括号，那么消消乐，并尝试计算结果；
// 4. 右括号遇到右括号，前者取代后者，只保留一个右括号即可。 
//
// 32. 最长有效括号: https://leetcode.cn/problems/longest-valid-parentheses/
int longestValidParentheses(string s) {
    stack<int> st;
    st.push(-1); // )上次不能消掉的位置
    int res = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            int lastPos = st.top();
            st.pop();
            if (lastPos == -1 || s[lastPos] == ')') {
                st.push(i);
            } else {
                res = max(res, i - st.top());
            }
        }
    }
    return res;
}

// 一个元素的消消乐，往往可以将栈的使用优化掉，代码很简单：
// 1. 之前的栈，使用两个变量来代替。不能只使用一个leftNum，因为需要知道完成消消乐时，总的长度信息，长度信息是left + right，单靠一个left不成事；
// 2. 小结论：不论哪边遍历，一旦发现leftNum == rightNum，那么其实对于当前「right」来说，[left, right]就已经是最大长度了。
//
// 32. 最长有效括号: https://leetcode.cn/problems/longest-valid-parentheses/
int longestValidParentheses(string s) {
    int leftNum = 0, rightNum = 0;
    int res = 0;
    for (char ch : s) {
        if (ch == '(') leftNum++;
        else rightNum++;

        if (leftNum == rightNum) res = max(res, leftNum + rightNum);
        if (rightNum > leftNum) {
            leftNum = rightNum = 0;
        }
    }
    leftNum = rightNum = 0;
    for (int i = s.size() - 1; i >= 0; i--) { // 没有反向遍历的range语句。
        if (s[i] == '(') leftNum++;
        else rightNum++;

        if (leftNum == rightNum) res = max(res, leftNum + rightNum);
        if (rightNum < leftNum) {
            leftNum = rightNum = 0;
        }
    }
    return res;
}

// 再次消消乐问题：消消乐是栈，栈一般也可以用数组实现，数组更加灵活，可以取到多个元素去比较，可以一次出栈多个
// 本次的消消乐：一次消掉一个substr。
//
// 1910. 删除一个字符串中所有出现的给定子字符串 https://leetcode.cn/problems/remove-all-occurrences-of-a-substring/
bool isSuffix(const string& s, const string& part) {
    for (int i = s.size() - 1, j = part.size() - 1; i >= 0 && j >= 0; i--, j--) {
        if (s[i] != part[j]) {
            return false;
        }
    }
    return true;
}
string removeOccurrences(string s, string part) {
    string res;
    for (int i = 0; i < s.size(); i++) {
        res.push_back(s[i]);               // 入栈
        if (res.size() >= part.size() && isSuffix(res, part)) {
            res.resize(res.size() - part.size()); // 出栈
        }
    }
    return res;
}