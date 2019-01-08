## 首先，我要开始刷面试题了，对每个面试题进行深挖 组织 设计 组织成自己的说辞
#### 结构体和共同体的区别 struct 和 union
在回答这个问题之前，先来看看这两段代码
```cpp
struct Node{
    int i;
    Node *next;
    char ctr;
    const char* name;
};

union{
    int i;
    char c;
    double d;
};

```
#### c和c++的区别
