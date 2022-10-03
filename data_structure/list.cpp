// 链表问题，有好多结论可以记住，这样可以极大地增大解题速度。

// 定位到第n个节点(n从1开始)。注意未考虑节点个数少于n的情况。
ListNode* findNthNode(ListNode* head, int n) {
    for (int i = 0; i < n - 1; i++) {
        head = head->next;
    }
    return head;
}

// 定位到倒数第n个节点（注意，未做n的校验）。代码非常简单直白。非常好记。
// 推导：倒数第n个点，那么fast肯定在nullptr，slow在倒数第n个节点。既然倒数第n个，所以slow和fast之间[slow, fast]共有n个节点，从slow到fast需要走n步。
//
// 使用上，（如下题）给的条件一般是倒数第n个节点，但是我们一般需要获取倒数第n+1个节点。这个时候就可能会越界，此时head需要传递进来&dummy。 
//
// 19. 删除链表的倒数第 N 个结点: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
ListNode* findNthNodeFromEnd(ListNode* head, int n) {
    ListNode* fast = head;
    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }
    ListNode* slow = head;
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

// 反转链表[head, tail)。
// 思路倒是没得说，但是注意使用tail的地方有3点！
ListNode* reverse(ListNode* head, ListNode* tail) {
    if (head == tail || head->next == tail) return head;

    ListNode dummy(0, head);
    while (head->next != tail) {
        ListNode* next = head->next;
        head->next = next->next;
        next->next = dummy.next;
        dummy.next = next;
    }
    return dummy.next;
}

// 链表常用技巧，四指针法
// 四个指针解决区间问题：preHead, currHead, currTail, nextHead
//
// 25. K 个一组翻转链表: https://leetcode.cn/problems/reverse-nodes-in-k-group/
ListNode* reverseKGroup(ListNode* head, int k) {
    if (k < 2) return head;

    ListNode dummy(0, head);

    ListNode* preHead = &dummy;
    ListNode* currHead = preHead->next, *currTail;
    ListNode* nextHead = nullptr;

    while (currHead != nullptr) {
        // 赋值未初始化的变量
        currTail = findNthNode(currHead, k);
        if(currTail == nullptr) {
            break;
        }
        nextHead = currTail->next;

        // 反转逻辑
        reverse(currHead, nextHead);
        preHead->next = currTail;
        currHead->next = nextHead;

        // 恢复现场
        preHead = currHead;
        currHead = nextHead;
    } 
    return dummy.next;
}