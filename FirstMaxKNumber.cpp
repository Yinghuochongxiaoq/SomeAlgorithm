#include "stdafx.h"
#include "FirstMaxKNumber.h"
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

/*
0��   �����ȼ򵥵���⣬Ҫ��һ����������С�� k ���������չ��е�˼ά��ʽ����
�򵥣��ȶ�������д�С��������Ȼ�����ǰ�����С�� k �������ɡ� 

1��   ����ѡȡʲô�����򷽷�����������ܻ��һʱ���뵽������������֪����
��������ƽ������ʱ��Ϊ n*logn��Ȼ���ٱ���������ǰ k ��Ԫ����������ɣ��ܵ�
ʱ�临�Ӷ�Ϊ O��n*logn+k��=O��n*logn�� ��

2��   �����ٽ�һ�����룬��Ŀ��û��Ҫ��Ҫ���ҵ� k ������������ n-k ����������
�ģ���Ȼ��ˣ������ֺαض����е� n ����������������? 
       ��ʱ�������뵽����ѡ��򽻻����򣬼����� n �������Ȱ����ȱ������� k ��
�������СΪ k ������֮�У����� k ����������ѡ��򽻻������ҵ� k �����е�
����� kmax��kmax ��Ϊ k ��Ԫ�ص����������Ԫ�أ� ����ʱ O��k�� ����Ӧ��֪����
�����ѡ��������Ҳ�����Ҫ O ��k�� ��ʱ�䣩 �� ���ټ��������� n-k ������ x �� kmax
�Ƚϣ���� x<kmax���� x ���� kmax�����ٴ������ҳ� k ��Ԫ�ص����������Ԫ��
kmax������л kk791159796 ���������� ����� x>kmax���򲻸������顣������ÿ�� 
���»򲻸�����������õ�ʱ��Ϊ O��k���� O��0�� �������������ܵ�ʱ�临�Ӷ�ƽ
������Ϊ��n*O��k��=O��n*k�� ��

3��   ��Ȼ�����õİ취��ά�� k ��Ԫ�ص����ѣ�ԭ���������� 2 ������һ�£�
��������Ϊ k �����Ѵ洢���ȱ������� k ���������������Ǽ�����С�� k ������
���ѷ�ʱ O��k������ k1<k2<...<kmax��kmax ��Ϊ�󶥶������Ԫ�أ� ��������
�����У�ÿ�α���һ��Ԫ�� x����Ѷ�Ԫ�رȽϣ�x<kmax�����¶ѣ���ʱ logk�� ��
���򲻸��¶ѡ������������ܷ�ʱ O��k+��n-k��*logk��=O��n*logk�� ���˷�������
���ڶ��У����ҵȸ������ʱ�临�ӶȾ�Ϊ logk����Ȼ����������˼· 2 ������ֱ
��������Ҳ�����ҳ�ǰ k ��С��Ԫ�أ���ʱ O��n*k�� �� �� 

4�� �����֮���� 141 ҳ�Ͻⷨ�������������ƿ�������Ļ��ַ�����N �����洢
������ S �У��ٴ����������ѡȡһ���� X�����ѡȡ��ŦԪ����������������ʱ
�� O ��N�� �ĸ��Ӷȣ� �ڵڶ��������� �� �����黮��Ϊ Sa �� Sb �����֣� Sa<=X<=Sb��
���Ҫ���ҵ� k ��Ԫ��С�� Sa ��Ԫ�ظ������򷵻� Sa �н�С�� k ��Ԫ�أ�����
�� Sa �� k ��С��Ԫ��+Sb ��С�� k-|Sa|��Ԫ�ء� ����������һ���� ����������ƿ�
������� partition �Ŀ���ѡ�� SELECT �㷨Ѱ����С�� k ��Ԫ�أ� ����������
������ O��N���ĸ��Ӷȡ�����ֵ��һ����ǣ��������ѡ�� SELECT �㷨��ѡȡ
�����С���λ������λ������Ϊ��ŦԪ���������ѡȡ��ŦԪ��
*/

#pragma region С���Ѵ���
/*
����С����
�ȶ�Ԫ������ԭ�ؽ���С�ѣ�O(n)��Ȼ����ȡ K �Σ�����ÿ����ȡʱ��   
����������Ԫ��ֻ��Ҫ���ƶ��� k �ξ��㹻�ˣ����ƴ�����μ��١����ַ����ĸ��Ӷ�Ϊ O
��n+k^2�� 
*/
#define MAXLEN 12
#define K 2
//��ʼ����
void HeapAdjust(int arraytemp[],int i ,int length)
{
	int child;
	for (int tmep=arraytemp[i] ;2*i+1<length; i=child)
	{
		child=2*i+1;
		if(child<length-1 && arraytemp[child+1]<arraytemp[child])
		{
			child++;
		}
		if(tmep>arraytemp[child])
		{
			arraytemp[i]=arraytemp[child];
		}
		else
		{
			break;
		}
		arraytemp[child]=tmep;
	}
}

void Swap(int* a,int* b)
{
	*a=*a^*b;
	*b=*a^*b;
	*a=*a^*b;
}

int GetMin(int arraytemp[],int length,int k)
{
	int min=arraytemp[0];
	Swap(&arraytemp[0],&arraytemp[length-1]);

	int child,temp;
	int i=0,j=k-1;
	for (temp= arraytemp[0]; j>0 && 2*i+1<length; --j,i=child)
	{
		child=2*i+1;
		if(child<length-1 && arraytemp[child=1]<arraytemp[child])
		{
			child++;
		}
		if(temp>arraytemp[child])
		{
			arraytemp[i]=arraytemp[child];
		}
		else
		{
			break;
		}
		arraytemp[child]=temp;
		return min;
	}
}

void Kmin(int arraytemp[],int length,int k)
{
	for (int i=length/2-1;i>=0;--i)
	{
		//��ʼ���ѣ�ʱ�临�Ӷ�ΪO��n��
		//HeapAdjust(arraytemp,i,length);
		int child;
	for (int tmep=arraytemp[i] ;2*i+1<length; i=child)
	{
		child=2*i+1;
		if(child<length-1 && arraytemp[child+1]<arraytemp[child])
		{
			child++;
		}
		if(tmep>arraytemp[child])
		{
			arraytemp[i]=arraytemp[child];
		}
		else
		{
			break;
		}
		arraytemp[child]=tmep;
	}

	}
	int j=length;
	for (;k>0;--k,--j)
	{
		//k��ѭ����ÿ��ѭ���ĸ��Ӷ����Ϊk�ν��������Ӷ�ΪO��k^2��
		int min=GetMin(arraytemp,j,k);
		cout<<min<<endl;
	}
}
#pragma endregion


//������Сk�����ķ���
void FirstMaxKNumber::FirstMaxKNumberDeal(void)
{
	//С���Ѵ���
	int array[MAXLEN];
	for (int i=MAXLEN;i>0;--i)
	{
		array[MAXLEN-i]=rand()%MAXLEN;
	}
	Kmin(array,MAXLEN,K);
}
