#include <stack>

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
        std::stack<ListNode*> nodes; 
        ListNode* current = head; 

        while (current) {
            nodes.push(current); 
            current = current->next; 
        }

        ListNode dummy; 
        ListNode* reversed = &dummy; 
        while (!nodes.empty()) {
            reversed->next = nodes.top(); 
            nodes.pop(); 
            reversed = reversed->next; 
        }

        reversed->next = nullptr; 

        return dummy.next; 
    }
};
