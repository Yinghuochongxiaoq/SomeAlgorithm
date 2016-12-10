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
//�洢��iλ����ǰ��Ȩ�صĺ�
int Sumvec[Nsymbols];

//���캯��
ShannonFanoCompress::ShannonFanoCompress()
{
	left = right = NULL;
	weight = 0;
	ch = '\0';
}

//���캯��
ShannonFanoCompress::ShannonFanoCompress(ShannonFanoCompress* l, ShannonFanoCompress* r, int w, char c)
{
	left = l;
	right = r;
	weight = w;
	ch = c;
}

//��������
ShannonFanoCompress::~ShannonFanoCompress()
{
	delete left;
	delete right;
}

//�ж��Ƿ���Ҷ�ӽڵ�
bool ShannonFanoCompress::IsLeaf()
{
	return !left && !right;
}

//�Ƚ�Ȩ��
bool comp(const ShannonFanoCompress* t1, const ShannonFanoCompress* t2)
{
	return (*t1).weight > (*t2).weight;
}

//���ָ������
typedef vector<ShannonFanoCompress*> TreeVector;
TreeVector TreeArr; 

//�����ѡ�ָ��
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
		//Sumvec[i]-(Sumvec[b]-Sumvec[i])��õ�ǰλ��ǰ������󲿷ֵĲ�ֵ
		curdiff = Sumvec[i] * 2  - Sumvec[b];
		//��СֵΪ�ָ��
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
	//�ݹ���ü����ֵ��
	Optimize_Tree(a,x,*lc);
	Optimize_Tree(x+1,b,*rc);
}

//������
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
		//����Ȩ��
		Sumvec[i] = Sumvec[i - 1] + TreeArr[i - 1]->weight;
	}
	ShannonFanoCompress* root = new ShannonFanoCompress;
	Optimize_Tree(1,TreeArr.size(),*root);
	return root;
}

//���ɱ���
void GenerateCoding(ShannonFanoCompress* root, SF_Code& curcode)
{
	if (root->IsLeaf())
	{
		SF_Dic[root->ch] = curcode;
		return;
	}
	SF_Code lcode = curcode;
	SF_Code rcode = curcode;
	//����������Ϊfalse��0��
	lcode.push_back(false);
	//����������Ϊtrue��0��
	rcode.push_back(true);
	GenerateCoding(root->left, lcode);
	GenerateCoding(root->right, rcode);
}


//������Ũ����
void ShannonFanoCompress::DealShannonFano()
{
	int freq[Nsymbols] = { 0 };
	char *str = "bbbbbbbccccccaaaaaaaaaaaaaaaeeeeedddddd";//15a,7b,6c,6d,5e

	//ͳ���ַ�Ƶ��
	while (*str != '\0')
	{
		freq[*str++]++;
	}

	//����
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
