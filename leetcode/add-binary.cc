class Solution {
public:
    string addBinary(string a, string b) {
        string res_str;
        if(a.size()==0&&b.size()==0) return res_str;
        int ia = a.size()-1;
        int ib = b.size()-1;
        int flag = 0;
        stack<string> sta_res;
        while(ia>=0&&ib>=0){
            if(flag){
                int isum = (a.at(ia)-48)+(b.at(ib)-48)+1;
                if(isum==2) {
                    flag = 1;
                    sta_res.push("0");
                }else if(isum == 1){
                    flag = 0;
                    sta_res.push("1");
                }else if(isum==3){
                    flag = 1;
                    sta_res.push("1");
                }else{
                    flag = 0;
                    sta_res.push("0");
                }
            }else{
                int isum = (a.at(ia)-48)+(b.at(ib)-48);
                if(isum>1) {
                    flag = 1;
                    sta_res.push("0");
                }else if(isum == 1){
                    flag = 0;
                    sta_res.push("1");
                }else if(isum==3){
                    flag = 1;
                    sta_res.push("1");
                }else{
                    flag = 0;
                    sta_res.push("0");
                }
            }
            ia--;
            ib--;
        }
        while(ia>=0){
            if(flag){
                int isum = (a.at(ia)-48)+1;
                if(isum>1) {
                    flag = 1;
                    sta_res.push("0");
                }else if(isum == 1){
                    flag = 0;
                    sta_res.push("1");
                }else{
                    flag = 0;
                    sta_res.push("0");
                }
            }else{
                if(a.at(ia)=='1')
                sta_res.push("1");
                else
                    sta_res.push("0");
            }
            ia--;
        }
        while(ib>=0){
            if(flag){
                int isum = (b.at(ib)-48)+1;
                if(isum>1) {
                    flag = 1;
                    sta_res.push("0");
                }else if(isum == 1){
                    flag = 0;
                    sta_res.push("1");
                }else{
                    flag = 0;
                    sta_res.push("0");
                }
            }else{
                if(b.at(ib)=='1')
                sta_res.push("1");
                else
                sta_res.push("0");
            }
            ib--;
        }
        if(flag==1){
            sta_res.push("1");
        }
        while(sta_res.size()){
            res_str+=sta_res.top();
            sta_res.pop();
        }
        return res_str;
    }
};