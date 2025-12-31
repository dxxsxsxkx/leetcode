// 141: Linked list cycle 1
class Solution {
public:
    bool hasCycle(ListNode *head) {
        
        // Does the list have at least two nodes? 
        if (head == nullptr || head -> next == nullptr) {
            return false;
        }

        // Define two pointers
        ListNode* fast = head -> next -> next; // two at a time
        ListNode* slow = head -> next; // one at a time
        
        // Loop till the two meet
        while (fast != nullptr && fast -> next != nullptr) {
            if (fast == slow) {
                return true;
            }

            // Update
            fast = fast -> next -> next;
            slow = slow -> next;
        }

        return false;
    }
};