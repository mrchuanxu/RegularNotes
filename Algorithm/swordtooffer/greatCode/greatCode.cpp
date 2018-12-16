/***
 * 考虑异常输入情况
 * 考虑边界调节
 * 考虑错误抛出如何获知
 * 定义全局变量，获知错误情况
 * ***/
// 实现base的次方
double PowerWithNumber(double base,int exponent){
    if(exponent == 1)
        return base;
    if(exponent == 0)
        return 1;   
    double result = PowerWithNumber(base,exponent>>1);
    result *= result; // 求出两个数的平方，例如2的平方4，4再到8，8再到16如此类推咯
    if(exponent & 0x1 == 1) // 位与运算判断一个exponent是奇数还是偶数
        result *= base; // 奇数则多乘一次base！！！
    return result;
}

/***
 * 打印从1到n的数字，打印到n位数
 * 考虑大数问题
 * 引入字符串
 * 进1考虑与打印考虑
 * ***/
