// 链表问题，有好多结论可以记住，这样可以极大地增大解题速度。

// 定位到第n个节点(n从1开始)。注意未考虑节点个数少于n的情况。
ListNode* findNthNode(ListNode* head, int n) {
    for (int i = 1; i < n; i++) { // 既然从1开始，那么i也从1开始
        head = head->next;
    }
    return head;
}

// 定位到倒数第n个节点（注意，未做n的校验）。代码非常简单直白。非常好记。
// 推导：倒数第n个点，那么fast肯定在nullptr，slow在倒数第n个节点。既然倒数第n个，所以slow和fast之间[slow, fast]共有n+1个节点（包含nullptr），
// [slow, nullptr]有n + 1个节点，所以fast也要先走到第n+1个节点位置（即可用如上结论）。
//
// 使用上，（如下题）给的条件一般是倒数第n个节点，但是我们一般需要获取倒数第n+1个节点。这个时候就可能会越界，此时head需要传递进来&dummy。 
//
// 19. 删除链表的倒数第 N 个结点: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
ListNode* findNthNodeFromEnd(ListNode* head, int n) {
    ListNode* fast = head;
    for (int i = 1; i < n+1; i++) {
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

// 两指针判断相交链表
//
// 重点在于两点：
// 1. 两个指针，每次循环必走一步，不要走两步；（何时走两步？遇到空重定位到最开始的位置，这也算一步的）
// 2. nullptr也算其中一步。所以可以放心走，需要走下一步的时候再判断空即可。
//
// 160. 相交链表 https://leetcode.cn/problems/intersection-of-two-linked-lists/
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (!headA || !headB) return nullptr;
    ListNode* l1=  headA, *l2 = headB;
    while (l1 != l2) {
        if (!l1) l1 = headB;
        else l1 = l1->next;

        if (!l2) l2 = headA;
        else l2 = l2->next;
    }
    return l1;
}

// 链表题的循环最考验代码能力：循环过程中的状态需要被很好的赋值。
//
// 检查时，统计下有哪些状态，挨个检查是否被很好的赋值。
// 
// 2. 两数相加 https://leetcode.cn/problems/add-two-numbers/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (!l1 && !l2) return nullptr;

    ListNode dummy;
    ListNode* curr = &dummy;
    int flag = 0;
    while (l1 || l2 || flag) {
        int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + flag;
        curr->next = new ListNode(sum % 10);

        flag = sum / 10;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next; // 都有哪些变量，都需要被很好的维护。
        curr = curr->next;
    }
    return dummy.next;
}