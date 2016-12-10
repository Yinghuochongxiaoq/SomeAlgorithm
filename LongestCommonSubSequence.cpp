#include "stdafx.h"
#include "LongestCommonSubSequence.h"
#include <string>
#include <math.h>
#include <ctime>
#include <iostream>
using namespace std;

string GetRandomString(int length);
//处理最长子序列方法
void LongestCommonSubSequence::DealLongestCommonSubString()
{
	clock_t start = clock(), finish;
	//设置字符串的长度 长度有限制，原因是在生成二维数组时需要一个连续的空间，可能出现溢出
	const int subStringLengthOne = 500;
	const int subStringLengthTwo = 500;

	//随机生成字符串
	string x=GetRandomString(subStringLengthOne);
	string y = GetRandomString(subStringLengthTwo);

	//构造二维数组记录子问题x[i]和y[i]的LCS的长度
	int opt[subStringLengthOne + 1][subStringLengthTwo + 2] = { 0 };

	//动态规划计算所有子问题
	for (int i = subStringLengthOne-1; i >=0; i--)
	{
		for (int j = subStringLengthTwo - 1; j >= 0; j--)
		{
			if (x[i] == y[j])
			{
				opt[i][j] = opt[i + 1][j + 1] + 1;
			}
			else
			{
				opt[i][j] = fmax(opt[i+1][j], opt[i][j+1]);
			}
		}
	}
	cout << "第一个序列:" << x << "\n" << "第二个序列:" << y << "\n子序列如下：";

	int i = 0, j = 0;
	while (i<subStringLengthOne && j<subStringLengthTwo)
	{
		if (x[i] == y[j])
		{
			cout << x[i];
			i++;
			j++;
		}
		else if (opt[i + 1][j] >= opt[i][j + 1])
		{
			i++;
		}
		else
		{
			j++;
		}
	}
	finish = clock();
	cout << "\n程序耗时： " << (finish - start) << "/" << CLOCKS_PER_SEC << "(s)" << endl;
}

//生成随机字符串
string GetRandomString(int length)
{
	string  outRandomString;
	char * buffer = { "abcdefghijklmnopqrstuvwxyz" };
	srand(rand());
	for (int i = 0; i < length; i++)
	{
		int index = rand() % 26;
		outRandomString += buffer[index];
	}
	return outRandomString;
}
