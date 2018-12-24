#include "haspMapHead.h"
#include <iostream>

int main(){
    HashMapLru<int> hasLru;
    for(int i = 0;i<40;i++){
        if(hasLru.hash_value_addto_key(i)){
            cout << "input" << i << endl;
        }
    }
    if(hasLru.hash_value_find(5)){
            cout << "find" << endl;
    }
    if(hasLru.hash_value_delete(20)){
        if(hasLru.hash_value_find(5))
            cout << "find" << endl;
    }
    return 0;
}
