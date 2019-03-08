/***
 * 遇到一个很特别的算法题
 * 求一组数组中，其他所有都都出现两次，就一个数出现一次，找出这个数
 * 异或，两个相同的数异或为0
 * 最后一个不同的数可以
 * 求出来***/
#include <iostream>
#include <vector>

namespace bit_problem{
class Bit_Problem{
        public:
            Bit_Problem(std::vector<int>& vec_):vec(vec_){
                bit_calc(vec);
            }
        private:
            std::vector<int> vec;
            void bit_calc(std::vector<int> &vec){
                int res = 0;
                for(auto num:vec){
                    res^=num;
                }
                std::cout<<"alone num"<<res<<std::endl;
            }
    };
}