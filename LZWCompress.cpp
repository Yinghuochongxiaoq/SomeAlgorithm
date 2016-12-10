#include "stdafx.h"
#include "LZWCompress.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//模板类型
template<typename TypeIterator>
//压缩编码
TypeIterator Compress(string str, TypeIterator result)
{
	//存储编码表
	map<string,int>dictionary;
	int Dictsize = 256;
	//初始化256个编码位
	for (int i = 0; i < Dictsize; i++)
	{
		dictionary[string(1, i)] = i;
	}
	char z;
	string S;
	for (string::const_iterator it = str.begin(); it!=str.end(); it++)
	{
		z = *it;
		//能够找到
		if (dictionary.count(S + z))
		{
			S += z;
		}
		//字典中没有找到
		else
		{
			//输出前缀到结果表中
			*result++ = dictionary[S];
			//并添加到字典中
			dictionary[S + z] = Dictsize++;
			//将后缀变成前缀
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
//压缩解码
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

//处理压缩算法
void LZWCompress::DealLZWCompress()
{
	typedef vector<int> TypeIterator;
	TypeIterator compress_res;
	//string S = "the/rain/in/Spain/falls/mainly/on/the/plain";
	string S = "ABABABABBBABABAACDACDADCABAAABAB";
	//string S = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAB";
	Compress(S, std::back_inserter(compress_res));
	//输出压缩结果
	for (TypeIterator::iterator it = compress_res.begin(); it != compress_res.end(); it++)
	{
		cout << (*it) << endl;
	}
	//解压结果
	string decompress = DeCompress(compress_res);
	cout << decompress << endl;
}

