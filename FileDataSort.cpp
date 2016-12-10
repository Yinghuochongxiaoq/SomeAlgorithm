#include "stdafx.h"
#include "FileDataSort.h"
#include <iostream>
#include <time.h>
#include <assert.h>
#include <bitset>
#include <io.h>
using namespace std;

const int max_each_scan = 100000;
const int size = 2 * max_each_scan;

//生成测试数据文件
void ProductTestDataFile()
{
	int num[size] = {0};
	int n;
	//判断文件是否存在，存在则自动返回
	//if (_access("data.txt", 0) == 0) return;
	FILE *fp = fopen("data.txt", "w");
	assert(fp);
	for (n = 1; n < size; n++)
	{
		num[n] = n;
	}
	srand((unsigned)time(NULL));
	int i, j;
	for (n = 0; n < size; n++)
	{
		i = (rand()*RAND_MAX + rand()) % size;
		j = (rand()*RAND_MAX + rand()) % size;
		swap(num[i], num[j]);
	}
	for (n = 0; n < size-1; n++)
	{
		fprintf(fp, "%d\n", num[n]);
	}
	fclose(fp);
}

//位图方案解决 10^7 个数据量的文件的排序问题
//如果有重复的数据，那么只能显示其中一个 其他的将被忽略 
void FileDataSort::DealFileDataSort()
{
	//创建文件
	ProductTestDataFile();
	//计时开始
	clock_t begin = clock();
	//定义位图数据
	bitset<max_each_scan> bit_map;
	//重置位图
	bit_map.reset();
	//重文件中读取数据
	FILE *fp_unsort_file = fopen("data.txt","r");
	//文件判空
	assert(fp_unsort_file);
	int num;

	//文件扫描
	while (fscanf(fp_unsort_file,"%d\n",&num)!=EOF)
	{
		if (num < max_each_scan)
		{
			bit_map.set(num, 1);
		}
	}

	FILE *fp_sort_file = fopen("sort.txt","w");
	assert(fp_sort_file);
	int i;

	//文件回写
	for (i = 0; i < max_each_scan; i++)
	{
		if (bit_map[i] == 1) fprintf(fp_sort_file,"%d\n",i);
	}
	//以上处理完500W，处理剩余500W
	int result = fseek(fp_unsort_file,0,SEEK_SET);
	if (result)
	{
		cout << "fseek 失败" << endl;
	}
	else
	{
		bit_map.reset();
		int maxNumber = 2 * max_each_scan;
		while (fscanf(fp_unsort_file, "%d\n", &num) != EOF)
		{
			if (num >= max_each_scan && num<maxNumber)
			{
				num -= max_each_scan;
				bit_map.set(num, 1);
			}
		}
		for (i = 0; i < max_each_scan; i++)
		{
			if (bit_map[i] == 1) fprintf(fp_sort_file, "%d\n", i+max_each_scan);
		}
	}
	clock_t end = clock();
	cout << "位图方法耗时：" << (end - begin) / CLK_TCK << "s" << endl;
	//关闭文件
	fclose(fp_unsort_file);
	fclose(fp_sort_file);
}
