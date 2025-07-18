# Idea 

all words[i] length are same, so, we can do sliding windows, every time the windows size increase words[i].size(), and then we check if the s.substr(right, words[i].size()) is in the words or not, if not, we know it is no longer a valid windwos, we break it, and advanced the left to the right + step, continue to logic, the only different is we need to start at different pos, to try out all the possibilities, but we only need to start at 0 - words[i].size(), because after that it got repeated.

when the right - left == words[i].szie() * words.size(), we output the res.



# Solution 

```C++
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int step = words[0].size();
        int ans_len = step * words.size();
        int n = s.size();
        unordered_map<string, int> fre_map;
        vector<int> res;
        for(auto word : words){
            fre_map[word]++;
        }
        for(int anchor = 0; anchor < step; anchor++){
            int lft = anchor;
            unordered_map<string, int> count_map;
            int count = 0;
            for(int rght = anchor; rght + step <= n; rght+=step){
                string extract_word = s.substr(rght, step);
                // two cases we need to shrink down the windows
                // one the windows is in max size, 
                // second the windows contains more word fre than provided
                if(fre_map.count(extract_word)){
                    count_map[extract_word]++;
                    count++;
                    while(count_map[extract_word] > fre_map[extract_word]){
                        count_map[s.substr(lft, step)]--;
                        lft += step;
                        count--;
                    }
                    if(count == words.size()){
                        res.push_back(lft);
                        count_map[s.substr(lft, step)]--;
                        lft += step;
                        
                        count--;
                    }
                }else{
                    count_map.clear();
                    lft = rght + step;
                    count = 0;
                }
            }
        } 
        return res;
    }
};
```