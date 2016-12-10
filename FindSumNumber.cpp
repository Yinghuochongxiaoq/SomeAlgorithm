#include "stdafx.h"
#include "FindSumNumber.h"
#include <string.h>
#include <list>
#include <iostream>
using namespace std;

//���캯��
FindSumNumber::FindSumNumber()
{
}

//��������
FindSumNumber::~FindSumNumber()
{
}

//�������͹��캯��
Pair::Pair()
{
	Begin = -1;
	End = -1;
}

//�������͹��캯��
Pair::Pair(int begin, int end)
{
	Begin = begin;
	End = end;
}

list<int>list1;
//�ٶ�����������ҵ���
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

//�ٶ�����������ҵ���
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

//������������ n �� m�������� 1��2��3.......n �� ����ȡ������, ʹ��͵��� m, Ҫ���������еĿ�������г�����
void find_factor(int sum, int n)
{
	//�ݹ����
	if (n <= 0 || sum <= 0) return;
	//����ҵ��Ľ��
	if (sum == n)
	{
		//��תlist
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

//������
void FindSumNumber::DealFindSum()
{
	int sum, n;
	cout << "��������Ҫ���ڶ��ٵ���ֵ sum:" << endl;
	cin >> sum;
	cout << "��������Ҫ�� 1.....n ������ȡֵ�� n��" << endl;
	cin >> n;
	cout << "���п��ܵ����У����£�" << endl;
	find_factor(sum, n);
}
