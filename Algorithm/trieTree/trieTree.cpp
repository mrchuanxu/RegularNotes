/***
 * trie🌲，字典树
 * 专门处理字符串匹配的数据结构
 * 用来解决一组字符串集合中快速查找某个字符串的问题
 * 
 * 但是，要求前缀重合率较高
 * 
 * 空间换时间，内存消耗较大因为结构是数组申请存储空间
 * 因而查找的时间复杂度O(k),构建的空间复杂度为O(n)
 * 
 * 存储结构
 * 可以尝试缩点优化，将子节点压缩在一起
 * 
 * 对于动态集合数据的查找，更倾向于散列表或红黑树
 * 
 * ***/

#include <iostream>
#include <vector>
#include <string>
#include <memory.h>
#include <typeinfo>
using namespace std;

struct trieNode{
    char ctr;
    trieNode *children[26];
    trieNode(const char &cr){
        ctr = cr;
    }
    bool isEndingChar = false;
    ~trieNode(){
        cout << "haha" <<endl;
    }
};
class TrieTree{
    public:
        TrieTree() = default;
        trieNode* getNewTrieNode(const char ctr){
            triNew = new trieNode(ctr);
            vectri_ptr.push_back(triNew);
            return triNew;
        }
        void insertTrie(const char *str);
        bool searchTrie(char *str);
        ~TrieTree(){
            for(auto itptr:vectri_ptr){
                delete itptr;
            }
            cout << "delete" <<endl;
        }
    private:
        trieNode *triNew;
        vector<trieNode*> vectri_ptr; // 避免动态内存泄露
};
/***
 * 使用散列表存储
 * 下标表示存储的值
 * ***/
static trieNode trRoot('/');// 全局变量区

void TrieTree::insertTrie(const char *str){
    if(str == nullptr) return;
    int len = strlen(str);
    trieNode *p = &trRoot;
    //trieNode *p = &trRoot;
    for(int i = 0;i<len;++i){
        int index = str[i] - 'a';
        // cout << str[i] << endl;
        if(p->children[index] == nullptr){
            trieNode *triNew = getNewTrieNode(str[i]);
            p->children[index] = triNew; // 散列表下标指向
        }
        p = p->children[index];
    }
    p->isEndingChar = true; // 遍历到尾部的节点
}

/***
 * 查找trie🌲
 * 用于匹配字符
 * 查到最后的节点
 * ***/
bool TrieTree::searchTrie(char *str){
    bool found = false;
    if(str == nullptr) return found;
    int len = strlen(str);
    trieNode *p = &trRoot;
    for(int i = 0;i<len;++i){
        // 查字符
        int index = str[i] - 'a';
        if(p->children[index] == nullptr) return found;
        p = p->children[index];
    }
    if(p->isEndingChar == true){
        found = true; // 找到了，就true
        return found;
    }else{ // 否则仅仅是匹配了前缀，这时候就构造这个trie树
        insertTrie(str);
    }
    return found;
}

int main(){
    vector<const char*> vec{"hello","hi","how","so","see"};
    TrieTree *triTree = new TrieTree();
    for(auto iter:vec){
       triTree->insertTrie(iter);
    }
    char ctr[30];
    // char *ctr = str;
    
    while(cin >> ctr){ // 对于输入的问题要深究一下
        if(triTree->searchTrie(ctr)){
            cout << "found"<<endl;
        }else{
            cout << "no" << endl;
        }
    }
    delete triTree;
    return 0;
}