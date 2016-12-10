#include "stdafx.h"
#include "AmicableNumbers.h"
#include <iostream>
#include <ctime>
using namespace std;

#define ArrarLength 5000000
int sum[ArrarLength];
//��500W���ڵ��׺���
void AmicableNumbers::AmicableNumbersDeal()
{
	//����׺�������
	//��һ�� for �͵ڶ��� for ѭ���� logn�����ͼ�����*N �α���,������ for ѭ��ɨ�� O��N��
	//�����ܵ�ʱ�临�Ӷ�Ϊ O��n*logn��+O��n��=O��N*logN�� ������ logN Ϊ���ͼ����� ��
	//���ڵ�һ�� for �͵ڶ��� for Ѱ���У����ͼ�����˵����
	//����� 2 �ı����� 2����ôӦ����  n/2 �Σ�3 �ı����� 3 Ӧ���� n/3 �Σ�...
	//��ô��ʵ���� n*��1+1/2+1/3+1/4+...1/(n/2)��=n*�����ͼ�����=n*logn
	clock_t start, finish;
	start = clock();
	int i, j;
	for (i = 0; i <= ArrarLength; i++)
	{
		//1����������������������ȫ����Ϊ1
		sum[i] = 1;
	}
	for (i = 2; i + i <= ArrarLength; i++)
	{
		j = i + i;
		while (j <= ArrarLength)
		{
			//������i�ı�����λ���ϼ�i
			sum[j] += i;
			j += i;
		}
	}
	for (i = 220; i <= ArrarLength; i++)
	{
		//һ�α�������Ϊ֪����С��220��284�����Դ�220��ʼ
		//ȥ�أ���Խ�磬�����׺�
		if (sum[i] > i && sum[i] <= ArrarLength && sum[sum[i]] == i)
		{
			cout << i << "\t" << sum[i] << endl;
		}
	}
	finish = clock();
	cout <<"����ʱ�䣺"<< finish - start << "/" << CLOCKS_PER_SEC << " (s) " << endl;
	return;
}