#include "stdafx.h"
#include "AmicableNumbers.h"
#include <iostream>
#include <ctime>
using namespace std;

#define ArrarLength 5000000
int sum[ArrarLength];
//求500W以内的亲和数
void AmicableNumbers::AmicableNumbersDeal()
{
	//求解亲和数问题
	//第一个 for 和第二个 for 循环是 logn（调和级数）*N 次遍历,第三个 for 循环扫描 O（N）
	//所以总的时间复杂度为 O（n*logn）+O（n）=O（N*logN） （其中 logN 为调和级数） 。
	//关于第一个 for 和第二个 for 寻找中，调和级数的说明：
	//比如给 2 的倍数加 2，那么应该是  n/2 次，3 的倍数加 3 应该是 n/3 次，...
	//那么其实就是 n*（1+1/2+1/3+1/4+...1/(n/2)）=n*（调和级数）=n*logn
	clock_t start, finish;
	start = clock();
	int i, j;
	for (i = 0; i <= ArrarLength; i++)
	{
		//1是所有数的真因数，所以全部置为1
		sum[i] = 1;
	}
	for (i = 2; i + i <= ArrarLength; i++)
	{
		j = i + i;
		while (j <= ArrarLength)
		{
			//将所有i的倍数的位置上加i
			sum[j] += i;
			j += i;
		}
	}
	for (i = 220; i <= ArrarLength; i++)
	{
		//一次遍历，因为知道最小是220和284，所以从220开始
		//去重，不越界，满足亲和
		if (sum[i] > i && sum[i] <= ArrarLength && sum[sum[i]] == i)
		{
			cout << i << "\t" << sum[i] << endl;
		}
	}
	finish = clock();
	cout <<"运行时间："<< finish - start << "/" << CLOCKS_PER_SEC << " (s) " << endl;
	return;
}