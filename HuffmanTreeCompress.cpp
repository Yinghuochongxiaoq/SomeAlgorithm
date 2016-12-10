#include "stdafx.h"
#include "HuffmanTreeCompress.h"
#include <string>
#include <iostream>
using namespace std;

//函数声明
void Select(HuffmanTree &ht, int n, int *s1, int *s2);
void Creat_HuffmanTree(HuffmanTree &ht, int *w, char *st, int n);
void outputHuffman(HuffmanTree &ht, int m);
void Creat_HuffmanCode(HuffmanTree &ht, HuffmanCode &hc, int n);
void Decoding_HuffmanTree(HuffmanTree &ht, char code[], char result[]);

//处理Huffman编码
void HuffmanTreeCompress::DealHuffmanTree()
{
	HuffmanTree HT;
	HuffmanCode HC;
	//动态数组，存放各字符的权重
	int *w;
	//字符串，存放节点的值
	char *st;
	//n为叶子节点个数
	int i, n;
	int m;

	cout << "输入字符数:" << endl;
	cin >> n;
	//0号单元不用
	w = (int *)malloc((n + 1)*sizeof(int));
	//0号单元不用
	st = (char *)malloc((n + 1)*sizeof(char));

	FILE *fin = fopen("test.txt", "r");
	for (i = 1; i <= n; i++)
	{
		fscanf(fin, "%c%d", &st[i], &w[i]);
	}
	/*构造H树*/
	Creat_HuffmanTree(HT, w, st, n);

	m = 2 * n - 1;
	/*显示H树*/
	outputHuffman(HT, m);
	cout << endl;
	/*根据H树,求每个字符的编码,放在HC中*/
	Creat_HuffmanCode(HT, HC, n);
	/*输出编码*/
	for (i = 1; i <= n; i++)
	{
		cout << HC[i].value << "  " << HC[i].HfmCode << endl;
	}

	//解码
	//char *code = "01101110101010001110110110011100";
	char *code = "000001111001";
	char *result;
	result = (char *)malloc(100 * sizeof(char));
	//result[]存放解码结果
	Decoding_HuffmanTree(HT, code, result);
	for (i = 0; result[i]; i++)
		cout << result[i] << "  ";
}

//选择最小权重的两个树
void Select(HuffmanTree &ht, int n, int *s1, int *s2)
{
	/*ht,为树所在数组的头指针,n为允许查找的最大序号,s1,s2,返回最小的两个序号*/
	int p1 = MAX;
	int p2 = MAX;
	int pn1 = 0;
	int pn2 = 0;
	int i;
	for (i = 1; i <= n; i++)
	{
		if (ht[i].weight<p1 && ht[i].parent == 0)//ht[i].parent=0的作用是去掉已经选过的节点
		{
			pn2 = pn1;
			p2 = p1;
			pn1 = i;
			p1 = ht[i].weight;
		}
		else if (ht[i].weight<p2 && ht[i].parent == 0)
		{
			pn2 = i;
			p2 = ht[i].weight;
		}
	}
	*s1 = pn1;    //赋值返回
	*s2 = pn2;
}

//创建霍夫曼树
void Creat_HuffmanTree(HuffmanTree &ht, int *w, char *st, int n)
{
	//需要的结点数量
	int m = 2 * n - 1;
	//申请空间 0号单元不用
	ht = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));
	HuffmanTree p;
	int i;
	//因为w[]的0号单元没有用
	w = w + 1;
	st = st + 1;
	//1-n号放叶子结点，初始化
	for (p = ht + 1, i = 1; i <= n; i++, p++, w++, st++)
	{
		(*p).weight = *w;
		(*p).value = *st;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i <= m; i++, p++)        //非叶子结点初始化
	{
		(*p).weight = 0;
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	//在select函数中使用,用来存储最小权的结点的序号
	int s1, s2;
	for (i = n + 1; i <= m; ++i)//创建非叶子结点,建哈夫曼树
	{
		//在ht[1]~ht[i-1]的范围内选择两个parent为0且weight最小的结点，其序号分别赋值给s1、s2返回
		Select(ht, i - 1, &s1, &s2);
		ht[s1].parent = i;
		ht[s2].parent = i;
		ht[i].lchild = s1;
		ht[i].rchild = s2;
		ht[i].weight = ht[s1].weight + ht[s2].weight;
	}
}//哈夫曼树建立完毕

//输出所有节点权重
void outputHuffman(HuffmanTree &ht, int m)
{
	for (int i = 1; i <= m; i++)
		cout << ht[i].weight << " ";
}

//从叶子结点到根，逆向求每个叶子结点对应的哈夫曼编码
void Creat_HuffmanCode(HuffmanTree &ht, HuffmanCode &hc, int n)
{
	char *cd;
	int start;
	//c指向当前节点
	int c;
	//p指向当前节点的双亲结点
	int p;
	int i;
	//分配n个编码的头指针
	hc = (HuffmanCode)malloc((n + 1)*sizeof(code));
	//分配求当前编码的工作空间
	cd = (char *)malloc(n * sizeof(char));
	//从右向左逐位存放编码，首先存放编码结束符
	cd[n - 1] = '\0';
	//求n个叶子结点对应的哈夫曼编码
	for (i = 1; i <= n; i++)
	{
		hc[i].value = ht[i].value;
		//初始化编码起始指针
		start = n - 1;
		//从叶子到根结点求编码
		for (c = i, p = ht[i].parent; p != 0; c = p, p = ht[p].parent)
		{
			if (ht[p].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		//为第i个编码分配空间
		hc[i].HfmCode = (char *)malloc(n*sizeof(char));
		strcpy(hc[i].HfmCode, &cd[start]);
	}
	free(cd);
}

//解码
void Decoding_HuffmanTree(HuffmanTree &ht, char code[], char result[])
{
	int i, k = 0;
	int p = 0, root;
	//root是霍夫曼树的根 
	for (root = 1; ht[root].parent != 0; root = ht[root].parent);
	for (i = 0, p = root; code[i] != '\0'; i++)
	{
		if (code[i] == '0')
			p = ht[p].lchild;
		else
			p = ht[p].rchild;
		if (ht[p].lchild == NULL && ht[p].rchild == NULL)
		{
			result[k++] = ht[p].value;
			p = root;
		}
	}
	result[k] = '\0';
}
