#include <iostream>
#include <vector>

using namespace std;

//  建立大顶堆 i>= 2i,i>=2i+1 
void heapBuild(vector<int> &arr){
    int arrnum = arr.size()/2;
    int i=0;
    while(arrnum){
        i = arrnum;
        arrnum--; // 不断往前交换 ⬅️⬅️
        while(true){
            int maxPos = i;
            if(2*i+1<=arr.size()&&arr[2*i]>arr[i]) maxPos = 2*i; // 堆化 寻找合适的最大坐标交换
            if(2*i+1<=arr.size()&&arr[maxPos]<arr[2*i+1]) maxPos = 2*i+1; 
            if(maxPos==i) break; // 没有交换，说明没有节点可交换
            swap(arr[i],arr[maxPos]);
            i = maxPos;// 继续将后面的交换 ➡️➡️
        }
    }
}

// void 删除一个堆顶元素
// 删除一个堆顶元素需要持续堆化
void heapDelete(vector<int> &arr){
    if(arr.size()<=1)
        return;
    arr[1] = arr[arr.size()-1];
    arr.pop_back(); // 删掉最后的元素
    int i = 1;
    while(true){
        int maxPos = i;
        if(2*i+1<arr.size()&&arr[2*i]>arr[i]) maxPos = 2*i;
        if(2*i+1<arr.size()&&arr[maxPos]<arr[2*i+1]) maxPos = 2*i+1;
        if(maxPos==i) break;
        swap(arr[maxPos],arr[i]);
        i = maxPos;
    }
}
// 往堆中插入一个元素
void heapInsert(vector<int> &arr,int val){
    if(arr.size()<=1)
        arr.push_back(val);
        return;
    arr.push_back(val);
    int arri = arr.size()-1;
    while(arri){
        if(arri/2>0&&arr[arri/2]>arr[arri]) swap(arr[arri/2],arr[arri]);
        arri = arri>>1;
    }
}

// 排序 主要是将顶元素交换到后面，然后前面持续堆化
void heapSort(vector<int> &arr){
    if(arr.size()<=1)
        return;
    vector<int> arrSort;
    cout << arr.size() <<endl;
   while(arr.size()>=1){
        swap(arr[arr.size()-1],arr[1]); // 这里的交换 FIXME:
        arrSort.push_back(arr[arr.size()-1]);
        arr.pop_back();
        heapBuild(arr);
    }
    arr = arrSort;
}

int main(){
    vector<int> hArr;
    int inum;
    cout << "enter the numbers you want to heap and press q to quit"<<endl;
    hArr.push_back(0);
    while(cin>>inum){
        hArr.push_back(inum);
    }
    // 堆化
    heapBuild(hArr);
    // for(int i=0;i<hArr.size();i++){
    //     cout << hArr[i] << endl;
    // }
    // heapDelete(hArr);
    // for(int i=0;i<hArr.size();i++){
    //     cout << hArr[i] << endl;
    // }
    // heapInsert(hArr,9);
    // for(int i=0;i<hArr.size();i++){
    //     cout << hArr[i] << endl;
    // }
    heapSort(hArr);
    for(int i=0;i<hArr.size();i++){
        cout << hArr[i] << endl;
    }
    return 0;
}