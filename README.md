# ExcelCODE
工作中EXCEL各种功能vba代码实现

**求和居中 
TestSumRange1()
'假如输入的是A1：A100（值是1，2，3，1，2，1,1）获取B1：B100的值，求和居中（C1:C3，C4:C5,C1:C3,C6）解决序列求和问题

**经纬度  
InsertFiveRowsAfterSpecificRow()
'对sheet2中F1开始的F列，根据单元格的值插入减一行
InsertRowsBasedOnDifference()
'处理Sheet3中E1开始的E列序数（1234679）序数断开的情况差几个插入多少行

**readCSV.cpp
对房屋面积进行批量的计算，
读取csv格式为：id	name	area	struct	floor1	floor2	floors 七列
其中读取文件名字为“房屋3.csv”，可更改代码中的文件名，其中floor1，floor2为该结构的起始结束层数，floors为最高层数
表格每一行为房屋块，多行共同构建一个房屋，运行输出一个csv

**housetoxy.py
将cad房屋数据按栋号批量导出经纬度，其中封装了两个方法，一个是已经标号了栋号(名字-数字)的，
其二是栋号是标了1,2,3。当然dwg中的图层名按一定要求命名，方法为特定工作要求环境下，无多参考性。

**经纬度未封装.py
为housetoxy.py没分装好的版本，可以参考

**批量块面积表.py
将cad的dwg房屋数据直接得出一个excel表，其中未封装。该表就是房屋块
两次空间连接房屋属性，带有房屋栋号和块面积的表。经过后续处理可以变为
readCSV.cpp读入的csv数据。当然读入数据有一定的规范。


