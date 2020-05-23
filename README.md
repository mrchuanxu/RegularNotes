# RegularNotes 🔥
### C➕➕
✨✨👀最近在研究golang了，已经转到[go_learning](https://github.com/MrTrans/go_learning)，喜欢基础文章的的小伙伴可以跟我多提issue跟我交流，有空就会更新。<br>
#### 数据结构与算法
记录常用数据结构，包括快速排序，冒泡排序，插入排序，图，树等数据结构以及剑指offer部分题目<br>
##### 线性表结构
* [栈的实现，顺序栈，支持动态扩容(模版实现)](./Algorithm/stack/stackUse.cpp)<br>
* [队列实现，循环队列的实现，动态扩容的支持(模版实现)](./Algorithm/queue/queueUse.cpp)<br>
* [单链表，头插法与尾插法，链表反转，增删查改，检测回文字符，快慢指针获取链表中间节点](./Algorithm/singleLinkOper/singleLinkOper.cpp)<br>
##### 经典排序
* [冒泡排序与插入排序，同样是O(n^2)，我选择插入](./Algorithm/bubble_insertSort/bubbleInsertSort.cpp)<br>
* [归并与快速查询O(nlogn)如何在O(n)找到第k大元素？](./Algorithm/merge_quickSort/mergeQuickSort.cpp)<br>
* [线性排序，计数排序，桶排序，对数据的要求更加严格，寻找最大值K](./Algorithm/lineSort/countSort.cpp)<br>
#### 查找
* [二分查找，快速查找，O(logn)的查找速度，寻找旋转数组最小数字](./Algorithm/binarySearch/binarySearch.cpp)<br>
* [为什么redis底层使用跳表来实现](./Algorithm/SkipList/SkipList.cpp)<br>
* [Word单词拼写检查功能如何实现，如何散列表与链表一同使用](./Algorithm/hashMap/haspMapHead.h)<br>
#### 非线性结构
* [二叉树，构树，二叉查找树？什么样的二叉树适合用数组存储](./Algorithm/binaryTree/binaryTree.cpp)<br>
* [堆，为什么说堆排序没有快速排序快？持续堆化的完全二叉树](./Algorithm/heapSort/heapSort.cpp)<br>
* [堆的应用，如何查找topk的搜索关键词](./Algorithm/swordtooffer/minKnums/minKnums.cpp)<br>
* [图，如何存储微博，微信等社交网络好友关系？散列表与链表的存储结构，邻接表](./Algorithm/graphStorage/graphStorage.cpp)
* [图的广度优先遍历与深度优先遍历，广度优先，存储三个关系，深度优先，压栈关系](./Algorithm/bfsGraph/bfsGraph.cpp)
* [Trie🌲，如何实现搜索引擎的搜索关键词提示功能呢？和散列表以及红黑树比较又有什么优缺点？](./Algorithm/trieTree/trieTree.cpp)
#### 字符串匹配 凹凸
* [BM算法，如何实现文本编辑器中的查找功能](./Algorithm/bmstring/bmstring.cpp)
* [借助BM算法轻松理解KMP算法](./Algorithm/kmpstring/kmp.cpp)
#### 算法思想
* [贪心，如何用贪心算法实现哈夫曼编码，讲究贪心策略，我一开始只要最好的，实例，剪绳子问题](./Algorithm/swordtooffer/dynamic_greedy/dynamic_greedy.cpp)
* [分治，分而治之，分的策略以及合并的策略，求逆序度](./Algorithm/merge_nums/merge_nums.cpp)
* [回溯，蝴蝶效应，回到原点，8皇后的争锋相对](./Algorithm/back_origin/back_origin.cpp)
* [暴力回溯解决杨辉三角最短路径问题，动态规划解决重复问题](./Algorithm/dynamic_program/triangle_pro.cpp)
* [动态规划，存储的是一个状态或者一个价值](./Algorithm/dynamic_program/dynamic_pro.cpp)
##### 动态规划，每日一练
* [硬币只有1，3，5，选择最少硬币](./Algorithm/dynamic_program/coin_problem.cpp)
#### 高级算法篇
* [拓扑排序，通过局部的依赖关系，推导全局有序](./Algorithm/topoSort/topoSort.cpp)
* [广度优先搜索，权值加入，让优先队列以及小顶堆完成地图最短路径](./Algorithm/shorterPath/shorterPath.cpp)
* [BitMap，让思维转换到二进制，0，1判断可去重，布隆过滤器实现多个哈希判断](https://mp.weixin.qq.com/s/xxauNrJY9HlVNvLrL5j2hg)
* [B+树的存在，数据库索引查找，提高查找效率，降低内存空间](./Algorithm/bplustree/bplus_tree.cpp)
* [A*启发式搜索🔍，欧几里得公式与最短路径启发寻路，曼哈顿解决求平方根问题](./Algorithm/astar_dijkstra/astar_dijkstra.cpp)
#### 算法高级篇 并发处理算法
思想:先正确再优化!

#### leetcode刷一刷
* [twoSum提供两种解法，分别是时间换空间与空间换时间](./leetcode/twoSum.cc)
* [addTwoNumbers其实这个有个类比的string写法，有机会要将这个整个写法重新修改，但是确实是用时最少](./leetcode/addTwoNum.cc)
* [reverseInt其实就是分析是否溢出，通过余数分析与整数得到的结果分析](./leetcode/reverseInt.cc)
* [判断回文整数，最简单的做法，求余最快](./leetcode/palindrom.cc)
* [rommantoInt，倒过来就好了](./leetcode/romantoint.cc)
* [longestCommonPrefix计数](./leetcode/longestPrefix.cc)
* [mergeTwoSortList眼界真的要开阔一点，递归的做法之前一直用循环做，傻不傻](./leetcode/mergeTwoSortLists.cc)
* [Subtree of Another Tree 不行就左，不行就右，递归是一个好解法](./leetcode/subtree.cc)
* [symetric树的对称，分两个树](./leetcode/symetricTree.cc)
* [Binary_preorder_traversal前序遍历循坏，仿栈](./leetcode/binary-tree-preorder.cc)
* [Binary_inorder_traversal好吧，受到了前序遍历的干扰，其实就是遍历完左边，然后再看右边](./leetcode/InOrder_binary.cc)
* [ValidParenthess判断有效，map先构造，而后再实现栈匹配](./leetcode/ValidParenthess.cc)
* [RemoveDuplicate去重，快慢指针做，做完就数据搬移](./leetcode/removeDuplicates.cc)
* [MergeTwoSortedArray其实就是归并的设计，只不过最后将申请的空间都浓缩到nums1中，尝试直接在最后赋值，关键就是边界条件](./leetcode/mergeTwoSortedArray.cc)
* [Maxi_SubArray最长最大的数组子串，一个一个加，两个Sum比对](./leetcode/Maxim_SubArray.cc)
* [BinaryTreeTravel两个队列实现遍历](./leetcode/BinaryTree_Travel.js)
* [Binary_zigzag_travel两个栈实现之字形遍历](./leetcode/binary_zigzag_travel.cc)
* [longestSubstring尝试获取i到j的最大长度，用哈希的思维计算](./leetcode/longestSubstring.js)
* [sqrt(x)求平方，牛顿迭代公式，求K值斜率求得result](./leetcode/mysqrt.cc)
* [二分查找从一个有序数组构建一颗平衡二叉树，中序遍历的思想](./leetcode/sortArraytoBst.cc)
* [插入排序的思想，超级简单searchInsertPosition](./leetcode/searchInsertPosition.cc)
* [进行add-binary，只是排除一下情况，然后加个flag](./leetcode/add-binary.cc)
* [很巧妙的后序遍历以及计算两个子树的深度差大于1，这个要多看！](./leetcode/balanced_tree.cc)
#### 剑指offer 📃✅
##### 基础知识
* [大数相加，可以思考一下大数相乘计算](./Algorithm/swordtooffer/bigNumAdd/bigNumAdd.cpp)
* [从外到内打印矩阵，两种解法，对比，佩服剑指](./Algorithm/swordtooffer/matrixPrint/matrixPrint.cpp)
* [数组中，找出其他数都出现两次的数组中只出现一次的数](./Algorithm/bit_problem/bit_problem.cc)
* [解耦，函数指针，让代码可持续重用](./Algorithm/swordtooffer/expandMode/expandMode.cpp)
#### Cpp程序设计知识点集合
重读cpp Primer，并且将代码实现的过程
* [拷贝构造函数。类值与类指针行为](./Cpp_Program/copy_control/copyControl.cpp)<br>
* [读写流](./Cpp_Program/readStream/readStream.cpp)<br>
* [iostream与ostream文件读写流](./Cpp_Program/fileRead/simpleCode.h)<br>
* [关于文件读写](./Cpp_Program/sstream/strstream.cpp)
* [allocator的使用，一块申请到的内存，怎么去使用](./Cpp_Program/StrVec/StrVec.h)
* [new与delete，枚举与智能指针的实现](./Cpp_Program/smartPtr/smartPtrUse.cpp)
* [基本关联容器map与pair使用](./Cpp_Program/assocontainer/assocontainer.cpp)
* [容器，顺序容器使用](./Cpp_Program/container/seqcontainer.cpp)
* [动态内存管理](./Cpp_Program/dynamicmemory)
* [泛型算法结合可调用对象的使用](./Cpp_Program/genericAlogrithm/genericAlogrithm.cpp)
* [面向对象程序设计public继承](./Cpp_Program/oopProgram/ooprogram.h)
* [运算符重载(没写完呐)](./Cpp_Program/operatorRe/operator.h)
* [私有继承，继承实现](./Cpp_Program/privateClass/privateClass.cpp)
* [完美赋值运算符重载](./Cpp_Program/review/review.cpp)
* [我只是抄一下screen的实现](./Cpp_Program/screen/screen.h)
* [封装数据成员private](./Cpp_Program/selectName/account.h)
* [右值引用，参考四行代码带你理解右值引用](./Cpp_Program/rightRef/rightRef.cpp)
* [发现好文const还有续命内存机制-(int *const&p=&a)](./CppNotes/pointer_refer.cc)

#### Cpp面试题精讲㊙️
主要收集各大面试题，并且写出了自己的理解。
* [结构体和共同体的区别struct和union](./cppInterviewTest/cppInterview1.md)
* [static和const分别怎么用，类里面的static和const可以同时修饰成员函数吗？](./cppInterviewTest/cppInterview2.md)
* [指针和引用区别，引用可以用常指针实现吗？](./cppInterviewTest/cppInterview3.md)
* [什么是智能指针？为什么要用智能指针？如何打破循环引用的问题？实现一个智能指针呗！对于资源管理有什么作用？](./cppInterviewTest/cppInterview4.md)
* [什么是可调用对象？了解lambda表达式吗？function又是怎么回事？](./cppInterviewTest/cppInterview5.md)
* [什么是多态，多态有什么用途。(虚函数)](./cppInterviewTest/cppInterview7.md)
* [水文-C调用C++](./cppInterviewTest/cppInterview9.md)
* [C++面试考点陈列](./cppInterviewTest/cppInterview12.md)
* [C++面试题杂谈，字节对齐-vector-list-allocator-红黑树](./cppInterviewTest/cppInterview14.md)
* [C++面试题杂谈，红黑树与B树，声明与定义，malloc匹配与一致性哈希](./cppInterviewTest/cppInterview15.md)
* [C++面试题杂谈，TCP，慢启动，流量控制，301与302，poll与epoll](./cppInterviewTest/cppInterview16.md)
#### Cpp Primer与TCPL部分
对Cpp Primer的学习笔记以及部分实现。以及研读Effective C++55 items
* [关于深拷贝与浅拷贝，知道多少？](./CppNotes/deepCopy_shallowCopy/deep_shallow.cpp)
* [虚析构函数的用法--体验一下继承--构造](./CppNotes/importImpl/importImpl.cpp)
* [相依于声明式，不相依于定义式，继承关系的is-a](./CppNotes/Person/Person.cpp)
* [强制左侧运算对象是一个左值，面向对象编程](./CppNotes/review/oopdesign/oopdesign.cpp)
* [标准库部分](./CppNotes/stlib/stlib.cpp)
* [结构体struct的使用](./CppNotes/structPointer/structPointer.cpp)
* [模版编程](./CppNotes/template/templateImpl.h)
* [C++primer变量与基本类型&字符串、向量和数组](./CppNotes/Cppprimer_var_type_string_vector_arr.md)
* [C++表达式&语句&函数&类](./CppNotes/Cpp_expression_function_sentance_class.md)
* [IO库与顺序容器](./CppNotes/Cpp_io_order_vector.md)
* [Cpp范型算法，关联容器以及动态内存](./CppNotes/Cpp_genericAlogrithm_associative-container_dynamicMemory.md)
* [面向对象程序设计](./CppNotes/Cpp_OOP.md)
* [运算符重载与类型转换](./CppNotes/CppOperatorRe_Conversion_Operator.md)
* [拷贝控制，了解cpp默默为你创建的四个函数](./CppNotes/Cpp_copy_control.md)
* [模版与泛型编程(这篇偷懒，😠，可怕，估计是feed up)](./CppNotes/Cpp_template_program.md)
* [杂项](./CppNotes/review/compoundType.cpp)
### CSS
尝试读了一篇博文叫flexbox，了解css
* [FlexBoxp-完全指南，图片兼容浏览器size](./CSSNotes/flexBoxGuide.md)
### 设计模式与部分实现CPP
设计模式精讲以及理解
* [工厂模式，抽象工厂模式](./DesignPattern/factoryPattern/factoryPattern.cpp)
* [命令模式-将一个请求封装成一个对象，从而让你使用不同的请求把客户端参数化](./DesignPattern/command_Mode/commandMode.cpp)
* [装饰模式-主要靠包装-动态地给一个对象添加一些额外的职责](./DesignPattern/DecoratorMode/decoratorMode.cpp)
* [代理模式-找人帮忙打游戏，打着打着给你送金币](./DesignPattern/proxyMode/proxyMode.cpp)
* [单例模式-我就是我，不一样的烟火，限量版的我](./DesignPattern/Single_Pattern/singleton.cpp)
* [模版方法-我有一套模版，一套有一套](./DesignPattern/templateMethod/templateMethod.cpp)
* [设计模式之禅-遵循六大，可以到处溜达](./DesignPattern/designPatternPrincple.md)
* [创建类型模式-单例、原型、工厂方法、抽象工厂、建造模式](./DesignPattern/CreateMode.md)
* [结构类型模式-适配器模式、桥梁模式、组合模式、装饰模式、门面模式、享元模式和代理模式](./DesignPattern/StructMode.md)
### JavaScript 学习笔记与部分实现
工作的时候用到了js，做了一些笔记，希望以后查询的时候可以用得上
* [红宝书，读一读](./Js_Tutorial/EcmaScript/redBookTravel.md)
* [好文好读，async/await，解决回调](./Js_Tutorial/aysnc_await_solve_call-back.md)
* [Es6_7_8学习指南，只是简单了解一下新特性](./Js_Tutorial/es6_7_8.md)
* [闭包与高阶函数](./Js_Tutorial/闭包与高阶函数.md)
* [面向对象的js，居然！有设计模式](./Js_Tutorial/面向对象的js.md)
### Nodejs 深入浅出笔记
主要参考nodejs深入浅出的书
* [Node简介，特点，模块，异步，学习笔记](./NodeNotes/Nodejs_origin_Module_async.md)
* [理解Buffer，深入理解buffer缓存机制](./NodeNotes/Nodejs_know_Buffer.md)
* [v8内核初识，内存控制](./NodeNotes/Nodejs_Memory_control.md)
* [Node网络编程，引入tcp与http模块](./NodeNotes/Node_web_program.md)
* [玩转进程，node也能新建进程，基于多核CPU](./NodeNotes/Nodejs_process.md)
### Python 工作笔记
学了一天的python，实现了一下excel的简单读取
* [一个python读取excel的简单demo](./PythonNotes/python_read_excel.md)
### TCP/IP协议簇 ⛓️
参考tcp/ip详解与图解tcp/ip以及刘超老师的课程，尝试网络编程实现
* [mac层与链路层以及ip网际层，网络上跑的包都是完整的，不能有上层没下层，可以有下层没上层](./tcp_ip/mac层与链路层，ip网际层.md)
* [TCP与UDP区别详述，以及网络编程部分](./tcp_ip/TCP与UDP.md)
* [HTTP状态码与首部字段解读，应用层的世界，从来都不简单](./tcp_ip/https_http.md)
* [HTTP缓存机制，渣男需要被负责](./tcp_ip/cache_status.md)
* [HTTP2.0我受够了等待](./tcp_ip/http2.md)
* [HTTPS-为了安全🔐，我愿意带上套](./tcp_ip/HTTPS.md)
* [Google-QUIC官宣HTTP/3.0-QUIC协议"城会玩" UDP也是我的主场](./tcp_ip/QUIC-http3.md)
* [DNS->HTTPDNS，网络的负载均衡手段](./tcp_ip/DNS_address.md)
* [CDN，京东建仓策略，就近配送](./tcp_ip/CDN.md)
### unix 环境高级编程 APUE巨著 😱
apue巨著，每天读一个小时，理解并深入每个知识点，对进程与多线程多一点了解。
* [UNIX标准及实现](./unixAdvance/APUE-SYSIO.md)
* [标准IO库](./unixAdvance/APUE-STDIO.md)
* [文件和目录](./unixAdvance/APUE-FILE_INDEX.md)
* [系统文件信息亚数据](./unixAdvance/APUE-SYS_MSG.md)
* [进程环境](./unixAdvance/APUE-PROCESS.md)
* [进程控制fork、wait、exec](./unixAdvance/APUE-PROCESS_CONTROL.md)
* [进程关系(会话，进程组，进程)与守护进程(setsid)](./unixAdvance/APUE-PROCESS_RELATIVE_DEFEND.md)
* [信号，进程与线程异步的思想](./unixAdvance/APUE-SIGNAL.md)
* [线程，就是一个正在运行的函数](./unixAdvance/APUE-THREAD.md)
* [线程控制，根据线程的属性，pthread_kill](./unixAdvance/APUE-THREAD_CONTROL.md)
* [高级IO，非阻塞IO，epoll、select、poll通知](./unixAdvance/APUE-ADVANCEIO.md)
* [进程间通信，管道，socket，XSI(System V)](./unixAdvance/APUE-COMUNICARTION.md)
* [终篇-网络通信IPC，socket，协议决定通信](./unixAdvance/APUE-NETIPC_SOCKET.md)
### 现代操作系统
开始学习操作系统的知识，分为进程与线程，内存管理，文件系统，输入输出，死锁。不会看书，只会不断查博客，然后做知识总结。
* [进程与线程，很抽象](./OS/process_thread.md)
* [信号量，条件变量，互斥锁以及读写锁🔒，保证线程顺序执行的方法](./OS/process_signal_lock.md)
* [进程与线程调度，因环境而已，离不开抢占](./OS/process_thread_use.md)
* [内存管理，分页还是分段，看你的笔记本怎么写](./OS/memory_manage.md)
* [死锁，先发制人还是后发制人？银行家有经验](./OS/dead_lock.md)

### 攻克linux系统编程
* [深入程序布局内部，增强应用控制能力](./unixAdvance/linux_Deep1/elf_header.c)
* [理解进程内存排布，掌握程序动态](./unixAdvance/linux_Deep2/processMem.c)
* [理解线程实现，达成高效率和低复杂度](./unixAdvance/linuxDeep3/thread_create.c)
* [探究进程间通信技术，优化数据传输效率](./unixAdvance/linuxDeep4/process_com.c)
* [解析共享库工作机理，灵活组织大型项目](./unixAdvance/linuxDeep5/sharelib.c)
* [理解文件系统设计思想，站在巨人肩上](./unixAdvance/linuxDeep6/fileSystem.c)
* [掌握信号处理，稳健处理信号中断和异常](./unixAdvance/linuxDeep7/signal_handle.c)
* [理解时钟与定时器，电子世界中的脉动](./unixAdvance/linuxDeep8/timer_set.c)
* [理解系统安全，保护你重要的资产](./unixAdvance/linuxDeep9/sys_sec.c)
* [线程同步，让复杂的工作流协调有序](./unixAdvance/linuxDeep10/thread_com.c)
* [活用内存映射与虚拟内存，让应用更高效](./unixAdvance/linuxDeep11/mmap.c)
### 🐂牛客网刷题 错题集
* [基础语言题C/Cpp](./nowcoder_wrong/nowcoder_1.md)
* [基础语言题C/Cpp](./nowcoder_wrong/nowcoder_2.md)
* [基础语言题C/Cpp](./nowcoder_wrong/nowcoder_3.md)
* [基础语言题C/Cpp](./nowcoder_wrong/nowcoder_4.md)
* [基础语言题C/Cpp](./nowcoder_wrong/nowcoder_5.md)
* [Linux基础](./nowcoder_wrong/nowcoder_6.md)
* [Linux基础](./nowcoder_wrong/nowcoder_7.md)
