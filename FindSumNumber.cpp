#include "stdafx.h"
#include "FindSumNumber.h"
#include <string.h>
#include <list>
#include <iostream>
using namespace std;

//构造函数
FindSumNumber::FindSumNumber()
{
}

//析构函数
FindSumNumber::~FindSumNumber()
{
}

//返回类型构造函数
Pair::Pair()
{
	Begin = -1;
	End = -1;
}

//返回类型构造函数
Pair::Pair(int begin, int end)
{
	Begin = begin;
	End = end;
}

list<int>list1;
//假定数组有序查找单个
Pair findSum(int * s, int n, int x)
{
	//sort(s, s + n);
	int *begin = s;
	int *end = s + n - 1;
	while (begin<end)
	{
		if (*begin + *end>x) --end;
		else if (*begin + *end < x) ++begin;
		else return Pair(*begin,*end);
	}
	return Pair(-1,-1);
}

//假定数组有序查找单个
bool find_num(int data[], unsigned int length, int sum, int& first_num, int&second_num)
{
	if (length < 1) return true;
	int begin = 0;
	int end = length - 1;
	while (end>begin)
	{
		long current_sum = data[begin] + data[end];
		if (current_sum == sum)
		{
			first_num = data[begin];
			second_num = data[end];
			return true;
		}
		else if (current_sum > sum) end--;
		else begin++;
	}
	return false;
}

//输入两个整数 n 和 m，从数列 1，2，3.......n 中 随意取几个数, 使其和等于 m, 要求将其中所有的可能组合列出来。
void find_factor(int sum, int n)
{
	//递归出口
	if (n <= 0 || sum <= 0) return;
	//输出找到的结果
	if (sum == n)
	{
		//反转list
		list1.reverse();
		for (list<int>::iterator iter = list1.begin(); iter!=list1.end(); iter++)
		{
			cout << *iter << " + ";
		}
		cout << n << endl;
		list1.reverse();
	}
	list1.push_front(n);
	find_factor(sum-n,n-1);
	list1.pop_front();
	find_factor(sum,n-1);
}

//处理函数
void FindSumNumber::DealFindSum()
{
	int sum, n;
	cout << "请输入你要等于多少的数值 sum:" << endl;
	cin >> sum;
	cout << "请输入你要从 1.....n 数列中取值的 n：" << endl;
	cin >> n;
	cout << "所有可能的序列，如下：" << endl;
	find_factor(sum, n);
}
