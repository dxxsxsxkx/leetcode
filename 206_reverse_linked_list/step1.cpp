/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        stack<ListNode*> st;
        ListNode dummy(0);
        ListNode* node = head;
        ListNode* reversed_list = &dummy;

        while (node) {
            st.push(node);
            node = node->next;
        }

        while (!st.empty()) {
            reversed_list->next = st.top();
            st.pop();
            reversed_list = reversed_list->next;
        }

        reversed_list->next = nullptr;
        return dummy.next;
    }
};
