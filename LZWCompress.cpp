#include "stdafx.h"
#include "LZWCompress.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//ģ������
template<typename TypeIterator>
//ѹ������
TypeIterator Compress(string str, TypeIterator result)
{
	//�洢�����
	map<string,int>dictionary;
	int Dictsize = 256;
	//��ʼ��256������λ
	for (int i = 0; i < Dictsize; i++)
	{
		dictionary[string(1, i)] = i;
	}
	char z;
	string S;
	for (string::const_iterator it = str.begin(); it!=str.end(); it++)
	{
		z = *it;
		//�ܹ��ҵ�
		if (dictionary.count(S + z))
		{
			S += z;
		}
		//�ֵ���û���ҵ�
		else
		{
			//���ǰ׺���������
			*result++ = dictionary[S];
			//����ӵ��ֵ���
			dictionary[S + z] = Dictsize++;
			//����׺���ǰ׺
			S = z;
		}
	}
	if (!S.empty())
	{
		*result++ = dictionary[S];
	}
	return result;
}

template<typename TypeIterator>
//ѹ������
string DeCompress(TypeIterator result)
{
	map<int,string>inv_dictionary;
	int Dictsize = 256;
	for (int i = 0; i < Dictsize; i++)
	{
		inv_dictionary[i] = string(1, i);
	}
	char z;
	string S;
	string entry;
	string res;
	Dictsize--;
	for (TypeIterator::iterator it = result.begin(); it != result.end(); it++)
	{
		int k = *it;
		if (inv_dictionary.count(k))
		{
			entry = inv_dictionary[k];
		}
		else if (k == Dictsize)
		{
			entry = S + S[0];
		}
		else
		{
			throw "Bad compression code.";
		}
		res += entry;
		inv_dictionary[Dictsize++] = S + entry[0];
		S = entry;
	}
	return res;
}

//����ѹ���㷨
void LZWCompress::DealLZWCompress()
{
	typedef vector<int> TypeIterator;
	TypeIterator compress_res;
	//string S = "the/rain/in/Spain/falls/mainly/on/the/plain";
	string S = "ABABABABBBABABAACDACDADCABAAABAB";
	//string S = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAB";
	Compress(S, std::back_inserter(compress_res));
	//���ѹ�����
	for (TypeIterator::iterator it = compress_res.begin(); it != compress_res.end(); it++)
	{
		cout << (*it) << endl;
	}
	//��ѹ���
	string decompress = DeCompress(compress_res);
	cout << decompress << endl;
}

