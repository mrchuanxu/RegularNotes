# 一个python读取excel的简单demo
根据业务需求，写了一个python读取excel数据，并传送到ibm的nosql-cloudant数据库，写成文件的形式上传<br>
首先打开excel文件<br>
定义一个readxlsx.py文件<br>
引入xdrlib，sys库，还有xlrd库，还有转换为json的库
```python
import xdrlib, sys
import xlrd
import json

#open excel
def open_excel(file = 'filepath'):
    try:
        data = xlrd.open_workbook(file)
        return data
    except Exception,e:
        print str(e)

#通过读取excel文件的列数开始读取excel文件，按最上面的index作为基准
def excel_table_byindex(file='filepath',colnameindex = 0,by_index = 0): #change the file path
    data = open_excel(file)
    table = data.sheets()[by_index]
    nrows = table.nrows  #rows number
    ncols = table.ncols  #col number
    colnames = table.row_values(colnameindex) # a data
    list = []
    for rownum in range(1,nrows):
        row = table.row_values(rownum)
        if row:
            app ={}
            for i in range(len(colnames)):
                app[colnames[i]] = row[i]
            list.append(app)
    return list #最后读成连标，方便存入cloudant
```

然后定义一个读取excel文件到cloudant的py文件，命名为readtocloudant.py<br>
先下载cloudant的库，用pip可以下载，命令为pip install cloudant=2.3.1<br>
这里的版本是可以根据cloudant的更新更换版本号，20180831今天最新是2.3.1<br>
然后开始引入cloudant的库<br>
```python
from cloudant.client import Cloudant
from cloudant.error import CloudantException
from cloudant.result import Result,ResultByKey
import readxlsx

client = Cloudant("username","password",url="url");
client.connect()

databaseName = "youDBName"

def main():
    mydatabase = client[databaseName]
    docnumber = 0
    tables = readxlsx.excel_table_byindex()
    for row in tables:
        jsonrow = json.dumps(row)
        json_to_object = json.loads(jsonrow)
        convertDate = xlrd.xldate.xldate_as_datetime(json_to_object['Date'],0)
        json_to_object['Date'] = convertDate.strftime("%Y/%m/%d %H:%M:%S") #Date 是我强行转换的时间，这里要注意，读出出来的时间是通过转换的时间，要呈现原来excel的时间，必须转换！可按业务需求查看得到的数据是否需要转换！
        # json_to_object = json.dumps(json_to_object)
        # print json_to_object
        newDocument = mydatabase.create_document(json_to_object)
 
        if newDocument.exists():
            docnumber=docnumber+1
            print docnumber


    client.disconnect()
if __name__ == "__main__":
    main()
```
**参考文档**<br>
[cloudant-document](https://console.bluemix.net/docs/services/Cloudant/getting-started.html#getting-started-with-cloudant)

