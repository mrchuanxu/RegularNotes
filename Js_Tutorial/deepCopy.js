// 判断是否复杂类型，需要继续深入递归
let isComplex = data =>{
    let str = Object.prototype.toString.call(data);
    let dict = {
        '[object Array]':true,
        '[object Object]':true
    };
    if(dict[str]){
        return true;
    }else{
        return false;
    }
 }
 deepCopy = function(target,source){
    //let stack = [];// 使用一个数组作为调用栈，系统的调用栈，避免递归栈限制
    // 使用一个WeakMap存储已经拷贝过的对象
    let currentMap = new Map();
    for(let attr in source){
        if(isComplex(source[attr])){
            let hasAlready = currentMap.has(source[attr]); // 判断之前是否已经拷贝过一次 
            if(hasAlready){
                target[attr] = source[attr]; // 若已经拷贝过，则将原来拷贝的一份取出来(也包括嵌套的问题，因为不再取去拷贝了)  
            }else{  
                let result = deepCopy(source[attr]); 
                currentMap.set(result,result);
                target[attr] = result; 
            }
        }else{
            target[attr] = source[attr];
        }
    }
    return target;
}



let duptest = {key:999}
let source = {
    key1:123,
    key2:{
        key22:456
    },
    key3:[567,798,{key33:890}],
    dup1:duptest,
    dup2:duptest,
    fun:function(){
        console.log('asdad')
    }
}

let result = deepCopy({},source);