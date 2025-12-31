class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        set<ListNode*> visited;
        ListNode* node_curr = head;

        while (node_curr != nullptr) {
            if (visited.contains(node_curr)) {
                return node_curr;
            }

            visited.insert(node_curr);
            node_curr = node_curr->next;
        }

        return nullptr;
    }
};