#include <set>
#include <string>
#include <vector>

class Solution {
public:
    int numUniqueEmails(std::vector<std::string>& emails) {
        std::set<std::string> unique_emails; 
        for (const auto& email : emails) {
            int idx_at = email.find('@'); 
            std::string local = email.substr(0, idx_at); 
            std::string domain = email.substr(idx_at + 1); 
            
            std::string normalized_local; 
            for (char ch : local) {
                if (ch == '+') {
                    break; 
                }
                if (ch == '.') {
                    continue; 
                }
                normalized_local += ch; 
            }
            unique_emails.emplace(normalized_local + "@" + domain); 
        }
        return unique_emails.size(); 
    }
};
