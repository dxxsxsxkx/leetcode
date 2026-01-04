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
        ListNode* original_head = head;
        ListNode* new_head = &dummy;

        while (original_head) {
            st.push(original_head);
            original_head = original_head->next;
        }

        while (!st.empty()) {
            new_head->next = st.top();
            st.pop();
            new_head = new_head->next;
        }

        new_head->next = nullptr;
        return dummy.next;
    }
};
