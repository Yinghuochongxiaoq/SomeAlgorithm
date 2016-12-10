
#pragma once
/*
什么是最长公共子序列呢?好比一个数列 S，如果分别是两个或多个已知数列的子序列，
且是所有符合此条件序列中最长的，则 S 称为已知序列的最长公共子序列。
举个例子，如：有两条随机序列，如 1 3 4 5 5 ，and 2 4 5 5 7 6，则它们的最长公共子
序列便是：4 5 5。

注意最长公共子串（Longest CommonSubstring）和最长公共子序列（LongestCommon
Subsequence, LCS）的区别：子串（Substring）是串的一个连续的部分，子序列
（Subsequence）则是从不改变序列的顺序，而从序列中去掉任意的元素而获得的新序列；
更简略地说，前者（子串）的字符的位置必须连续，后者（子序列 LCS）则不必。比如字
符串 acdfg 同 akdfc 的最长公共子串为 df，而他们的最长公共子序列是 adf。

动态规划的一个计算最长公共子序列的方法如下，以两个序列 X、Y 为例子：
设有二维数组 f[i][j] 表示 X 的 i 位和 Y 的 j 位之前的最长公共子序列的长度，则有：
f[1][1] = same(1,1)
f[i][j] = max{f[i − 1][j − 1] +same(i,j), f[i − 1][j] ,f[i][j − 1]}
其中，same(a,b)当 X 的第 a 位与 Y 的第 b 位完全相同时为“1”，否则为“0”。
此时，f[i][j]中最大的数便是 X 和 Y 的最长公共子序列的长度，依据该数组回溯，便可找出
最长公共子序列。
该算法的空间、时间复杂度均为 O(n2)，经过优化后，空间复杂度可为 O(n)，时间复杂度为
O(nlogn)。
*/
class LongestCommonSubSequence
{
public:
	void DealLongestCommonSubString();
};

