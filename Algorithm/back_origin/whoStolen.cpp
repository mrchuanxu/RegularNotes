#include <iostream>
#include <vector>

using namespace std;

// 一个四种结果
bool stol_person(vector<int> &liar_true){
    vector<int> stolen{0,0,0,0};
    // 每次只修改一个状态
    if(liar_true[0] == 1){
        stolen[1] = 0;
        stolen[3] = 1;
    }
    if(liar_true[0] == 0){
        stolen[1] = 1;
        stolen[3] = 0;
    }

    if(liar_true[1] == 0){
        stolen[1] = 1;
        stolen[2] = 0;
    }
    if(liar_true[1] == 1){
        if(stolen[1]!=0) return false; // 有矛盾，所以排列错误
        stolen[1] = 0;
        stolen[2] = 1;
    }

    if(liar_true[2] == 0){
        if(stolen[1]!=0) return false; // 有矛盾，所以排列错误
        stolen[0] = 1;
        stolen[1] = 0;
    }
    if(liar_true[2] == 1){
        stolen[0] = 0;
        stolen[1] = 1;
    }

    if(liar_true[3] == 1){
        if(stolen[3]!=0) return false; // 有矛盾，所以排列错误
        stolen[3] = 0;
    }
    if(liar_true[3] == 0){
        stolen[3] = 1;
    }
    int result = 0;
    for(auto str:stolen){
        result +=str;
    }
    if(result == 1){
        if(stolen[0] == 1) cout << "甲是偷盗者";
        if(stolen[1] == 1) cout << "乙是偷盗者";
        if(stolen[2] == 1) cout << "丙是偷盗者";
        if(stolen[3] == 1) cout << "丁是偷盗者";
        return true; // 这个排列可以推断一个人是偷盗者
    }else return false; // 这个排列不可以推断偷盗者
}

// 找到排列是对的
bool isFound = false;
void who_stolen(vector<int> &vec,int start){ // 排列的数作为参数
    if(start == vec.size()){
        if(stol_person(vec)){ // 找到偷盗者
            isFound = true;
        }else{
            isFound = false;
        }
        if(isFound){
            if(vec[0] == 1)
                cout << "甲真";
            if(vec[1] == 1)
                cout << "乙真";
            if(vec[2] == 1)
                cout << "丙真";
            if(vec[3] == 1)
                cout << "丁真";
            cout << endl;
        }
    }
    for(int i = start;i<vec.size();++i){
        swap(vec[start],vec[i]); // 进行全排列
        who_stolen(vec,start+1);
        swap(vec[start],vec[i]);
    }
}

void tell_true(){
    // 一个人说谎，两个人说谎，三个人说谎，四个人说谎
    vector<int> liar{0,0,0,0};
    for(int i = 0;i<liar.size();++i){
        if(i == 3) break; // 全说真话是不可能的！剪掉不可能的部分
        liar[i] = 1;
        who_stolen(liar,0); // 排列都是全排列
    }
}

int main(){
    tell_true();
    return 0;
}