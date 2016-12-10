#include "stdafx.h"
#include "BinarySearch.h"
#include <iostream>
using namespace std;
int SearchValueInfo(int arrary[], int n, int value);
//处理二分查找
void BinarySearch::DealBinarySearch()
{
	int arrary[] = {1,4,5,7};
	int value = 5;
	int index = SearchValueInfo(arrary, sizeof(arrary) / sizeof(int), value);
	if (index > -1)
	{
		cout << arrary[index]<<"位置处于第："<<index+1<<"处";
	}
	else
	{
		cout << "没有查询到" << endl;
	}
}

//二分查找arrary表示需要查询的有序数组，n表示数组的长度，value表示需要查找的值
int SearchValueInfo(int arrary[], int n, int value)
{
	//设置左右指针
	int left = 0, right = n - 1;
	while (left <= right)
	{
		int middle = (left + right) / 2;
		if (arrary[middle] < value)
		{
			left = middle+1;
		}
		else if (arrary[middle]>value)
		{
			right = middle - 1;
		}
		else
		{
			return middle;
		}
	}
	return -1;
}
