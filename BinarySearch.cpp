#include "stdafx.h"
#include "BinarySearch.h"
#include <iostream>
using namespace std;
int SearchValueInfo(int arrary[], int n, int value);
//������ֲ���
void BinarySearch::DealBinarySearch()
{
	int arrary[] = {1,4,5,7};
	int value = 5;
	int index = SearchValueInfo(arrary, sizeof(arrary) / sizeof(int), value);
	if (index > -1)
	{
		cout << arrary[index]<<"λ�ô��ڵڣ�"<<index+1<<"��";
	}
	else
	{
		cout << "û�в�ѯ��" << endl;
	}
}

//���ֲ���arrary��ʾ��Ҫ��ѯ���������飬n��ʾ����ĳ��ȣ�value��ʾ��Ҫ���ҵ�ֵ
int SearchValueInfo(int arrary[], int n, int value)
{
	//��������ָ��
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
