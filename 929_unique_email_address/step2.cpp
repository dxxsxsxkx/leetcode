#include <set>
#include <string>
#include <vector>

class Solution {
public:
    int numUniqueEmails(std::vector<std::string>& emails) {
        std::set<std::string> unique_emails; 
        
        for (const auto& email : emails) {
            if (!email.contains('@')) {  // requires C++23
              break; 
            }

            size_t idx_at = email.find('@'); 
            std::string local = email.substr(0, idx_at); 
            std::string domain = email.substr(idx_at + 1); 

            std::string local_normalized; 
            for (char ch : local) {
                if (ch == '+') {
                    break; 
                }
                if (ch == '.') {
                    continue; 
                }
                local_normalized += ch; 
            }

            unique_emails.emplace(local_normalized + "@" + domain); 
        }

        return unique_emails.size(); 
    }
};
