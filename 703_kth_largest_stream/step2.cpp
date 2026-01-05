class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : K(k), top_k_vals_() {
        for (int x : nums) {
            add(x);
        }
    }
    
    int add(int val) {
        top_k_vals.push(val);
        if (top_k_vals.size() > K) {
            top_k_vals.pop();
        }
        return top_k_vals.top();
    }
private: 
    int K_; 
    priority_queue<int, vector<int>, greater<int>> top_k_vals_;
};
