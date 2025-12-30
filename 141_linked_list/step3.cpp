class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr || head -> next == nullptr) {
            return false;
        }

        set<ListNode*> visited;
        ListNode* curr = head;

        while (curr != nullptr) {
            if (visited.count(curr)) {
                return true;
            }

            visited.insert(curr);
            curr = curr -> next;
        }

        return false;
    }
};