#include "stdafx.h"
#include "MaxSumChildArrar.h"
#include <iostream>
using namespace std;

//��������
//����forѭ������
int ForLoop(int *A,int n);
int maxSum(int* A, int n);

//�����������������㷨
void MaxSumChildArrar::GetMaxSumChildArrar()
{
	//int A[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
	int A[] = { -11, -2, -3, -4,5,4,5,-2,-6,9,6,-4,-3,3,4 };
	int n = sizeof(A)/4;
	//int sum = ForLoop(A, n);
	int sum = maxSum(A,n);
	cout <<"����ִ��ͣ�"<< sum;
}

//�������������
/*
int A[]={ 1, -2, 3, 10, -4, 7,  2, -5 };
����
b  ��  0  1  -1  3  13   9  16  18  13
sum��  0  1   1  3  13  13  16  18  18

��ʵ�㷨�ܼ򵥣���ǰ��ļ���������������b<0 ��
�� b ���¸�ֵ����Ϊ��һ��Ԫ�أ�b=a[i]��
�� b>sum������� sum=b;
�� b<sum���� sum ����ԭֵ��������

�㷨˵����
�� sum[i] Ϊǰ i ��Ԫ���У������� i ��Ԫ��
�Һ��������������飬 result Ϊ���ҵ����������к����ġ� �Ե� i+1 ��Ԫ��������ѡ��
��Ϊ��������ĵ�һ��Ԫ�ء�����ǰ���ҵ��������顣
sum[i+1] = max(a[i+1], sum[i] + a[i+1])
result = max(result, sum[i])
*/
int maxSum(int* A, int n)
{
	//��ʼλ��
	int startIndex = 0,startIndexTemp=0;
	//����λ��
	int endIndex = 0 ;
	int sum = A[0];
	int b = 0;
	for (int i = 0; i < n; i++)
	{
		if (b < 0)
		{
			b = A[i];
			//��ǿ��ܵ������������ʼλ��
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
	cout << "��Ӧ�ִ����£�";
	for (int c = startIndex; c <= endIndex; c++)
	{
		cout << A[c] << "\t";
	}
	cout << endl;
	return sum;
}

//����forѭ������
int ForLoop(int *A,int n)
{
	//��ֵһ����Сֵ
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
