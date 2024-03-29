﻿#pragma once
/*
问题描述：
输入：一个最多含有 n 个不重复的正整数（也就是说可能含有少于 n 个不重复正整数）的
文件，其中每个数都小于等于 n，且 n=10^7。
输出：得到按从小到大升序排列的包含所有输入的整数的列表。
条件：最多有大约 1MB 的内存空间可用，但磁盘空间足够。且要求运行时间在 5 分钟以下，
10 秒为最佳结果。

分析：下面咱们来一步一步的解决这个问题，
1、归并排序。你可能会想到把磁盘文件进行归并排序，但题目要求你只有 1MB 的内存
空间可用，所以，归并排序这个方法不行。
2、位图方案。熟悉位图的朋友可能会想到用位图来表示这个文件集合。例如正如编程珠
玑一书上所述，用一个 20 位长的字符串来表示一个所有元素都小于 20 的简单的非负整数
集合，边框用如下字符串来表示集合{1,2,3,5,8,13}：

248

0 1 1 1 0 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0
上述集合中各数对应的位置则置 1，没有对应的数的位置则置 0。
参考编程珠玑一书上的位图方案，针对我们的 10^7 个数据量的磁盘文件排序问题， 我们
可以这么考虑，由于每个 7 位十进制整数表示一个小于 1000 万的整数。我们可以使用一个
具有 1000 万个位的字符串来表示这个文件，其中，当且仅当整数 i 在文件中存在时，第 i
位为 1。采取这个位图的方案是因为我们面对的这个问题的特殊性：1、输入数据限制在相
对较小的范围内，2、数据没有重复，3、其中的每条记录都是单一的整数，没有任何其它
与之关联的数据。
所以，此问题用位图的方案分为以下三步进行解决：

第一步，将所有的位都置为 0，从而将集合初始化为空。

第二步，通过读入文件中的每个整数来建立集合，将每个对应的位都置为 1。

第三步，检验每一位，如果该位为 1，就输出对应的整数。
经过以上三步后， 产生有序的输出文件。 令n为位图向量中的位数 （本例中为1000 0000） ，
程序可以用伪代码表示如下：
//磁盘文件排序位图方案的伪代码
//第一步，将所有的位都初始化为 0
for i ={0,....n}
bit[i]=0;
//第二步，通过读入文件中的每个整数来建立集合，将每个对应的位都置为 1。
for each i in the input file
bit[i]=1;
//第三步，检验每一位，如果该位为 1，就输出对应的整数。
for i={0...n}
if bit[i]==1
write i on the output file
*/

class FileDataSort
{
public:
	//处理排序方法
	void DealFileDataSort();
};

