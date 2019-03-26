 #include <vector>
 #include <string>
 using namespace std;
 
 string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==0) return "";
        if(strs.size()==1) return strs[0];
        int ksum = strs[0].size();
        // 可以持续降维度 以一个为基准 遍历所有元素
        for(int i = 1;i<strs.size();i++){ // 从第二个开始比较
           int k = 0;
           while(k<strs[i].size()){
               if(strs[0][k] == strs[i][k])  k++;// k一定小于str[0].size()
               else break;
           }
            while(k<ksum){
                ksum--;
            }
            if(k == 0) return "";
        }
        if(ksum == 0) return strs[0];
        string s = strs[0].substr(0,ksum);
        return s;
    }