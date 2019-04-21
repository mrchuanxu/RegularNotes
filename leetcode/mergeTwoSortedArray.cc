#include <vector>
using namespace std;


class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // 模仿归并排序 只不过现在这个数组是有序的 造成内存溢出 现在开始尝试直接往nums1插入数据，进行数据搬移
       // 尝试从前往后进行数字的比对，然后进行数据的插入，搬移操作
       // if(m==0&&n==0)return;
        if(m+n<m) return;
        
        int len = m+n; // nums1的总大小
        int i,j;
        if(m>0)i = m-1;
        else i = m;
        if(n>0)j = n-1;
        else j = n;
        if(n==0) return;
        if(m == 0) {
            nums1=nums2;
            return;
        }
        
        while(i>=0&&j>=0){
            if(nums1[i]<=nums2[j]){
                nums1[len-1] = nums2[j];
                len--;
                j--;
            }else{
                nums1[len-1] = nums1[i];
                len--;
                i--;
            }
        }
        while(i>=0){
            nums1[len-1] = nums1[i];
            len--;
            i--;
        }
        while(j>=0){
            nums1[len-1] = nums2[j];
            len--;
            j--;
        }
    }
};