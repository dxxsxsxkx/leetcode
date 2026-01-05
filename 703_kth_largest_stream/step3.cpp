class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) :
    val_threshold_(k), counter_(), count_(0)
    {
        for (int num : nums) {
            add(num);
        }
    }
    
    int add(int val) {
        counter_[val]++; 
        count_++;

        if (count_ > val_threshold_) {
            auto it = counter_.begin();
            it->second--;
            count_--;
            if (it->second == 0) {
                counter_.erase(it->first);
            }
        }

        return counter_.begin()->first;
    }
private: 
    int val_threshold_; 
    map<int, int> counter_; // value - count
    int count_;
};
