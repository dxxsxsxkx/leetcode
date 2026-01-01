class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(-1000);
        dummy.next = head;

        ListNode* node_current = &dummy;
        ListNode* runner = head;

        while (runner != nullptr && runner->next != nullptr){
            if (runner->val == runner->next->val) {
                // flag
                int val_duplicate = runner->val;
                
                // ensures runner is past the duplicated block
                while (runner->val == val_duplicate) {
                    ListNode* node_duplicate = runner;
                    runner = runner->next;
                    delete node_duplicate;
                }

                node_current->next = runner;
                
            } else {
                node_current = runner;
                runner = runner->next;
            }
        }

        return dummy.next;
    }
};