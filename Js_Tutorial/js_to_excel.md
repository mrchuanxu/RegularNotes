# javacript 将json导出为excel
这是一个简单的将json数据导出为excel的简单demo<br>
这是一个简单的在vue上实现的简单demo<br>
首先引用xlsx，这是一个模块，一个npm包，直接用npm下载即可npm install xlsx<br>
### talk is cheap, show me the code
```js
import XLSX from 'xlsx';
handlejsontosheet(jsonData,fileName){
    let wsName = 'wsName';
    let wb = XLSX.utils.book_new();
    let ws = XLSX.utils.json_to_sheet(jsonData);
    XLSX.utils.book_append_sheet(wb,ws,wsName);
    XLSX.writeFile(wb,fileName);
},
```
### 参考文档
https://github.com/SheetJS/js-xlsx<br>

### 结束语
就这样结束了？对啊，你仲想点，结束了，以后直接调用就得了。