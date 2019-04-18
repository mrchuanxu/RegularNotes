#include <iostream>
#include <map>
#include <stack>
using namespace std; 

class Solution {
public:
    bool isValid(string s) {
    // 会用栈去处理
        if(s == "") return true;
        // 先构一个map
        // 然后用map比较
        map<char,char> map_str = {{'(',')'},{'{','}'},{'[',']'}};
        stack<char> sta_str;
        sta_str.push(s[0]);
        int i = 1;
        bool flag = false;
        map<char,char>::iterator map_iter;
        while(i<s.size()){
            if(sta_str.size()>0){
                map_iter = map_str.find(sta_str.top());
                if(map_iter!=map_str.end()){
                    if(map_iter->second==s[i]){
                        flag = true;
                        sta_str.pop();
                    }else{
                    flag = false;
                    sta_str.push(s[i]);
                }
                }else return flag;
            }else {
                flag = false;
                sta_str.push(s[i]);
            }
            i++;
        }
        if(sta_str.size()>0) flag = false;
        return flag;
    }
};