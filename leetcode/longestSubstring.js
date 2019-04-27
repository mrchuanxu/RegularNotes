/**
 * @param {string} s
 * @return {number}
 */
var lengthOfLongestSubstring = function(s) {
    let numLen = s.length;
    let arrIndex = new Array(128);
    let ans = 0;
    //  尝试获取i到j的最大长度
    // 将数据放进桶内计算
    for(let i=0,j=0;j<numLen;j++){
        if(arrIndex[s.charCodeAt(j)]==undefined){
            arrIndex[s.charCodeAt(j)] = 0;
        }
        i = Math.max(arrIndex[s.charCodeAt(j)],i);
        ans = Math.max(ans,j-i+1);
        arrIndex[s.charCodeAt(j)] = j+1;
    }
    return ans;
};