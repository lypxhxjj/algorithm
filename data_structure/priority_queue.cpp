// 问题1：合并k个有序数组或者链表
// pq的使用点：
// 1. 如何自定义比较函数。
//
// 23. 合并K个升序链表：https://leetcode.cn/problems/merge-k-sorted-lists/
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.size() == 0) {
        return nullptr;
    }

    auto cmp = [](ListNode* l1, ListNode* l2) {
        return l1->val > l2->val;
    };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

    for (ListNode* l : lists) {
        if (l) pq.push(l);
    }

    ListNode dummy;
    ListNode* curr = &dummy;
    while (!pq.empty()) {
        curr->next = pq.top();
        pq.pop();
        if (curr->next->next) {
            pq.push(curr->next->next);
        }
        curr = curr->next;
    }
    curr->next = nullptr;
    return dummy.next; 
}