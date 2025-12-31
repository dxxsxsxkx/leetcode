class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* node_curr = head;

        while (node_curr != nullptr && node_curr->next != nullptr) {
            if (node_curr->val == node_curr->next->val) {
                node_curr->next = node_curr->next->next;
            }
            
            node_curr = node_curr->next;
        }

        return head;
    }
};