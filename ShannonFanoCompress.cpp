#include "stdafx.h"
#include "ShannonFanoCompress.h"
#include <queue>
#include <iostream>
#include <vector>
#include <math.h>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

#define NChar 8
#define Nsymbols 1<<NChar
#define INF 1<<31-1
typedef vector<bool> SF_Code;
map<char, SF_Code> SF_Dic;
//存储第i位及以前的权重的和
int Sumvec[Nsymbols];

//构造函数
ShannonFanoCompress::ShannonFanoCompress()
{
	left = right = NULL;
	weight = 0;
	ch = '\0';
}

//构造函数
ShannonFanoCompress::ShannonFanoCompress(ShannonFanoCompress* l, ShannonFanoCompress* r, int w, char c)
{
	left = l;
	right = r;
	weight = w;
	ch = c;
}

//析构函数
ShannonFanoCompress::~ShannonFanoCompress()
{
	delete left;
	delete right;
}

//判定是否是叶子节点
bool ShannonFanoCompress::IsLeaf()
{
	return !left && !right;
}

//比较权重
bool comp(const ShannonFanoCompress* t1, const ShannonFanoCompress* t2)
{
	return (*t1).weight > (*t2).weight;
}

//结点指针容器
typedef vector<ShannonFanoCompress*> TreeVector;
TreeVector TreeArr; 

//获得优选分割点
void ShannonFanoCompress:: Optimize_Tree(int a, int b, ShannonFanoCompress& root)
{
	if (a == b)
	{
		root = *TreeArr[a - 1];
		return;
	}
	else if (b - a == 1)
	{
		root.left = TreeArr[a - 1];
		root.right = TreeArr[b - 1];
		return;
	}
	int x, minn = INF, curdiff;
	for (int i = a; i < b; i++)
	{
		//Sumvec[i]-(Sumvec[b]-Sumvec[i])获得当前位置前部分与后部分的差值
		curdiff = Sumvec[i] * 2  - Sumvec[b];
		//最小值为分割点
		if (abs(curdiff) < minn)
		{
			x = i;
			minn = abs(curdiff);
		}
		else
		{
			break;
		}
	}
	ShannonFanoCompress* lc = new ShannonFanoCompress;
	ShannonFanoCompress* rc = new ShannonFanoCompress;
	root.left = lc;
	root.right = rc;
	//递归调用计算差值‘
	Optimize_Tree(a,x,*lc);
	Optimize_Tree(x+1,b,*rc);
}

//创建树
ShannonFanoCompress* ShannonFanoCompress::BuildTree(int* freqency)
{
	int i;
	for (i = 0; i < Nsymbols; i++)
	{
		if (freqency[i])
		{
			TreeArr.push_back(new ShannonFanoCompress(NULL,NULL,freqency[i],(char)i));
		}
	}
	sort(TreeArr.begin(),TreeArr.end(),comp);
	memset(Sumvec,0,sizeof(Sumvec));
	for (i = 1; i <= TreeArr.size(); i++)
	{
		//计算权重
		Sumvec[i] = Sumvec[i - 1] + TreeArr[i - 1]->weight;
	}
	ShannonFanoCompress* root = new ShannonFanoCompress;
	Optimize_Tree(1,TreeArr.size(),*root);
	return root;
}

//生成编码
void GenerateCoding(ShannonFanoCompress* root, SF_Code& curcode)
{
	if (root->IsLeaf())
	{
		SF_Dic[root->ch] = curcode;
		return;
	}
	SF_Code lcode = curcode;
	SF_Code rcode = curcode;
	//定义左子树为false（0）
	lcode.push_back(false);
	//定义右字数为true（0）
	rcode.push_back(true);
	GenerateCoding(root->left, lcode);
	GenerateCoding(root->right, rcode);
}


//处理香浓编码
void ShannonFanoCompress::DealShannonFano()
{
	int freq[Nsymbols] = { 0 };
	char *str = "bbbbbbbccccccaaaaaaaaaaaaaaaeeeeedddddd";//15a,7b,6c,6d,5e

	//统计字符频数
	while (*str != '\0')
	{
		freq[*str++]++;
	}

	//建树
	ShannonFanoCompress* r = BuildTree(freq);
	SF_Code nullcode;
	GenerateCoding(r, nullcode);

	for (map<char, SF_Code>::iterator it = SF_Dic.begin(); it != SF_Dic.end(); it++)
	{
		cout << (*it).first << '\t';
		copy(it->second.begin(), it->second.end(), ostream_iterator<bool>(cout));
		cout << endl;
	}
}
