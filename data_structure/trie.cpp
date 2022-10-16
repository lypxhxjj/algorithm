/*
    Trie树用于快速字符串搜索。从成员函数角度来看，有两个作用：
    1. 查找字符串：一般通过hash解决。
    2. 前缀搜索。

    所以功能主要用于前缀搜索。但是Trie是一个多叉树，势必会有如下问题：
    1. 字符集太大的话，叉数会很大，比如unicode字符集。
    2. 字符串长度很大的话，深度会很深。

    所以一般Trie用的不是很多，应该就是小数据量的前缀匹配，比如IP地址段匹配IP等。更大数据量的问题一般通过ES的倒排索引解决。
*/

// 最基础版本的trie树实现很优雅
// 1. insert函数中：(1) 不需要考虑word.size() == 0; (2) curr一直是有效的；
// 2. search函数和insert函数区别只有if和return两行代码；
// 3. startsWith和search函数区别只有最后return一行代码。
// 4. 如果没有指定字符集，可以将childs的类型换成unordered_map。（https://leetcode.cn/submissions/detail/370533259/）
//
// 208. 实现 Trie (前缀树) https://leetcode.cn/problems/implement-trie-prefix-tree/
class Trie {
    vector<Trie*> childs;
    bool isLeaf;
public:
    Trie() {
        childs.resize(26);
        isLeaf = false;
    }
    
    void insert(string word) {
        Trie* curr = this;
        for (int i = 0; i < word.size(); i++) {
            int idx = word[i] - 'a';
            if (!curr->childs[idx]) curr->childs[idx] = new Trie();
            curr = curr->childs[idx];
        }
        curr->isLeaf = true;
    }
    
    bool search(string word) {
        Trie* curr = this;
        for (int i = 0; i < word.size(); i++) {
            int idx = word[i] - 'a';
            if (!curr->childs[idx]) return false;
            curr = curr->childs[idx];
        }
        return curr->isLeaf;
    }
    
    bool startsWith(string prefix) {
        Trie* curr = this;
        for (int i = 0; i < prefix.size(); i++) {
            int idx = prefix[i] - 'a';
            if (!curr->childs[idx]) return false;
            curr = curr->childs[idx];
        }
        return true;
    }
};

// Trie树还可以实现较为复杂的搜索功能：按.模糊dfs搜索
//
// 第一行代码比较不好理解。得先理解下Trie树的一个小的方面。
// 1. 正常树的节点分成两个部分：data值，childs数组。前缀树额外包含了isLeaf字段；
// 2. 上述使用vector/unordered_map的实现中，data去哪了？data保存在了父节点中；对于vector，data是父节点中vector的索引值；对于unordered_map，data是父节点的key值。
// 3. Trie树的叶子节点是啥样的？TrieNode结构体中，childs数组都是nullptr && isLeaf = true;
// 4. 根节点是啥样子的？根据data的定位，根节点保存了所有字符串的第一个字符内容，并指向那个字符对应的node。
//
// dfs搜索，每层搜索一个字符。
//
// 211. 添加与搜索单词 - 数据结构设计 https://leetcode.cn/problems/design-add-and-search-words-data-structure/
bool find(const string& word, int i) {
    if (word.size() == i) return isLeaf == true;

    if (word[i] != '.') {
        int idx = word[i] - 'a';
        return this->nodes[idx] ? this->nodes[idx]->find(word, i + 1) : false;
    }
    for (int j = 0; j < nodes.size(); j++) {
        if (nodes[j] && nodes[j]->find(word, i + 1)) {
            return true;
        }
    }
    return false;
}