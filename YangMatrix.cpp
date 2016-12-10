#include "stdafx.h"
#include "YangMatrix.h"
#include <iostream>
using namespace std;

#define ROW 4
#define COL 4

//处理杨氏矩阵
bool YangMatrix::DealYangMatrix(int search)
{
	int arr[ROW][COL] = { { 1, 2, 8, 9 }, { 2, 4, 9, 12 }, { 4, 7, 10, 13 }, { 6, 8, 11, 15 } };
	int i = 0, j = COL - 1; 
	int var = arr[i][j];
	while (true)
	{
		if (var == search)
		{
			return true;
		}
		else if (var < search && i < ROW - 1)
		{
			var = arr[++i][j];
		}
		else if (var > search && j>0)
		{
			var = arr[i][--j];
		}
		else
		{
			return false;
		}
	}

}

//获得输入需要查找的值
void YangMatrix::GetInputSearchValue()
{
	for (int search = 1; search <= 15; search++)
	{
		if (DealYangMatrix(search))
		{
			cout << search<<":存在\n";
		}
		else
		{
			cout << search << "不存在\n";
		}
	}
}