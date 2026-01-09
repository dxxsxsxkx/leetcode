class Solution {
public:
    struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
    ListNode* reverseList(ListNode* head) {
        ListNode* reversed = nullptr; 
        ListNode* current = head; 
        ListNode* next_node = nullptr; 

        while (current) {
            next_node = current->next; 
            current->next = reversed; 
            reversed = current; 
            current = next_node; 
        }

        return reversed; 
    }
};
