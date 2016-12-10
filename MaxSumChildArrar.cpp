#include "stdafx.h"
#include "MaxSumChildArrar.h"
#include <iostream>
using namespace std;

//函数声明
//三层for循环遍历
int ForLoop(int *A,int n);
int maxSum(int* A, int n);

//处理计算最大子数组算法
void MaxSumChildArrar::GetMaxSumChildArrar()
{
	//int A[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
	int A[] = { -11, -2, -3, -4,5,4,5,-2,-6,9,6,-4,-3,3,4 };
	int n = sizeof(A)/4;
	//int sum = ForLoop(A, n);
	int sum = maxSum(A,n);
	cout <<"最大字串和："<< sum;
}

//计算最大子数组
/*
int A[]={ 1, -2, 3, 10, -4, 7,  2, -5 };
即：
b  ：  0  1  -1  3  13   9  16  18  13
sum：  0  1   1  3  13  13  16  18  18

其实算法很简单，当前面的几个数，加起来后，b<0 后，
把 b 重新赋值，置为下一个元素，b=a[i]。
当 b>sum，则更新 sum=b;
若 b<sum，则 sum 保持原值，不更新

算法说明：
设 sum[i] 为前 i 个元素中，包含第 i 个元素
且和最大的连续子数组， result 为已找到的子数组中和最大的。 对第 i+1 个元素有两种选择：
做为新子数组的第一个元素、放入前面找到的子数组。
sum[i+1] = max(a[i+1], sum[i] + a[i+1])
result = max(result, sum[i])
*/
int maxSum(int* A, int n)
{
	//起始位置
	int startIndex = 0,startIndexTemp=0;
	//结束位置
	int endIndex = 0 ;
	int sum = A[0];
	int b = 0;
	for (int i = 0; i < n; i++)
	{
		if (b < 0)
		{
			b = A[i];
			//标记可能的新字数组的起始位置
			startIndexTemp = i;
		}
		else
		{
			b += A[i];
		}
		if (sum < b)
		{
			sum = b;
			startIndex = startIndexTemp;
			endIndex = i;
		}
	}
	cout << "对应字串如下：";
	for (int c = startIndex; c <= endIndex; c++)
	{
		cout << A[c] << "\t";
	}
	cout << endl;
	return sum;
}

//三层for循环遍历
int ForLoop(int *A,int n)
{
	//赋值一个最小值
	int maximum = -INFINITY;
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			for (int k = i; k <=j; k++)
			{
				sum += A[k];
			}
			if (sum > maximum) maximum = sum;
			sum = 0;
		}
	}
	return maximum;
}
