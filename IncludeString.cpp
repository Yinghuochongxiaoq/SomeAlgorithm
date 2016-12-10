#include "stdafx.h"
#include "IncludeString.h"
#include <string>
#include <iostream>
#include "BigInt.h"
using namespace std;  
IncludeString::IncludeString(void)
{
}	  
IncludeString::~IncludeString(void)
{
}

#pragma region ��ѯ����
/*
1.1��O��n*m������ѯ���� 
�ж� string2 �е��ַ��Ƿ��� string1 ��?�� 
String 1: ABCDEFGHLMNOPQRS 
String 2: DCGSRQPOM 
�ж�һ���ַ����Ƿ�����һ���ַ����У���ֱ��Ҳ����򵥵�˼·�ǣ���Եڶ����ַ�
�� string2 ��ÿһ���ַ��� һһ���һ���ַ��� string1 ��ÿ���ַ�������ѯ�Ƚϣ� �����Ƿ�
�ڵ�һ���ַ��� string1 �С� 
���� n ���ַ��� string1 �ĳ��ȣ� m ���ַ��� string2 �ĳ��ȣ� ��ô���㷨�� ��Ҫ O ��n*m��
�β������������������˵���������½����� 16*8 = 128 �β����� 
*/
//��ѯ����
void ComparePoll(string LongString ,string ShortString)
{
	for (int i = 0; i < ShortString.length(); i++)
	{
		int j=0;
		//O(n*m)
		for (j = 0; j < LongString.length(); j++)
		{
			if(LongString[j]==ShortString[i]) break;
		}
		if(j==LongString.length()){
			cout<<"false"<<endl;
			return;
		}
	}
	cout<<"true"<<endl;
	return;
}
#pragma endregion	

#pragma region O(mlogm)+O(nlogn)+O(m+n)�����򷽷�
/*
1.2��O(mlogm)+O(nlogn)+O(m+n)�����򷽷� 
һ����΢��һ��ķ������ȶ��������ַ�������ĸ��������Ȼ��ͬʱ�������ִ�����
��ѯ�������ִ���������Ҫ(�������)O(m log m) + O(n log n)�β�����֮�������ɨ����
Ҫ O(m+n)�β����� 
ͬ����������ִ������ӣ�������Ҫ 16*4 + 8*3 = 88 ���϶������ִ�����ɨ��� 16 + 8 
= 24 �Ĳ�����(�����ִ����ȵ���������ᷢ������㷨��Ч����Խ��Խ��)
����ʹ�ú��ְ취��һ����ÿ������򷽷���
*/
//ȡ��ֵ
int Partition(string &str,int lo,int hi)
{
	while (lo<hi)
	{
		if(str[hi]<str[lo])
		{
			swap(str[hi],str[lo]);
			lo++;
		}
		else
		{
			hi--;
		}
	}
	return lo;
}

//�ݹ��������Partition���̣��������
void QuickSort(string &str,int lo,int hi)
{
	if(lo<hi)
	{
		//ȡ��ֵλ��
		int k=Partition(str,lo,hi);
		//�������
		QuickSort(str,lo,k-1);
		//�ұ�����
		QuickSort(str,k+1,hi);
	}
}

//�Ƚ���������
void CompareStr(string str1,string str2)
{
	int posOne=0;
	int posTwo=0;
	while (posTwo<str2.length() && posOne<str1.length())
	{
		//�Ƚ������������д�С
		while (str1[posOne]<str2[posTwo] && posOne<str1.length()-1)
		{
			posOne++;
		}
		//������ڲ������֤��str2[posTwo]>=str1[posOne] str2���к���
		if(str1[posOne]==str2[posTwo]) posTwo++;
		else break;
	}
	if(posTwo==str2.length()) cout<<"true"<<endl;
	else cout<<"false"<<endl;
}
#pragma endregion

#pragma region O��n+m���ļ������򷽷����ռ临�Ӷ�Ϊ O��n+m��
/*
1.3 ʹ�ü�������O��n+m��
*/
//��������
void CountSort(string str,string &help_str)
{
	//������������
	int help[26]={0};
	//help[index]����˵���index+'A'��Ԫ�ظ���
	for (int i = 0; i < str.length(); i++)
	{
		int index=str[i]-'A';
		help[index]++;
	}
	//���ÿ��Ԫ�ض�Ӧ������λ��
	for (int j = 1; j < 26; j++)
	{
		help[j]+=help[j-1];
	}
	//��ÿ��Ԫ�طŵ����Ӧ������λ��
	for (int k=str.length()-1; k>=0;k--)
	{
		int index=str[k]-'A';
		int pos=help[index]-1;
		help_str[pos]=str[k];
		help[index]--;
	}
}
#pragma endregion

#pragma region O��n+m���� hashtable �ķ��� 
/*
���ǿ��ԶԶ��ִ�������ѯ����˼·���������������ϵ�һЩ�����г��룬��Ϊ������
����Ӧ�ðѶ̵��ȴ洢���������ή����Ŀ��ʱ�临�Ӷȣ��������е�ÿ����ĸ������һ��
Hashtable ��(����ʼ���� m Ϊ���ַ����ĳ��ȣ���ô��������ɱ��� O(m)�� 8 �β���)��
Ȼ����ѯ���ַ������� Hashtable ���ѯ���ַ�����ÿ���ַ������ܷ��ҵ�������Ҳ�����
˵��û��ƥ��ɹ�����ѯ���ַ��������ĵ� 16 �β����������������������һ��ֻ��
8+16=24 �Ρ�

 1��hash[26]����ȫ�����㣬Ȼ��ɨ��̵��ַ�����������Ӧ���� 1�� 
 2������ hash[26]�� 1 �ĸ�������Ϊ m  
 3��ɨ�賤�ַ�����ÿ���ַ� a����ԭ�� hash[a] == 1 �����޸� hash[a] = 0������ m �� 1��
�� hash[a] == 0����������  
 4���� m == 0 or ɨ��������˳�ѭ���� 
*/
//ʹ��hashTable����
void HashTableCompare(string longStr,string shortStr)
{
	string str1=longStr;
	string str2=shortStr;
	if(longStr.length()<shortStr.length())
	{
		str1=shortStr;
		str2=longStr;
	}
	//����һ���������鲢����
	int hash[26]={0};
	//numΪ����������Ԫ�ظ���
	int num=0;
	//ɨ����ַ���
	for (int i = 0; i < str2.length(); i++)
	{
		//���ַ�ת���ɶ�Ӧ���������е�����
		int index=str2[i]-'A';
		//������������и�������ӦԪ��Ϊ0������1����num++
		if(hash[index]==0)
		{
			hash[index]=1;
			num++;
		}
	}
	//ɨ�賤�ַ���
	for (int j = 0; j < str1.length(); j++)
	{
		int index=str1[j]-'A';
		//������������и�������ӦԪ��Ϊ1����num--��Ϊ�㲻������
		if(hash[index]==1)
		{
			hash[index]=0;
			num--;
			if(num==0) break;
		}
	}
	if(num==0)
	{
		cout<<"true"<<endl;
	}
	else
	{
		cout<<"false"<<endl;
	}
}
#pragma endregion

#pragma region O��n���� O��n+m������������ 
/*
����ܻ���ô�룺O(n+m)�����ܵõ�����õĽ���ˣ�����Ҫ��ÿ����ĸ���ٷ���һ��
��������������������һ���������������Ǹպ��Ƕ�ÿ����ĸֻ����һ�Ρ�
ok���������һ�����õķ����� 
    ����������һ��һ����������ĸ����ִ����Ҹ�ÿ����ĸ����һ���������� 2 ��ʼ����
�����ơ����� A ������ 2��B ������ 3��C ������ 5���ȵȡ������ұ�����һ���ִ�����ÿ
����ĸ�����������ˡ������ջ�õ�һ���ܴ���������԰ɣ� 
    Ȼ�󡪡���ѯ�ڶ����ַ�������ÿ����ĸ������������Ľ������������˵���в�ƥ��
����ĸ���������������û����������Ӧ��֪�����ǵ�һ���ִ�ǡ�õ��Ӽ��ˡ� 
˼·�ܽ����£� 
1.������С�� 26 �������ֱ����ַ�'A'��'Z'��Ӧ�� 
2.�������ַ��������ÿ���ַ���Ӧ�����ĳ˻��� 
3.�������ַ������жϳ˻��ܷ񱻶��ַ����е��ַ���Ӧ������������ 
4.��������
	�����㷨��ʱ�临�Ӷ�Ϊ O(m+n)��ʱ�临�Ӷ���õ����Ϊ O(n)����
���̵��ַ����ĵ�һ�������볤�ַ��������ĳ˻����������������������˳����򣬷���
false����n Ϊ���ִ��ĳ��ȣ��ռ临�Ӷ�Ϊ O(1)�����������������Ѿ��Ż�������õĳ�
�ȡ�
*/
void PrimeNumberMoth(string strOne,string strTwo)
{
	//��������
	Bignum primeNumber[26]={2,3,5,7,11,13,19,23,29,31,37,41,43,47,53,59,61,67,71,73,83,89,97,101};
	//��Ҫʹ�ô�����
	Bignum product=1;
	//�������ַ������õ�ÿ���ַ���Ӧ�����ĳ˻�
	for (int i = 0; i < strOne.length(); i++)
	{
		int index=strOne[i]-'A';
		product=product * primeNumber[index];		
		product.display();
	}
	//�������ַ���
	int j=0;
	for (j = 0; j < strTwo.length(); j++)
	{
		int index=strTwo[j]-'A';
		//���������Ϊ0��˵�����������ַ����е��ַ�������ѭ��
		if(product%primeNumber[index]!=Bignum(0)) break;
	}
	if(strTwo.length()==j) cout<<"true"<<endl;
	else cout<<"false"<<endl;
}
#pragma endregion

#pragma region Bit-Map ����
/*
��ν�� Bit-map ������һ�� bit λ�����ĳ��Ԫ�ض�Ӧ�� Value�� �� Key ���Ǹ�
Ԫ�ء����ڲ����� Bit Ϊ��λ���洢���ݣ�����ڴ洢�ռ䷽�棬���Դ���ʡ�� 
    �����������˵�Ļ�û����ʲô�� Bit-map�� ��ô��������һ����������ӣ� ��������Ҫ
�� 0-7 �ڵ� 5 ��Ԫ��(4,7,2,5,3)�������������ЩԪ��û���ظ�������ô���ǾͿ��Բ���
Bit-map �ķ������ﵽ�����Ŀ�ġ�Ҫ��ʾ 8 ���������Ǿ�ֻ��Ҫ 8 �� Bit��1Bytes������
�����ǿ��� 1Byte �Ŀռ䣬����Щ�ռ������ Bit λ����Ϊ 0�������ٴ���ڶ���Ԫ�� 7�����ڰ�λ��Ϊ 1,�������ٴ��������Ԫ�أ�һֱ�������
�����е�Ԫ�أ�����Ӧ��λ��Ϊ 1 ����������ڱ���һ�� Bit ���򣬽���λ��һ��λ�ı�������2��3��4��5��7��������
�ʹﵽ�������Ŀ�ġ�
*/
#define BYTYSIZE 8
void SetBit(char *p,int posi)
{
	for (int i = 0; i < (posi/BYTYSIZE); i++)
	{
		p++;
	}
	//����BitΪ��ֵ1
	*p=*p|(0x01<<(posi%BYTYSIZE));
}

//λͼ����
void BitMapSortDemo()
{
	//�����Ǹ���
	int num[]={3,5,2,10,6,12,8,14,9};
	//BufferLen���ֵ�Ǹ��ݴ����������������ֵȷ����
	//�������е����ֵ��14�����ֻ��Ҫ2��Bytes��16��Bit��
	const int BufferLen=2;
	char *pBuffer=new char[BufferLen];
	//Ҫ�����е�Bitλ����Ϊ0
	memset(pBuffer,0,BufferLen);
	for (int i = 0; i < 9; i++)
	{
		//���Ƚ���Ӧ��Bitλ��1
		SetBit(pBuffer,num[i]);
	}
	//���������
	for (int i = 0; i < BufferLen; i++)
	{
		//������ֽ��е�ÿ��Bitλ
		for (int j = 0; j < BYTYSIZE; j++)
		{
			//�жϸ�λ���Ƿ���1�����������������жϱȽϱ������ȵõ��ĵ�jλ�����루0x01<<j��,���ڴ����е�λ�ʹ������������������ж������Ƿ�ʹ����Ľ��һ��
			if((*pBuffer&(0x01<<j))==(0x01<<j)) cout<<i*BYTYSIZE+j;

		}
		pBuffer++;
	}
}

#pragma endregion

//�ַ�����������
void IncludeString::IncludeStringDeal()
{
	//��ѯ����
	string LongString="ABCDEFGHLMNOPQR";
	string ShortString="DCGSQPOMT";
	//ComparePoll(LongString,ShortString);

	//����+�Ƚ�
	/*QuickSort(LongString,0,LongString.length()-1);
	QuickSort(ShortString,0,ShortString.length()-1);
	CompareStr(LongString,ShortString);*/

	//��������+�Ƚ�
	//string strOne="ABCDAK";
	//string strTwo="A";
	//string long_str=strOne;
	//string short_str=strTwo;
	////���ַ����м�������
	//CountSort(strOne,long_str);
	//CountSort(strTwo,short_str);
	//CompareStr(long_str,short_str);

	//ʹ��hashTable����
	//HashTableCompare(LongString,ShortString);

	//ʹ�ô�����������
	//PrimeNumberMoth(LongString,ShortString);
	BitMapSortDemo();
}
