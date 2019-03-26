#include <map>
#include <string>

using namespace std;
// 构造map
    map<char,int> map_res(){
        map<char,int> map_ret; // 这是用于存储I V X之类的罗马字符
        map_ret['I'] = 1;
        map_ret['V'] = 5;
        map_ret['X'] = 10;
        map_ret['L'] = 50;
        map_ret['C'] = 100;
        map_ret['D'] = 500;
        map_ret['M'] = 1000;
        // 规则就是 放在左边就是减 超过四个1就将I放在X、V左边
        // 超过三个X 就将X放在L、C的左边
        // 超过三个C 就将C放在D、M的左边
        // 所以做的工作就是，判断下一个与前一个的关系 申请的空间是需要的
        return map_ret;
    }
    int romanToInt(string s) {
        if(s.size() == 0) return 0;
        map<char,int> map_ret = map_res();
        // IV IX IM IC ID IL IM
        // XL XC XD XM
        // LC LD LM
        // CD CM
        // DM
        int inum = 0;
        // 倒过来就好了
        int slen = s.size()-1;
        int flag = 0;
        while(slen-1>=0){
            if(map_ret[s[slen]]>map_ret[s[slen-1]]){ // 边界条件
                flag = 1;
                }
            if(flag){
                inum =inum+(map_ret[s[slen]] - map_ret[s[slen-1]]);
                slen = slen-2;
                flag = 0;
            }else{
                inum += map_ret[s[slen--]];
            }
        }
        if(flag) inum -= map_ret[s[slen]];
        else inum += map_ret[s[slen]];
        return inum;
        
    }